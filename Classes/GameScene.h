//
//  GameScene.h
//  PenguinSlice
//
//  Created by lxc on 13-12-7.
//
//

#ifndef __PenguinSlice__GameScene__
#define __PenguinSlice__GameScene__

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "Global.h"
#include "BaseLayer.h"
#include "LevelScene.h"
#include "ContactListener.h"
#include "Sprite.h"
#include "GB2ShapeCache-x.h"
#include "DialogLayer.h"

class GameLayer : public BaseLayer{
public:
    GameLayer();
    ~GameLayer();
    
    static cocos2d::CCScene* scene();
    
    void initSprites();
    void initPhysics();
    
    void update(float dt);
    
    virtual void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    virtual void ccTouchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    virtual void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    virtual void onEnterTransitionDidFinish();

    virtual void keyBackClicked();
    
    void createSprites();
    
private:
    b2World* world;
	int mCount;
    long timeCount;
    
    bool isDotted;
};

#endif /* defined(__PenguinSlice__GameScene__) */
