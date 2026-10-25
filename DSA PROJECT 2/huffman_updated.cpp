#include <algorithm>
#include <cctype>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <filesystem>
#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

// Pang-check kung sakto ba na pareho ang original at restored file.
const uint64_t FNV_OFFSET = 14695981039346656037ULL;
const uint64_t FNV_PRIME = 1099511628211ULL;

struct Node
{
    uint64_t frequency;
    int character;
    int smallestCharacter;
    // Parang Node*, pero automatic na ang delete kapag hindi na ginagamit.
    shared_ptr<Node> left;
    shared_ptr<Node> right;

    Node(uint64_t count, int byte)
        : frequency(count), character(byte), smallestCharacter(byte) {}
};
//HELPER FUNCTIONS
// Mas mababang frequency muna. Kapag tabla, mas mababang byte value muna.
// Kailangan pareho ang order para pareho rin ang tree sa decompression.
bool compareNodes(const shared_ptr<Node> &a, const shared_ptr<Node> &b)
{
    if (a->frequency != b->frequency)
        return a->frequency < b->frequency;
    return a->smallestCharacter < b->smallestCharacter;
}

shared_ptr<Node> buildTree(const uint64_t frequency[])
{
    vector<shared_ptr<Node>> nodes;

    for (int i = 0; i < 256; i++)
    {
        if (frequency[i] > 0)
            nodes.push_back(make_shared<Node>(frequency[i], i));
    }

    if (nodes.empty())
        return nullptr;

    // ponytail: hanggang 256 byte values lang; kung mas malaki, priority_queue na.
    while (nodes.size() > 1)
    {
        sort(nodes.begin(), nodes.end(), compareNodes);

        // Pagsamahin ang dalawang may pinakamababang frequency.
        auto left = nodes[0];
        auto right = nodes[1];
        auto parent = make_shared<Node>(left->frequency + right->frequency, -1);
        parent->smallestCharacter = min(left->smallestCharacter, right->smallestCharacter);
        parent->left = left;
        parent->right = right;

        // Palitan ang dalawang nodes ng isang parent node.
        nodes[0] = parent;
        nodes.erase(nodes.begin() + 1);
    }

    return nodes[0];
}

// Bawat kaliwa = 0, bawat kanan = 1. Ang buong path ang code ng character.
void generateCodes(const shared_ptr<Node> &node, const string &path, string codes[])
{
    if (!node)
        return;

    if (node->character >= 0)
    {
        // Kapag iisang character lang, kailangan pa rin ng isang bit.
        codes[node->character] = path.empty() ? "0" : path;
        return;
    }

    generateCodes(node->left, path + "0", codes);
    generateCodes(node->right, path + "1", codes);
}

// Nag-iipon ng 8 bits bago isulat bilang isang byte.
class BitWriter
{
private:
    ostream &output;
    uint8_t buffer = 0;
    int bitsUsed = 0;

public:
    explicit BitWriter(ostream &stream) : output(stream) {}

    void writeBit(int bit)
    {
        // Usog pakaliwa, tapos idagdag ang bagong bit sa kanan.
        buffer = static_cast<uint8_t>((buffer << 1) | bit);
        ++bitsUsed;
        if (bitsUsed == 8)
        {
            output.put(static_cast<char>(buffer));
            buffer = 0;
            bitsUsed = 0;
        }
    }

    void finish()
    {
        if (bitsUsed == 0)
            return;
        // Kung kulang sa 8 bits, lagyan ng zero padding sa kanan.
        buffer = static_cast<uint8_t>(buffer << (8 - bitsUsed));
        output.put(static_cast<char>(buffer));
        bitsUsed = 0;
        buffer = 0;
    }
};

// Kabaligtaran ng BitWriter: isang byte, tapos basahin bawat bit.
class BitReader
{
private:
    istream &input;
    uint8_t buffer = 0;
    int bitsLeft = 0;

public:
    explicit BitReader(istream &stream) : input(stream) {}

    int readBit()
    {
        if (bitsLeft == 0)
        {
            int next = input.get();
            if (next == EOF)
                return -1;
            buffer = static_cast<uint8_t>(next);
            bitsLeft = 8;
        }

        // Kunin ang susunod na bit mula kaliwa papuntang kanan.
        int bit = (buffer >> (bitsLeft - 1)) & 1;
        --bitsLeft;
        return bit;
    }
};

// Fixed na bilang ng bytes ang gamit para mabasa ulit ang header nang tama.
// Pinakamababang byte muna ang isinusulat (little-endian).
void writeNumber(ostream &output, uint64_t value, int byteCount)
{
    for (int i = 0; i < byteCount; i++)
    {
        output.put(static_cast<char>(value & 0xFF));
        value >>= 8;
    }
}

uint64_t readNumber(istream &input, int byteCount)
{
    uint64_t value = 0;
    for (int i = 0; i < byteCount; i++)
    {
        int byte = input.get();
        if (byte == EOF)
            throw runtime_error("The compressed file has an incomplete header.");
        value |= static_cast<uint64_t>(static_cast<uint8_t>(byte)) << (i * 8);
    }
    return value;
}

void updateChecksum(uint64_t &checksum, uint8_t byte)
{
    checksum ^= byte;
    checksum *= FNV_PRIME;
}

uint64_t fileSize(const string &filename)
{
    ifstream file(filename, ios::binary | ios::ate);
    if (!file)
        throw runtime_error("Cannot check file size: " + filename);
    streampos position = file.tellg();
    if (position < 0)
        throw runtime_error("Cannot check file size: " + filename);
    return static_cast<uint64_t>(position);
}

// Kahit magkaiba ang spelling ng path, bawal patungan ang mismong input file.
void ensureDifferentFiles(const string &inputName, const string &outputName)
{
    namespace fs = std::filesystem;
    error_code error1, error2, equivalenceError;
    fs::path inputPath = fs::absolute(inputName, error1).lexically_normal();
    fs::path outputPath = fs::absolute(outputName, error2).lexically_normal();

    if ((!error1 && !error2 && inputPath == outputPath) ||
        fs::equivalent(inputName, outputName, equivalenceError))
        throw runtime_error("Input and output filenames must be different.");
}

//END OF HELPER FUNCTION

void compressFile(const string &inputName, const string &outputName)
{
    ensureDifferentFiles(inputName, outputName);
    ifstream input(inputName, ios::binary);
    if (!input)
        throw runtime_error("Cannot open the input file.");

    // Bilangin muna kung ilang beses lumabas ang bawat byte (0 hanggang 255).
    uint64_t frequency[256] = {};
    uint64_t originalSize = 0;
    uint64_t checksum = FNV_OFFSET;
    char c;

    while (input.get(c))
    {
        uint8_t byte = static_cast<uint8_t>(c);
        if (originalSize == numeric_limits<uint64_t>::max())
            throw runtime_error("The input file is too large.");
        ++frequency[byte];
        ++originalSize;
        updateChecksum(checksum, byte);
    }
    if (!input.eof())
        throw runtime_error("Error reading the input file.");

    uint16_t distinct = 0;
    for (uint64_t count : frequency)
        if (count > 0)
            ++distinct;

    auto root = buildTree(frequency);
    string codes[256];
    generateCodes(root, "", codes);

    // Balik sa simula ng file; sa second pass natin isusulat ang compressed bits.
    input.clear();
    input.seekg(0);
    if (!input)
        throw runtime_error("Cannot reread the input file.");

    ofstream output(outputName, ios::binary | ios::trunc);
    if (!output)
        throw runtime_error("Cannot create the compressed file.");

    try
    {
        // Header: file type, original size, checksum, at character frequencies.
        // Dito muling bubuuin ang tree kapag magde-decompress.
        output.write("HUF1", 4);
        writeNumber(output, originalSize, 8);
        writeNumber(output, checksum, 8);
        writeNumber(output, distinct, 2);

        for (int i = 0; i < 256; i++)
        {
            if (frequency[i] != 0)
            {
                output.put(static_cast<char>(i));
                writeNumber(output, frequency[i], 8);
            }
        }

        // Hindi text na '0' at '1' ang isusulat: 8 bits ang kasya sa isang byte.
        BitWriter bits(output);
        uint64_t secondSize = 0;
        uint64_t secondChecksum = FNV_OFFSET;

        while (input.get(c))
        {
            uint8_t byte = static_cast<uint8_t>(c);
            if (secondSize == numeric_limits<uint64_t>::max())
                throw runtime_error("The input file is too large.");
            ++secondSize;
            updateChecksum(secondChecksum, byte);
            for (char bit : codes[byte])
                bits.writeBit(bit == '1');
        }

        if (!input.eof())
            throw runtime_error("Error rereading the input file.");
        // Baka nagbago ang input habang binabasa ulit; huwag mag-save ng sirang file.
        if (secondSize != originalSize || secondChecksum != checksum)
            throw runtime_error("The input file changed during compression.");

        bits.finish();
        output.flush();
        if (!output)
            throw runtime_error("Could not finish writing the compressed file.");
        output.close();
        if (!output)
            throw runtime_error("Could not close the compressed file.");
    }
    catch (...)
    {
        // Kapag pumalya, burahin ang incomplete output bago ibalik ang error.
        output.close();
        remove(outputName.c_str());
        throw;
    }

    uint64_t compressedSize = fileSize(outputName);
    cout << "\nCompression completed.\n"
         << "Original size:   " << originalSize << " bytes\n"
         << "Compressed size: " << compressedSize << " bytes\n";
    if (originalSize > 0)
    {
        double ratio = static_cast<double>(compressedSize) / originalSize;
        double saved = (1.0 - ratio) * 100.0;
        cout << fixed << setprecision(2)
             << "Space saved:     " << saved << "%\n"
             << "Size ratio:      " << ratio * 100.0 << "% of the original\n";
        if (saved < 0)
            cout << "Note: The compressed file is larger because of its header.\n";
    }
    else
    {
        cout << "Space saved:     N/A (empty input file)\n";
    }
    cout << "Saved as: " << outputName << "\n";
}

void decompressFile(const string &inputName, const string &outputName)
{
    ensureDifferentFiles(inputName, outputName);
    ifstream input(inputName, ios::binary);
    if (!input)
        throw runtime_error("Cannot open the compressed file.");

    char magic[4];
    if (!input.read(magic, 4) || string(magic, 4) != "HUF1")
        throw runtime_error("This is not a supported Huffman file.");

    uint64_t originalSize = readNumber(input, 8);
    uint64_t expectedChecksum = readNumber(input, 8);
    uint64_t distinct = readNumber(input, 2);
    if (distinct > 256)
        throw runtime_error("Invalid number of characters in the header.");

    // I-check muna ang header bago gumawa ng output file.
    uint64_t frequency[256] = {};
    uint64_t sum = 0;
    for (uint64_t i = 0; i < distinct; i++)
    {
        int byte = input.get();
        if (byte == EOF)
            throw runtime_error("Incomplete character list in the header.");
        uint64_t count = readNumber(input, 8);
        if (count == 0 || frequency[byte] != 0 || count > originalSize - sum)
            throw runtime_error("Invalid character frequencies in the header.");
        frequency[byte] = count;
        sum += count;
    }

    if (sum != originalSize)
        throw runtime_error("The compressed file has an invalid header.");

    auto root = buildTree(frequency);
    ofstream output(outputName, ios::binary | ios::trunc);
    if (!output)
        throw runtime_error("Cannot create the decompressed file.");

    try
    {
        BitReader bits(input);
        uint64_t checksum = FNV_OFFSET;

        for (uint64_t i = 0; i < originalSize; i++)
        {
            auto current = root;
            if (root->character >= 0)
            {
                if (bits.readBit() != 0)
                    throw runtime_error("Damaged compressed data.");
            }
            else
            {
                while (current->character == -1)
                {
                    int bit = bits.readBit();
                    if (bit < 0)
                        throw runtime_error("Compressed data ended unexpectedly.");
                    // Sundan ang bit hanggang makarating sa character (leaf).
                    current = bit == 0 ? current->left : current->right;
                    if (!current)
                        throw runtime_error("Damaged Huffman tree data.");
                }
            }

            uint8_t byte = static_cast<uint8_t>(current->character);
            output.put(static_cast<char>(byte));
            updateChecksum(checksum, byte);
        }

        output.flush();
        if (!output)
            throw runtime_error("Could not write the decompressed file.");
        // Dapat tugma ang checksum para siguradong tama ang restored contents.
        if (checksum != expectedChecksum)
            throw runtime_error("Integrity check failed: the file may be damaged.");

        output.close();
        if (!output)
            throw runtime_error("Could not close the decompressed file.");
    }
    catch (...)
    {
        // Huwag mag-iwan ng output na kulang o may maling contents.
        output.close();
        remove(outputName.c_str());
        throw;
    }

    cout << "\nDecompression completed.\n"
         << "Restored size: " << fileSize(outputName) << " bytes\n"
         << "Integrity check: PASSED\n"
         << "Saved as: " << outputName << "\n";
}

// Puwedeng may extension na ang filename; huwag nang doblehin.
string addExtensionIfMissing(const string &filename, const string &extension)
{
    if (filename.size() >= extension.size())
    {
        string ending = filename.substr(filename.size() - extension.size());
        for (char &c : ending)
            c = static_cast<char>(tolower(static_cast<unsigned char>(c)));
        if (ending == extension)
            return filename;
    }
    return filename + extension;
}

int main()
{
    while (true)
    {
        cout << "\n===== HUFFMAN FILE COMPRESSION =====\n"
                "1. Compress a text file\n"
                "2. Decompress a .huf file\n"
                "3. Exit\n"
                "Choose an option: ";

        string option;
        if (!getline(cin, option) || option == "3")
            break;
        if (option != "1" && option != "2")
        {
            cout << "Invalid option. Please choose 1, 2, or 3.\n";
            continue;
        }

        bool compressing = option == "1";
        string inputName, outputName;
        cout << (compressing ? "Input text filename (without .txt): "
                             : "Input compressed filename (without .huf): ");
        if (!getline(cin, inputName))
            break;
        cout << (compressing ? "Output compressed filename (without .huf): "
                             : "Output text filename (without .txt): ");
        if (!getline(cin, outputName))
            break;

        if (inputName.empty() || outputName.empty())
        {
            cout << "Filenames cannot be empty.\n";
            continue;
        }

        try
        {
            inputName = addExtensionIfMissing(inputName, compressing ? ".txt" : ".huf");
            outputName = addExtensionIfMissing(outputName, compressing ? ".huf" : ".txt");
            if (compressing)
                compressFile(inputName, outputName);
            else
                decompressFile(inputName, outputName);
        }
        catch (const exception &error)
        {
            cout << "Error: " << error.what() << "\n";
        }
    }

    cout << "Goodbye!\n";
    return 0;
}
