#ifndef InputHandler_h
#define InputHandler_h

#include <stdio.h>
#include <iostream>
#include <utility>
#include <vector>
#include <SDL2/SDL.h>
#include "Vector2D.h"

enum mouse_buttons
{
    LEFT = 1,
    MIDDLE = 1,
    RIGHT = 2
};

class InputHandler
{
public:
    static InputHandler* Instance();

    void update();
    void clean();
    void initializeJoysticks();
    bool joysticksInitialized() { return m_bJoysticksInitialized; }
    int xvalue(int joy, int stick);
    int yvalue(int joy, int stick);
    bool getButtonState(int joy, int buttonNumber);
    bool getMouseButtonState(int buttonNumber);
    Vector2D* getMousePosition();
    bool isKeyDown(SDL_Scancode key);

private:
    InputHandler();
    ~InputHandler() {};

    // handle keybord events;
    void onKeyDown();
    void onKeyUp();

    // handle mouse events
    void onMouseMove(SDL_Event& event);
    void onMouseButtonDown(SDL_Event& event);
    void onMouseButtonUp(SDL_Event& event);

    // handle joysticks events
    void onJoystickAxisMove(SDL_Event& event);
    void onJoystickButtonDown(SDL_Event& event);
    void onJoystickButtonUp(SDL_Event& event);


    static InputHandler* s_pInstance;
    std::vector<SDL_Joystick*> m_joysticks;
    std::vector<std::pair<Vector2D*, Vector2D*>> m_joystickValues;
    std::vector<std::vector<bool>> m_buttonStates;
    std::vector<bool> m_mouseButtonStates;
    Vector2D* m_mousePosition;
    Uint8* m_keystates;
    
    bool m_bJoysticksInitialized;
    const int m_joystickDeadZone = 10000;
};

typedef InputHandler TheInputHandler;

#endif /* InputHandler_h */
