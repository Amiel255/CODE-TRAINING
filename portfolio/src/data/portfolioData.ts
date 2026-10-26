export interface Project {
  id: string;
  title: string;
  tagline: string;
  category: "Systems & C++" | "Assembly" | "Algorithms & DSA" | "Game Dev & Graphics" | "Web & HCI";
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
  linkedin: "https://www.linkedin.com/in/amiel-keith-padilla-6684a0381",
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
  {
    id: "raylib-game-engine",
    title: "Raylib 2D Game & Interactive Graphics Engine",
    tagline: "High-performance C++ interactive game loop with Raylib, OpenGL & physics",
    category: "Game Dev & Graphics",
    period: "2025 - 2026",
    description:
      "An interactive 2D game and graphics application engineered in C++ using Raylib and OpenGL. Features custom game loop architecture, delta-time physics calculation, collision detection algorithms, and frame-rate independent sprite animation.",
    highlights: [
      "Custom frame-rate independent 60 FPS game loop utilizing raylib windowing and input polling",
      "2D collision detection and vector physics routines (bounding box AABB & circle intersection)",
      "Sprite rendering, asset management, and procedural graphics using hardware-accelerated OpenGL pipeline",
      "Integrated build pipeline in VS Code leveraging MinGW, GCC, and raylib static linking",
    ],
    techStack: ["C++", "Raylib", "Game Development", "OpenGL", "Vector Physics", "VS Code"],
    metrics: [
      { label: "Target FPS", value: "60 FPS Locked" },
      { label: "Graphics API", value: "OpenGL / Raylib" },
      { label: "Architecture", value: "Delta-Time Loop" },
    ],
    codeSnippet: {
      language: "cpp",
      filename: "main.cpp",
      code: `#include "raylib.h"

int main() {
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Raylib Interactive Engine");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        // Delta-time physics update
        float dt = GetFrameTime();
        
        // Render frame
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("Raylib Engine running at 60 FPS", 190, 200, 20, DARKGRAY);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}`,
    },
    githubUrl: "https://github.com/Amiel255/VSCODE-RAYLIB",
    slug: "raylib-game-engine",
  },
  {
    id: "panaataan-hackathon",
    title: "Panataanph Fitness App — Hackathon 2026",
    tagline: "Condition-aware fitness & wellness HCI prototype (React + Figma)",
    category: "Web & HCI",
    period: "2026",
    description:
      "A full-featured HCI prototype and interactive wireframe for a mobile health & fitness app built during the Panataanph Hackathon 2026. Designed for accessibility-first, condition-aware personalization — targeting users with chronic conditions (asthma, joint pain, heart conditions) with calm, low-cognitive-load interfaces.",
    highlights: [
      "12+ mobile screens: Onboarding, Home, Activity Tracker, Weekly Planner, Progress, Wellness, Smart Route, Sync Center",
      "Condition-based personalization engine routing users to appropriate exercise plans based on health profile",
      "React Router browser-based SPA routing with PhoneShell wrapper for authentic mobile viewport simulation",
      "Real-time activity state management with Zustand-style activityStore, GPX export for route tracking, and emergency modal system",
      "Design system built on shadcn/ui, Radix UI primitives, MUI Material, and Tailwind CSS with calm sage/warm beige theme",
    ],
    techStack: ["React", "TypeScript", "Vite", "Tailwind CSS", "Radix UI", "Figma", "React Router", "shadcn/ui"],
    metrics: [
      { label: "Screens", value: "12+ Flows" },
      { label: "Design Tool", value: "Figma + Code" },
      { label: "Stack", value: "React + TS" },
    ],
    codeSnippet: {
      language: "tsx",
      filename: "routes.ts",
      code: `export const router = createBrowserRouter([
  {
    path: '/',
    Component: PhoneShell,
    children: [
      { path: 'onboarding',         Component: OnboardingScreen },
      { path: 'activities/setup',   Component: ActivitySetupScreen },
      { path: 'activities/track',   Component: ActivityTrackerScreen },
      { path: 'activities/route',   Component: SmartRouteScreen },
      { path: 'home',               Component: HomeScreen },
      { path: 'progress',           Component: ProgressScreen },
      { path: 'wellness',           Component: WellnessScreen },
      { path: 'profile',            Component: ProfileScreen },
    ],
  },
]);`,
    },
    githubUrl: "https://github.com/strob3/panataanph-hackathon-2026",
    slug: "panaataan-hackathon",
  },
  {
    id: "hash-table-set-operations",
    title: "Hash Table & Set Operations Engine",
    tagline: "Chaining hash table & custom Set ADT with union, intersection, difference",
    category: "Algorithms & DSA",
    period: "2026",
    description:
      "Dual DSA machine problems implementing a chaining hash table (MP7) and a full abstract Set data type (MP8) from scratch in C++. Covers collision resolution via linked-list chaining and complete mathematical set algebra operations.",
    highlights: [
      "Hash table with modular hash function and separate chaining collision resolution using linked list nodes",
      "Full Set ADT supporting union, intersection, difference, and subset operations with O(n²) worst-case bounds",
      "Custom contains(), add(), remove() with duplicate-safe enforced membership invariants",
    ],
    techStack: ["C++", "Hash Tables", "Linked Lists", "Set Theory", "Abstract Data Types"],
    metrics: [
      { label: "Hash Strategy", value: "Chaining" },
      { label: "Set Ops", value: "4 Operations" },
      { label: "Collision", value: "Linked List" },
    ],
    codeSnippet: {
      language: "cpp",
      filename: "mp7 - PADILLA.cpp",
      code: `class HashTable {
private:
    Node* table[SIZE];
    int hashFunction(int key) {
        return (key % SIZE + SIZE) % SIZE;
    }
public:
    void insert(int key) {
        int idx = hashFunction(key);
        Node* newNode = new Node(key);
        newNode->next = table[idx];
        table[idx] = newNode; // prepend for O(1) insert
    }
};`,
    },
    githubUrl: "https://github.com/Amiel255/CODE-TRAINING/tree/main/DSA",
    slug: "hash-table-set-operations",
  },
  {
    id: "stack-queue-dsa",
    title: "Stack & Queue Data Structures Suite",
    tagline: "Dual array & linked-list implementations of Stacks and Queues",
    category: "Algorithms & DSA",
    period: "2026",
    description:
      "A comprehensive DSA machine problem implementing both Stack and Queue abstract data types twice — once using arrays with bounded capacity and once using dynamically allocated linked lists. Compares performance and memory tradeoffs between both strategies.",
    highlights: [
      "Array-based Stack (StackArray) and Linked-list Stack (StackList) with push/pop/peek operations and overflow/underflow guards",
      "Array-based Queue (QueueArray) with circular indexing and Linked-list Queue (QueueList) with head-tail pointers",
      "Side-by-side interface for comparing O(1) amortized array operations vs. dynamic memory linked-list operations",
    ],
    techStack: ["C++", "Stack ADT", "Queue ADT", "Linked Lists", "Array Structures"],
    metrics: [
      { label: "Implementations", value: "2 per ADT" },
      { label: "Operations", value: "Push/Pop/Peek" },
      { label: "Memory", value: "Static + Dynamic" },
    ],
    codeSnippet: {
      language: "cpp",
      filename: "mp4 - Padilla.cpp",
      code: `// Array-based Stack — bounded capacity
class StackArray {
private:
    int data[MAX];
    int top;
public:
    void push(int x) {
        if (isFull()) { cout << "Stack Overflow"; return; }
        data[--top] = x;
    }
    void pop() {
        if (isEmpty()) { cout << "Stack Underflow"; return; }
        top++;
    }
};`,
    },
    githubUrl: "https://github.com/Amiel255/CODE-TRAINING/tree/main/DSA",
    slug: "stack-queue-dsa",
  },
  {
    id: "usb-activity-bank-system",
    title: "USB Bank Activity Monitoring System",
    tagline: "Enhanced ATM engine with activity log, session tracking & security audit",
    category: "Systems & C++",
    period: "2026",
    description:
      "An extended version of the banking DSA system featuring a full USB-style session activity monitor. Logs all account events (login, withdrawal, deposit, transfer) per session in a structured audit trail backed by a doubly linked list and CSV persistence.",
    highlights: [
      "Session-scoped event logging recording each action with timestamps in a doubly linked list audit node chain",
      "Full CRUD account management with CSV database read/write sync across sessions",
      "PIN security with masked input, failed attempt counters, and card lock after threshold exceeded",
      "Activity report generation with formatted table output sorted by account and event type",
    ],
    techStack: ["C++", "Doubly Linked List", "File I/O", "CSV Engine", "Audit Logging"],
    metrics: [
      { label: "Code Size", value: "1,352 Lines" },
      { label: "Data Structure", value: "Doubly Linked List" },
      { label: "Persistence", value: "CSV Audit Log" },
    ],
    codeSnippet: {
      language: "cpp",
      filename: "USBactivity.cpp",
      code: `struct Account {
    string accountNumber;
    string accountName;
    string birthday;
    string contactNumber;
    long long balance;
    string pin; // encrypted PIN
};

struct node {
    Account data;
    node *next;
    node *prev;
    node(Account x) : data(x), next(NULL), prev(NULL) {}
};`,
    },
    githubUrl: "https://github.com/Amiel255/CODE-TRAINING/tree/main/DSA",
    slug: "usb-activity-bank-system",
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
      { name: "Raylib & Game Physics", desc: "Frame-rate independent loops, OpenGL pipeline, 2D collisions" },
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
      { name: "Hash Tables", desc: "Chaining collision resolution, modular hash functions, set operations" },
      { name: "Stack & Queue ADTs", desc: "Array-based and linked-list-based with O(1) push/pop" },
      { name: "Search & Sort", desc: "Binary search, deterministic priority queues, heaps" },
    ],
  },
  {
    category: "Modern Web & Tools",
    description: "Developer tooling, frameworks, and deployment",
    skills: [
      { name: "React & TypeScript", desc: "Component architecture, hooks, SPA routing, Vite" },
      { name: "Next.js & App Router", desc: "SSR/SSG, server components, Vercel deployment" },
      { name: "Tailwind CSS & shadcn/ui", desc: "Utility-first design, accessible Radix UI primitives" },
      { name: "Figma & HCI Design", desc: "Wireframing, prototyping, condition-aware UX design systems" },
      { name: "Git & GitHub", desc: "Version control, branching, repository management" },
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
