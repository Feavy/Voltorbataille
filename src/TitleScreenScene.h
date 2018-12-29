#pragma once
#include "cocos2d.h"

class TitleScreenScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	static void playButtonPushed(cocos2d::Ref* sender);
	static void scoresButtonPushed(cocos2d::Ref* sender);

    // implement the "static create()" method manually
    CREATE_FUNC(TitleScreenScene);
};