import type { Metadata } from "next";
import "./globals.css";

export const metadata: Metadata = {
  title: "Amiel Keith Padilla | Software Developer & BSIT Student",
  description:
    "Portfolio of Amiel Keith Padilla — Systems programming, Algorithms, C++, x86 Assembly, and Modern Web Development.",
};

export default function RootLayout({
  children,
}: {
  children: React.ReactNode;
}) {
  return (
    <html lang="en" suppressHydrationWarning>
      <body className="min-h-screen bg-white text-zinc-900 dark:bg-zinc-950 dark:text-zinc-100 font-sans antialiased transition-colors duration-200">
        {children}
      </body>
    </html>
  );
}
