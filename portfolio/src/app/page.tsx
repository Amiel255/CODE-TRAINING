import { Navbar } from "@/components/Navbar";
import { Hero } from "@/components/Hero";
import { Projects } from "@/components/Projects";
import { Skills } from "@/components/Skills";
import { Education } from "@/components/Education";
import { Contact } from "@/components/Contact";
import { Footer } from "@/components/Footer";

export default function Home() {
  return (
    <div className="min-h-screen flex flex-col bg-white text-zinc-900 dark:bg-zinc-950 dark:text-zinc-100 font-sans selection:bg-zinc-200 dark:selection:bg-zinc-800">
      <Navbar />
      <main className="flex-1">
        <Hero />
        <Projects />
        <Skills />
        <Education />
        <Contact />
      </main>
      <Footer />
    </div>
  );
}
