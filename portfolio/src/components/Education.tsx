"use client";

import { EDUCATION_DATA } from "@/data/portfolioData";
import { GraduationCap, Award, BookOpen, CheckCircle2 } from "lucide-react";

export function Education() {
  return (
    <section id="education" className="py-20 border-t border-zinc-200/80 dark:border-zinc-800/80">
      <div className="max-w-5xl mx-auto px-4 sm:px-6">
        {/* Section Header */}
        <div className="mb-12">
          <div className="inline-flex items-center gap-1.5 px-2.5 py-1 rounded-md text-xs font-mono uppercase tracking-wide bg-zinc-100 dark:bg-zinc-900 border border-zinc-200 dark:border-zinc-800 text-zinc-600 dark:text-zinc-400 mb-2">
            <GraduationCap className="w-3.5 h-3.5" />
            Academic Path
          </div>
          <h2 className="text-2xl sm:text-3xl font-bold tracking-tight text-zinc-900 dark:text-zinc-100">
            Education & Coursework
          </h2>
          <p className="text-sm text-zinc-500 dark:text-zinc-400 mt-1 max-w-xl">
            Formal studies in Information Technology focusing on computer programming foundations,
            advanced data structures, and computer organization.
          </p>
        </div>

        {/* Education Timeline */}
        <div className="space-y-6">
          {EDUCATION_DATA.map((item, index) => (
            <div
              key={index}
              className="rounded-2xl border border-zinc-200 dark:border-zinc-800/90 bg-white dark:bg-zinc-900/40 p-6 sm:p-8 hover:border-zinc-300 dark:hover:border-zinc-700 transition-colors shadow-xs"
            >
              <div className="flex flex-col sm:flex-row sm:items-center justify-between gap-2 mb-3">
                <div>
                  <h3 className="text-lg sm:text-xl font-bold text-zinc-900 dark:text-zinc-100">
                    {item.degree}
                  </h3>
                  <p className="text-sm text-zinc-500 dark:text-zinc-400 font-medium">
                    {item.institution}
                  </p>
                </div>
                <div className="flex sm:flex-col sm:items-end gap-2">
                  <span className="px-2.5 py-0.5 rounded-full text-xs font-mono bg-emerald-500/10 text-emerald-600 dark:text-emerald-400 border border-emerald-500/20">
                    {item.status}
                  </span>
                  <span className="text-xs text-zinc-600 dark:text-zinc-400 font-mono">
                    {item.period}
                  </span>
                </div>
              </div>

              <p className="text-sm text-zinc-600 dark:text-zinc-400 leading-relaxed mb-6">
                {item.description}
              </p>

              {/* Highlights */}
              <div className="border-t border-zinc-100 dark:border-zinc-800/80 pt-5">
                <h4 className="text-xs font-semibold uppercase tracking-wider text-zinc-400 mb-3 flex items-center gap-1.5 font-mono">
                  <BookOpen className="w-3.5 h-3.5" />
                  Key Coursework & Milestones
                </h4>
                <div className="grid grid-cols-1 md:grid-cols-2 gap-3">
                  {item.highlights.map((hl, i) => (
                    <div
                      key={i}
                      className="p-3 rounded-xl bg-zinc-50 dark:bg-zinc-950/60 border border-zinc-100 dark:border-zinc-800/80 flex items-start gap-2.5 text-xs sm:text-sm text-zinc-700 dark:text-zinc-300"
                    >
                      <CheckCircle2 className="w-4 h-4 text-emerald-500 shrink-0 mt-0.5" />
                      <span>{hl}</span>
                    </div>
                  ))}
                </div>
              </div>
            </div>
          ))}
        </div>
      </div>
    </section>
  );
}
