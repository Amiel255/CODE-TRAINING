"use client";

import { useState, useRef, useEffect } from "react";
import { Terminal as TerminalIcon, CornerDownLeft, Sparkles } from "lucide-react";
import { PERSONAL_INFO, PROJECTS } from "@/data/portfolioData";

interface OutputLine {
  id: string;
  type: "command" | "response" | "system";
  text: string;
  highlight?: boolean;
}

const INITIAL_LINES: OutputLine[] = [
  {
    id: "init-1",
    type: "system",
    text: "AmielOS Terminal v1.0 [Systems & DSA Environment]",
  },
  {
    id: "init-2",
    type: "system",
    text: "Type 'help' to see available commands, or click the quick tags below.",
  },
  {
    id: "init-3",
    type: "command",
    text: "$ amiel --status",
  },
  {
    id: "init-4",
    type: "response",
    text: "✓ BSIT Student | C++ & x86 Assembly | Lossless Huffman Compression & Algorithms",
    highlight: true,
  },
];

export function TerminalPreview() {
  const [lines, setLines] = useState<OutputLine[]>(INITIAL_LINES);
  const [inputVal, setInputVal] = useState("");
  const outputRef = useRef<HTMLDivElement>(null);

  useEffect(() => {
    const output = outputRef.current;
    if (output) output.scrollTop = output.scrollHeight;
  }, [lines]);

  const handleCommand = (cmd: string) => {
    const trimmed = cmd.trim().toLowerCase();
    if (!trimmed) return;

    const newCommandEntry: OutputLine = {
      id: `${Date.now()}-cmd`,
      type: "command",
      text: `$ ${cmd}`,
    };

    let responseEntries: OutputLine[] = [];

    switch (trimmed) {
      case "help":
        responseEntries = [
          {
            id: `${Date.now()}-1`,
            type: "response",
            text: "Available commands:\n  about     - Brief background & profile\n  projects  - Featured academic & systems projects\n  skills    - Low-level and high-level stack\n  contact   - Direct email & github links\n  clear     - Clear terminal buffer",
          },
        ];
        break;
      case "about":
        responseEntries = [
          {
            id: `${Date.now()}-1`,
            type: "response",
            text: `${PERSONAL_INFO.name} — ${PERSONAL_INFO.title}\n${PERSONAL_INFO.bio}`,
          },
        ];
        break;
      case "projects":
        responseEntries = [
          {
            id: `${Date.now()}-1`,
            type: "response",
            text: PROJECTS.map((project, index) => `${index + 1}. [${project.category}] ${project.title}`).join("\n"),
          },
        ];
        break;
      case "skills":
        responseEntries = [
          {
            id: `${Date.now()}-1`,
            type: "response",
            text: "Languages: C++17, C, x86 Assembly (TASM/JWasm), Java, TypeScript, Python\nCore: Pointer Arithmetic, Shared Pointers, Bitwise Manipulation, Data Structures\nTools: Next.js, Tailwind CSS, Git, VS Code, GDB, GCC",
          },
        ];
        break;
      case "contact":
        responseEntries = [
          {
            id: `${Date.now()}-1`,
            type: "response",
            text: `Email:    ${PERSONAL_INFO.email}\nGitHub:   ${PERSONAL_INFO.github}\nLinkedIn: ${PERSONAL_INFO.linkedin}\nWeb:      Available on this site`,
          },
        ];
        break;
      case "clear":
        setLines([]);
        setInputVal("");
        return;
      default:
        responseEntries = [
          {
            id: `${Date.now()}-err`,
            type: "response",
            text: `Command not found: "${cmd}". Type 'help' for valid commands.`,
          },
        ];
    }

    setLines((prev) => [...prev, newCommandEntry, ...responseEntries]);
    setInputVal("");
  };

  const handleKeyDown = (e: React.KeyboardEvent<HTMLInputElement>) => {
    if (e.key === "Enter") {
      e.preventDefault();
      handleCommand(inputVal);
    }
  };

  return (
    <div className="w-full rounded-xl border border-zinc-200 dark:border-zinc-800 bg-zinc-950 text-zinc-300 shadow-xl overflow-hidden font-mono text-xs sm:text-sm">
      {/* Terminal Title Bar */}
      <div className="px-4 py-3 bg-zinc-900/90 border-b border-zinc-800 flex items-center justify-between select-none">
        <div className="flex items-center gap-2">
          <div className="flex items-center gap-1.5">
            <span className="w-2.5 h-2.5 rounded-full bg-red-500/80 inline-block" />
            <span className="w-2.5 h-2.5 rounded-full bg-amber-500/80 inline-block" />
            <span className="w-2.5 h-2.5 rounded-full bg-emerald-500/80 inline-block" />
          </div>
          <span className="text-zinc-400 text-xs font-medium ml-2 flex items-center gap-1.5">
            <TerminalIcon className="w-3.5 h-3.5 text-zinc-400" />
            amiel@dev-box: ~/code-training
          </span>
        </div>
        <div className="hidden sm:flex items-center gap-1.5 text-[11px] text-zinc-400 font-sans">
          <Sparkles className="w-3 h-3 text-emerald-400" />
          Interactive Terminal
        </div>
      </div>

      {/* Terminal Output Area */}
      <div ref={outputRef} role="log" aria-label="Terminal output" className="p-4 sm:p-5 max-h-72 overflow-y-auto space-y-2 bg-zinc-950 font-mono">
        {lines.map((line) => (
          <div
            key={line.id}
            className={`leading-relaxed whitespace-pre-wrap ${
              line.type === "command"
                ? "text-emerald-400 font-semibold"
                : line.type === "system"
                ? "text-zinc-300 text-xs"
                : line.highlight
                ? "text-cyan-300"
                : "text-zinc-300"
            }`}
          >
            {line.text}
          </div>
        ))}
      </div>

      {/* Interactive Input Prompt */}
      <div className="px-4 py-2.5 bg-zinc-900/70 border-t border-zinc-800 flex items-center gap-2">
        <span className="text-emerald-400 font-bold">$</span>
        <input
          type="text"
          aria-label="Terminal command"
          value={inputVal}
          onChange={(e) => setInputVal(e.target.value)}
          onKeyDown={handleKeyDown}
          placeholder="Type 'help', 'projects', 'skills'..."
          className="flex-1 bg-transparent border-none text-zinc-100 placeholder:text-zinc-600 focus:outline-none text-xs sm:text-sm font-mono"
        />
        <button
          onClick={() => handleCommand(inputVal)}
          aria-label="Execute command"
          className="p-1 rounded text-zinc-400 hover:text-zinc-200 hover:bg-zinc-800 transition-colors"
        >
          <CornerDownLeft className="w-3.5 h-3.5" />
        </button>
      </div>

      {/* Quick Action Pills */}
      <div className="px-4 py-2 bg-zinc-950/90 border-t border-zinc-800/80 flex items-center flex-wrap gap-1.5 text-[11px]">
        <span className="text-zinc-400 mr-1 select-none font-sans">Quick pills:</span>
        {["help", "projects", "skills", "about", "contact", "clear"].map((cmd) => (
          <button
            key={cmd}
            onClick={() => handleCommand(cmd)}
            className="px-2 py-0.5 rounded bg-zinc-900 hover:bg-zinc-800 text-zinc-300 hover:text-white border border-zinc-800 transition-colors cursor-pointer"
          >
            {cmd}
          </button>
        ))}
      </div>
    </div>
  );
}
