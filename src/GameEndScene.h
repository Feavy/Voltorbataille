#pragma once
#include "cocos2d.h"

class GameEndScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	static void returnButtonPushed(cocos2d::Ref* sender);

    // implement the "static create()" method manually
    CREATE_FUNC(GameEndScene);
};