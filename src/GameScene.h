#pragma once

#include "cocos2d.h"

class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
	static bool touchBegan(cocos2d::Touch *touch, cocos2d::Event *ev);

	void createGamegrid(int bombPercent, int onePercent, int twoPercent, int threePercent);
	void addScore(int amount);

	static void backButtonPushed(cocos2d::Ref* sender);

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
private:
	static GameScene *instance;
	bool initialized;
	int score;
	int m_gameGrid[5][5];

	int *getPointsAndBombsAmountInColumn(int column) const;
	int *getPointsAndBombsAmountInRow(int row) const;
};