#pragma once
#include "cocos2d.h"
class Card : public cocos2d::Sprite {
public:
	static Card* create(int number);
	static Card* createMasterCard(int pointAmount, int bombAmount);
	void playAnimation(cocos2d::Vec2 origin);
	void flip();
	bool isFlipped() const;
	int getPointAmount() const;
	static float width;
private:
	Card(int number, int pointAmount = 0, int bombAmount = 0);
	bool m_flipped;
	int m_number;

	bool isMasterCard() const;
	int m_bombAmount;
	int m_pointAmount;
};