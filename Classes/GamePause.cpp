/*
************************************************************************
*
*	GamePause.cpp
*	Author: ���Ƿ�
*   describe: ��Ϸ��ͣ����
*
************************************************************************
*/

#include "GamePause.h"
#include "GameStart.h"
#include "AudioController.h"
#include "CScore.h"
#include "AdHelp.h"


// ����һ����̬�ĳ�������
Scene* GamePause::createScene()
{
	// ��scene��������
	Scene *myscene = Scene::create();

	// ����һ��layer
	GamePause *mylayer = GamePause::create();

	// �����layer���뵽scene��
	myscene->addChild(mylayer);

	// ����scene
	return myscene;
}
Scene* GamePause::createScene(RenderTexture* sqr)
{
	Scene *myscene = Scene::create();

	Sprite *_spr = Sprite::createWithTexture(sqr->getSprite()->getTexture());
	_spr->setPosition(Vec2(160, 270));
	_spr->setFlippedY(true);
	_spr->setColor(Color3B::GRAY);
	myscene->addChild(_spr);

	GamePause* mylayer = GamePause::create();

	myscene->addChild(mylayer);

	return myscene;
}

// ��ʼ��
bool GamePause::init()
{
	if (!Layer::init())
	{
		return false;
	}
	Size mysize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	if (AudioController::getInstance()->isMusicOpen())
	{
		AudioController::getInstance()->pauseBackgroundMusic();
	}

	//����
	Sprite *bg = Sprite::create("koala.png");
	bg->setScale(2.0f);
	bg->setPosition(Vec2(mysize.width/2,mysize.height-bg->getContentSize().height));
	this->addChild(bg);

	//������Ϸ ��ť
	auto spriteNor3 = Sprite::create("button_goto.png");
	auto spriteSel3 = Sprite::create("button_goto.png");
	spriteSel3->setScale(1.2);

	auto returnItem = MenuItemSprite::create(
		spriteNor3,
		spriteSel3
		);
	returnItem->setCallback(CC_CALLBACK_1(GamePause::returnGame, this));

	//���������� ��ť
	auto spriteNor2 = Sprite::create("button_return.png");
	auto spriteSel2 = Sprite::create("button_return.png");
	spriteSel2->setScale(1.2);

	auto mainItem = MenuItemSprite::create(
		spriteNor2,
		spriteSel2
		);
	mainItem->setCallback(CC_CALLBACK_1(GamePause::mianGame, this));

	auto menu = Menu::create(returnItem, mainItem, nullptr);
	menu->alignItemsVerticallyWithPadding(returnItem->getContentSize().height / 2);
	menu->setPosition(Vec2(mysize.width / 2, mysize.height / 4));
	addChild(menu);
	
	//�������
	AdHelp::showAd(1);

	return true;
}

//������Ϸ
void GamePause::returnGame(Ref * pSender)
{
	if (AudioController::getInstance()->isMusicOpen())
	{
		AudioController::getInstance()->clickOk();

		AudioController::getInstance()->resumeBackgroundMusic();
	}

	Director::getInstance()->popScene();
	Director::getInstance()->resume();
}

//������Ϸ�˵�
void GamePause::mianGame(Ref * pSender)
{
	if (AudioController::getInstance()->isMusicOpen())
	{
		AudioController::getInstance()->clickOk();

		AudioController::getInstance()->stopBackgroundMusic();
	}

	Director::getInstance()->popScene();
	Director::getInstance()->resume();

	CScore::getInstance()->reStart();

	Scene *gamemenu = GameStart::createScene();
	auto *tt = TransitionPageTurn::create(0.5f, gamemenu, false);
	Director::getInstance()->replaceScene(tt);
}

void GamePause::onExit()
{
	Layer::onExit();
}