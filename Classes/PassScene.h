//
//  PassScene.h
//
//  Created by lxc on 13-12-2.
//
//

#ifndef __PenguinSlice__PassScene__
#define __PenguinSlice__PassScene__

#include "cocos2d.h"
#include "BaseLayer.h"
#include "Global.h"
#include "LevelScene.h"

class PassLayer : public BaseLayer{
public:
    PassLayer();
    
    static cocos2d::CCScene* scene();
    
    virtual void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    virtual void ccTouchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    virtual void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    
    virtual void keyBackClicked();

	void hand(float dt);
};


#endif /* defined(__PenguinSlice__PassScene__) */
