#include "Game.h"
#include "InputHandler.h"

Game* Game::s_pInstance = 0;

Game* Game::Instance()
{
    if (s_pInstance == 0) {
        s_pInstance = new Game();
    }

    return s_pInstance;
}

bool Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;
    
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "SDL init success\n";
        
        m_pWindow = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        
        if (m_pWindow != 0) {
            std::cout << "window creation success\n";
            
            m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, 0);
            
            if (m_pRenderer != 0) {
                std::cout << "renderer creation success\n";
                SDL_SetRenderDrawColor(m_pRenderer, 255, 0, 0, 255);
            } else {
                std::cout << "renderer init failed\n";
                return false;
            }
        } else {
            std::cout << "window init failed\n";
            return false;
        }
    } else {
        std::cout << "SDL init failed\n";
        return false;
    }

    if (!TheTextureManager::Instance()->load("assets/donkey.png", "donkey", m_pRenderer)) {
        return false;
    }

    if (!TheTextureManager::Instance()->load("assets/duck.bmp", "duck", m_pRenderer)) {
        return false;
    }

    TheInputHandler::Instance()->initializeJoysticks();

    Player* player = new Player(new LoaderParams(300, 300, 128, 128, "donkey"));
    Enemy* enemy = new Enemy(new LoaderParams(0, 0, 128, 128, "duck"));
    
    m_gameObjects.push_back(player);
    m_gameObjects.push_back(enemy);

    std::cout << "init success\n";
    m_bRunning = true;
    
    return true;
}

void Game::render()
{
    
    SDL_RenderClear(m_pRenderer);
    
    for (std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++) {
        m_gameObjects[i]->draw();
    }
    
    SDL_RenderPresent(m_pRenderer);
    
}

void Game::update() 
{

    m_currentFrame =int((SDL_GetTicks() / 100) % 6);
    for (std::vector<GameObject*>::size_type i = 0; i != m_gameObjects.size(); i++) {
        m_gameObjects[i]->update();
    }

}

void Game::handleEvents()
{
    TheInputHandler::Instance()->update();
}

void Game::clean()
{
    std::cout << "cleaning game\n";
    TheInputHandler::Instance()->clean();
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}

SDL_Renderer* Game::getRenderer() const
{
    return m_pRenderer;
}