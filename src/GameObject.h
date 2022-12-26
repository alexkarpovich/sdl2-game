//
//  Game.h
//  SDL2 window
//
//  Created by Aliaksandr on 21.12.22.
//

#ifndef GameObject_h
#define GameObject_h

#include "LoaderParams.h"

class GameObject
{
public:
    virtual void draw()=0;
    virtual void update()=0;
    virtual void clean()=0;
    
protected:
    GameObject(const LoaderParams* pParams) {}
    virtual ~GameObject() {}
};

#endif /* GameObject_h */
