#ifndef Enemy_h
#define Enemy_h

#include <stdio.h>
#include <iostream>
#include "LoaderParams.h"
#include "SDLGameObject.h"

class Enemy : public SDLGameObject
{
public:
    Enemy(const LoaderParams* pParams);

    virtual void draw();
    virtual void update();
    virtual void clean();
};

#endif /* Enemy_h */
