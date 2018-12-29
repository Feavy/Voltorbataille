#include "GameEndScene.h"
#include "TitleScreenScene.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"

USING_NS_CC;

Scene* GameEndScene::createScene()
{
    return GameEndScene::create();
}

bool GameEndScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto lostbg = LayerColor::create(Color4B(66, 66, 66, 1000));
	lostbg->setContentSize(visibleSize);
	lostbg->setAnchorPoint(Vec2(0, 0));
	lostbg->setPosition(origin);
	addChild(lostbg);

	auto lostlbl = LabelTTF::create("Vous avez perdu !", "Roboto-Medium", 32 * 4);
	lostlbl->setScale(0.25f);
	lostlbl->setPosition(origin.x+visibleSize.width / 2, origin.y+2 * visibleSize.height / 3);
	lostlbl->setColor(Color3B::WHITE);
	addChild(lostlbl, 1);
	lostlbl->runAction(Sequence::create(FadeTo::create(1.f, 255.f),
		EaseElasticInOut::create(ScaleTo::create(1.f, 0.3f)),
		ScaleTo::create(0.2f, 0.25f),
		nullptr));

	Vector<MenuItem*> items;
	auto button = MenuItemImage::create("button_continue.png", "button_continue_selected.png", GameEndScene::returnButtonPushed);
	button->setPosition(visibleSize.width / 2, 3*visibleSize.height / 8);
	button->setScale(0.25f);
	items.pushBack(button);

	auto menu = Menu::createWithArray(items);
	menu->setPosition(origin);
	addChild(menu, 1);

    return true;
}

void GameEndScene::returnButtonPushed(cocos2d::Ref* sender) {
	Director::getInstance()->replaceScene(TransitionFade::create(1, TitleScreenScene::createScene(), Color3B(255, 255, 255)));
}
