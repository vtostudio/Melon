//
//  DialogLayer.h
//  PenguinSlice
//
//  Created by lxc on 14-3-19.
//
//

#ifndef __PenguinSlice__DialogLayer__
#define __PenguinSlice__DialogLayer__

#include "cocos2d.h"
#include "Global.h"
#include "GameScene.h"
#include "PassScene.h"

class DialogLayer : public cocos2d::CCLayerColor{
public:
    DialogLayer();
    ~DialogLayer();
    
    static DialogLayer* create();
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
    virtual void ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
    virtual void ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
    virtual void onExit();
    
    cocos2d::CCSprite* getSprite();
    void setSprite(cocos2d::CCSprite* mSprite);
    void addSprite(cocos2d::CCSprite* mSprite);
    void addSprite(cocos2d::CCSprite* mSprite, bool isTouch);
    cocos2d::CCSprite* getSpriteByTag(int tag);
    void removeSprite(cocos2d::CCSprite* mSprite);
	cocos2d::CCSprite* createSpriteByNumber(int n);
    
    void initSuccessDialog();
    void initFailedDialog();
    void initPauseDialog();
private:
    cocos2d::CCArray* mSprites;
    cocos2d::CCSprite* mSprite;
};


#endif /* defined(__PenguinSlice__DialogLayer__) */
