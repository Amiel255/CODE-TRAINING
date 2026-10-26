// Run against a production server: NODE_PATH=<Playwright installation>/node_modules node scripts/check-portfolio.cjs
const assert = require("node:assert/strict");
const { chromium } = require("playwright");

(async () => {
  const browser = await chromium.launch({ headless: true });
  try {
    const page = await browser.newPage({ viewport: { width: 1440, height: 1000 } });
    const errors = [];
    page.on("pageerror", (error) => errors.push(error.message));
    await page.addInitScript(() => {
      Object.defineProperty(navigator, "clipboard", {
        value: { writeText: async (text) => {
          if (window.denyClipboard) throw new Error("Clipboard denied");
          window.copiedText = text;
        } },
      });
    });
    await page.goto(process.argv[2] || "http://localhost:3001", { waitUntil: "networkidle" });
    await page.screenshot({ path: ".next/check-desktop.png" });
    assert.equal(await page.evaluate(() => window.scrollY), 0, "Terminal must not scroll the page on load");
    const titles = await page.locator("#projects h3").allTextContents();
    assert.equal(new Set(titles).size, titles.length, "Project cards must be distinct");
    for (const title of ["Procedural 3D Maze Explorer", "Arithmetic Quiz & Leaderboard", "Sorted Student Records Manager", "Python JSON Records Manager"]) {
      assert.ok(titles.includes(title), `Missing local project: ${title}`);
    }
    await page.locator("#about").getByText(String(titles.length), { exact: true }).waitFor();
    await page.getByRole("button", { name: "projects", exact: true }).click();
    const output = await page.getByRole("log").innerText();
    titles.forEach((title) => assert.ok(output.includes(title), `Terminal missing ${title}`));
    assert.equal(await page.evaluate(() => window.scrollY), 0, "Terminal commands must keep page position");

    await page.getByRole("button", { name: "Web & HCI", exact: true }).click();
    assert.deepEqual(await page.locator("#projects h3").allTextContents(), [
      "PanataanPH — Donation Drive Verification",
      "HCI Project — Fitness & Wellness Prototype",
      "HCI Wireframe — Fitness & Wellness UX",
    ]);
    for (const [title, source, snippets] of [
      ["PanataanPH — Donation Drive Verification", "https://github.com/strob3/panataanph-hackathon-2026", 0],
      ["HCI Project — Fitness & Wellness Prototype", "https://github.com/Amiel255/CODE-TRAINING/blob/main/COMPROG%201%262/HCI%20WIREFRAME.make", 1],
      ["HCI Wireframe — Fitness & Wellness UX", "https://github.com/Amiel255/CODE-TRAINING/blob/main/COMPROG%201%262/HCI%20WIREFRAME.make", 0],
    ]) {
      await page.getByRole("button", { name: `Inspect architecture: ${title}`, exact: true }).click();
      const details = page.getByRole("dialog");
      await details.getByRole("heading", { name: title, exact: true }).waitFor();
      assert.equal(await details.getByRole("link", { name: "View Source on GitHub" }).getAttribute("href"), source);
      assert.equal(await details.locator("pre").count(), snippets);
      await page.keyboard.press("Escape");
      await details.waitFor({ state: "detached" });
    }
    await page.getByRole("button", { name: "Python", exact: true }).click();
    assert.deepEqual(await page.locator("#projects h3").allTextContents(), ["Python JSON Records Manager"]);

    await page.getByRole("button", { name: "Assembly", exact: true }).click();
    assert.equal(await page.getByRole("button", { name: "Assembly", exact: true }).getAttribute("aria-pressed"), "true");
    assert.ok(await page.locator("#projects h3").count() < titles.length);
    const inspect = page.getByRole("button", { name: /^Inspect architecture:/ }).first();
    await inspect.click();
    const dialog = page.getByRole("dialog");
    await dialog.waitFor();
    await dialog.getByRole("button", { name: "Copy snippet" }).click();
    await dialog.getByRole("button", { name: "Copied", exact: true }).waitFor();
    assert.equal(await page.evaluate(() => window.copiedText), await dialog.locator("pre").innerText());
    assert.ok(await page.evaluate(() => document.querySelector("dialog").contains(document.activeElement)));
    for (const key of ["Tab", "Shift+Tab"]) {
      for (let i = 0; i < 8; i++) {
        await page.keyboard.press(key);
        assert.ok(await page.evaluate(() => document.querySelector("dialog").contains(document.activeElement)), "Focus must remain in dialog");
      }
    }
    await page.keyboard.press("Escape");
    await dialog.waitFor({ state: "detached" });
    assert.ok(await inspect.evaluate((element) => element === document.activeElement), "Focus must return to opener");
    assert.equal(await page.evaluate(() => document.body.style.overflow), "");
    await inspect.click();
    await dialog.waitFor();
    await dialog.getByRole("button", { name: "Copy snippet" }).waitFor();
    await dialog.click({ position: { x: 5, y: 5 } });
    await dialog.waitFor({ state: "detached" });
    await page.getByRole("button", { name: "All", exact: true }).click();
    assert.equal(await page.locator("#projects h3").count(), titles.length);

    await page.getByRole("button", { name: "Copy Email", exact: true }).click();
    await page.getByRole("button", { name: "Copied!", exact: true }).waitFor();
    assert.equal(await page.evaluate(() => window.copiedText), "amielkeithpadilla5@gmail.com");
    await page.evaluate(() => { window.denyClipboard = true; });
    await page.getByRole("button", { name: "Copy email address", exact: true }).click();
    await page.getByText("Could not copy. Select the email address or use the email link.").waitFor();

    const cdp = await page.context().newCDPSession(page);
    await cdp.send("Page.enable");
    let draftUrl;
    cdp.on("Page.frameRequestedNavigation", ({ url }) => {
      if (url.startsWith("mailto:")) draftUrl = url;
    });
    await page.getByLabel("Your Name").fill("Ada & José");
    await page.getByLabel("Your Email").fill("ada@example.com");
    await page.getByLabel("Message", { exact: true }).fill("Hello & thanks!\nC++ / #systems");
    await page.getByRole("button", { name: "Open Email Draft" }).click();
    await page.getByRole("heading", { name: "Email Draft Prepared" }).waitFor();
    assert.ok(draftUrl, "Submit must open a mailto draft");
    const draft = new URL(draftUrl);
    assert.equal(draft.searchParams.get("subject"), "Portfolio inquiry from Ada & José");
    assert.equal(draft.searchParams.get("body"), "Name: Ada & José\nEmail: ada@example.com\n\nHello & thanks!\nC++ / #systems");
    await page.getByRole("button", { name: "Edit message" }).click();
    assert.equal(await page.getByLabel("Your Name").inputValue(), "Ada & José");
    assert.equal(await page.getByLabel("Message", { exact: true }).inputValue(), "Hello & thanks!\nC++ / #systems");

    await page.getByRole("button", { name: "Toggle theme" }).click();
    const theme = await page.evaluate(() => localStorage.getItem("theme"));
    await page.reload({ waitUntil: "networkidle" });
    assert.equal(await page.evaluate(() => document.documentElement.classList.contains("dark")), theme === "dark");
    for (const width of [390, 320]) {
      await page.setViewportSize({ width, height: 844 });
      assert.ok(await page.evaluate(() => document.documentElement.scrollWidth <= window.innerWidth), `Overflow at ${width}px`);
    }
    await page.evaluate(() => window.scrollTo({ top: 0, behavior: "instant" }));
    await page.screenshot({ path: ".next/check-mobile.png" });
    await page.getByRole("button", { name: "Toggle Navigation Menu" }).click();
    await page.getByRole("navigation", { name: "Mobile navigation" }).getByRole("link", { name: "Skills", exact: true }).click();
    assert.equal(await page.getByRole("button", { name: "Toggle Navigation Menu" }).getAttribute("aria-expanded"), "false");
    await page.emulateMedia({ reducedMotion: "reduce" });
    assert.equal(await page.evaluate(() => getComputedStyle(document.documentElement).scrollBehavior), "auto");
    assert.deepEqual(errors, [], "Browser runtime errors");
    console.log("PASS: distinct project cards, source links, project count, terminal, filters, dialog focus/Escape/backdrop, clipboard, email draft, theme, mobile layout/navigation, reduced motion");
  } finally {
    await browser.close();
  }
})().catch((error) => {
  console.error(error);
  process.exitCode = 1;
});
