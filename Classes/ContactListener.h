//
//  ContactListener.h
//  PenguinSlice
//
//  Created by lxc on 13-11-18.
//
//

#ifndef __PenguinSlice__ContactListener__
#define __PenguinSlice__ContactListener__

#include "Box2D/Box2D.h"
#include "cocos2d.h"
#include "Sprite.h"
#include "GameScene.h"

class ContactListener : public b2ContactListener{
public:
    virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
    
	void doContact(Sprite* sprite, float force);
};

#endif /* defined(__PenguinSlice__ContactListener__) */
