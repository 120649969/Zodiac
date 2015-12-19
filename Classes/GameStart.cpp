/*
************************************************************************
*
*	GameStart.h
*	Author: ���Ƿ�
*   describe: ��Ϸ��ʼ����
*
************************************************************************
*/

#include "GameStart.h"
#include "GameScene.h"
#include "CAboutGame.h"
#include "CDegree.h"
#include "CShop.h"
#include "CRank.h"
#include "AdHelp.h"

#include "AudioController.h"

GameStart::~GameStart()
{
	Director::getInstance()->getEventDispatcher()->removeEventListener(m_listener);
}

Scene* GameStart::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameStart::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameStart::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto m_textureCache = TextureCache::getInstance();

	//���ر���
	auto bg = Sprite::createWithTexture(m_textureCache->getTextureForKey("bg_main.jpg"));
//	bg->setScale(1.5);
	bg->setAnchorPoint(Vec2(0, 0));
	bg->setPosition(Vec2(0, 0));
	addChild(bg);

	//���ر���	title_main
	auto title = Sprite::create("title_main.png");
	title->setAnchorPoint(Vec2(0.5, 1));
	title->setPosition(Vec2(visibleSize.width/2, visibleSize.height));
	addChild(title);

	//��ʼ��Ϸ ��ť
	auto tempStart1 = Sprite::createWithTexture(m_textureCache->getTextureForKey("button_start.png"));
	auto tempStart2 = Sprite::createWithTexture(m_textureCache->getTextureForKey("button_start.png"));
	tempStart2->setScale(1.2);

	auto startItem = MenuItemSprite::create(
		tempStart1, tempStart2, CC_CALLBACK_1(GameStart::startGame, this)
		);

	moveWithBezier(startItem, Vec2(visibleSize.width / 4, visibleSize.height * 3 / 4), Vec2(visibleSize.width * 2 / 3, visibleSize.height / 3));

	log("startButton's size %lf, %lf", startItem->getPositionX(), startItem->getPositionY());

	//��Ϸ˵�� ��ť
	auto tempHelp1 = Sprite::createWithTexture(m_textureCache->getTextureForKey("button_about.png"));
	auto tempHelp2 = Sprite::createWithTexture(m_textureCache->getTextureForKey("button_about.png"));
	tempHelp2->setScale(1.2);

	auto aboutGameItem = MenuItemSprite::create(
		tempHelp1, tempHelp2, CC_CALLBACK_1(GameStart::aboutGame, this)
		);

	moveWithBezier(aboutGameItem, Vec2(visibleSize.width / 2, visibleSize.height * 2 / 3), Vec2(visibleSize.width * 3 / 4, visibleSize.height / 4));

	//��Ϸ�Ѷ����� ��ť
	auto tempDegree1 = Sprite::createWithTexture(m_textureCache->getTextureForKey("button_degree.png"));
	auto tempDegree2 = Sprite::createWithTexture(m_textureCache->getTextureForKey("button_degree.png"));
	tempDegree2->setScale(1.2);

	auto degreeItem = MenuItemSprite::create(
		tempDegree1, tempDegree2, CC_CALLBACK_1(GameStart::degreeUtil, this)
		);

	moveWithBezier(degreeItem, Vec2(visibleSize.width / 8, visibleSize.height*7 / 8), Vec2(visibleSize.width * 7 / 8, visibleSize.height  / 8));
/*

	//�������� ��ť
	auto tempMusic1 = Sprite::createWithTexture(m_textureCache->getTextureForKey("button_music.png"));
	auto tempMusic2 = Sprite::createWithTexture(m_textureCache->getTextureForKey("button_music.png"));
	tempMusic2->setScale(1.2);

	auto musicItem = MenuItemSprite::create(
		tempMusic1, tempMusic2, CC_CALLBACK_1(GameStart::musicUtil, this)
		);

	moveWithBezier(musicItem, Vec2(visibleSize.width / 4, visibleSize.height / 4), Vec2(visibleSize.width * 2 / 3, visibleSize.height * 2 / 3));

*/

	//�˳���Ϸ ��ť
	auto tempOver1 = Sprite::createWithTexture(m_textureCache->getTextureForKey("button_quit.png"));
	auto tempOver2 = Sprite::createWithTexture(m_textureCache->getTextureForKey("button_quit.png"));
	tempOver2->setScale(1.2);

	auto closeItem = MenuItemSprite::create(
		tempOver1, tempOver2, CC_CALLBACK_1(GameStart::menuCloseCallback, this)
		);

	moveWithBezier(closeItem, Vec2(visibleSize.width * 3 / 4, visibleSize.height / 4), Vec2(visibleSize.width / 4, visibleSize.height * 3 / 4));


	// create menu, it's an autorelease object
	auto menu = Menu::create(startItem, aboutGameItem,  degreeItem, closeItem, NULL);
	menu->alignItemsVerticallyWithPadding(closeItem->getContentSize().height / 2);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);
/*

	//��ȡ��� ��ť
	auto tempGold1 = Sprite::createWithTexture(m_textureCache->getTextureForKey("rest_gold.png"));
	auto tempGold2 = Sprite::createWithTexture(m_textureCache->getTextureForKey("rest_gold.png"));
	tempGold2->setScale(1.2);

	auto goldItem = MenuItemSprite::create(
		tempGold1, tempGold2, CC_CALLBACK_1(GameStart::buyGold, this)
		);

	moveWithBezier(goldItem, Vec2(visibleSize.width / 8, visibleSize.height *0.6), Vec2(visibleSize.width / 4, visibleSize.height * 3 / 5));
*/

	//�߷ּ�¼ ��ť
	auto tempScore1 = Sprite::createWithTexture(m_textureCache->getTextureForKey("button_rank.png"));
	auto tempScore2 = Sprite::createWithTexture(m_textureCache->getTextureForKey("button_rank.png"));
	tempScore2->setScale(1.2);

	auto highScoreItem = MenuItemSprite::create(
		tempScore1, tempScore2, CC_CALLBACK_1(GameStart::highScore, this)
		);

	moveWithBezier(highScoreItem, Vec2(visibleSize.width / 2, visibleSize.height / 3), Vec2(visibleSize.width / 4, visibleSize.height * 3 / 4));

	//��Ϸ�̳� ��ť

	auto tempShop1 = Sprite::createWithTexture(m_textureCache->getTextureForKey("button_shop.png"));
	auto tempShop2 = Sprite::createWithTexture(m_textureCache->getTextureForKey("button_shop.png"));
	tempShop2->setScale(1.2);

	auto shopItem = MenuItemSprite::create(
		tempShop1, tempShop2, CC_CALLBACK_1(GameStart::gameShoping, this)
		);

	moveWithBezier(shopItem, Vec2(visibleSize.width * 3 / 4, visibleSize.height / 4), Vec2(visibleSize.width / 3, visibleSize.height * 2 / 3));

//	auto menu1 = Menu::create(goldItem,highScoreItem, shopItem, NULL);
	auto menu1 = Menu::create(highScoreItem, shopItem, NULL);
	menu1->alignItemsVerticallyWithPadding(closeItem->getContentSize().height / 2);
	menu1->setPosition(Vec2(-visibleSize.width*0.4,-visibleSize.height/4));
	this->addChild(menu1, 1);

		
	//�����ֻ�����
	m_listener = EventListenerKeyboard::create();
	m_listener->onKeyReleased = CC_CALLBACK_2(GameStart::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(
		m_listener, this);

	//��ʾbanner���
	AdHelp::showAd(2);

	return true;
}


void GameStart::moveWithBezier(Node* node,Vec2 point1, Vec2 point2)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	ccBezierConfig bezier2;
	bezier2.controlPoint_1 = point1;
	bezier2.controlPoint_2 = point2;
	bezier2.endPosition = Vec2(visibleSize.width/2, visibleSize.height*0.45);

	auto bezierTo1 = BezierTo::create(1.0f, bezier2);

	node->runAction(bezierTo1);
}

//��ʼ��Ϸ
void GameStart::startGame(Ref* pSender)
{

	if (AudioController::getInstance()->isMusicOpen())
	{
		AudioController::getInstance()->changeScene();
	}

	Director::getInstance()->replaceScene(
		TransitionPageTurn::create(0.5f, GameScene::createScene(), false));
}

//��Ϸ˵��
void GameStart::aboutGame(Ref* pSender)
{
	if (AudioController::getInstance()->isMusicOpen())
	{
		AudioController::getInstance()->changeScene();
	}

	Director::getInstance()->replaceScene(
		TransitionPageTurn::create(0.5f, CAboutGame::createScene(), false));
}


//�Ѷ�����
void GameStart::degreeUtil(Ref* pSender)
{
	if (AudioController::getInstance()->isMusicOpen())
	{
		AudioController::getInstance()->changeScene();
	}

	Director::getInstance()->replaceScene(
		TransitionPageTurn::create(0.5f, CDegree::createScene(), false));
}
/*

//��ȡ���
void GameStart::buyGold(Ref* pSender)
{
	if (AudioController::getInstance()->isMusicOpen())
	{
		AudioController::getInstance()->changeScene();
	}
	//��ʾ����ǽ
	AdHelp::showOfferWall();
}
*/

//���а�
void GameStart::highScore(Ref* pSender)
{
	if (AudioController::getInstance()->isMusicOpen())
	{
		AudioController::getInstance()->changeScene();
	}
	Director::getInstance()->replaceScene(
		TransitionPageTurn::create(0.5f, CRank::createScene(), false));
}

//��Ϸ�̳�
void GameStart::gameShoping(Ref* pSender)
{
	if (AudioController::getInstance()->isMusicOpen())
	{
		AudioController::getInstance()->changeScene();
	}

	Director::getInstance()->replaceScene(
		TransitionPageTurn::create(0.5f, CShop::createScene(), false));
}

/*

//��������
void GameStart::musicUtil(Ref* pSender)
{
	if (AudioController::getInstance()->isMusicOpen())
	{
		AudioController::getInstance()->changeScene();
	}
/ *
	Director::getInstance()->replaceScene(
		TransitionPageTurn::create(0.5f, CMusic::createScene(),false));* /
}
*/

//�˳���Ϸ
void GameStart::menuCloseCallback(Ref* pSender)
{
	if (AudioController::getInstance()->isMusicOpen())
	{
		AudioController::getInstance()->clickOk();
	}

	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

//��Ӧ����(��Ҫ���Android)
void GameStart::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE)
		Director::getInstance()->end();
}

void GameStart::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
}

void GameStart::onExit()
{
	this->stopAllActions();
	this->removeAllChildrenWithCleanup(true);
	Layer::onExit();
}