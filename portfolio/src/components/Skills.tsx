"use client";

import { SKILL_CATEGORIES } from "@/data/portfolioData";
import { Cpu, Binary, Layers, Wrench } from "lucide-react";

export function Skills() {
  const getCategoryIcon = (category: string) => {
    switch (category) {
      case "Languages & Core":
        return <Binary className="w-4 h-4 text-emerald-500" />;
      case "Systems & Architecture":
        return <Cpu className="w-4 h-4 text-cyan-500" />;
      case "Data Structures & Algorithms":
        return <Layers className="w-4 h-4 text-amber-500" />;
      case "Modern Web & Tools":
        return <Wrench className="w-4 h-4 text-blue-500" />;
      default:
        return <Binary className="w-4 h-4" />;
    }
  };

  return (
    <section id="skills" className="py-20 border-t border-zinc-200/80 dark:border-zinc-800/80">
      <div className="max-w-5xl mx-auto px-4 sm:px-6">
        {/* Section Header */}
        <div className="mb-12">
          <div className="inline-flex items-center gap-1.5 px-2.5 py-1 rounded-md text-xs font-mono uppercase tracking-wide bg-zinc-100 dark:bg-zinc-900 border border-zinc-200 dark:border-zinc-800 text-zinc-600 dark:text-zinc-400 mb-2">
            <Cpu className="w-3.5 h-3.5" />
            Capabilities
          </div>
          <h2 className="text-2xl sm:text-3xl font-bold tracking-tight text-zinc-900 dark:text-zinc-100">
            Technical Stack & Expertise
          </h2>
          <p className="text-sm text-zinc-500 dark:text-zinc-400 mt-1 max-w-xl">
            A comprehensive overview of programming languages, computer systems foundations,
            algorithmic analysis, and modern web technologies.
          </p>
        </div>

        {/* Categories Grid */}
        <div className="grid grid-cols-1 md:grid-cols-2 gap-6">
          {SKILL_CATEGORIES.map((cat) => (
            <div
              key={cat.category}
              className="rounded-2xl border border-zinc-200 dark:border-zinc-800/90 bg-white dark:bg-zinc-900/40 p-6 flex flex-col justify-between hover:border-zinc-300 dark:hover:border-zinc-700 transition-colors shadow-xs"
            >
              <div>
                <div className="flex items-center gap-2 mb-1">
                  {getCategoryIcon(cat.category)}
                  <h3 className="text-base font-bold text-zinc-900 dark:text-zinc-100">
                    {cat.category}
                  </h3>
                </div>
                <p className="text-xs text-zinc-500 dark:text-zinc-400 mb-5">
                  {cat.description}
                </p>

                <div className="space-y-3">
                  {cat.skills.map((skill) => (
                    <div
                      key={skill.name}
                      className="p-3 rounded-xl bg-zinc-50 dark:bg-zinc-950/60 border border-zinc-100 dark:border-zinc-800/80 flex items-start justify-between gap-3"
                    >
                      <div>
                        <div className="flex items-center gap-2">
                          <span className="text-sm font-semibold text-zinc-800 dark:text-zinc-200 font-mono">
                            {skill.name}
                          </span>
                          {"level" in skill && skill.level && (
                            <span className="px-1.5 py-0.2 rounded text-[10px] font-mono bg-zinc-200 dark:bg-zinc-800 text-zinc-600 dark:text-zinc-400">
                              {skill.level}
                            </span>
                          )}
                        </div>
                        <p className="text-xs text-zinc-500 dark:text-zinc-400 mt-0.5">
                          {skill.desc}
                        </p>
                      </div>
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
