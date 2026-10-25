const { compile } = require("@tailwindcss/node");
const { Scanner } = require("@tailwindcss/oxide");
const fs = require("fs");
const path = require("path");

const rootDir = path.resolve(__dirname, "..");
const srcDir = path.join(rootDir, "src");
const templateCssPath = path.join(rootDir, "src", "app", "tailwind.source.css");
const outputCssPath = path.join(rootDir, "src", "app", "globals.css");

// Base source CSS if not existing
const baseCss = `@import "tailwindcss";

@variant dark (&:where(.dark, .dark *));

@theme {
  --font-sans: -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, "Helvetica Neue", Arial, sans-serif;
  --font-mono: ui-monospace, SFMono-Regular, Menlo, Monaco, Consolas, "Liberation Mono", "Courier New", monospace;
}
`;

if (!fs.existsSync(templateCssPath)) {
  fs.writeFileSync(templateCssPath, baseCss, "utf8");
}

async function build() {
  const sourceCss = fs.readFileSync(templateCssPath, "utf8");
  const compiler = await compile(sourceCss, {
    from: templateCssPath,
    base: rootDir,
    onDependency: () => {},
  });

  const scanner = new Scanner({
    sources: [
      {
        base: rootDir,
        pattern: "src/**/*.{ts,tsx,js,jsx}",
        negated: false,
      },
    ],
  });

  const candidates = scanner.scan();
  let builtCss = compiler.build(candidates);

  // Custom utilities and scrollbar
  const customStyles = `
/* Custom scrollbar and behavior */
html {
  scroll-behavior: smooth;
}

::-webkit-scrollbar {
  width: 6px;
  height: 6px;
}

::-webkit-scrollbar-track {
  background: transparent;
}

::-webkit-scrollbar-thumb {
  background: rgba(150, 150, 150, 0.25);
  border-radius: 9999px;
}

::-webkit-scrollbar-thumb:hover {
  background: rgba(150, 150, 150, 0.45);
}
`;

  fs.writeFileSync(outputCssPath, builtCss + "\n" + customStyles, "utf8");
  console.log(`[build-css] Successfully compiled ${candidates.length} utility candidates into globals.css`);
}

build().catch((err) => {
  console.error("[build-css] Error:", err);
  process.exit(1);
});
