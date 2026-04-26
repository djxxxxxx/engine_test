#include "game.h"

// #undef main
int main()
{
    if (Game::init())
    {
        Game::run();
    }

    Game::quit();

    return 0;
}
