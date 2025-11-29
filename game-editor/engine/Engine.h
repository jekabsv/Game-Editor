#pragma once
#include "ECS.h"
#include "SDL.h"
#include "Struct.h"
#include "RenderComponent.h"
#include <string>
static bool mainLoopRegistered = false;

class Engine 
{
private:
    const int GAME_WIDTH = 1920;
    const int GAME_HEIGHT = 1080;
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
public:
    ecs::ECS ecs;
    
    Engine() = default;
    ~Engine() = default;

    bool Initialize(const std::string& elementId);
    void Update(float deltaTime);
    void Render();
    void AddTriangle();
};