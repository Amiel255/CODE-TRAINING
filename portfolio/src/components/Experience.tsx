import { BriefcaseBusiness, MapPin } from "lucide-react";
import { EXPERIENCE_DATA } from "@/data/portfolioData";

export function Experience() {
  return (
    <section id="experience" className="py-20 border-t border-zinc-200/80 dark:border-zinc-800/80">
      <div className="max-w-5xl mx-auto px-4 sm:px-6">
        <div className="mb-10">
          <div className="inline-flex items-center gap-1.5 px-2.5 py-1 rounded-md text-xs font-mono uppercase tracking-wide bg-zinc-100 dark:bg-zinc-900 border border-zinc-200 dark:border-zinc-800 text-zinc-600 dark:text-zinc-400 mb-2">
            <BriefcaseBusiness aria-hidden="true" className="w-3.5 h-3.5" />
            Campus Leadership
          </div>
          <h2 className="text-2xl sm:text-3xl font-bold tracking-tight text-zinc-900 dark:text-zinc-100">
            Experience
          </h2>
        </div>

        <div className="space-y-6">
          {EXPERIENCE_DATA.map((item) => (
            <article key={item.role} className="rounded-2xl border border-zinc-200 dark:border-zinc-800/90 bg-white dark:bg-zinc-900/40 p-6 sm:p-8 shadow-xs">
              <div className="flex flex-col sm:flex-row sm:items-start justify-between gap-3">
                <div>
                  <h3 className="text-lg sm:text-xl font-bold text-zinc-900 dark:text-zinc-100">{item.role}</h3>
                  <p className="text-sm text-zinc-600 dark:text-zinc-400 mt-1">{item.organization}</p>
                </div>
                {item.current && (
                  <span className="self-start shrink-0 px-2.5 py-0.5 rounded-full text-xs font-mono bg-emerald-500/10 text-emerald-700 dark:text-emerald-400 border border-emerald-500/20">
                    Current Role
                  </span>
                )}
              </div>
              <p className="text-xs sm:text-sm font-mono text-zinc-600 dark:text-zinc-400 mt-4">{item.period}</p>
              <p className="flex items-start gap-1.5 text-xs text-zinc-500 dark:text-zinc-400 mt-2">
                <MapPin aria-hidden="true" className="w-3.5 h-3.5 shrink-0" />
                {item.location}
              </p>
            </article>
          ))}
        </div>
      </div>
    </section>
  );
}
