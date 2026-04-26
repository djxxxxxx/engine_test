#include "Game.h"

#include "../engine/Engine.h"

namespace Game
{

bool init()
{
    if (!Core::init())
    {
        return false;
    }

    Renderer::Renderer *quad = new Renderer::Renderer("shader/basic.vert", "shader/basic.frag");
    Renderer::setVertices(quad, sizeof(BaseObject::quad), BaseObject::quad);
    Core::_rendererList.push_back(quad);

    Renderer::Renderer *cube = new Renderer::Renderer("shader/cube.vert", "shader/cube.frag");
    Renderer::setVertices(cube, sizeof(BaseObject::cube), BaseObject::cube);
    cube->mvpLoc = glGetUniformLocation(cube->program, "mvp");
    Core::_rendererList.push_back(cube);

    return true;
}

void run()
{
    Core::loop();
}

void quit()
{
    Core::quit();
}

} // namespace Game