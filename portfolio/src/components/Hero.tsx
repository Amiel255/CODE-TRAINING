"use client";

import { ArrowDown, Mail, Copy, Check } from "lucide-react";
import { GithubIcon } from "@/components/icons/GithubIcon";
import { LinkedinIcon } from "@/components/icons/LinkedinIcon";
import { PERSONAL_INFO, PROJECTS } from "@/data/portfolioData";
import { TerminalPreview } from "./TerminalPreview";
import { useClipboard } from "./useClipboard";

export function Hero() {
  const { copy: handleCopyEmail, status: copyStatus } = useClipboard(PERSONAL_INFO.email);

  return (
    <section id="about" className="relative pt-28 pb-16 md:pt-36 md:pb-24 overflow-hidden">
      {/* Subtle background grid pattern */}
      <div className="absolute inset-0 -z-10 bg-[linear-gradient(to_right,#8080800a_1px,transparent_1px),linear-gradient(to_bottom,#8080800a_1px,transparent_1px)] bg-[size:24px_24px] [mask-image:radial-gradient(ellipse_60%_50%_at_50%_0%,#000_70%,transparent_100%)]" />

      <div className="max-w-5xl mx-auto px-4 sm:px-6">
        <div className="grid grid-cols-1 lg:grid-cols-12 gap-10 lg:gap-8 items-start">
          {/* Main Info Column */}
          <div className="lg:col-span-7 space-y-6">
            {/* Status Badge */}
            <div className="inline-flex items-center gap-2 px-3 py-1 rounded-full text-xs font-medium bg-emerald-500/10 border border-emerald-500/20 text-emerald-700 dark:text-emerald-400">
              <span className="relative flex h-2 w-2">
                <span className="animate-ping absolute inline-flex h-full w-full rounded-full bg-emerald-400 opacity-75" />
                <span className="relative inline-flex rounded-full h-2 w-2 bg-emerald-500" />
              </span>
              <span>Available for internships & roles</span>
            </div>

            {/* Headline */}
            <div className="space-y-2">
              <h1 className="text-3xl sm:text-4xl md:text-5xl font-bold tracking-tight text-zinc-900 dark:text-zinc-50">
                {PERSONAL_INFO.name}
              </h1>
              <p className="text-lg sm:text-xl font-medium text-zinc-600 dark:text-zinc-400">
                {PERSONAL_INFO.title}
              </p>
            </div>

            {/* Bio */}
            <p className="text-base text-zinc-600 dark:text-zinc-400 leading-relaxed max-w-xl">
              {PERSONAL_INFO.bio}
            </p>

            {/* Quick Skills Pills */}
            <div className="flex flex-wrap gap-2 pt-1">
              {[
                "C++17 & STL",
                "x86 Assembly",
                "Lossless Compression",
                "Data Structures",
                "React & TypeScript",
                "Next.js",
              ].map((badge) => (
                <span
                  key={badge}
                  className="px-2.5 py-1 text-xs font-mono rounded-md bg-zinc-100 dark:bg-zinc-900 border border-zinc-200 dark:border-zinc-800 text-zinc-700 dark:text-zinc-300"
                >
                  {badge}
                </span>
              ))}
            </div>

            {/* Quick Stats Grid */}
            <div className="grid grid-cols-3 gap-3 pt-3 border-t border-zinc-200/60 dark:border-zinc-800/80">
              <div className="p-2.5 rounded-xl bg-zinc-50/70 dark:bg-zinc-900/40 border border-zinc-200/60 dark:border-zinc-800/60">
                <div className="text-lg sm:text-xl font-bold font-mono text-zinc-900 dark:text-zinc-100">
                  {PROJECTS.length}
                </div>
                <div className="text-[11px] font-mono text-zinc-500 dark:text-zinc-400">
                  Selected Projects
                </div>
              </div>
              <div className="p-2.5 rounded-xl bg-zinc-50/70 dark:bg-zinc-900/40 border border-zinc-200/60 dark:border-zinc-800/60">
                <div className="text-lg sm:text-xl font-bold font-mono text-zinc-900 dark:text-zinc-100">
                  C++ / x86
                </div>
                <div className="text-[11px] font-mono text-zinc-500 dark:text-zinc-400">
                  Low-Level Core
                </div>
              </div>
              <div className="p-2.5 rounded-xl bg-zinc-50/70 dark:bg-zinc-900/40 border border-zinc-200/60 dark:border-zinc-800/60">
                <div className="text-lg sm:text-xl font-bold font-mono text-zinc-900 dark:text-zinc-100">
                  BSIT
                </div>
                <div className="text-[11px] font-mono text-zinc-500 dark:text-zinc-400">
                  Academic Focus
                </div>
              </div>
            </div>

            {/* Action Buttons */}
            <div className="flex flex-wrap items-center gap-3 pt-2">
              <a
                href="#projects"
                className="inline-flex items-center gap-2 px-4 py-2 rounded-lg bg-zinc-900 text-white dark:bg-zinc-100 dark:text-zinc-950 hover:bg-zinc-800 dark:hover:bg-zinc-200 text-sm font-medium transition-all shadow-xs"
              >
                View Projects
                <ArrowDown className="w-3.5 h-3.5" />
              </a>

              <button
                onClick={handleCopyEmail}
                className="inline-flex items-center gap-2 px-3.5 py-2 rounded-lg border border-zinc-200 dark:border-zinc-800 bg-white dark:bg-zinc-900 hover:bg-zinc-50 dark:hover:bg-zinc-800/80 text-sm font-medium text-zinc-700 dark:text-zinc-200 transition-colors"
                title="Copy email address"
              >
                {copyStatus === "copied" ? (
                  <>
                    <Check className="w-3.5 h-3.5 text-emerald-500" />
                    <span>Copied!</span>
                  </>
                ) : (
                  <>
                    <Copy className="w-3.5 h-3.5 text-zinc-500" />
                    <span>Copy Email</span>
                  </>
                )}
              </button>

              <a
                href={PERSONAL_INFO.github}
                target="_blank"
                rel="noopener noreferrer"
                className="p-2 rounded-lg border border-zinc-200 dark:border-zinc-800 bg-white dark:bg-zinc-900 hover:bg-zinc-50 dark:hover:bg-zinc-800/80 text-zinc-700 dark:text-zinc-200 transition-colors"
                aria-label="GitHub Profile"
              >
                <GithubIcon className="w-4 h-4" />
              </a>

              {PERSONAL_INFO.linkedin && (
                <a
                  href={PERSONAL_INFO.linkedin}
                  target="_blank"
                  rel="noopener noreferrer"
                  className="p-2 rounded-lg border border-zinc-200 dark:border-zinc-800 bg-white dark:bg-zinc-900 hover:bg-zinc-50 dark:hover:bg-zinc-800/80 text-zinc-700 dark:text-zinc-200 transition-colors"
                  aria-label="LinkedIn Profile"
                >
                  <LinkedinIcon className="w-4 h-4" />
                </a>
              )}

              <a
                href={`mailto:${PERSONAL_INFO.email}`}
                className="p-2 rounded-lg border border-zinc-200 dark:border-zinc-800 bg-white dark:bg-zinc-900 hover:bg-zinc-50 dark:hover:bg-zinc-800/80 text-zinc-700 dark:text-zinc-200 transition-colors"
                aria-label="Send Email"
              >
                <Mail className="w-4 h-4" />
              </a>
            </div>
            <p role="status" className="text-xs text-zinc-500 dark:text-zinc-400">
              {copyStatus === "error" ? "Could not copy. Use the email link to get in touch." : copyStatus === "copied" ? "Email address copied." : ""}
            </p>
          </div>

          {/* Interactive Terminal / Code Column */}
          <div className="lg:col-span-5 w-full">
            <TerminalPreview />
          </div>
        </div>
      </div>
    </section>
  );
}
