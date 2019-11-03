#include "GameScene.h"
#include "Card.h"
#include "SimpleAudioEngine.h"
#include "TitleScreenScene.h"
#include "GameEndScene.h"

#include <random>

USING_NS_CC;

GameScene *GameScene::instance{ nullptr };

Scene* GameScene::createScene()
{
	return GameScene::create();
}

bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	srand(time(0));

	score = 0;
	initialized = false;
	instance = this;
	createGamegrid(20, 50, 20, 10);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto background = LayerColor::create(Color4B::WHITE);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = touchBegan;

	getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);

	background->setContentSize(visibleSize);
	background->setAnchorPoint(Vec2(0, 0));
	background->setPosition(origin);
	addChild(background, 0);

	float width = visibleSize.width / 7;
	Card::width = width;
	float offset = (visibleSize.width - 6 * width) / 7;

	int d = (visibleSize.height - 6 * offset) / 5;

	float delay = 0.05f;

	for (int j = 5; j >= 0; j--) {
		for (int i = 0; i < 6; i++) {
			if (i == 5 && j == 0) 
				continue;
			auto func = CallFunc::create([this, origin, i, j, width, offset, d]() -> void {
				Card *square;
				if (i == 5) {
					int *points = getPointsAndBombsAmountInRow(j-1);
					square = Card::createMasterCard(points[0], points[1]);
				}else if (j == 0) {
					int *points = getPointsAndBombsAmountInColumn(i);
					square = Card::createMasterCard(points[0], points[1]);
				}else {
					square = Card::create(m_gameGrid[i][j-1]);
				}
				square->setContentSize(Size(width, width));
				square->setScale(0);
				square->setPosition(origin.x + width/2 + i * width + (i + 1)*offset, origin.y + width / 2 + d + j * width + j*offset);
				square->playAnimation(origin);
				addChild(square, 1);
				if(i == 4 && j == 0)
					initialized = true;
			});
			runAction(Sequence::create(DelayTime::create(delay+=0.05), func, nullptr));
		}
	}

	Vector<MenuItem*> items;

	auto playButton = MenuItemImage::create("button_back.png", "button_back_selected.png", GameScene::backButtonPushed);
	playButton->setAnchorPoint(Vec2(0, 0));
	playButton->setScale(0.175f);
	items.pushBack(playButton);

	auto menu = Menu::createWithArray(items);
	menu->setAnchorPoint(Vec2(0, 0));
	menu->setPosition(origin.x + 10, origin.y + 10);
	addChild(menu, 1);

	auto scoreLabel = LabelTTF::create("Score : 0000", "Roboto-Medium", 30*4);
	scoreLabel->setTag(10);
	scoreLabel->setScale(0.25);
	scoreLabel->setColor(Color3B::BLACK);
	scoreLabel->setAnchorPoint(Vec2(1, 0.5));
	//351 / 410
	scoreLabel->setPosition(origin.x + visibleSize.width - 5, origin.y + width / 2 + d + 6 * width + 6*offset);
	addChild(scoreLabel, 1);

	return true;
}

bool GameScene::touchBegan(cocos2d::Touch * touch, cocos2d::Event * ev) {
	for (auto sprite : instance->getChildren()) {
		Card *card = dynamic_cast<Card*>(sprite);
		if (card && instance->initialized) {
			if (!card->isFlipped()) {
				if (sprite->getBoundingBox().containsPoint(touch->getLocation())) {
					card->flip();
					instance->addScore((instance->score == 0) ? card->getPointAmount() : instance->score * card->getPointAmount() - instance->score);
					if (card->getPointAmount() == 0) {
						Director::getInstance()->replaceScene(TransitionFade::create(1, GameEndScene::createScene(), Color3B(66, 66, 66)));
					}
				}
			}
		}
	}
	return true;
}

void GameScene::createGamegrid(int bombPercent, int onePercent, int twoPercent, int threePercent) {
	CCASSERT(bombPercent + onePercent + twoPercent + threePercent == 100, "!= 100");
	int p[5] = {
		0,
		bombPercent,
		bombPercent + onePercent,
		bombPercent + onePercent + twoPercent,
		100 };
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			int nb = rand() % 100;
			for (int k = 0; k < 4; k++) {
				if (nb >= p[k] && nb <= p[k + 1]) {
					m_gameGrid[i][j] = k;
					break;
				}
			}
		}
	}
}

void GameScene::addScore(int amount) {
	CCLOG("add score");

	if (amount == 0)
		return;

	auto child = getChildByTag(10);
	LabelTTF *scoreLabel = static_cast<LabelTTF*>(child);
	if (getActionByTag(9) != nullptr) {
		stopActionByTag(9);
		scoreLabel->setString(String::createWithFormat("Score : %i", score)->getCString());
	}
	float d = 0.2f;
	int nb = (amount / 10 > 10) ? 10 : amount/10;

	int lastScore = score;
	score += amount;

	for (int i = 0; i < nb+1; i++) {
		auto func = CallFunc::create([this, lastScore, scoreLabel, i, amount, nb]() {
			if (i == nb) {
				scoreLabel->setString(String::createWithFormat("Score : %i", score)->getCString());
			}else
				scoreLabel->setString(String::createWithFormat("Score : %i", lastScore + (amount / (nb + 1))*(i + 1))->getCString());
		});
		auto seq = Sequence::create(DelayTime::create(d += 0.2), EaseElasticInOut::create(ScaleTo::create(0.1f, 0.3f)), func, ScaleTo::create(0.1f, .25f), nullptr);
		seq->setTag(9);
		scoreLabel->runAction(seq);
	}
}

void GameScene::backButtonPushed(cocos2d::Ref * sender) {
	Director::getInstance()->replaceScene(TransitionFade::create(1, TitleScreenScene::createScene(), Color3B(66, 66, 66)));
}

int *GameScene::getPointsAndBombsAmountInColumn(int column) const {
	int rep[2] = { 0,0 };
	for (int i = 0; i < 5; i++) {
		rep[0] += m_gameGrid[column][i];
		rep[1] += m_gameGrid[column][i] == 0;
	}
	return rep;
}

int *GameScene::getPointsAndBombsAmountInRow(int row) const {
	int rep[2] = { 0,0 };
	for (int i = 0; i < 5; i++) {
		rep[0] += m_gameGrid[i][row];
		rep[1] += m_gameGrid[i][row] == 0;
	}
	return rep;
}
