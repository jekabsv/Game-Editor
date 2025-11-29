// #include <emscripten.h>
// #include <emscripten/bind.h>
// #include "SDL.h"
// #include <vector>
// #include <string>

// #ifndef SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT
// #define SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT "SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT"
// #endif

// const int GAME_WIDTH = 1920;
// const int GAME_HEIGHT = 1080;

// SDL_Window* window = nullptr;
// SDL_Renderer* renderer = nullptr;
// static bool mainLoopRegistered = false;

// struct Vec2 { float x, y; };

// std::vector<Vec2> triangle = {  
//     {0.5f, 0.25f},
//     {0.25f, 0.75f},
//     {0.75f, 0.75f}
// };

// // Optional: Vertex structure for SDL_RenderGeometry
// struct Vertex {
//     float x, y;
//     SDL_Color color;
// };

// void render_frame() 
// {
//     if (!renderer) 
//         return;

//     int w, h;
//     SDL_GetWindowSize(window, &w, &h);

//     float scale = static_cast<float>(w) / GAME_WIDTH;
//     int scaled_height = static_cast<int>(GAME_HEIGHT * scale);
//     int y_offset = (h - scaled_height) / 2;

//     SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
//     SDL_RenderClear(renderer);

//     // Prepare vertices
//     Vertex verts[3];
//     for (int i = 0; i < 3; i++) {
//         verts[i].x = triangle[i].x * GAME_WIDTH * scale;
//         verts[i].y = triangle[i].y * GAME_HEIGHT * scale + y_offset;
//         verts[i].color = {255, 0, 0, 255}; // Red
//     }

//     // Draw triangle using SDL_RenderGeometry
//     SDL_Vertex sdlVerts[3];
//     for (int i = 0; i < 3; i++) {
//         sdlVerts[i].position.x = verts[i].x;
//         sdlVerts[i].position.y = verts[i].y;
//         sdlVerts[i].color = verts[i].color;
//         sdlVerts[i].tex_coord = {0,0};
//     }

//     SDL_RenderGeometry(renderer, nullptr, sdlVerts, 3, nullptr, 0);

//     SDL_RenderPresent(renderer);
// }

// bool init(const std::string& elementId) 
// {
//     if (SDL_Init(SDL_INIT_VIDEO) != 0) return false;

//     SDL_SetHint(SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT, elementId.c_str());

//     window = SDL_CreateWindow("WASM", 0, 0, GAME_WIDTH, GAME_HEIGHT, SDL_WINDOW_SHOWN);
//     if (!window) return false;

// #ifdef __EMSCRIPTEN__
//     if (!mainLoopRegistered) {
//         emscripten_set_main_loop(render_frame, 0, 0);
//         mainLoopRegistered = true;
//     }
//     SDL_GL_SetSwapInterval(1);
// #endif

//     renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
// #ifdef __EMSCRIPTEN__
//     emscripten_set_main_loop_timing(1, 1);
// #endif
//     return renderer != nullptr;
// }

// EMSCRIPTEN_BINDINGS(engine_module) 
// {
//     emscripten::function("initInElement", &initInElement);
//     emscripten::function("render_frame", &render_frame);
// }
