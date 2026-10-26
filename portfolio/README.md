# Amiel Keith Padilla — Developer Portfolio

A clean, modern, minimal portfolio site built with **Next.js 16 (App Router)** and **Tailwind CSS v4**, designed with a refined Vercel/Linear aesthetic.

---

## ✨ Features & Highlights

- **Aesthetic**: Minimalist monochromatic and slate palette with subtle borders, glowing status indicators, and clean typography.
- **Dark / Light Mode**: Seamless theme toggle syncing with system preferences and local storage persistence.
- **Interactive Terminal**: Unix/DOS-inspired interactive CLI terminal preview allowing visitors to run commands (`help`, `projects`, `skills`, `about`, `contact`) or click quick pills.
- **Featured Systems Projects**: Detailed showcase of authentic academic projects:
  - **Lossless Huffman Compression Engine** (C++17, bitwise streams, FNV-1a 64-bit verification)
  - **Bank & ATM Account System** (C++, Doubly Linked List, CSV persistence)
  - **x86 Bare-Metal Assembly Suite** (16-bit 8086, VGA Mode 13h graphics, traffic light controller)
  - **Binary Expression Tree & Syntax Parser** (C++, recursive arithmetic evaluator)
  - **PanataanPH**: Donation-drive verification with local AI evidence extraction and human review; separate from the fitness HCI work.
  - **HCI Fitness & Wellness Prototype** and **HCI Wireframe**: Separate implementation and design deliverables supported by the local `COMPROG 1&2/HCI WIREFRAME.make` archive.
  - **Procedural 3D Maze Explorer**, **Arithmetic Quiz & Leaderboard**, **Sorted Student Records Manager**, and **Python JSON Records Manager**: Additional projects selected from local coursework.
- **Interactive Code Inspector Modal**: Inspect architecture details, metrics, and formatted source code snippets with 1-click copy.
- **Technical Skills Matrix**: Categorized breakdown across Languages, Systems & Architecture, Data Structures & Algorithms, and Modern Web.
- **Education & Milestones**: Formal BSIT academic journey, coursework, and focus areas.
- **LinkedIn Background**: GDG on Campus TUP Manila leadership roles, TUP BSIT education (2025–2029), listed security/AI skills, and certifications from the supplied profile PDF. Certificate issuers and dates are omitted because the export does not include them.
- **Contact & Direct Actions**: Email copy with success/error feedback, a form that opens a prefilled draft in the visitor's email app, and direct GitHub links. Visitors review and send the email themselves; the site does not claim delivery.

---

## 🚀 Getting Started

### 1. Development Server
Run the local development server:

```bash
cd portfolio
npm run dev
```

Open [http://localhost:3000](http://localhost:3000) in your browser.

### 2. Production Build
Create an optimized production build:

```bash
cd portfolio
npm run build
npm run start
```

### Browser check

With the production server running on port 3001 and Playwright available to Node
(directly or through `NODE_PATH`), run:

```bash
node scripts/check-portfolio.cjs http://localhost:3001
```

Checks terminal scrolling, project filters, dialog keyboard/focus behavior,
clipboard feedback, encoded email drafts, theme persistence, mobile navigation,
320px/390px layouts, and reduced motion. Screenshots go into `.next/`.

---

## 📁 Project Structure

```
portfolio/
├── src/
│   ├── app/
│   │   ├── globals.css         # Tailwind CSS v4 styling & dark mode setup
│   │   ├── layout.tsx          # Root metadata, font styling, and shell
│   │   └── page.tsx            # Main portfolio page assembly
│   ├── components/
│   │   ├── Navbar.tsx          # Minimal fixed navigation & theme toggle
│   │   ├── ThemeToggle.tsx     # Light/Dark mode switcher
│   │   ├── Hero.tsx            # Hero presentation with stats & terminal
│   │   ├── TerminalPreview.tsx # Interactive developer CLI widget
│   │   ├── Projects.tsx        # Filterable project cards
│   │   ├── ProjectModal.tsx    # Code & architecture inspector dialog
│   │   ├── Skills.tsx          # Categorized technical capabilities
│   │   ├── Education.tsx       # BSIT academic path & milestones
│   │   ├── Contact.tsx         # Email copy & contact form
│   │   ├── Footer.tsx          # Minimalist footer
│   │   └── icons/              # Custom optimized SVGs (GitHub)
│   └── data/
│       └── portfolioData.ts    # Centralized portfolio data & content
├── package.json
├── tsconfig.json
└── next.config.ts
```

---

## 🛠 Customizing Information

All personal details, projects, code snippets, skills, and coursework are located in a single file:
👉 **[`src/data/portfolioData.ts`](./src/data/portfolioData.ts)**

You can easily update your email, GitHub link, add new projects, or modify skill levels there without touching the UI components.
