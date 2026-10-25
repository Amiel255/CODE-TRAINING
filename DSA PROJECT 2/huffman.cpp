#include <array>
#include <cstdint>
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <memory>
#include <queue>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;

const uint64_t FNV_OFFSET = 14695981039346656037ULL;
const uint64_t FNV_PRIME = 1099511628211ULL;

struct Node {
    uint64_t frequency;
    int character;
    int smallestCharacter;
    shared_ptr<Node> left;
    shared_ptr<Node> right;

    Node(uint64_t f, int c)
        : frequency(f), character(c), smallestCharacter(c) {}

    Node(shared_ptr<Node> a, shared_ptr<Node> b)
        : frequency(a->frequency + b->frequency), character(-1),
          smallestCharacter(a->smallestCharacter < b->smallestCharacter
                                ? a->smallestCharacter : b->smallestCharacter),
          left(a), right(b) {}
};

struct CompareNodes {
    bool operator()(const shared_ptr<Node>& a, const shared_ptr<Node>& b) const {
        if (a->frequency != b->frequency)
            return a->frequency > b->frequency;
        return a->smallestCharacter > b->smallestCharacter;
    }
};

shared_ptr<Node> buildTree(const array<uint64_t, 256>& frequency) {
    priority_queue<shared_ptr<Node>, vector<shared_ptr<Node>>, CompareNodes> nodes;

    for (int i = 0; i < 256; ++i) {
        if (frequency[i] > 0)
            nodes.push(make_shared<Node>(frequency[i], i));
    }

    if (nodes.empty())
        return nullptr;

    while (nodes.size() > 1) {
        auto left = nodes.top();
        nodes.pop();
        auto right = nodes.top();
        nodes.pop();
        nodes.push(make_shared<Node>(left, right));
    }

    return nodes.top();
}

void generateCodes(const shared_ptr<Node>& node, const string& path,
                   array<string, 256>& codes) {
    if (!node)
        return;

    if (node->character >= 0) {
        codes[node->character] = path.empty() ? "0" : path;
        return;
    }

    generateCodes(node->left, path + "0", codes);
    generateCodes(node->right, path + "1", codes);
}

class BitWriter {
    ostream& output;
    uint8_t buffer = 0;
    int bitsUsed = 0;

public:
    explicit BitWriter(ostream& stream) : output(stream) {}

    void writeBit(int bit) {
        buffer = static_cast<uint8_t>((buffer << 1) | bit);
        ++bitsUsed;
        if (bitsUsed == 8) {
            output.put(static_cast<char>(buffer));
            buffer = 0;
            bitsUsed = 0;
        }
    }

    void finish() {
        if (bitsUsed > 0) {
            buffer = static_cast<uint8_t>(buffer << (8 - bitsUsed));
            output.put(static_cast<char>(buffer));
            bitsUsed = 0;
            buffer = 0;
        }
    }
};

class BitReader {
    istream& input;
    uint8_t buffer = 0;
    int bitsLeft = 0;

public:
    explicit BitReader(istream& stream) : input(stream) {}

    int readBit() {
        if (bitsLeft == 0) {
            int next = input.get();
            if (next == EOF)
                return -1;
            buffer = static_cast<uint8_t>(next);
            bitsLeft = 8;
        }

        int bit = (buffer >> (bitsLeft - 1)) & 1;
        --bitsLeft;
        return bit;
    }
};

void writeNumber(ostream& output, uint64_t value, int byteCount) {
    for (int i = 0; i < byteCount; ++i) {
        output.put(static_cast<char>(value & 0xFF));
        value >>= 8;
    }
}

uint64_t readNumber(istream& input, int byteCount) {
    uint64_t value = 0;
    for (int i = 0; i < byteCount; ++i) {
        int byte = input.get();
        if (byte == EOF)
            throw runtime_error("The compressed file has an incomplete header.");
        value |= static_cast<uint64_t>(static_cast<uint8_t>(byte)) << (i * 8);
    }
    return value;
}

void updateChecksum(uint64_t& checksum, uint8_t byte) {
    checksum ^= byte;
    checksum *= FNV_PRIME;
}

uint64_t fileSize(const string& filename) {
    ifstream file(filename, ios::binary | ios::ate);
    if (!file)
        throw runtime_error("Cannot check file size: " + filename);
    streampos position = file.tellg();
    if (position < 0)
        throw runtime_error("Cannot check file size: " + filename);
    return static_cast<uint64_t>(position);
}

void ensureDifferentFiles(const string& inputName, const string& outputName) {
    if (inputName == outputName)
        throw runtime_error("Input and output filenames must be different.");
}

void compressFile(const string& inputName, const string& outputName) {
    ensureDifferentFiles(inputName, outputName);
    ifstream input(inputName, ios::binary);
    if (!input)
        throw runtime_error("Cannot open the input file.");

    array<uint64_t, 256> frequency{};
    uint64_t originalSize = 0;
    uint64_t checksum = FNV_OFFSET;
    char c;

    while (input.get(c)) {
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
        if (count != 0)
            ++distinct;

    auto root = buildTree(frequency);
    array<string, 256> codes{};
    generateCodes(root, "", codes);

    input.clear();
    input.seekg(0);
    if (!input)
        throw runtime_error("Cannot reread the input file.");

    ofstream output(outputName, ios::binary | ios::trunc);
    if (!output)
        throw runtime_error("Cannot create the compressed file.");

    try {
        output.write("HUF1", 4);
        writeNumber(output, originalSize, 8);
        writeNumber(output, checksum, 8);
        writeNumber(output, distinct, 2);

        for (int i = 0; i < 256; ++i) {
            if (frequency[i] != 0) {
                output.put(static_cast<char>(i));
                writeNumber(output, frequency[i], 8);
            }
        }

        BitWriter bits(output);
        uint64_t secondSize = 0;
        uint64_t secondChecksum = FNV_OFFSET;

        while (input.get(c)) {
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
        if (secondSize != originalSize || secondChecksum != checksum)
            throw runtime_error("The input file changed during compression.");

        bits.finish();
        output.flush();
        if (!output)
            throw runtime_error("Could not finish writing the compressed file.");
        output.close();
        if (!output)
            throw runtime_error("Could not close the compressed file.");
    } catch (...) {
        output.close();
        remove(outputName.c_str());
        throw;
    }

    uint64_t compressedSize = fileSize(outputName);
    cout << "\nCompression completed.\n";
    cout << "Original size:   " << originalSize << " bytes\n";
    cout << "Compressed size: " << compressedSize << " bytes\n";
    if (originalSize > 0) {
        double saved = (1.0 - static_cast<double>(compressedSize) /
                                     static_cast<double>(originalSize)) * 100.0;
        cout << fixed << setprecision(2);
        cout << "Space saved:     " << saved << "%\n";
        cout << "Size ratio:      " << static_cast<double>(compressedSize) /
                                         static_cast<double>(originalSize) * 100.0
             << "% of the original\n";
        if (saved < 0)
            cout << "Note: The compressed file is larger because of its header.\n";
    } else {
        cout << "Space saved:     N/A (empty input file)\n";
    }
    cout << "Saved as: " << outputName << "\n";
}

void decompressFile(const string& inputName, const string& outputName) {
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

    array<uint64_t, 256> frequency{};
    uint64_t sum = 0;
    for (uint64_t i = 0; i < distinct; ++i) {
        int byte = input.get();
        if (byte == EOF)
            throw runtime_error("Incomplete character list in the header.");
        uint64_t count = readNumber(input, 8);
        if (count == 0 || frequency[byte] != 0 || count > originalSize - sum)
            throw runtime_error("Invalid character frequencies in the header.");
        frequency[byte] = count;
        sum += count;
    }

    if (sum != originalSize || (originalSize == 0 && distinct != 0) ||
        (originalSize > 0 && distinct == 0))
        throw runtime_error("The compressed file has an invalid header.");

    auto root = buildTree(frequency);
    ofstream output(outputName, ios::binary | ios::trunc);
    if (!output)
        throw runtime_error("Cannot create the decompressed file.");

    try {
        BitReader bits(input);
        uint64_t checksum = FNV_OFFSET;

        for (uint64_t i = 0; i < originalSize; ++i) {
            auto current = root;
            if (root->character >= 0) {
                if (bits.readBit() != 0)
                    throw runtime_error("Damaged compressed data.");
            } else {
                while (current->character == -1) {
                    int bit = bits.readBit();
                    if (bit < 0)
                        throw runtime_error("Compressed data ended unexpectedly.");
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
        if (checksum != expectedChecksum)
            throw runtime_error("Integrity check failed: the file may be damaged.");

        output.close();
        if (!output)
            throw runtime_error("Could not close the decompressed file.");
    } catch (...) {
        output.close();
        remove(outputName.c_str());
        throw;
    }

    cout << "\nDecompression completed.\n";
    cout << "Restored size: " << fileSize(outputName) << " bytes\n";
    cout << "Integrity check: PASSED\n";
    cout << "Saved as: " << outputName << "\n";
}

int main() {
    while (true) {
        cout << "\n===== HUFFMAN FILE COMPRESSION =====\n";
        cout << "1. Compress a text file\n";
        cout << "2. Decompress a .huf file\n";
        cout << "3. Exit\n";
        cout << "Choose an option: ";

        string option;
        if (!getline(cin, option))
            break;
        if (option == "3")
            break;
        if (option != "1" && option != "2") {
            cout << "Invalid option. Please choose 1, 2, or 3.\n";
            continue;
        }

        string inputName, outputName;
        cout << "Input filename: ";
        if (!getline(cin, inputName))
            break;
        cout << "Output filename: ";
        if (!getline(cin, outputName))
            break;

        if (inputName.empty() || outputName.empty()) {
            cout << "Filenames cannot be empty.\n";
            continue;
        }

        try {
            if (option == "1")
                compressFile(inputName, outputName);
            else
                decompressFile(inputName, outputName);
        } catch (const exception& error) {
            cout << "Error: " << error.what() << "\n";
        }
    }

    cout << "Goodbye!\n";
    return 0;
}
