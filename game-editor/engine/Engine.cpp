#include "Engine.h"
#include <emscripten.h>
#include <emscripten/bind.h>
#include <iostream>



bool Engine::Initialize(const std::string& elementId)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) 
        return false;

    SDL_SetHint(SDL_HINT_EMSCRIPTEN_KEYBOARD_ELEMENT, elementId.c_str());

    window = SDL_CreateWindow("WASM", 0, 0, GAME_WIDTH, GAME_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) 
        return false;

#ifdef __EMSCRIPTEN__
    if (!mainLoopRegistered) {
        emscripten_set_main_loop_arg([](void* arg) {static_cast<Engine*>(arg)->Render();},this,0,false);
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

void Engine::Render()
{
    if (!renderer) 
        return;

    int w, h;
    SDL_GetWindowSize(window, &w, &h);

    float scale = static_cast<float>(w) / GAME_WIDTH;
    int scaled_height = static_cast<int>(GAME_HEIGHT * scale);
    int y_offset = (h - scaled_height) / 2;

    SDL_RenderClear(renderer);


    

    ecs.for_each(ecs.CreateMask<RenderComponent>(), [this](ecs::Entity e, std::function<void*(ecs::TypeId)> getComponent) 
    {
        RenderComponent* rc = reinterpret_cast<RenderComponent*>(getComponent(ecs::getTypeId<RenderComponent>()));
        if (rc->render) 
        {
            SDL_Vertex vert[3];
            auto x = rc->mesh;
            //for(auto x : rc->mesh)
            //{
                vert[0].position.x = x.v1.x;
                vert[0].position.y = x.v1.y;
                vert[0].color = x.color;
                vert[1].position.x = x.v2.x;
                vert[1].position.y = x.v2.y;
                vert[1].color = x.color;
                vert[2].position.x = x.v3.x;
                vert[2].position.y = x.v3.y;
                vert[2].color = x.color;
                SDL_RenderGeometry(renderer, nullptr, vert, 3, nullptr, 0);
                ecs.get(e);
                std::cout << "Rendered triangle for entity " << e << ' ' << x.v1.x << ' ' << x.v1.y <<  std::endl;
           // }
        }
    });

    SDL_RenderPresent(renderer);
}

void Engine::AddTriangle()
{
    ecs::Entity entity = ecs.create_entity();

    Triangle tri;
    tri.v1 = {0.5f * GAME_WIDTH, 0.25f * GAME_HEIGHT};
    tri.v2 = {0.25f * GAME_WIDTH, 0.75f * GAME_HEIGHT};
    tri.v3 = {0.75f * GAME_WIDTH, 0.25f * GAME_HEIGHT};
    tri.color = {255, 0, 0, 255};

    // std::vector<Triangle> mesh = { tri };

    RenderComponent rc(true, tri);

    ecs.add_component<RenderComponent>(entity, rc);
}



EMSCRIPTEN_BINDINGS(engine_module)
{
    emscripten::class_<Engine>("Engine")
        .constructor<>()
        .function("Initialize", &Engine::Initialize)
        .function("Render", &Engine::Render)
        .function("AddTriangle", &Engine::AddTriangle);
}
