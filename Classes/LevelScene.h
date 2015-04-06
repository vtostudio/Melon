//
//  LevelScene.h
//  PenguinSlice
//
//  Created by lxc on 13-12-2.
//
//

#ifndef __PenguinSlice__LevelScene__
#define __PenguinSlice__LevelScene__

#include "cocos2d.h"
#include "BaseLayer.h"
#include "Global.h"
#include "MainScene.h"
#include "GameScene.h"

#define N     15

class LevelLayer : public BaseLayer{
public:
    LevelLayer();
    
    static cocos2d::CCScene* scene();
    
    virtual void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    virtual void ccTouchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    virtual void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    
    virtual void keyBackClicked();
    
    void changePage(int step, float dx);
    
    bool isRunActions();
    
private:
    int pages;
    
    float mLastX;
    float mLastX2;
};


#endif /* defined(__PenguinSlice__LevelScene__) */
