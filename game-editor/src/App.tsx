import { useState } from 'react';

function App() {
  const [insertLocked, setInsertLocked] = useState(false);
  const [insertHovered, setInsertHovered] = useState(false);

  const toggleInsertLock = () => setInsertLocked(!insertLocked);

  const handleAddCube = () => {
    // Call your C++ WASM function here later
    // EngineModule.addCube();
    console.log('smth');
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
                onClick={handleAddCube}
                className="w-full text-left px-4 py-2 hover:bg-gray-600 rounded"
              >
                Add Cube
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
          <p className="text-gray-500">Preview Area</p>
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
