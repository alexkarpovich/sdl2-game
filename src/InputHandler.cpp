#include "InputHandler.h"
#include "Game.h"

InputHandler* InputHandler::s_pInstance = 0;

InputHandler::InputHandler()
{
    m_mousePosition = new Vector2D(0, 0);

    for (int i = 0; i < 3; i++) {
        m_mouseButtonStates.push_back(false);
    }
}

InputHandler* InputHandler::Instance()
{
    if (s_pInstance == 0) {
        s_pInstance = new InputHandler();
    }

    return s_pInstance;
}

void InputHandler::initializeJoysticks()
{
    if (SDL_WasInit(SDL_INIT_JOYSTICK) == 0) {
        SDL_InitSubSystem(SDL_INIT_JOYSTICK);
    }

    if (SDL_NumJoysticks() > 0) {
        for (int i = 0; i < SDL_NumJoysticks(); i++) {
            SDL_Joystick* joy = SDL_JoystickOpen(i);
        
            if (joy) {
                m_joysticks.push_back(joy);
                m_joystickValues.push_back(std::make_pair(
                    new Vector2D(0, 0), new Vector2D(0, 0)
                ));

                std::vector<bool> tempButtons;

                for (int j = 0; j < SDL_JoystickNumButtons(joy); j++) {
                    tempButtons.push_back(false);
                }

                m_buttonStates.push_back(tempButtons);
            } else {
                std::cout << SDL_GetError();
            }
        }

        SDL_JoystickEventState(SDL_ENABLE);
        m_bJoysticksInitialized = true;

        std::cout << "Initialized " << m_joysticks.size() << " joystick(s)";
    } else {
        m_bJoysticksInitialized = false;
    }
}

void InputHandler::update()
{
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        m_keystates = (Uint8 *) SDL_GetKeyboardState(0);

        switch (event.type) {
        case SDL_QUIT: 
            TheGame::Instance()->quit();
            break;
        case SDL_JOYAXISMOTION:
            onJoystickAxisMove(event);
            break;
        case SDL_JOYBUTTONDOWN:
            onJoystickButtonDown(event);
            break;
        case SDL_JOYBUTTONUP:
            onJoystickButtonUp(event);
            break;
        case SDL_MOUSEMOTION:
            onMouseMove(event);
            break;
        case SDL_MOUSEBUTTONDOWN:
            onMouseButtonDown(event);
            break;
        case SDL_MOUSEBUTTONUP:
            onMouseButtonUp(event);
            break;
        case SDL_KEYDOWN:
            onKeyDown();
            break;
        case SDL_KEYUP:
            onKeyUp();
            break;
        default:
            break;
        }
    }
}

void InputHandler::clean()
{}

int InputHandler::xvalue(int joy, int stick)
{
    if (m_joystickValues.size() > 0) {
        if (stick == 1) {
            return m_joystickValues[joy].first->getX();
        } else if (stick == 2) {
            return m_joystickValues[joy].second->getX();
        }
    }

    return 0;
}

int InputHandler::yvalue(int joy, int stick)
{
    if (m_joystickValues.size() > 0) {
        if (stick == 1) {
            return m_joystickValues[joy].first->getY();
        } else if (stick == 2) {
            return m_joystickValues[joy].second->getY();
        }
    }

    return 0;
}

bool InputHandler::getButtonState(int joy, int buttonNumber)
{
    return m_buttonStates[joy][buttonNumber];
}

bool InputHandler::getMouseButtonState(int buttonNumber)
{
    return m_mouseButtonStates[buttonNumber];
}

Vector2D* InputHandler::getMousePosition()
{
    return m_mousePosition;
}

bool InputHandler::isKeyDown(SDL_Scancode key)
{
    if (m_keystates != 0) {
        return m_keystates[key] == 1;
    }

    return false;
}

void InputHandler::onKeyDown()
{}
void InputHandler::onKeyUp()
{}

void InputHandler::onMouseMove(SDL_Event& event) 
{
    if (event.type == SDL_MOUSEMOTION) {
            m_mousePosition->setX(event.motion.x);
            m_mousePosition->setY(event.motion.y);
        }
}

void InputHandler::onMouseButtonDown(SDL_Event& event)
{
    if (event.type == SDL_MOUSEBUTTONDOWN) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            m_mouseButtonStates[LEFT] = true;
        }

        if (event.button.button == SDL_BUTTON_MIDDLE) {
            m_mouseButtonStates[MIDDLE] = true;
        }

        if (event.button.button == SDL_BUTTON_RIGHT) {
            m_mouseButtonStates[RIGHT] = true;
        }
    }
}

void InputHandler::onMouseButtonUp(SDL_Event& event)
{
    if (event.type == SDL_MOUSEBUTTONUP) {
        if (event.button.button == SDL_BUTTON_LEFT) {
            m_mouseButtonStates[LEFT] = false;
        }

        if (event.button.button == SDL_BUTTON_MIDDLE) {
            m_mouseButtonStates[MIDDLE] = false;
        }

        if (event.button.button == SDL_BUTTON_RIGHT) {
            m_mouseButtonStates[RIGHT] = false;
        }
    }
}

void InputHandler::onJoystickAxisMove(SDL_Event& event)
{
    if (event.type == SDL_JOYAXISMOTION) {
        int whichOne = event.jaxis.which;
        int value = 0;

        // left stick moves left and right
        if (event.jaxis.axis == 0) {
            if (event.jaxis.value > m_joystickDeadZone) {
                value = 1;
            } else if (event.jaxis.value < -m_joystickDeadZone) {
                value = -1;
            }

            m_joystickValues[whichOne].first->setX(value);
        }

        // left stick moves up and down
        if (event.jaxis.axis == 1) {
            if (event.jaxis.value > m_joystickDeadZone) {
                value = 1;
            } else if (event.jaxis.value < -m_joystickDeadZone) {
                value = -1;
            }

            m_joystickValues[whichOne].first->setY(value);
        }

        // right stick moves left and right
        if (event.jaxis.axis == 3) {
            if (event.jaxis.value > m_joystickDeadZone) {
                value = 1;
            } else if (event.jaxis.value < -m_joystickDeadZone) {
                value = -1;
            }
            
            m_joystickValues[whichOne].second->setY(value);
        }

        // right stick moves up and down
        if (event.jaxis.axis == 4) {
            if (event.jaxis.value > m_joystickDeadZone) {
                value = 1;
            } else if (event.jaxis.value < -m_joystickDeadZone) {
                value = -1;
            }
            
            m_joystickValues[whichOne].second->setY(value);
        }
    }
}

void InputHandler::onJoystickButtonDown(SDL_Event& event)
{
    if (event.type == SDL_JOYBUTTONDOWN) {
        int whichOne = event.jaxis.which;

        m_buttonStates[whichOne][event.jbutton.button] = true;
    }
}
void InputHandler::onJoystickButtonUp(SDL_Event& event)
{
    if (event.type == SDL_JOYBUTTONUP) {
        int whichOne = event.jaxis.which;

        m_buttonStates[whichOne][event.jbutton.button] = false;
    }
}