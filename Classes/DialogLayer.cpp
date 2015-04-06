//
//  DialogLayer.cpp
//  PenguinSlice
//
//  Created by lxc on 14-3-19.
//
//

#include "DialogLayer.h"

using namespace cocos2d;

DialogLayer::DialogLayer(){
    
    setTouchEnabled(true);
    setAccelerometerEnabled(true);
    
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -129, true);
    
    CCTexture2D* texture = CCTextureCache::sharedTextureCache()->textureForKey("Sprite.png");
    CCSpriteBatchNode* nodes = CCSpriteBatchNode::createWithTexture(texture);
    nodes->setTag(TAG_NODES);
    this->addChild(nodes);
    
    mSprite = NULL;
    mSprites = CCArray::create();
    mSprites->retain();
}

DialogLayer::~DialogLayer(){
    CC_SAFE_RELEASE(mSprites);
    CC_SAFE_RELEASE(mSprite);
}

DialogLayer* DialogLayer::create(){
    DialogLayer* dialog = new DialogLayer();
    if (dialog && dialog->initWithColor(ccc4(60, 60, 60, 200))){
        dialog->autorelease();
    }else{
        CC_SAFE_DELETE(dialog);
    }
    return dialog;
}

bool DialogLayer::ccTouchBegan(CCTouch *touch, CCEvent *event){
    CCPoint p = CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
    for(int i = 0; i < mSprites->count(); i++){
        CCSprite* sprite = (CCSprite*)mSprites->objectAtIndex(i);
        if(sprite->isVisible() && sprite->boundingBox().containsPoint(p)){
            sprite->setScale(sprite->getScale() * 1.1f);
            setSprite(sprite);
            break;
        }
    }
    return true;
}

void DialogLayer::ccTouchMoved(CCTouch *touch, CCEvent *event){
    CCPoint p = CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
    CCSprite* sprite = getSprite();
    if(sprite && !sprite->boundingBox().containsPoint(p)){
        sprite->setScale(sprite->getScale() / 1.1f);
        setSprite(NULL);
    }
}

void DialogLayer::ccTouchEnded(CCTouch *touch, CCEvent *event){
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
            case TAG_RESET:{
                CCTransitionFade* sc = CCTransitionFade::create(1.2f, GameLayer::scene());
                CCDirector::sharedDirector()->replaceScene(sc);
            }
                break;
            case TAG_MENU:{
                CCTransitionFade* sc = CCTransitionFade::create(1.2f, LevelLayer::scene());
                CCDirector::sharedDirector()->replaceScene(sc);
            }
                break;
            case TAG_NEXT_LEVEL:{
				if(CL == N_LEVEL){
					CCTransitionFade* sc = CCTransitionFade::create(1.2f, PassLayer::scene());
					CCDirector::sharedDirector()->replaceScene(sc);
				}else{
					CL = CL + 1;
					CCTransitionFade* sc = CCTransitionFade::create(1.2f, GameLayer::scene());
					CCDirector::sharedDirector()->replaceScene(sc);
				}
				CP = (CL - 1) / N + 1;
            }
                break;
            case TAG_CLOSE:{
				AudioEngine->end();
				CCDirector::sharedDirector()->end();
            }
                break;
            default:{
            }
                break;
        }
        setSprite(NULL);
    }
}

void DialogLayer::onExit(){
	 CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

CCSprite* DialogLayer::getSprite(){
    return mSprite;
}

void DialogLayer::setSprite(CCSprite* sprite){
    
    CC_SAFE_RELEASE(mSprite);
    CC_SAFE_RETAIN(sprite);
    mSprite = sprite;
}


void DialogLayer::addSprite(CCSprite* sprite){
    addSprite(sprite, false);
}

void DialogLayer::addSprite(CCSprite* sprite, bool isTouch){
    CCSpriteBatchNode* nodes = (CCSpriteBatchNode*)this->getChildByTag(TAG_NODES);
    nodes->addChild(sprite);
    if(isTouch){
        mSprites->addObject(sprite);
    }
}

CCSprite* DialogLayer::getSpriteByTag(int tag){
    CCSpriteBatchNode* nodes = (CCSpriteBatchNode*)this->getChildByTag(TAG_NODES);
    return (CCSprite*)nodes->getChildByTag(tag);
}

void DialogLayer::removeSprite(CCSprite* sprite){
    CCSpriteBatchNode* nodes = (CCSpriteBatchNode*)this->getChildByTag(TAG_NODES);
    nodes->removeChild(sprite, true);
}

CCSprite* DialogLayer::createSpriteByNumber(int n){
    CCArray* nums = CCArray::create();
    if(n >= 0){
        while(true){
            CCString* sn = CCString::createWithFormat("N%i.png", n % 10);
            nums->addObject(CCSprite::createWithSpriteFrameName(sn->getCString()));
			
            if(n < 10){
                break;
            }
            n = n / 10;
        }
		nums->reverseObjects();
    }
    CCSprite* spri = CCSprite::createWithSpriteFrameName("Lipid.png");
    for(int i = 0; i < nums->count(); i++){
        CCSprite* s = (CCSprite*)nums->objectAtIndex(i);
        s->setPosition(ccp(i * 8, 10));
        s->setScale(0.32f);
        spri->addChild(s);
    }
    return spri;
}


void DialogLayer::initSuccessDialog(){
	
	CCParticleSystemQuad* par = CCParticleSystemQuad::create("Success.plist");
	par->setPosition(ccp(LSCenter.x - 350, LSCenter.y + 50));
	this->addChild(par);
	par->setAutoRemoveOnFinish(true);

	CCParticleSystemQuad* par2 = CCParticleSystemQuad::create("Success.plist");
	par2->setPosition(ccp(LSCenter.x + 350, LSCenter.y + 50));
	this->addChild(par2);
	par2->setAutoRemoveOnFinish(true);
	
	CCParticleSystemQuad* par3 = CCParticleSystemQuad::create("Success.plist");
	par3->setPosition(ccp(LSCenter.x, LSCenter.y + 280));
	this->addChild(par3);
	par3->setAutoRemoveOnFinish(true);

    CCSprite* background = CCSprite::createWithSpriteFrameName("Dialog.png");
    background->setPosition(LSCenter);
    background->setScale(3);
    addSprite(background);
    
	CCSprite* ltext = CCSprite::createWithSpriteFrameName("Level.png");
	ltext->setPosition(ccp(LSCenter.x - 10, LSCenter.y - 10));
	ltext->setAnchorPoint(ccp(1, 0.5f));
	ltext->setScale(1.6f);
	addSprite(ltext);
	CCSprite* subtext = CCSprite::createWithSpriteFrameName("Sub.png");
	subtext->setPosition(ccp(LSCenter.x + 20, LSCenter.y - 10));
	addSprite(subtext);
    CCSprite* cls = createSpriteByNumber(CL);
	cls->setAnchorPoint(ccp(0, 0.5f));
	cls->setScale(2.4f);
    cls->setPosition(ccp(LSCenter.x +  60, LSCenter.y - 10));
    addSprite(cls);

    CCSprite*  completed = CCSprite::createWithSpriteFrameName("Success.png");
    completed->setPosition(ccp(LSCenter.x, LSCenter.y + 120));
    completed->setScale(1.2);
    addSprite(completed);
    
    CCSprite* reset = CCSprite::createWithSpriteFrameName("Reset.png");
    reset->setPosition(ccp(LSCenter.x - 120, LSCenter.y - 150));
    reset->setTag(TAG_RESET);
    reset->setScale(1.3f);
    addSprite(reset, true);
    
    CCSprite* menu = CCSprite::createWithSpriteFrameName("Menu.png");
    menu->setPosition(ccp(LSCenter.x, LSCenter.y - 150));
    menu->setTag(TAG_MENU);
    menu->setScale(1.3f);
    addSprite(menu, true);
    
    CCSprite* nextLevel = CCSprite::createWithSpriteFrameName("NextLevel.png");
    nextLevel->setPosition(ccp(LSCenter.x + 120, LSCenter.y - 150));
    nextLevel->setTag(TAG_NEXT_LEVEL);
    nextLevel->setScale(1.3f);
    addSprite(nextLevel, true);
}

void DialogLayer::initFailedDialog(){
    CCSprite* background = CCSprite::createWithSpriteFrameName("Dialog.png");
    background->setPosition(LSCenter);
    background->setScale(2);
    addSprite(background);
    
    CCSprite* failed = CCSprite::createWithSpriteFrameName("Failed.png");
    failed->setPosition(ccp(LSCenter.x, LSCenter.y + 95));
    failed->setScale(1.5f);
    addSprite(failed);
    
    CCSprite* piw = CCSprite::createWithSpriteFrameName("Pig5.png");
    piw->setPosition(ccp(LSCenter.x, LSCenter.y - 40));
	piw->setScale(2.0f);
    addSprite(piw);
	CCAnimation* animation = CCAnimation::create();
	animation->addSpriteFrame(SpriteFrame->spriteFrameByName("Pig5.png"));
	animation->addSpriteFrame(SpriteFrame->spriteFrameByName("bPig5.png"));
	animation->setDelayPerUnit(0.6f);
	piw->runAction(CCRepeatForever::create(CCAnimate::create(animation)));
    
    CCSprite* reset = CCSprite::createWithSpriteFrameName("Reset.png");
    reset->setPosition(ccp(LSCenter.x + 120, LSCenter.y - 190));
    reset->setTag(TAG_RESET);
    reset->setScale(1.3f);
    addSprite(reset, true);
    
    CCSprite* menu = CCSprite::createWithSpriteFrameName("Menu.png");
    menu->setPosition(ccp(LSCenter.x - 120, LSCenter.y - 190));
    menu->setTag(TAG_MENU);
    menu->setScale(1.3f);
    addSprite(menu, true);
}

void DialogLayer::initPauseDialog(){
    CCSprite* background = CCSprite::createWithSpriteFrameName("Dialog.png");
    background->setPosition(LSCenter);
    background->setScale(3);
    addSprite(background);
    
    CCSprite* failed = CCSprite::createWithSpriteFrameName("Pirate.png");
    failed->setPosition(ccp(LSCenter.x, LSCenter.y + 100));
    failed->setScale(2.5f);
    addSprite(failed);
    
    CCSprite* close = CCSprite::createWithSpriteFrameName("Close.png");
    close->setPosition(ccp(LSCenter.x, LSCenter.y - 190));
    close->setTag(TAG_CLOSE);
    close->setScale(1.3f);
    addSprite(close, true);
}