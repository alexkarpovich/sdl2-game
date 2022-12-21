//
//  Game.cpp
//  SDL2 window
//
//  Created by Aliaksandr on 21.12.22.
//

#include "Game.h"

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
                SDL_SetRenderDrawColor(m_pRenderer, 255, 255, 255, 255);
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
    
    SDL_Surface* pTempSurface = SDL_LoadBMP("assets/duck.bmp");
    
    if (!pTempSurface) {
        std::cout << "SDL load bmp failed\n";
        return false;
    }
    
    m_pTexture = SDL_CreateTextureFromSurface(m_pRenderer, pTempSurface);
    
    SDL_FreeSurface(pTempSurface);
    
    SDL_QueryTexture(m_pTexture, NULL, NULL, &m_sourceRect.w, &m_sourceRect.h);
    m_destRect.x = m_sourceRect.x = 0;
    m_destRect.y = m_sourceRect.y = 0;
    m_destRect.w = m_sourceRect.w = 50;
    m_destRect.h = m_sourceRect.h = 50;
    std::cout << m_sourceRect.w << " " << m_sourceRect.h << "\n";
    
    std::cout << "init success\n";
    m_bRunning = true;
    
    return true;
}

void Game::render()
{
    
    SDL_RenderClear(m_pRenderer);
    
    SDL_RenderCopy(m_pRenderer, m_pTexture, &m_sourceRect, &m_destRect);
    
    SDL_RenderPresent(m_pRenderer);
    
}

void Game::update() {}

void Game::handleEvents()
{
    SDL_Event event;
    
    if (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                m_bRunning = false;
                break;
            default:
                break;
        }
    }
}

void Game::clean()
{
    std::cout << "cleaning game\n";
    SDL_DestroyWindow(m_pWindow);
    SDL_DestroyRenderer(m_pRenderer);
    SDL_Quit();
}
