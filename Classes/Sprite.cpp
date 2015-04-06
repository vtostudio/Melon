//
//  Sprite.cpp
//  PenguinSlice
//
//  Created by lxc on 13-12-10.
//
//

#include "Sprite.h"

using namespace cocos2d;

Sprite::Sprite(){
    density = 2.0f;
    friction = 0.1f;
    isRemove = false;
    parPlist = "PigPar.plist";
}

Sprite* Sprite::create(const char* name){
    Sprite* sprite = new Sprite();
	sprite->name = name;
    CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(name);
    sprite->initWithSpriteFrame(pFrame);
    sprite->autorelease();
    return sprite;
}

void Sprite::createStaticBody(b2World *world){

    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(getPositionX() / PTM_RATIO, getPositionY() / PTM_RATIO);
    
    b2Body* body = world->CreateBody(&bodyDef);
    body->SetTransform(body->GetPosition(), CC_DEGREES_TO_RADIANS(-1 * getRotation()));
	
    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    float w = getContentSize().width * getScaleX() / 2.0f;
    float h = getContentSize().height * getScaleY() / 2.0f;
    dynamicBox.SetAsBox(w / PTM_RATIO, h / PTM_RATIO);

    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.friction = friction;
    body->CreateFixture(&fixtureDef);
    body->SetUserData(this);
}

void Sprite::createCircleBody(b2World *world){
    
    b2BodyDef bodyDef2;
    bodyDef2.type = density > 0 ? b2_dynamicBody : b2_staticBody;
    bodyDef2.position.Set(getPositionX() / PTM_RATIO, getPositionY() / PTM_RATIO);
    
    b2Body *body = world->CreateBody(&bodyDef2);
    
    b2CircleShape circleBox;
    float r = getContentSize().width * getScale() / 2.0f;
    circleBox.m_radius = r / PTM_RATIO;//These are mid points for our 1m box
    
    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef2;
    fixtureDef2.shape = &circleBox;
    fixtureDef2.density = density;
    fixtureDef2.friction = friction;
    body->CreateFixture(&fixtureDef2);
    body->SetUserData(this);
}

void Sprite::createRectBody(b2World *world){
    
    b2BodyDef bodyDef;
    bodyDef.type = density > 0 ? b2_dynamicBody : b2_staticBody;
    bodyDef.position.Set(getPositionX() / PTM_RATIO, getPositionY() / PTM_RATIO);
    
    b2Body* body = world->CreateBody(&bodyDef);
    body->SetTransform(body->GetPosition(), CC_DEGREES_TO_RADIANS(-1 * getRotation()));
    
    // Define another box shape for our dynamic body.
    b2PolygonShape dynamicBox;
    float w = getContentSize().width * getScaleX() / 2.0f;
    float h = getContentSize().height * getScaleY() / 2.0f;
    dynamicBox.SetAsBox(w / PTM_RATIO, h / PTM_RATIO);
    
    // Define the dynamic body fixture.
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = density;
    fixtureDef.friction = friction;
    body->CreateFixture(&fixtureDef);
    body->SetUserData(this);
}

void Sprite::createShapeBody(b2World *world, const char *name){
    
    b2BodyDef bodyDef;
    bodyDef.type = density > 0 ? b2_dynamicBody : b2_staticBody;
    bodyDef.position.Set(getPositionX() / PTM_RATIO, getPositionY() / PTM_RATIO);
    
    b2Body* body = world->CreateBody(&bodyDef);
    body->SetTransform(body->GetPosition(), CC_DEGREES_TO_RADIANS(-1 * getRotation()));
    
    GB2ShapeCache::sharedGB2ShapeCache()->addFixturesToBody(body, name);
    
    body->SetUserData(this);
}


