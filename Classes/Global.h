//
//  Global.h
//  PenguinSlice
//
//  Created by lxc on 13-11-16.
//
//

#ifndef __PenguinSlice__Global__
#define __PenguinSlice__Global__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

#define PTM_RATIO 64

#define PUB_KEY "efadd71875072f3e7f8f75817764fd04"

#define DEFAULT_LEVEL_LOCK 1
#define DEFAULT_STAR       1

#define TYPE_STONE         0
#define TYPE_MELON         1
#define TYPE_ORANGE        2
#define TYPE_BLOCK         3
#define TYPE_ICE           4
#define TYPE_KNIFT         5
#define TYPE_ROTATE        6

#define TAG_NODES          8000
#define TAG_SOUND          8001
#define TAG_PLAY           8002
#define TAG_BACK           8003
#define TAG_SLICE          8004
#define TAG_FORWARD        8005
#define TAG_BACKWARD       8006
#define TAG_CLOSE          8007
#define TAG_RESET          8008
#define TAG_LINE           8009
#define TAG_SCORE          8010
#define TAG_MENU           8011
#define TAG_NEXT_LEVEL     8012
#define TAG_DOTTED_LINE    8013
#define TAG_OK             8014
#define TAG_DEL            8015
#define TAG_NAME           8016
#define TAG_POSITION       8017
#define TAG_ROTATION       8018
#define TAG_SCALE          8019
#define TAG_DIALOG         8020

#define KEY_SOUND          "Sound"
#define KEY_CURRENT_PAGE   "CurrentPage"
#define KEY_LEVEL_LOCK     "LevelLock"
#define KEY_HIGH_SCORE     "HighScore"

#define MP3_CLICK          "Click.mp3"
#define MP3_DISAPPEAR      "Disappear.mp3"
#define MP3_FAILED         "Failed.mp3"
#define MP3_GIFT           "Gift.mp3"
#define MP3_PASS_LEVELS    "PassLevels.mp3"
#define MP3_PENGUIN_SOUND  "PenguinSound.mp3"
#define MP3_SLICE          "Slice.mp3"
#define MP3_SUCCESS        "Success.mp3"


#define N_STAR             3
#define N_LEVEL            Global::share()->NLevel
#define AudioEngine        CocosDenshion::SimpleAudioEngine::sharedEngine()
#define UserDefault        CCUserDefault::sharedUserDefault()
#define SpriteFrame        CCSpriteFrameCache::sharedSpriteFrameCache()
#define LSPoint            Global::share()->Point
#define LSSize             Global::share()->Size
#define LSCenter           Global::share()->Center
#define CP                 Global::share()->CurrentPage
#define CL                 Global::share()->CurrentLevel
#define SOUND              Global::share()->Sound

class Global{
public:
    Global();
    ~Global();
    static Global* share();
    void initLevelData(const char* plist);
    cocos2d::CCDictionary* getLevelData();
    void print(const char* str);
    
    cocos2d::CCPoint Point;
    cocos2d::CCSize Size;
    cocos2d::CCPoint Center;
    int NLevel;
	int CurrentPage;
    int CurrentLevel;
    bool Sound;
    bool IsSigned, IsSigned2;
private:
    cocos2d::CCDictionary* levelData;
};

#endif /* defined(__PenguinSlice__Global__) */