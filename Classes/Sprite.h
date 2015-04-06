//
//  Sprite.h
//  PenguinSlice
//
//  Created by lxc on 13-12-10.
//
//

#ifndef __PenguinSlice__Sprite__
#define __PenguinSlice__Sprite__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "Global.h"
#include "GB2ShapeCache-x.h"

class Sprite : public cocos2d::CCSprite{
public:
    Sprite();
    static Sprite* create(const char* name);
    
    void createStaticBody(b2World* world);
    void createCircleBody(b2World* world);
    void createRectBody(b2World* world);
    void createShapeBody(b2World* world, const char* name);
    void createPolygonBody(b2World* world, cocos2d::CCPointArray* points);
    void updatePolygonBody(b2Body* body, cocos2d::CCPointArray* points);
    
	std::string name;
    int type;
    float density;
    float friction;
    bool isRemove;
    std::string parPlist;
};

#endif /* defined(__PenguinSlice__Sprite__) */
