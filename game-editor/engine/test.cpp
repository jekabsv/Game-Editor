#include <emscripten/bind.h>
#include <string>

std::string test() 
{
    return "hello world!";
}

EMSCRIPTEN_BINDINGS(my_module) 
{
    emscripten::function("test", &test);
}

///SDL

#include <emscripten.h>
#include <emscripten/bind.h>
#include <SDL/SDL.h>
#include <vector>
#include <string>

#ifndef SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT
#define SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT "SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT"
#endif



const int GAME_WIDTH = 1920;
const int GAME_HEIGHT = 1080;

SDL_Window* window = nullptr;
SDL_Renderer* renderer = nullptr;

static bool mainLoopRegistered = false;

struct Vec2 { float x, y; };
std::vector<Vec2> triangle = {  
    {0.5f, 0.25f},
    {0.25f, 0.75f},
    {0.75f, 0.75f}
};

void render_frame() {
    if (!renderer) return;

    int w, h;
    SDL_GetWindowSize(window, &w, &h);

    float scale = static_cast<float>(w) / GAME_WIDTH;
    int scaled_height = static_cast<int>(GAME_HEIGHT * scale);
    int y_offset = (h - scaled_height) / 2;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (int i = 0; i < 3; i++) 
    {
        Vec2 a = triangle[i];
        Vec2 b = triangle[(i + 1) % 3];

        int x1 = static_cast<int>(a.x * GAME_WIDTH * scale);
        int y1 = static_cast<int>(a.y * GAME_HEIGHT * scale + y_offset);
        int x2 = static_cast<int>(b.x * GAME_WIDTH * scale);
        int y2 = static_cast<int>(b.y * GAME_HEIGHT * scale + y_offset);

        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    }

    SDL_RenderPresent(renderer);
}



bool initInElement(const std::string& elementId) 
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
        return false;
    SDL_SetHint(SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT, elementId.c_str());

    window = SDL_CreateWindow("WASM", 0, 0, GAME_WIDTH, GAME_HEIGHT, SDL_WINDOW_SHOWN);

    if (!window) 
        return false;


#ifdef __EMSCRIPTEN__
    if (!mainLoopRegistered) 
    {
        emscripten_set_main_loop(render_frame, 0, 0);
        mainLoopRegistered = true;
    }

    SDL_GL_SetSwapInterval(1);
#endif
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
#ifdef __EMSCRIPTEN__
    emscripten_set_main_loop_timing(1, 1);
#endif
    return renderer != nullptr;
}

EMSCRIPTEN_BINDINGS(engine_module) 
{
    emscripten::function("initInElement", &initInElement);
    emscripten::function("render_frame", &render_frame);
}
