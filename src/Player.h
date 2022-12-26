#ifndef Player_h
#define Player_h

#include <stdio.h>
#include <iostream>
#include "LoaderParams.h"
#include "SDLGameObject.h"

class Player : public SDLGameObject
{
public:
    Player(const LoaderParams* pParams);

    virtual void draw();
    virtual void update();
    virtual void clean();

    void handleInput();
};

#endif /* Player_h */
