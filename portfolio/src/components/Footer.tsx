"use client";

import { ArrowUp, Mail } from "lucide-react";
import { GithubIcon } from "@/components/icons/GithubIcon";
import { PERSONAL_INFO } from "@/data/portfolioData";

export function Footer() {
  const scrollToTop = () => {
    window.scrollTo({ top: 0, behavior: "smooth" });
  };

  return (
    <footer className="border-t border-zinc-200/80 dark:border-zinc-800/80 py-12 bg-white dark:bg-zinc-950 text-zinc-500 dark:text-zinc-400 text-xs">
      <div className="max-w-5xl mx-auto px-4 sm:px-6 flex flex-col sm:flex-row items-center justify-between gap-6">
        <div className="space-y-1 text-center sm:text-left">
          <div className="flex items-center justify-center sm:justify-start gap-2 text-zinc-900 dark:text-zinc-100 font-medium">
            <span className="w-5 h-5 rounded bg-zinc-900 dark:bg-zinc-100 text-white dark:text-zinc-950 flex items-center justify-center font-bold text-[10px]">
              AP
            </span>
            <span>{PERSONAL_INFO.name}</span>
          </div>
          <p className="font-mono text-[11px] text-zinc-400 dark:text-zinc-500">
            Engineered with Next.js & Tailwind CSS • Clean & Minimal Design
          </p>
        </div>

        <div className="flex items-center gap-4">
          <a
            href={PERSONAL_INFO.github}
            target="_blank"
            rel="noopener noreferrer"
            className="hover:text-zinc-900 dark:hover:text-zinc-100 transition-colors"
          >
            GitHub
          </a>
          <a
            href={`mailto:${PERSONAL_INFO.email}`}
            className="hover:text-zinc-900 dark:hover:text-zinc-100 transition-colors"
          >
            Email
          </a>
          <a
            href={PERSONAL_INFO.facebook}
            target="_blank"
            rel="noopener noreferrer"
            className="hover:text-zinc-900 dark:hover:text-zinc-100 transition-colors"
          >
            Facebook
          </a>

          <button
            onClick={scrollToTop}
            aria-label="Scroll to top"
            className="p-1.5 rounded-lg border border-zinc-200 dark:border-zinc-800 hover:bg-zinc-100 dark:hover:bg-zinc-800 text-zinc-600 dark:text-zinc-300 transition-colors"
          >
            <ArrowUp className="w-3.5 h-3.5" />
          </button>
        </div>
      </div>
    </footer>
  );
}
