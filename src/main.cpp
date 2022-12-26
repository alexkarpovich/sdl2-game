#include "SDL2/SDL.h"
#include "Game.h"

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char** args) {

    Uint32 frameStart, frameTime;
    Game* g_game = TheGame::Instance();
    
    if (!g_game->init("Chapter 1", 100, 100, 720, 480, false)) {

        std::cout << "Game init failure - " << SDL_GetError() << "\n";
        
        return EXIT_FAILURE;

    }
    
    while (g_game->running()) {
        frameStart = SDL_GetTicks();
        
        g_game->handleEvents();
        g_game->update();
        g_game->render();

        frameTime = SDL_GetTicks() - frameStart;

        if (frameTime < DELAY_TIME) {
            SDL_Delay((int)(DELAY_TIME - frameTime));
        }        
    }

    g_game->clean();
    
    return EXIT_SUCCESS;
    
}
