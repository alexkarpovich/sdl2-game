#ifndef Game_h
#define Game_h

#include <stdio.h>
#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "LoaderParams.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Player.h"
#include "Enemy.h"

class Game
{
public:
    ~Game() {};
    static Game* Instance();
    
    bool init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void render();
    void update();
    void handleEvents();
    void clean();
    void quit() { m_bRunning = false; };
    SDL_Renderer* getRenderer() const;
    
    bool running() { return m_bRunning; }
    
private:
    Game() {};

    static Game* s_pInstance;

    SDL_Window* m_pWindow;
    SDL_Renderer* m_pRenderer;
    std::vector<GameObject*> m_gameObjects;

    int m_currentFrame;
    bool m_bRunning;
};

typedef Game TheGame;

#endif /* Game_h */
