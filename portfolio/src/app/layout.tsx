import type { Metadata } from "next";
import "./globals.css";

export const metadata: Metadata = {
  title: "Amiel Keith Padilla | BSIT Student & Cybersecurity Core Lead",
  description:
    "Amiel Keith Padilla — BSIT student at the Technological University of the Philippines and Cybersecurity Core Lead at GDG on Campus TUP Manila. Explore systems, web, and HCI projects.",
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
