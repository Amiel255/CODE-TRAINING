"use client";

import { useState } from "react";
import { Mail, Copy, Check, Send, ArrowUpRight, MessageSquare } from "lucide-react";
import { GithubIcon } from "@/components/icons/GithubIcon";
import { PERSONAL_INFO } from "@/data/portfolioData";

export function Contact() {
  const [copied, setCopied] = useState(false);
  const [formData, setFormData] = useState({ name: "", email: "", message: "" });
  const [submitted, setSubmitted] = useState(false);

  const handleCopyEmail = () => {
    navigator.clipboard.writeText(PERSONAL_INFO.email);
    setCopied(true);
    setTimeout(() => setCopied(false), 2000);
  };

  const handleSubmit = (e: React.FormEvent) => {
    e.preventDefault();
    if (!formData.email || !formData.message) return;
    // Client-side simulation of message submission
    setSubmitted(true);
  };

  return (
    <section id="contact" className="py-20 border-t border-zinc-200/80 dark:border-zinc-800/80">
      <div className="max-w-5xl mx-auto px-4 sm:px-6">
        <div className="grid grid-cols-1 md:grid-cols-12 gap-10">
          {/* Left Column: Direct Info */}
          <div className="md:col-span-5 space-y-6">
            <div>
              <div className="inline-flex items-center gap-1.5 px-2.5 py-1 rounded-md text-xs font-mono uppercase tracking-wide bg-zinc-100 dark:bg-zinc-900 border border-zinc-200 dark:border-zinc-800 text-zinc-600 dark:text-zinc-400 mb-2">
                <MessageSquare className="w-3.5 h-3.5" />
                Connect
              </div>
              <h2 className="text-2xl sm:text-3xl font-bold tracking-tight text-zinc-900 dark:text-zinc-100">
                Let&apos;s Build Together
              </h2>
              <p className="text-sm text-zinc-500 dark:text-zinc-400 mt-2 leading-relaxed">
                I am actively seeking software engineering internships, technical collaborations,
                or discussions about systems programming and computer science.
              </p>
            </div>

            {/* Direct Contact Cards */}
            <div className="space-y-3 pt-2">
              {/* Email Card */}
              <div className="p-4 rounded-xl border border-zinc-200 dark:border-zinc-800 bg-white dark:bg-zinc-900/60 flex items-center justify-between gap-3">
                <div className="flex items-center gap-3 truncate">
                  <div className="p-2 rounded-lg bg-zinc-100 dark:bg-zinc-800 text-zinc-700 dark:text-zinc-300">
                    <Mail className="w-4 h-4" />
                  </div>
                  <div className="truncate">
                    <div className="text-[11px] font-mono text-zinc-600 dark:text-zinc-400">Direct Email</div>
                    <a
                      href={`mailto:${PERSONAL_INFO.email}`}
                      className="text-xs sm:text-sm font-semibold text-zinc-900 dark:text-zinc-100 hover:underline truncate block"
                    >
                      {PERSONAL_INFO.email}
                    </a>
                  </div>
                </div>
                <button
                  onClick={handleCopyEmail}
                  className="p-2 rounded-lg border border-zinc-200 dark:border-zinc-800 hover:bg-zinc-100 dark:hover:bg-zinc-800 text-zinc-500 hover:text-zinc-800 dark:hover:text-zinc-200 transition-colors shrink-0"
                  title="Copy email address"
                  aria-label="Copy email address"
                >
                  {copied ? (
                    <Check className="w-4 h-4 text-emerald-500" />
                  ) : (
                    <Copy className="w-4 h-4" />
                  )}
                </button>
              </div>

              {/* GitHub Card */}
              <a
                href={PERSONAL_INFO.github}
                target="_blank"
                rel="noopener noreferrer"
                className="group p-4 rounded-xl border border-zinc-200 dark:border-zinc-800 bg-white dark:bg-zinc-900/60 flex items-center justify-between gap-3 hover:border-zinc-400 dark:hover:border-zinc-700 transition-colors"
              >
                <div className="flex items-center gap-3">
                  <div className="p-2 rounded-lg bg-zinc-100 dark:bg-zinc-800 text-zinc-700 dark:text-zinc-300">
                    <GithubIcon className="w-4 h-4" />
                  </div>
                  <div>
                    <div className="text-[11px] font-mono text-zinc-600 dark:text-zinc-400">GitHub Profile</div>
                    <div className="text-xs sm:text-sm font-semibold text-zinc-900 dark:text-zinc-100 font-mono">
                      @{PERSONAL_INFO.handle}
                    </div>
                  </div>
                </div>
                <ArrowUpRight className="w-4 h-4 text-zinc-400 group-hover:text-zinc-900 dark:group-hover:text-zinc-100 transition-colors" />
              </a>
            </div>
          </div>

          {/* Right Column: Quick Contact Form */}
          <div className="md:col-span-7">
            <div className="rounded-2xl border border-zinc-200 dark:border-zinc-800/90 bg-white dark:bg-zinc-900/40 p-6 sm:p-8 shadow-xs">
              <h3 className="text-base font-bold text-zinc-900 dark:text-zinc-100 mb-1">
                Send a Message
              </h3>
              <p className="text-xs text-zinc-500 dark:text-zinc-400 mb-6">
                Fill out the quick form below or reach me directly at my email.
              </p>

              {submitted ? (
                <div className="p-6 rounded-xl bg-emerald-500/10 border border-emerald-500/20 text-center space-y-2">
                  <div className="w-10 h-10 rounded-full bg-emerald-500/20 text-emerald-600 dark:text-emerald-400 flex items-center justify-center mx-auto">
                    <Check className="w-5 h-5" />
                  </div>
                  <h4 className="text-sm font-bold text-emerald-800 dark:text-emerald-300">
                    Message Sent
                  </h4>
                  <p className="text-xs text-emerald-700 dark:text-emerald-400 max-w-sm mx-auto">
                    Thank you! Your message has been prepared. You can also reach me directly at{" "}
                    <span className="font-mono">{PERSONAL_INFO.email}</span>.
                  </p>
                  <button
                    onClick={() => {
                      setSubmitted(false);
                      setFormData({ name: "", email: "", message: "" });
                    }}
                    className="mt-3 text-xs font-medium text-emerald-700 dark:text-emerald-400 underline cursor-pointer"
                  >
                    Send another message
                  </button>
                </div>
              ) : (
                <form onSubmit={handleSubmit} className="space-y-4">
                  <div className="grid grid-cols-1 sm:grid-cols-2 gap-4">
                    <div>
                      <label className="block text-xs font-mono text-zinc-600 dark:text-zinc-400 mb-1.5">
                        Your Name
                      </label>
                      <input
                        type="text"
                        required
                        value={formData.name}
                        onChange={(e) => setFormData({ ...formData, name: e.target.value })}
                        placeholder="Ada Lovelace"
                        className="w-full px-3.5 py-2 rounded-lg border border-zinc-200 dark:border-zinc-800 bg-zinc-50 dark:bg-zinc-950 text-zinc-900 dark:text-zinc-100 text-sm focus:outline-none focus:ring-1 focus:ring-zinc-400 dark:focus:ring-zinc-600"
                      />
                    </div>
                    <div>
                      <label className="block text-xs font-mono text-zinc-600 dark:text-zinc-400 mb-1.5">
                        Your Email
                      </label>
                      <input
                        type="email"
                        required
                        value={formData.email}
                        onChange={(e) => setFormData({ ...formData, email: e.target.value })}
                        placeholder="ada@example.com"
                        className="w-full px-3.5 py-2 rounded-lg border border-zinc-200 dark:border-zinc-800 bg-zinc-50 dark:bg-zinc-950 text-zinc-900 dark:text-zinc-100 text-sm focus:outline-none focus:ring-1 focus:ring-zinc-400 dark:focus:ring-zinc-600"
                      />
                    </div>
                  </div>

                  <div>
                    <label className="block text-xs font-mono text-zinc-600 dark:text-zinc-400 mb-1.5">
                      Message
                    </label>
                    <textarea
                      required
                      rows={4}
                      value={formData.message}
                      onChange={(e) => setFormData({ ...formData, message: e.target.value })}
                      placeholder="Hi Amiel, I saw your Huffman compression and systems work..."
                      className="w-full px-3.5 py-2 rounded-lg border border-zinc-200 dark:border-zinc-800 bg-zinc-50 dark:bg-zinc-950 text-zinc-900 dark:text-zinc-100 text-sm focus:outline-none focus:ring-1 focus:ring-zinc-400 dark:focus:ring-zinc-600 resize-none"
                    />
                  </div>

                  <button
                    type="submit"
                    className="w-full sm:w-auto inline-flex items-center justify-center gap-2 px-5 py-2.5 rounded-lg bg-zinc-900 text-white dark:bg-zinc-100 dark:text-zinc-950 hover:bg-zinc-800 dark:hover:bg-zinc-200 text-sm font-medium transition-colors shadow-xs"
                  >
                    <Send className="w-3.5 h-3.5" />
                    Send Message
                  </button>
                </form>
              )}
            </div>
          </div>
        </div>
      </div>
    </section>
  );
}
