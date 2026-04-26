#include "Engine.h"
#include "SDL2/SDL_events.h"
#include "SDL2/SDL_video.h"

#include <SDL2/SDL.h>
#include <glad/glad.h>

namespace Core
{

bool _running = true;

SDL_Window *_window = nullptr;
SDL_GLContext _glContext = 0;

std::vector<Renderer::Renderer *> _rendererList;

bool init()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        Log::error("SDL_Init Error: %s", SDL_GetError());
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    _window = SDL_CreateWindow("Blue Point (Shader)", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
    if (!_window)
    {
        Log::error("SDL_CreateWindow Error: %s", SDL_GetError());
        SDL_Quit();
        return false;
    }

    _glContext = SDL_GL_CreateContext(_window);
    if (!_glContext)
    {
        Log::error("SDL_GL_CreateContext Error: %s", SDL_GetError());
        SDL_DestroyWindow(_window);
        SDL_Quit();
        return false;
    }

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        Log::error("Failed to initialize GLAD\n");
        SDL_GL_DeleteContext(_glContext);
        SDL_DestroyWindow(_window);
        SDL_Quit();
        return false;
    }

    Log::info("OpenGL Version: %s", glGetString(GL_VERSION));
    glEnable(GL_DEPTH_TEST);

    return true;
}

void loop()
{
    while (_running)
    {
        input();
        update();
        render();
    }
}

void input()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            _running = false;
            break;
        default:
            break;
        }
    }
}

void update()
{
    static Uint32 lastTick = 0;
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), lastTick + 16))
        ;
    float deltaTime = (SDL_GetTicks() - lastTick) / 1000.0f;
    if (deltaTime > 0.05f)
    {
        deltaTime = 0.05f;
    }
    lastTick = SDL_GetTicks();

    for (auto renderer : _rendererList)
    {
        if (renderer->mvpLoc != -1)
        {
            renderer->rotAngle += deltaTime * 90.0f;
            renderer->model = glm::rotate(glm::mat4(1.0f), glm::radians(renderer->rotAngle), glm::vec3(1.0f, 1.0f, 0.0f));
        }
    }
}

void render()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (auto renderer : _rendererList)
    {
        Renderer::render(renderer);
    }

    SDL_GL_SwapWindow(_window);
}

void quit()
{
    _rendererList.clear();

    SDL_GL_DeleteContext(_glContext);

    if (_window != nullptr)
    {
        SDL_DestroyWindow(_window);
    }

    SDL_Quit();
}

} // namespace Core
