//
//  PenguinSliceAppDelegate.cpp
//  PenguinSlice
//
//  Created by lxc on 13-11-26.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "MainScene.h"
#include "Global.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>   
#include "platform/android/jni/JniHelper.h"   
#include <android/log.h>   
#endif

USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // turn on display FPS
    //pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    CCSize frameSize = CCEGLView::sharedOpenGLView()->getFrameSize();
    CCSize lsSize = CCSizeMake(960, 640);
    
    float scaleX = (float)frameSize.width / lsSize.width;
    float scaleY = (float)frameSize.height / lsSize.height;
    
    float scale = MAX(scaleX, scaleY);
    if(scaleX > scaleY)
        scale = scaleX / (frameSize.height / (float)lsSize.height);
    else
        scale = scaleX / (frameSize.width / (float)lsSize.width);
    
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(lsSize.width * scale, lsSize.height * scale, kResolutionNoBorder);
    
    CCSize winSize = pDirector->getWinSize();
    scale = frameSize.height / lsSize.height;
    float x = (winSize.width - (frameSize.width / scale)) / 2.0f;
    float y = (winSize.height - lsSize.height) / 2.0f;
	
    LSPoint = ccp(x, y);
    LSSize = CCSizeMake(frameSize.width / scale, lsSize.height);
    LSCenter = ccp(winSize.width / 2.0f, winSize.height / 2.0f);
    
    SpriteFrame->addSpriteFramesWithFile("Sprite.plist", "Sprite.png");
    
	GB2ShapeCache::sharedGB2ShapeCache()->addShapesWithFile("Knift.plist");
    
    Global::share()->initLevelData("Levels.plist");
	
	CP = UserDefault->getIntegerForKey(KEY_CURRENT_PAGE, 1);
    
    AudioEngine->preloadEffect(MP3_CLICK);
    AudioEngine->preloadEffect(MP3_DISAPPEAR);
    AudioEngine->preloadEffect(MP3_FAILED);
    AudioEngine->preloadEffect(MP3_GIFT);
    AudioEngine->preloadEffect(MP3_PASS_LEVELS);
    AudioEngine->preloadEffect(MP3_PENGUIN_SOUND);
    AudioEngine->preloadEffect(MP3_SLICE);
    AudioEngine->preloadEffect(MP3_SUCCESS);
	
    SOUND = UserDefault->getBoolForKey(KEY_SOUND, true);

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    bool isHave = JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/lib/Cocos2dxActivity", "getSignature", "()Ljava/lang/Object;");
    jobject jobj;
    if (isHave) {
        jobj = minfo.env->CallStaticObjectMethod(minfo.classID, minfo.methodID);
        isHave = JniHelper::getMethodInfo(minfo, "android/content/pm/Signature", "toCharsString", "()Ljava/lang/String;");
        jstring jstr;
        if (isHave) {
            jstr = (jstring)minfo.env->CallObjectMethod(jobj, minfo.methodID);
            std::string str = JniHelper::jstring2string(jstr);
            std::string s1 = md5(str.substr(0, 150));
            std::string s2 = md5(str.substr(150, 250));
            std::string s3 = md5(str.substr(400, 280));
            std::string s4 = md5(str.substr(680, 218));
            s4.append(s1);
            s4.append(s3);
            s4.append(s2);
            if (strcmp(PUB_KEY, md5(s4).c_str()) == 0) {
                Global::share()->IsSigned = true;
            }
            if (strcmp(PUB_KEY, md5(s4).c_str()) == 0) {
                Global::share()->IsSigned2 = true;
            }
        }
    }
    #endif

    // create a scene. it's an autorelease object
    CCScene *pScene = MainLayer::scene();

    // run
    pDirector->runWithScene(pScene);
    
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}
