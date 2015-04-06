//
//  GameScene.cpp
//  PenguinSlice
//
//  Created by lxc on 13-12-7.
//
//

#include "GameScene.h"

using namespace cocos2d;

GameLayer::GameLayer(){
	
	setKeypadEnabled(false);

	#pragma region 初始化成员值
	mCount = 0;
    timeCount = 0;
    isDotted = false;
	#pragma endregion

    initSprites();
    
    initPhysics();
    
    createSprites();
	
    scheduleUpdate();
}

GameLayer::~GameLayer(){
    delete world;
    world = NULL;
}

CCScene* GameLayer::scene(){
    
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // add layer as a child to scene
    CCLayer* layer = new GameLayer();
    scene->addChild(layer);
    layer->release();
    
    return scene;
}

void GameLayer::initSprites(){

	init(2);
    
    CCSprite* back = CCSprite::createWithSpriteFrameName("Menu.png");
    back->setPosition(ccp(LSPoint.x + 55, LSCenter.y + 265));
	back->setScale(1.3f);
    back->setTag(TAG_BACK);
    addSprite(back, true);
    
    CCSprite* reset = CCSprite::createWithSpriteFrameName("Reset.png");
    reset->setPosition(ccp(LSPoint.x + LSSize.width - 55, LSCenter.y + 265));
	reset->setScale(1.3f);
    reset->setTag(TAG_RESET);
    addSprite(reset, true);
    
	/*CCSprite* ltext = CCSprite::createWithSpriteFrameName("Level.png");
	ltext->setPosition(ccp(LSCenter.x - 30, LSCenter.y + 265));
	ltext->setAnchorPoint(ccp(1, 0.5f));
	ltext->setScale(1.6f);
	addSprite(ltext);
	CCSprite* subtext = CCSprite::createWithSpriteFrameName("Sub.png");
	subtext->setPosition(ccp(LSCenter.x, LSCenter.y + 265));
	addSprite(subtext);
    CCSprite* cls = createSpriteByNumber(CL);
	cls->setAnchorPoint(ccp(0, 0.5f));
	cls->setScale(2.4f);
    cls->setPosition(ccp(LSCenter.x +  40, LSCenter.y + 265));
    addSprite(cls);*/

	#pragma region 帮助框
	if(CL == 1){
		CCSprite* help = CCSprite::createWithSpriteFrameName("Help.png");
		help->setPosition(ccp(LSCenter.x + 200, LSCenter.y + 120));
		addSprite(help);
	}
	#pragma endregion
}

void GameLayer::initPhysics(){
    
    b2Vec2 gravity;
    gravity.Set(0.0f, -10.0f);
    world = new b2World(gravity);
    
    // Do we want to let bodies sleep?
    world->SetAllowSleeping(true);
    world->SetContinuousPhysics(true);
    
    ContactListener* listener = new ContactListener();
    world->SetContactListener(listener);
    
    b2Vec2 v1, v2, v3, v4;
    v1.Set((LSPoint.x - LSSize.width) / PTM_RATIO, (LSPoint.y + 40.0f) / PTM_RATIO);
    v2.Set((LSPoint.x + 2 * LSSize.width) / PTM_RATIO, (LSPoint.y + 40.0f) / PTM_RATIO);
    v3.Set((LSPoint.x + 2 * LSSize.width)  / PTM_RATIO, (LSPoint.y + 2 * LSSize.height) / PTM_RATIO);
    v4.Set((LSPoint.x - LSSize.width) / PTM_RATIO, (LSPoint.y + 2 * LSSize.height) / PTM_RATIO);
    
    // Define the ground body.
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0, 0); // bottom-left corner
    b2Body* groundBody = world->CreateBody(&groundBodyDef);
    
    // Define the ground box shape.
    b2EdgeShape groundBox;
    
    // bottom
    groundBox.Set(v1, v2);
    groundBody->CreateFixture(&groundBox, 0);
    // top
    groundBox.Set(v4, v3);
    groundBody->CreateFixture(&groundBox, 0);
    // left
    groundBox.Set(v4, v1);
    groundBody->CreateFixture(&groundBox, 0);
    // right
    groundBox.Set(v3, v2);
    groundBody->CreateFixture(&groundBox, 0);
}

void GameLayer::onEnterTransitionDidFinish(){
	
}

void GameLayer::update(float dt){
    //It is recommended that a fixed time step is used with Box2D for stability
    //of the simulation, however, we are using a variable time step here.
    //You need to make an informed choice, the following URL is useful
    //http://gafferongames.com/game-physics/fix-your-timestep/
    // Instruct the world to perform a single step of simulation. It is
    // generally best to keep the time step and iterations fixed.
    world->Step(dt, 8, 1);

	#pragma region Iterate over the bodies in the physics world
	std::set<b2Body*> delbodys;
    for (b2Body* b = world->GetBodyList(); b; b = b->GetNext())
    {
        if (b->GetUserData() != NULL) {
            Sprite* sprite = (Sprite*)b->GetUserData();
			if(sprite->isRemove){
				delbodys.insert(b);
				if(sprite->type == TYPE_MELON){
					mCount--;
				}
                /*CCParticleSystemQuad* par = CCParticleSystemQuad::create(sprite->parPlist.c_str());
				par->setPosition(sprite->getPosition());
				this->addChild(par);
				par->setAutoRemoveOnFinish(true);//*/
            }else{
                CCPoint p = ccp(b->GetPosition().x * PTM_RATIO, b->GetPosition().y * PTM_RATIO);
                sprite->setPosition(p);
                sprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(b->GetAngle()));
				if(sprite->type == TYPE_ROTATE){
					sprite->setRotation(sprite->getRotation() + 0.5f);
					b->SetTransform(b->GetPosition(), CC_DEGREES_TO_RADIANS(-1 * sprite->getRotation()));
				}
            }
        }
    }
	std::set<b2Body*>::iterator pos; 
    for(pos = delbodys.begin(); pos != delbodys.end(); ++pos){
		b2Body *b = *pos;
		Sprite* sprite = (Sprite*)b->GetUserData();
		removeSprite(sprite);
		b->SetUserData(NULL);
		world->DestroyBody(b);
	}
	#pragma endregion

	#pragma region 关卡完成
    if(mCount == 0){
		timeCount++;
        if(timeCount == 20){
            timeCount = 0;
			mCount = -1;
			if (SOUND) {
				AudioEngine->playEffect(MP3_SUCCESS);
			}
			unscheduleUpdate();
			
			int lLock = UserDefault->getIntegerForKey(KEY_LEVEL_LOCK, DEFAULT_LEVEL_LOCK);
			if(CL <= N_LEVEL && CL + 1 > lLock){
					UserDefault->setIntegerForKey(KEY_LEVEL_LOCK, CL + 1);
			}
			DialogLayer* dialog = DialogLayer::create();
			dialog->initSuccessDialog();
			addChild(dialog, 101);
		}
    }
	#pragma endregion
}

void GameLayer::ccTouchesBegan(CCSet* touches, CCEvent* event){
    BaseLayer::ccTouchesBegan(touches, event);
}

void GameLayer::ccTouchesMoved(CCSet* touches, CCEvent* event){
    BaseLayer::ccTouchesMoved(touches, event);
}

void GameLayer::ccTouchesEnded(CCSet* touches, CCEvent* event){
    if(touches->count() == 1){
        CCTouch* touch = (CCTouch*)touches->anyObject();
        CCPoint p = CCDirector::sharedDirector()->convertToGL(touch->getLocationInView());
        //if(getSprite() &&!getSprite()->boundingBox().containsPoint(p)){
		if(getSprite() && !isClick(getSprite(), p)){
            setSprite(NULL);
        }
        CCSprite* sprite = getSprite();
        if(sprite){
            if (SOUND) {
                AudioEngine->playEffect(MP3_CLICK);
            }
			if(sprite->getTag() < 9000){
				sprite->setScale(sprite->getScale() / 1.1f);
			}
            switch (sprite->getTag()) {
                case TAG_BACK:
                    keyBackClicked();
                    break;
                case TAG_RESET:{
                    CCTransitionFade* sc = CCTransitionFade::create(1.2f, GameLayer::scene());
                    CCDirector::sharedDirector()->replaceScene(sc);
                }
                    break;
                default:{
					Sprite* s = (Sprite*)sprite;
					s->isRemove = true;
				}
                    break;
            }
            setSprite(NULL);
        }
    }
}

void GameLayer::keyBackClicked(){
    CCTransitionFade* sc = CCTransitionFade::create(1.2f, LevelLayer::scene());
    CCDirector::sharedDirector()->replaceScene(sc);
}

void GameLayer::createSprites(){
    
    CCDictionary* levelData = Global::share()->getLevelData();
    const char* level = CCString::createWithFormat("Level%i", CL)->getCString();
    CCDictionary* levelDict = (CCDictionary *)levelData->objectForKey(level);
    
    CCString* sBox = static_cast<CCString *>(levelDict->objectForKey("Box"));
    int box = sBox ? sBox->intValue() : 1;
    
    CCDictionary* spritesDict = (CCDictionary *)levelDict->objectForKey("Sprites");
    CCArray* spritesKeys = spritesDict->allKeys();
    for(unsigned int i = 0; i < spritesKeys->count(); i++){
        const char* spriteKey = ((CCString *)spritesKeys->objectAtIndex(i))->getCString();
        CCDictionary* spriteDict = (CCDictionary *)spritesDict->objectForKey(spriteKey);
        
        const char* name = spriteDict->valueForKey("Name")->getCString();
        int type = spriteDict->valueForKey("Type")->intValue();
        CCPoint position = CCPointFromString(spriteDict->valueForKey("Position")->getCString());
        
        CCString* density = static_cast<CCString *>(spriteDict->objectForKey("Density"));
        CCString* friction = static_cast<CCString *>(spriteDict->objectForKey("Friction"));
        CCString* rotation = static_cast<CCString *>(spriteDict->objectForKey("Rotation"));
        CCString* scale = static_cast<CCString *>(spriteDict->objectForKey("Scale"));
        
        Sprite* sprite = Sprite::create(name);
        sprite->type = type;
        sprite->density = density ? density->floatValue() : 2.0;
        sprite->friction = friction ? friction->floatValue() : 0.1;
        sprite->setRotation(rotation ? rotation->floatValue() : 0);
        if(scale){
            CCPoint sp = CCPointFromString(scale->getCString());
            sprite->setScaleX(sp.x);
            sprite->setScaleY(sp.y);
        }
		
        sprite->setPosition(ccpAdd(LSCenter, position));
        addSprite(sprite, type == TYPE_ICE ? true : false);
        switch (type) {
            case TYPE_STONE:{
				sprite->createStaticBody(world);
            }
                break;
            case TYPE_MELON:{
				sprite->density = density ? density->floatValue() : 1.0;
				mCount++;
				if(box){
                    sprite->createCircleBody(world);
                }
            }
                break;
            case TYPE_ORANGE:{
				sprite->density = density ? density->floatValue() : 4.0;
				if(box){
                    sprite->createCircleBody(world);
                }
            }
                break;
            case TYPE_BLOCK:{
                if(box){
                    sprite->createRectBody(world);
                }
            }
                break;
            case TYPE_ICE:{
				sprite->setTag(9000 + i);
				int res = sprite->name.find("Ice2");
				if(res != -1){
					if(box){
						sprite->createRectBody(world);
					}
				}else{
					sprite->createStaticBody(world);
				}
            }
                break;
            case TYPE_KNIFT:{
				sprite->density = 0;
				sprite->setAnchorPoint(ccp(0.5f, 0.0f));
                if(box){
                    sprite->createShapeBody(world, "Knift");
                }
            }
                break;
			case TYPE_ROTATE:{
				sprite->createStaticBody(world);
            }
                break;
        }
    }
}


