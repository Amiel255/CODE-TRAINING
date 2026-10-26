"use client";

import { useRef, useState, type PointerEvent } from "react";
import { Code2, ShieldCheck, Layers, Pause, Play } from "lucide-react";

const FOCUS_AREAS = [
  { name: "Systems", icon: Code2, tag: "C++", caption: "C++ · x86 · algorithms", code: "build → compress → verify" },
  { name: "Security", icon: ShieldCheck, tag: "SEC", caption: "Privacy · risk · responsible AI", code: "protect → assess → improve" },
  { name: "Web", icon: Layers, tag: "UI", caption: "React · TypeScript · HCI", code: "design → build → iterate" },
];

export function FocusScene() {
  const [active, setActive] = useState(0);
  const [paused, setPaused] = useState(false);
  const stageRef = useRef<HTMLDivElement>(null);
  const focus = FOCUS_AREAS[active];
  const Icon = focus.icon;

  const resetTilt = () => {
    stageRef.current?.style.removeProperty("--tilt-x");
    stageRef.current?.style.removeProperty("--tilt-y");
  };

  const tilt = (event: PointerEvent<HTMLDivElement>) => {
    if (paused || event.pointerType !== "mouse" || window.matchMedia("(prefers-reduced-motion: reduce)").matches) return;
    const rect = event.currentTarget.getBoundingClientRect();
    event.currentTarget.style.setProperty("--tilt-x", `${12 - ((event.clientY - rect.top) / rect.height - 0.5) * 16}deg`);
    event.currentTarget.style.setProperty("--tilt-y", `${-18 + ((event.clientX - rect.left) / rect.width - 0.5) * 22}deg`);
  };

  return (
    <section className="focus-scene" aria-label="Explore my focus areas" data-paused={paused}>
      <div className="scene-heading">
        <span>Curiosity, in every layer.</span>
        <button
          type="button"
          onClick={() => { setPaused(!paused); resetTilt(); }}
          aria-label={paused ? "Resume 3D animation" : "Pause 3D animation"}
          aria-pressed={paused}
          className="scene-motion"
        >
          {paused ? <Play size={13} /> : <Pause size={13} />}
        </button>
      </div>
      <div ref={stageRef} className="scene-stage" onPointerMove={tilt} onPointerLeave={resetTilt} aria-hidden="true">
        <div className="scene-grid" />
        <div className="scene-float">
          <div className="scene-stack">
            <div className="scene-panel scene-back" />
            <div className="scene-panel scene-middle" />
            <div className="scene-panel scene-front">
              <div className="scene-window"><span /><span /><span /><small>amiel.dev</small></div>
              <Icon className="scene-icon" strokeWidth={1.3} />
              <code>{focus.code}</code>
            </div>
            <span className="scene-tag">{focus.tag}</span>
          </div>
        </div>
      </div>
      <div className="scene-controls" role="group" aria-label="Focus area">
        {FOCUS_AREAS.map((area, index) => (
          <button key={area.name} type="button" aria-pressed={active === index} onClick={() => setActive(index)}>
            {area.name}
          </button>
        ))}
      </div>
      <p className="scene-caption" role="status">{focus.caption}</p>
    </section>
  );
}
