//
//  Global.cpp
//  PenguinSlice
//
//  Created by lxc on 13-11-16.
//
//

#include "Global.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <jni.h>
#include "platform/android/jni/JniHelper.h"
#include <android/log.h>
#endif

using namespace cocos2d;

static Global* instance = NULL;

Global::Global(){
    levelData = NULL;
    CurrentLevel = 0;
    NLevel = 1;
	CurrentPage = 1;
    Sound = false;
    IsSigned = false;
    IsSigned2 = false;
}

Global::~Global(){
    CC_SAFE_RELEASE(levelData);
}

Global* Global::share(){
    if(!instance){
        instance = new Global();
    }
    return instance;
}

void Global::initLevelData(const char *plist){
    
    if(levelData == NULL){
        levelData = CCDictionary::createWithContentsOfFile(plist);
        CC_SAFE_RETAIN(levelData);
        CCAssert(levelData != NULL, "Shape-file not found");
        CCAssert(levelData->count() != 0, "plist file empty or not existing");
        
        N_LEVEL = levelData->count();
    }
}

cocos2d::CCDictionary* Global::getLevelData(){
    return levelData;
}

void Global::print(const char *str){
    #if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    JniMethodInfo minfo;
    bool isHave = JniHelper::getStaticMethodInfo(minfo, "org/cocos2dx/lib/Cocos2dxActivity", "print", "(Ljava/lang/String;)V");
    if (isHave) {
        jstring js = minfo.env->NewStringUTF(str);
        minfo.env->CallStaticVoidMethod(minfo.classID, minfo.methodID, js);
    }
    #endif
}