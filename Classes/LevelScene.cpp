//
//  LevelScene.cpp
//  PenguinSlice
//
//  Created by lxc on 13-12-2.
//
//

#include "LevelScene.h"

using namespace cocos2d;

LevelLayer::LevelLayer(){

	setKeypadEnabled(false);

	init(1);
    
    pages = (N_LEVEL - 1) / N + 1;
    
    CCSprite* back = CCSprite::createWithSpriteFrameName("Back.png");
    back->setPosition(ccp(LSPoint.x + 55, LSCenter.y + 265));
    back->setTag(TAG_BACK);
	back->setScale(1.3f);
    addSprite(back, true);
    
    int levelLock = UserDefault->getIntegerForKey(KEY_LEVEL_LOCK, DEFAULT_LEVEL_LOCK);

    float fsize = (LSSize.width - 400) / 4.0f;
    for(int i = 1; i <= N_LEVEL; i++){
        int n = (i - 1) % N;
        float fwidth = LSSize.width * ((i - 1) / N - CP + 1);
        float x = LSCenter.x + (n % 5 - 2) * fsize + fwidth;
        float y = LSCenter.y + 160 - n / 5 * 150;
        if(i > levelLock){
            CCSprite* lock = CCSprite::createWithSpriteFrameName("LevelLock.png");
            lock->setPosition(ccp(x, y + 5));
            lock->setTag(i);
            addSprite(lock);
        }else{
            CCSprite* level = CCSprite::createWithSpriteFrameName("LevelPass.png");
            level->setPosition(ccp(x, y + 5));
            level->setTag(i);
            addSprite(level, true);
            
            if(i < 10){
                CCString* sln = CCString::createWithFormat("N%i.png", i);
                CCSprite* ln = CCSprite::createWithSpriteFrameName(sln->getCString());
                ln->setPosition(ccp(50, 50));
                level->addChild(ln);
            }else{
                CCString* sln1 = CCString::createWithFormat("N%i.png", i / 10);
                CCSprite* ln1 = CCSprite::createWithSpriteFrameName(sln1->getCString());
                ln1->setPosition(ccp(36.5f, 50));
                level->addChild(ln1);
                
                CCString* sln2 = CCString::createWithFormat("N%i.png", i % 10);
                CCSprite* ln2 = CCSprite::createWithSpriteFrameName(sln2->getCString());
                ln2->setPosition(ccp(63.5f, 50));
                level->addChild(ln2);
            }
            
            if(i < levelLock){
                CCSprite* ok = CCSprite::createWithSpriteFrameName("Ok.png");
                ok->setPosition(ccp(65.0f, 35.0f));
				ok->setScale(0.8f);
                level->addChild(ok);
            }
        }
    }
    if(pages > 1){
        float px = (pages - 1) * 15;
        for(int i = 1; i <= pages; i++){
            CCSprite* wp = CCSprite::createWithSpriteFrameName(i == CP ? "CurrentPage.png" : "Page.png");
            wp->setPosition(ccp(LSCenter.x - px + (i - 1) * 30, LSCenter.y - 230));
            wp->setTag(N_LEVEL + i);
            addSprite(wp);
        }
    
        CCSprite* forward = CCSprite::createWithSpriteFrameName("Next.png");
        forward->setPosition(ccp(LSPoint.x + LSSize.width - 100, LSCenter.y + 10));
        forward->setTag(TAG_FORWARD);
        forward->setVisible(CP < pages ? true : false);
        addSprite(forward, true);
    
        CCSprite* backward = CCSprite::createWithSpriteFrameName("Previous.png");
        backward->setPosition(ccp(LSPoint.x + 100, LSCenter.y + 10));
        backward->setTag(TAG_BACKWARD);
        backward->setVisible(CP > 1 ? true : false);
        addSprite(backward, true);
    }
    
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (!Global::share()->IsSigned2) {
        AudioEngine->end();
        CCDirector::sharedDirector()->end();
    }
    #endif
}

CCScene* LevelLayer::scene(){
    
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // add layer as a child to scene
    CCLayer* layer = new LevelLayer();
    scene->addChild(layer);
    layer->release();
    
    return scene;
}

void LevelLayer::ccTouchesBegan(CCSet* touches, CCEvent* event){
    BaseLayer::ccTouchesBegan(touches, event);
    if(touches->count() == 1){
        CCTouch* touch = (CCTouch*)touches->anyObject();
        CCPoint p = CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
        mLastX = p.x;
        mLastX2 = p.x;
    }
}

void LevelLayer::ccTouchesMoved(CCSet* touches, CCEvent* event){
    BaseLayer::ccTouchesMoved(touches, event);
    if(touches->count() == 1){
        CCTouch* touch = (CCTouch*)touches->anyObject();
        CCPoint p = CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
        if(!getSprite() && !isRunActions()){
            float dx = p.x - mLastX;
            if(dx > 0 && CP == 1){
                float sx = getSpriteByTag(1 + (CP - 1) * N)->getPositionX();
                if(sx + dx >= LSPoint.x + 352){
                    dx = LSPoint.x + 352 - sx;
                }
            }else if(dx < 0 && CP == pages){
                float sx = getSpriteByTag(1 + (CP - 1) * N)->getPositionX();
                if(sx + dx < LSPoint.x + 48){
                    dx = LSPoint.x + 48 - sx;
                }
            }
            if(dx != 0){
                for(int i = 1; i <= N_LEVEL; i++){
                    CCSprite* sprite = getSpriteByTag(i);
                    sprite->setPositionX(sprite->getPositionX() + dx);
                }
            }
        }
        mLastX2 = mLastX;
        mLastX = p.x;
    }
}

void LevelLayer::ccTouchesEnded(CCSet* touches, CCEvent* event){
    if(touches->count() == 1){
        CCTouch* touch = (CCTouch*)touches->anyObject();
        CCPoint p = CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
        if(getSprite() &&!getSprite()->boundingBox().containsPoint(p)){
            setSprite(NULL);
        }
        CCSprite* sprite = getSprite();
        if(sprite){
            if (SOUND) {
                AudioEngine->playEffect(MP3_CLICK);
            }
            sprite->setScale(sprite->getScale() / 1.1f);
            switch (sprite->getTag()) {
                case TAG_BACK:
                    keyBackClicked();
                    break;
                case TAG_FORWARD:{
                    if(!isRunActions()){
                        changePage(1, -LSSize.width);
                    }
                }
                    break;
                case TAG_BACKWARD:{
                    if(!isRunActions()){
                        changePage(-1, LSSize.width);
                    }
                }
                    break;
                default:{
                    CL = sprite->getTag();
                    CCTransitionFade* sc = CCTransitionFade::create(1.2f, GameLayer::scene());
                    CCDirector::sharedDirector()->replaceScene(sc);
                }
                    break;
            }
            setSprite(NULL);
        }else if(!isRunActions()){
            float sx = getSpriteByTag(1 + (CP - 1) * N)->getPositionX();
            float vt =  p.x - mLastX2;
            if(vt > 5 && CP > 1){
                changePage(-1, LSPoint.x + 200 + LSSize.width - sx);
            }else if( vt < -5 && CP < pages){
                changePage(1, LSPoint.x + 200 - LSSize.width - sx);
            }else{
                float mincx = LSPoint.x + 48;
                float maxcx = LSPoint.x + 352;
                if(sx >= mincx && sx <= maxcx){
                    changePage(0, LSPoint.x + 200 - sx);
                }else if(sx < mincx){
                    changePage(1, LSPoint.x + 200 - LSSize.width - sx);
                }else if(sx > maxcx){
                    changePage(-1, LSPoint.x + 200 + LSSize.width - sx);
                }
            }
        }
    }
}

void LevelLayer::keyBackClicked(){
	UserDefault->setIntegerForKey(KEY_CURRENT_PAGE, CP);
    CCTransitionFade* sc = CCTransitionFade::create(1.2f, MainLayer::scene());
    CCDirector::sharedDirector()->replaceScene(sc);
}

void LevelLayer::changePage(int step, float dx){
    
    if (step != 0) {
        CP = MAX(CP + step, 1);
        CP = MIN(CP, pages);
        
        getSpriteByTag(TAG_FORWARD)->setVisible(CP < pages ? true : false);
        getSpriteByTag(TAG_BACKWARD)->setVisible(CP > 1 ? true : false);
        
        CCSprite* sp = getSpriteByTag(N_LEVEL + CP - step);
        sp->setDisplayFrame(SpriteFrame->spriteFrameByName("Page.png"));
        CCSprite* csp = getSpriteByTag(N_LEVEL + CP);
        csp->setDisplayFrame(SpriteFrame->spriteFrameByName("CurrentPage.png"));
    }
    
    for(int i = 1; i <= N_LEVEL; i++){
        CCMoveBy* moveBy = CCMoveBy::create(abs(dx) / LSSize.width, ccp(dx, 0));
        getSpriteByTag(i)->runAction(moveBy);
    }
}

bool LevelLayer::isRunActions(){
    for(int i = 1; i <= N_LEVEL; i++){
        if(getSpriteByTag(i)->numberOfRunningActions() > 0){
            return true;
        }
    }
    return false;
}

