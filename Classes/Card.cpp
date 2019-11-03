#include "Card.h"

using namespace cocos2d;

float Card::width{ 0 };

Card::Card(int number, int pointAmount, int bombAmount) :
	m_number{ number },
	m_flipped{ false },
	m_pointAmount{ pointAmount },
	m_bombAmount{ bombAmount } {
}

Card* Card::create(int number) {
	Card *rep = new Card(number);
	if (rep->initWithFile("case.png", Rect(0,0,256,256))) {
		return rep;
	}
}

Card* Card::createMasterCard(int pointAmount, int bombAmount) {
	Card *rep = new Card(-1, pointAmount, bombAmount);
	if (rep->initWithFile("case2.png")) {
		return rep;
	}
}


void Card::playAnimation(Vec2 origin) {
	if (isMasterCard()) {

		auto s = String::createWithFormat("%i", m_bombAmount);

		auto labelBombAmount = LabelTTF::create(s->getCString(), "Roboto-Medium", 20*4);
		labelBombAmount->setScale(0.25f);
		labelBombAmount->setAnchorPoint(Vec2(0.5, 0));
		labelBombAmount->setPosition(Vec2(2*getContentSize().width/3, 0));
		addChild(labelBombAmount);
		s->autorelease();

		s = String::createWithFormat("%s%i", (m_pointAmount < 10) ? "0" : "", m_pointAmount);

		auto pointAmount = LabelTTF::create(s->getCString(), "Roboto-Medium", 15*4);
		pointAmount->setScale(0.25f);
		pointAmount->setAnchorPoint(Vec2(0.5, 1));
		pointAmount->setPosition(Vec2(getContentSize().width/2, getContentSize().height));
		addChild(pointAmount);
		s->autorelease();
	}
	runAction(ScaleTo::create(0.05f, 1.f));
}

void Card::flip() {
	if (isMasterCard() || m_flipped)
		return;
	m_flipped = true;
	CCLOG("points : %i", m_number);
	auto func = CallFunc::create([this]() -> void {
		setTextureRect(Rect(256 + m_number * 256, 0, 256, 256));
		setContentSize(Size(width, width));
	});
	runAction(Sequence::create(ScaleTo::create(0.25, 0, 1), func, ScaleTo::create(0.25, 1, 1), nullptr));
}

bool Card::isFlipped() const {
	return m_flipped;
}

int Card::getPointAmount() const {
	return m_number;
}

bool Card::isMasterCard() const {
	return m_number == -1;
}