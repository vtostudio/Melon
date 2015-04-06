//
//  ContactListener.cpp
//  PenguinSlice
//
//  Created by lxc on 13-11-18.
//
//

#include "ContactListener.h"

using namespace cocos2d;

void ContactListener::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse)
{
    /*float force = impulse->normalImpulses[0];
	int count = contact->GetManifold()->pointCount;
	for (int i = 1; i < count; i++){
		force = b2Max(force, impulse->normalImpulses[i]);
	} */
    Sprite* a = (Sprite*)contact->GetFixtureA()->GetBody()->GetUserData();
    Sprite* b = (Sprite*)contact->GetFixtureB()->GetBody()->GetUserData();
	if(a && b && ((a->type == TYPE_KNIFT && b->type == TYPE_MELON) || (b->type == TYPE_KNIFT && a->type == TYPE_MELON))){
		if(a->type == TYPE_MELON){
			a->isRemove = true;
		}else if(b->type == TYPE_MELON){
			b->isRemove = true;
		}
	}
}