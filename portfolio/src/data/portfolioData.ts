export interface Project {
  id: string;
  title: string;
  tagline: string;
  category: "Systems & C++" | "Assembly" | "Algorithms & DSA";
  period: string;
  description: string;
  highlights: string[];
  techStack: string[];
  codeSnippet?: {
    language: string;
    filename: string;
    code: string;
  };
  metrics?: { label: string; value: string }[];
  githubUrl?: string;
  slug: string;
}

export const PERSONAL_INFO = {
  name: "Amiel Keith Padilla",
  shortName: "Amiel",
  handle: "Amiel255",
  title: "Software Developer & BSIT Student",
  location: "Philippines",
  status: "Open to Internships & Software Engineering Roles",
  email: "amielkeithpadilla5@gmail.com",
  github: "https://github.com/Amiel255",
  facebook: "https://www.facebook.com/amielkeith.padilla",
  bio: "Passionate BSIT student and software developer specializing in systems programming, data structures, and computer architecture. Driven by low-level curiosity—from bitwise file compression and memory management in C++ to hardware interrupt routines in x86 Assembly, paired with modern web engineering.",
  about: [
    "I am an Information Technology student with a deep interest in software engineering, systems programming, and algorithmic problem-solving.",
    "My hands-on experience spans low-level x86 Assembly programming (BIOS/DOS interrupts, video memory), building high-performance C++ applications with custom memory management (Huffman compression, binary expression trees), and creating full-stack web applications.",
    "I focus on writing clean, readable, and efficient code with strong foundational principles in computer science and software architecture.",
  ],
};

export const PROJECTS: Project[] = [
  {
    id: "huffman-engine",
    title: "Huffman Lossless Compression Engine",
    tagline: "High-performance file compressor with canonical trees & bitwise I/O",
    category: "Systems & C++",
    period: "2026",
    description:
      "A complete C++17 implementation of the Huffman lossless compression algorithm. Features deterministic binary tree reconstruction, custom bit-level stream serialization, and FNV-1a 64-bit checksum verification ensuring 100% bit-exact restoration.",
    highlights: [
      "Custom bitstream buffer packing arbitrary-length variable bit codes into physical byte streams",
      "Deterministic min-priority queue tree construction with tie-breaking rules for identical decompression parity",
      "FNV-1a 64-bit checksum integrity verification computed during stream compression & decompression",
      "Modern C++ architecture using std::shared_ptr for leak-free, automated memory lifecycle management",
    ],
    techStack: ["C++17", "Data Compression", "Bitwise Stream I/O", "FNV-1a Hash", "Binary Trees"],
    metrics: [
      { label: "Integrity", value: "64-bit FNV-1a" },
      { label: "Memory Safety", value: "std::shared_ptr" },
      { label: "Tree Complexity", value: "O(n log k)" },
    ],
    codeSnippet: {
      language: "cpp",
      filename: "huffman_updated.cpp",
      code: `struct Node {
    uint64_t frequency;
    int character;
    int smallestCharacter;
    shared_ptr<Node> left;
    shared_ptr<Node> right;
};

// Deterministic priority ordering for matching tree parity
bool compareNodes(const shared_ptr<Node>& a, const shared_ptr<Node>& b) {
    if (a->frequency != b->frequency)
        return a->frequency < b->frequency;
    return a->smallestCharacter < b->smallestCharacter;
}`,
    },
    githubUrl: "https://github.com/Amiel255/CODE-TRAINING/tree/main/DSA%20PROJECT%202",
    slug: "huffman-engine",
  },
  {
    id: "bank-mgmt-system",
    title: "Bank & ATM Account Management System",
    tagline: "Doubly linked list banking engine with CSV database synchronization",
    category: "Algorithms & DSA",
    period: "2026",
    description:
      "A console-driven banking and ATM transaction engine built on an optimized doubly linked list architecture. Manages persistent client accounts, multi-tier transactions (withdrawals, deposits, transfers), and encrypted PIN security.",
    highlights: [
      "Bidirectional Doubly Linked List enabling O(1) node traversals, dynamic insertions, and in-place balance mutations",
      "Persistent two-way CSV file database synchronization preserving account records across sessions",
      "Encrypted PIN validation routine with masked input security and robust transaction confirmation workflows",
      "Fail-safe input sanitization preventing memory overflows and invalid state execution",
    ],
    techStack: ["C++", "Doubly Linked List", "File I/O", "Data Persistence", "Security Masking"],
    metrics: [
      { label: "Data Structure", value: "Doubly Linked List" },
      { label: "Persistence", value: "CSV Engine" },
      { label: "Access Security", value: "Masked PIN Auth" },
    ],
    codeSnippet: {
      language: "cpp",
      filename: "Padilla_Rhem_PROJECT1DSA.cpp",
      code: `struct Account {
    string accountNumber;
    string accountName;
    string birthday;
    string contactNumber;
    long long balance;
    string pin; // encrypted pin
};

struct node {
    Account data;
    node *next;
    node *prev;
    node(Account x) : data(x), next(NULL), prev(NULL) {}
};`,
    },
    githubUrl: "https://github.com/Amiel255/CODE-TRAINING/tree/main/DSA%20PROJECT1",
    slug: "bank-mgmt-system",
  },
  {
    id: "x86-assembly-suite",
    title: "x86 Bare-Metal Assembly Suite",
    tagline: "Low-level 8086 programs: traffic light state machine & VGA graphics",
    category: "Assembly",
    period: "2026",
    description:
      "A collection of 16-bit x86 Assembly programs developed for TASM/JWasm environments. Explores low-level hardware control, DOS/BIOS interrupts, and direct memory mapped I/O.",
    highlights: [
      "Real-time traffic controller state machine with hardware clock timing loops and interrupt routines",
      "VGA Mode 13h (320x200 256 colors) graphics rasterizer writing directly to video segment 0A000h",
      "Low-level register manipulation (AX, BX, CX, DX, SI, DI) with custom BIOS int 10h and DOS int 21h calls",
      "Efficient assembly routines for signed/unsigned arithmetic and console string parsing",
    ],
    techStack: ["x86 Assembly", "8086 Architecture", "TASM / JWasm", "BIOS / DOS Interrupts", "VGA Graphics"],
    metrics: [
      { label: "Target Architecture", value: "16-bit x86 / 8086" },
      { label: "Video Mode", value: "Mode 13h (320x200)" },
      { label: "Direct Memory", value: "0A000h Segment" },
    ],
    codeSnippet: {
      language: "assembly",
      filename: "GFX.asm",
      code: `; Set 320x200 256-color graphics mode
mov ax, 0013h
int 10h

; Point ES to VGA video memory buffer
mov ax, 0A000h
mov es, ax
xor di, di

; Write color byte directly to pixel coordinate
mov al, 04h       ; Red color
mov es:[di], al`,
    },
    githubUrl: "https://github.com/Amiel255/CODE-TRAINING/tree/main/ASSEMBLY%208086",
    slug: "x86-assembly-suite",
  },
  {
    id: "expression-tree-parser",
    title: "Binary Expression Tree & Math Parser",
    tagline: "Recursive infix-to-postfix syntax tree builder & evaluator",
    category: "Algorithms & DSA",
    period: "2026",
    description:
      "A comprehensive parser and binary expression tree evaluator. Translates mathematical expressions into hierarchical node graphs, performing recursive traversals (Inorder, Preorder, Postorder) and arithmetic evaluation.",
    highlights: [
      "Operator precedence parsing converting mathematical infix notation to binary syntax trees",
      "Recursive traversal implementations showcasing prefix, infix, and postfix evaluation",
      "Dynamic node allocation with robust pointer handling and error detection",
    ],
    techStack: ["C++", "Binary Trees", "Recursion", "Stack Data Structure", "Syntax Parsing"],
    metrics: [
      { label: "Notation", value: "Infix / Postfix" },
      { label: "Traversal", value: "3 Recursive Modes" },
      { label: "Data Structure", value: "Binary Tree" },
    ],
    codeSnippet: {
      language: "cpp",
      filename: "ExpressionTreeRenegado.cpp",
      code: `struct TreeNode {
    string value;
    TreeNode* left;
    TreeNode* right;
    TreeNode(string val) : value(val), left(nullptr), right(nullptr) {}
};

// Recursive post-order arithmetic evaluation
double evaluateTree(TreeNode* root) {
    if (!root) return 0;
    if (!root->left && !root->right) return stod(root->value);
    double lVal = evaluateTree(root->left);
    double rVal = evaluateTree(root->right);
    return applyOperator(root->value, lVal, rVal);
}`,
    },
    githubUrl: "https://github.com/Amiel255/CODE-TRAINING/tree/main/DSA",
    slug: "expression-tree-parser",
  },
];

export const SKILL_CATEGORIES = [
  {
    category: "Languages & Core",
    description: "Systems, object-oriented, and scripted languages",
    skills: [
      { name: "C++ (C++17)", level: "Advanced", desc: "STL, Pointers, Memory Management, OOP" },
      { name: "C", level: "Proficient", desc: "Low-level logic, Structs, File Streams, Pointers" },
      { name: "x86 Assembly", level: "Intermediate", desc: "8086, TASM, JWasm, Interrupts, Registers" },
      { name: "Java", level: "Intermediate", desc: "OOP, Class hierarchies, Application logic" },
      { name: "TypeScript / JS", level: "Proficient", desc: "Modern ES6+, Next.js, React integration" },
      { name: "Python", level: "Intermediate", desc: "Scripting, Verification tests, Automation" },
    ],
  },
  {
    category: "Systems & Architecture",
    description: "Low-level computation and systems design",
    skills: [
      { name: "Memory Management", desc: "Dynamic allocation, pointers, std::shared_ptr" },
      { name: "Hardware Interrupts", desc: "BIOS INT 10h, DOS INT 21h, 16-bit register execution" },
      { name: "Bitwise Operations", desc: "Bit streams, bitmasks, bit shifting, custom compression" },
      { name: "File Systems & I/O", desc: "Binary serialization, CSV streams, structured persistence" },
    ],
  },
  {
    category: "Data Structures & Algorithms",
    description: "Theoretical and applied computer science",
    skills: [
      { name: "Huffman Trees", desc: "Lossless compression, frequency analysis, prefix codes" },
      { name: "Expression Trees", desc: "Syntax evaluation, operator precedence, tree traversals" },
      { name: "Linked Lists", desc: "Doubly linked with tail, singly linked, cycle detection" },
      { name: "Search & Sort", desc: "Binary search, deterministic priority queues, heaps" },
    ],
  },
  {
    category: "Modern Web & Tools",
    description: "Developer tooling, frameworks, and deployment",
    skills: [
      { name: "Next.js & React", desc: "App router, SSR/SSG, modern component architecture" },
      { name: "Tailwind CSS", desc: "Utility-first design, minimal dark/light themes" },
      { name: "Git & GitHub", desc: "Version control, branching, repository management" },
      { name: "VS Code & Terminal", desc: "Debugging, build tasks, PowerShell & Bash workflows" },
    ],
  },
];

export const EDUCATION_DATA = [
  {
    degree: "Bachelor of Science in Information Technology (BSIT)",
    institution: "Higher Education Degree",
    period: "2025 - Present",
    status: "Currently Enrolled",
    description:
      "Comprehensive program encompassing software development, data structures, computer systems architecture, database management, and network fundamentals.",
    highlights: [
      "Data Structures & Algorithms — Advanced implementations of linked lists, expression trees, and Huffman encoding",
      "Computer Programming 1 & 2 — Mastery in procedural and object-oriented C/C++ architecture",
      "Computer Organization & Assembly Language — 16-bit x86 architecture, registers, and BIOS/DOS interrupts",
      "Active Academic Projects & Repository Maintainer",
    ],
  },
];
