//
//  BaseLayer.h
//  PenguinSlice
//
//  Created by lxc on 13-11-24.
//
//

#ifndef __PenguinSlice__BaseLayer__
#define __PenguinSlice__BaseLayer__

#include "cocos2d.h"
#include "Global.h"

class BaseLayer : public cocos2d::CCLayer{
public:
    BaseLayer();
    ~BaseLayer();
    
    void init(int scence);
    
    cocos2d::CCSprite* getSprite();
    void setSprite(cocos2d::CCSprite* mSprite);
    
    virtual void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    virtual void ccTouchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    
	bool isClick(cocos2d::CCSprite* sprite, cocos2d::CCPoint p);

    cocos2d::CCSprite* createSpriteByNumber(int n);
    cocos2d::CCArray* createSpritesByNumber(int n);
    cocos2d::CCArray* createSpritesByNumber(int n, bool isReverse);
    void addSprite(cocos2d::CCSprite* mSprite);
    void addSprite(cocos2d::CCSprite* mSprite, bool isTouch);
    cocos2d::CCSprite* getSpriteByTag(int tag);
    void removeSprite(cocos2d::CCSprite* mSprite);
	void removeSpriteByTag(int tag);

private:
    cocos2d::CCArray* mSprites;
    cocos2d::CCSprite* mSprite;
    
};

#endif /* defined(__PenguinSlice__BaseLayer__) */
