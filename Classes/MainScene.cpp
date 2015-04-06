//
//  MainScene.cpp
//  PenguinSlice
//
//  Created by lxc on 13-11-26.
//
//

#include "MainScene.h"

using namespace cocos2d;

MainLayer::MainLayer(){
    
    init(0);
    
    CCSprite* title = CCSprite::createWithSpriteFrameName("Title.png");
    title->setPosition(ccp(LSCenter.x, LSCenter.y + 150));
	title->setScale(1.2f);
    addSprite(title);

    CCSprite* play = CCSprite::createWithSpriteFrameName("Play.png");
    play->setPosition(ccp(LSCenter.x, LSCenter.y - 80));
    play->setTag(TAG_PLAY);
    addSprite(play, true);
    
    CCSprite* sound = CCSprite::createWithSpriteFrameName(SOUND ? "TurnOn.png" : "TurnOff.png");
    sound->setPosition(ccp(LSPoint.x + 55, LSCenter.y + 265));
    sound->setTag(TAG_SOUND);
	sound->setScale(1.3f);
    addSprite(sound, true);

	CCSprite* close = CCSprite::createWithSpriteFrameName("Close.png");
    close->setPosition(ccp(LSPoint.x + LSSize.width - 55, LSCenter.y + 265));
    close->setTag(TAG_CLOSE);
	close->setScale(1.3f);
    addSprite(close, true);
	
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (!Global::share()->IsSigned) {
		DialogLayer* dialog = DialogLayer::create();
		dialog->initPauseDialog();
		addChild(dialog, 101);
    }
    #endif
}

CCScene* MainLayer::scene(){
    
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // add layer as a child to scene
    CCLayer* layer = new MainLayer();
    scene->addChild(layer);
    layer->release();
    
    return scene;
}

void MainLayer::ccTouchesEnded(CCSet* touches, CCEvent* event){
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
                case TAG_PLAY:{
                    CCTransitionFade* sc = CCTransitionFade::create(1.2f, LevelLayer::scene());
                    CCDirector::sharedDirector()->replaceScene(sc);
                }
                    break;
                case TAG_SOUND:{
                    SOUND = !SOUND;
                    CCSpriteFrame* frame = SpriteFrame->spriteFrameByName(SOUND ? "TurnOn.png" : "TurnOff.png");
                    sprite->setDisplayFrame(frame);
					
					UserDefault->setBoolForKey(KEY_SOUND, SOUND);
                }
                    break;
				case TAG_CLOSE:{
                    keyBackClicked();
                }
					break;
            }
            setSprite(NULL);
        }
    }
}

void MainLayer::keyBackClicked(){
    AudioEngine->end();
    CCDirector::sharedDirector()->end();
}