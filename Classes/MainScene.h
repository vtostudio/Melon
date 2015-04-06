//
//  MainScene.h
//  PenguinSlice
//
//  Created by lxc on 13-11-26.
//
//

#ifndef __PenguinSlice__MainScene__
#define __PenguinSlice__MainScene__

#include "cocos2d.h"
#include "BaseLayer.h"
#include "Global.h"
#include "LevelScene.h"
#include "MD5.h"

class MainLayer : public BaseLayer{
public:
    MainLayer();
    
    static cocos2d::CCScene* scene();
    
    virtual void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    
    virtual void keyBackClicked();

};

#endif /* defined(__PenguinSlice__MainScene__) */
