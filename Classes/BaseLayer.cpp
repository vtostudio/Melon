//
//  BaseLayer.cpp
//  PenguinSlice
//
//  Created by lxc on 13-11-24.
//
//

#include "BaseLayer.h"

using namespace cocos2d;

BaseLayer::BaseLayer(){
    
    setTouchEnabled(true);
    setAccelerometerEnabled(true);
    setKeypadEnabled(true);
    
    mSprite = NULL;
    mSprites = CCArray::create();
    mSprites->retain();
    
    CCTexture2D* texture = CCTextureCache::sharedTextureCache()->textureForKey("Sprite.png");
    CCSpriteBatchNode* nodes = CCSpriteBatchNode::createWithTexture(texture);
    nodes->setTag(TAG_NODES);
    this->addChild(nodes);
}

BaseLayer::~BaseLayer(){
    CC_SAFE_RELEASE(mSprites);
    CC_SAFE_RELEASE(mSprite);
}

void BaseLayer::init(int scence){

    CCSpriteBatchNode* nodes = (CCSpriteBatchNode*)this->getChildByTag(TAG_NODES);
    CCSprite* background = CCSprite::createWithSpriteFrameName("Bg.png");
    background->setScaleX(LSSize.width / 480.0f);
    background->setScaleY(2.0f);
    background->setPosition(LSCenter);
    nodes->addChild(background);
        
	if(scence == 0){
		CCSprite* left = CCSprite::createWithSpriteFrameName("Left.png");
		left->setPosition(ccp(LSCenter.x - 288, LSCenter.y - 224));
		nodes->addChild(left);
		CCSprite* right = CCSprite::createWithSpriteFrameName("Right.png");
		right->setPosition(ccp(LSCenter.x + 266, LSCenter.y - 214));
		nodes->addChild(right);
	}
}

CCSprite* BaseLayer::getSprite(){
    return mSprite;
}

void BaseLayer::setSprite(CCSprite* sprite){
    
    CC_SAFE_RELEASE(mSprite);
    CC_SAFE_RETAIN(sprite);
    mSprite = sprite;
}

void BaseLayer::ccTouchesBegan(CCSet* touches, CCEvent* event){
    if(touches->count() == 1){
        CCTouch* touch = (CCTouch*)touches->anyObject();
        CCPoint p = CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
        for(int i = mSprites->count() - 1; i >= 0; i--){
            CCSprite* sprite = (CCSprite*)mSprites->objectAtIndex(i);
			//if(sprite->isVisible() && sprite->boundingBox().containsPoint(p)){
			if(isClick(sprite, p)){
				if(sprite->getTag() < 9000){
					sprite->setScale(sprite->getScale() * 1.1f);
				}
                setSprite(sprite);
                break;
            }
        }
    }
}

void BaseLayer::ccTouchesMoved(CCSet* touches, CCEvent* event){
    if(touches->count() == 1){
        CCTouch* touch = (CCTouch*)touches->anyObject();
        CCPoint p = CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
        CCSprite* sprite = getSprite();
        //if(sprite && !sprite->boundingBox().containsPoint(p)){
		if(sprite && !isClick(sprite, p)){
            if(sprite->getTag() < 9000){
				sprite->setScale(sprite->getScale() / 1.1f);
			}
            setSprite(NULL);
        }
    }
}

bool BaseLayer::isClick(CCSprite* s, CCPoint p){
	if(s && s->isVisible()){
		float rd = s->getRotation();
		if(((int)rd) % 90 == 0){
			if(s->boundingBox().containsPoint(p)){
				return true;
			}
		}else{
			float w = s->getContentSize().width * s->getScaleX() / 2.0f;
			float h = s->getContentSize().height * s->getScaleY() / 2.0f;
			CCPoint pos = s->getPosition();
			float k1 = tan(CC_DEGREES_TO_RADIANS(-1 * rd));
			float k2 = -1 / k1;
			float m1 = pos.y - k1 * pos.x;
			float m2 = pos.y - k2 * pos.x;
			float d1 = abs(k1 * p.x - p.y + m1) / sqrt(k1 * k1 + 1);
			float d2 = abs(k2 * p.x - p.y + m2) / sqrt(k2 * k2 + 1);
			if(d1 <= h && d2 <= w){
				return true;
			}
		}
	}
	return false;
}

CCSprite* BaseLayer::createSpriteByNumber(int n){
    CCArray* nums = createSpritesByNumber(n);
    //float left = (80 - nums->count() * 15) / 2.0f;
    CCSprite* spri = CCSprite::createWithSpriteFrameName("Lipid.png");
    for(int i = 0; i < nums->count(); i++){
        CCSprite* s = (CCSprite*)nums->objectAtIndex(i);
        s->setPosition(ccp(i * 8, 10));
        s->setScale(0.32f);
        spri->addChild(s);
    }
    return spri;
}

CCArray* BaseLayer::createSpritesByNumber(int n){
    return createSpritesByNumber(n, false);
}

CCArray* BaseLayer::createSpritesByNumber(int n, bool isReverse){
    CCArray* sprites = CCArray::create();
    if(n >= 0){
        while(true){
            CCString* sn = CCString::createWithFormat("N%i.png", n % 10);
            sprites->addObject(CCSprite::createWithSpriteFrameName(sn->getCString()));
            
            if(n < 10){
                break;
            }
            n = n / 10;
        }
        if(!isReverse){
            sprites->reverseObjects();
        }
    }
    return sprites;
}

void BaseLayer::addSprite(CCSprite* sprite){
    addSprite(sprite, false);
}

void BaseLayer::addSprite(CCSprite* sprite, bool isTouch){
    CCSpriteBatchNode* nodes = (CCSpriteBatchNode*)this->getChildByTag(TAG_NODES);
    nodes->addChild(sprite);
    if(isTouch){
        mSprites->addObject(sprite);
    }
}

CCSprite* BaseLayer::getSpriteByTag(int tag){
    CCSpriteBatchNode* nodes = (CCSpriteBatchNode*)this->getChildByTag(TAG_NODES);
    return (CCSprite*)nodes->getChildByTag(tag);
}

void BaseLayer::removeSprite(CCSprite* sprite){
    CCSpriteBatchNode* nodes = (CCSpriteBatchNode*)this->getChildByTag(TAG_NODES);
    nodes->removeChild(sprite, true);
}

void BaseLayer::removeSpriteByTag(int tag){
	CCSpriteBatchNode* nodes = (CCSpriteBatchNode*)this->getChildByTag(TAG_NODES);
    nodes->removeChildByTag(tag, true);
}


