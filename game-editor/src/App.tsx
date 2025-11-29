import { useState, useEffect, useRef } from 'react';
import engine_Module from "../wasm/engine.mjs";

interface WasmModule {
  test: () => string;
  Engine: any; // class exported from Emscripten
  canvas?: HTMLCanvasElement | string | null;
}

let wasmModule: WasmModule | null = null;

function App() {
  const [insertLocked, setInsertLocked] = useState(false);
  const [insertHovered, setInsertHovered] = useState(false);

  const toggleInsertLock = () => setInsertLocked(!insertLocked);

  const engineRef = useRef<any | null>(null);
  const initRef = useRef(false);

  useEffect(() => {
    engine_Module().then((Module: WasmModule) => {
      wasmModule = Module;
      const canvas = document.getElementById('canvas') as HTMLCanvasElement | null;
      if (canvas) wasmModule.canvas = canvas;
    }).catch((err: unknown) => console.error('Failed to load wasm module', err));
  }, []);

  const handleAddTriangle = () => {
    if (!wasmModule) {
      console.log("No WASM module found!");
      return;
    }

    try {
      let canvas = document.getElementById('canvas') as HTMLCanvasElement | null;
      if (!canvas) {
        const parent = document.querySelector('#preview-canvas');
        if (parent) {
          canvas = document.createElement('canvas');
          canvas.id = 'canvas';
          canvas.style.width = '100%';
          canvas.style.height = '100%';
          parent.appendChild(canvas);
        }
      }

      if (canvas && wasmModule) {
        wasmModule.canvas = canvas;
      }

      // create engine instance once
      if (!engineRef.current) {
        engineRef.current = new wasmModule.Engine();
      }

      const engine = engineRef.current;

      // initialize once
      if (!initRef.current) {
        const ok = engine.Initialize("#preview-canvas");
        console.log('Initialize returned', ok);
        initRef.current = true;
      }

      // add triangle
      engine.AddTriangle();

      // render frame
      engine.Render();
    } catch (err) {
      console.error('handleAddTriangle failed:', err);
    }
  };

  const insertOpen = insertLocked || insertHovered;

  return (
    <div className="h-screen flex flex-col bg-gray-900 text-white">
      {/* Top Bar */}
      <div className="flex items-center bg-gray-800 p-2 shadow-md">
        <button className="px-4 py-1 hover:bg-gray-700 rounded">File</button>
        <button className="px-4 py-1 hover:bg-gray-700 rounded">Edit</button>

        {/* Insert with hover + click toggle */}
        <div
          className="relative"
          onMouseEnter={() => setInsertHovered(true)}
          onMouseLeave={() => setInsertHovered(false)}
        >
          <button
            onClick={toggleInsertLock}
            className="px-4 py-1 hover:bg-gray-700 rounded"
          >
            Insert
          </button>

          {insertOpen && (
            <div className="absolute top-full left-0 mt-1 w-40 bg-gray-700 rounded shadow-lg z-10">
              <button
                onClick={handleAddTriangle}
                className="w-full text-left px-4 py-2 hover:bg-gray-600 rounded"
              >
                Add Triangle
              </button>
            </div>
          )}
        </div>

        <button className="px-4 py-1 hover:bg-gray-700 rounded">Other</button>
      </div>

      {/* Main Content */}
      <div className="flex flex-1">
        {/* Left Panel */}
        <div className="w-64 bg-gray-800 p-2">
          {/* Empty for now */}
        </div>

        {/* Middle / Preview Area */}
        <div className="flex-1 bg-gray-900 flex items-center justify-center">
          {/* SDL / WASM canvas will be attached to this element by initInElement */}
          <div id="preview-canvas" className="w-full h-[540px] bg-gray-800 rounded border border-gray-700 flex items-center justify-center">
            {/* Add a real canvas early so Emscripten can register event handlers without errors */}
            <canvas id="canvas" className="w-full h-full" />
            <div className="absolute text-center pointer-events-none">
              <p className="text-gray-500"></p>
            </div>
          </div>
        </div>

        {/* Right Panel */}
        <div className="w-64 bg-gray-800 p-2">
          {/* Empty for now */}
        </div>
      </div>
    </div>
  );
}

export default App;
