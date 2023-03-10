#include "Player.h"
#include "InputHandler.h"

Player::Player(const LoaderParams* pParams) : SDLGameObject(pParams)
{

}

void Player::draw() 
{ 
    SDLGameObject::draw();
}

void Player::update() 
{
    m_velocity.setX(0);
    m_velocity.setY(0);

    handleInput();

    //m_currentFrame = int((SDL_GetTicks() / 100) % 6);

    SDLGameObject::update();
}

void Player::clean() 
{ 
    SDLGameObject::clean();
}

void Player::handleInput()
{
    int val;
    InputHandler* inputHandler = TheInputHandler::Instance();

    if (inputHandler->joysticksInitialized()) {
        val = inputHandler->xvalue(0, 1);

        if (val != 0) {
            m_velocity.setX(1 * val);
        }

        val = inputHandler->yvalue(0, 1);
        if (val != 0) {
            m_velocity.setY(1 * val);
        }

        val = inputHandler->xvalue(0, 2);
        if (val != 0) {
            m_velocity.setX(1 * val);
        }

        val = inputHandler->yvalue(0, 2);
        if (val != 0) {
            m_velocity.setY(1 * val);
        }

        if (inputHandler->getButtonState(0, 3)) {
            m_velocity.setX(1);
        }

        if (inputHandler->getMouseButtonState(LEFT)) {
            m_velocity.setX(1);
        }
    }

    Vector2D* vec = inputHandler->getMousePosition();
    m_velocity = (*vec - m_position) / 100;

    if (inputHandler->isKeyDown(SDL_SCANCODE_RIGHT)) {
        m_velocity.setX(2);
    }

    if (inputHandler->isKeyDown(SDL_SCANCODE_LEFT)) {
        m_velocity.setX(-2);
    }

    if (inputHandler->isKeyDown(SDL_SCANCODE_UP)) {
        m_velocity.setY(-2);
    }

    if (inputHandler->isKeyDown(SDL_SCANCODE_DOWN)) {
        m_velocity.setY(2);
    }
}