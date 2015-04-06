//
//  PassScene.cpp
//  PenguinSlice
//
//  Created by lxc on 13-12-2.
//
//

#include "PassScene.h"

using namespace cocos2d;

PassLayer::PassLayer(){

	setKeypadEnabled(false);

	init(2);
    
    CCSprite* back = CCSprite::createWithSpriteFrameName("Menu.png");
    back->setPosition(ccp(LSPoint.x + 55, LSCenter.y + 265));
    back->setTag(TAG_BACK);
	back->setScale(1.3f);
    addSprite(back, true);
    
	CCSprite* title = CCSprite::createWithSpriteFrameName("GameCompleted.png");
    title->setPosition(ccp(LSCenter.x, LSCenter.y + 200));
    title->setScale(2.5f);
    addSprite(title);

	CCSprite* cup = CCSprite::createWithSpriteFrameName("Cup.png");
    cup->setPosition(ccp(LSCenter.x, LSCenter.y - 60));
    cup->setScale(2.0f);
    addSprite(cup);

	CCParticleSystemQuad* par = CCParticleSystemQuad::create("Success.plist");
	par->setPosition(ccp(LSCenter.x, LSCenter.y + 200));
	this->addChild(par);
	par->setAutoRemoveOnFinish(true);

	schedule(schedule_selector(PassLayer::hand), 3.0f);

}

CCScene* PassLayer::scene(){
    
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // add layer as a child to scene
    CCLayer* layer = new PassLayer();
    scene->addChild(layer);
    layer->release();
    
    return scene;
}

void PassLayer::ccTouchesBegan(CCSet* touches, CCEvent* event){
    BaseLayer::ccTouchesBegan(touches, event);
}

void PassLayer::ccTouchesMoved(CCSet* touches, CCEvent* event){
    BaseLayer::ccTouchesMoved(touches, event);
}

void PassLayer::ccTouchesEnded(CCSet* touches, CCEvent* event){
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
            }
            setSprite(NULL);
        }
    }
}

void PassLayer::keyBackClicked(){
    CCTransitionFade* sc = CCTransitionFade::create(1.2f, LevelLayer::scene());
    CCDirector::sharedDirector()->replaceScene(sc);
}

void PassLayer::hand(float dt){CCLOG("......");
	int n = (int)(CCRANDOM_0_1() * 80);
	float x = n * 10 - 400;
	n = (int)(CCRANDOM_0_1() * 28);
	float y = n * 10;
	CCParticleSystemQuad* par = CCParticleSystemQuad::create("Success.plist");
	par->setPosition(ccp(LSCenter.x + x, LSCenter.y + y));
	this->addChild(par);
	par->setAutoRemoveOnFinish(true);
}
