//
//  Game.h
//  SDL2 window
//
//  Created by Aliaksandr on 21.12.22.
//

#ifndef Game_h
#define Game_h

#include <stdio.h>
#include <iostream>
#include <SDL2/SDL.h>

class Game
{
public:
    Game() {};
    ~Game() {};
    
    bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void render();
    void update();
    void handleEvents();
    void clean();
    
    bool running() { return m_bRunning; }
    
private:
    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;
    SDL_Texture* m_pTexture;
    SDL_Rect m_sourceRect;
    SDL_Rect m_destRect;
    
    bool m_bRunning;
};

#endif /* Game_h */
