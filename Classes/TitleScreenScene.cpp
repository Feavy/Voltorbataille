#include "TitleScreenScene.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"

USING_NS_CC;

Scene* TitleScreenScene::createScene()
{
    return TitleScreenScene::create();
}

bool TitleScreenScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
	auto background = LayerColor::create(Color4B(66, 66, 66, 1000));
	background->setContentSize(visibleSize);
	background->setAnchorPoint(Vec2(0, 0));
	background->setPosition(origin);
	addChild(background, 0);

	Vector<MenuItem*> items;

	auto playButton = MenuItemImage::create("button_play.png", "button_play_selected.png", TitleScreenScene::playButtonPushed);
	playButton->setPosition(visibleSize.width/2, origin.y + 8*visibleSize.height / 12 - visibleSize.height/10);
	playButton->setScale(0.25f);
	items.pushBack(playButton);

	auto scoresButton = MenuItemImage::create("button_scores.png", "button_scores_selected.png", TitleScreenScene::scoresButtonPushed);
	scoresButton->setPosition(visibleSize.width / 2, origin.y + 5*visibleSize.height/12 - visibleSize.height / 10);
	scoresButton->setScale(0.25f);
	items.pushBack(scoresButton);

	auto logo = Sprite::create("logo.png");
	logo->setScale(0.6f*Director::getInstance()->getContentScaleFactor());
	logo->setAnchorPoint(Vec2(0.5, 1));
	logo->setPosition(origin.x+visibleSize.width / 2, origin.y+visibleSize.height - 5);
	addChild(logo, 1);

	auto menu = Menu::createWithArray(items);
	menu->setAnchorPoint(Vec2(0,0));
	menu->setPosition(origin);
	addChild(menu, 1);

    return true;
}

void TitleScreenScene::playButtonPushed(cocos2d::Ref* sender) {
	CCLOG("play button pushed");
	Director::getInstance()->replaceScene(TransitionFade::create(1, GameScene::createScene(), Color3B(255, 255, 255)));
}

void TitleScreenScene::scoresButtonPushed(cocos2d::Ref* sender) {
	CCLOG("score button pushed");
}
