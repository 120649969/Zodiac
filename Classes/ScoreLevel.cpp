/*
************************************************************************
*
*	ScoreLevel.h
*	Author: ���Ƿ�
*   describe: ��ʾ�������ؿ�����ҵ���Ϣ
*
************************************************************************
*/

#include "ScoreLevel.h"
#include "CScore.h"
#include "AudioController.h"

bool ScoreLevel::init()
{
	if (!Node::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//�ؿ���ǩ

	auto m_tollgateSprite = Sprite::create("title_tollgate.png");
	m_tollgateSprite->setAnchorPoint(Vec2(0, 0));
	m_tollgateSprite->setPosition(Vec2(0, visibleSize.height - m_tollgateSprite->getContentSize().height));
	this->addChild(m_tollgateSprite);

	m_labelTollgate = Label::createWithCharMap(
		"digital.png",
		20, 24,
		'0');
	m_labelTollgate->setString(String::createWithFormat("%d", CScore::getInstance()->getCurLevel())->_string);
	m_labelTollgate->setAlignment(TextHAlignment::LEFT);
	m_labelTollgate->setAnchorPoint(Vec2(0, 0));
	m_labelTollgate->setPosition(Vec2(m_tollgateSprite->getContentSize().width*1.1, visibleSize.height - m_labelTollgate->getContentSize().height));
	this->addChild(m_labelTollgate);

	//��ұ�ǩ

	auto m_goldSprite = Sprite::create("title_gold.png");
	m_goldSprite->setAnchorPoint(Vec2(0, 0));
	m_goldSprite->setPosition(Vec2(m_goldSprite->getContentSize().width/2 + m_tollgateSprite->getContentSize().width * 2, visibleSize.height - m_goldSprite->getContentSize().height));
	this->addChild(m_goldSprite);


	m_labelGold = Label::createWithCharMap(
		"digital.png",
		20, 24,
		'0');

	m_labelGold->setString(String::createWithFormat("%d", CScore::getInstance()->getGold())->_string);
	m_labelGold->setAlignment(TextHAlignment::LEFT);
	m_labelGold->setAnchorPoint(Vec2(0, 0));
	m_labelGold->setPosition(Vec2(m_goldSprite->getContentSize().width*1.5 + m_tollgateSprite->getContentSize().width * 2, visibleSize.height - m_labelTollgate->getContentSize().height));
	this->addChild(m_labelGold);

	//������ǩ

	auto m_scoreSprite = Sprite::create("title_nowScore.png");
	m_scoreSprite->setAnchorPoint(Vec2(0, 0));
	m_scoreSprite->setPosition(Vec2(0, visibleSize.height - m_scoreSprite->getContentSize().height*2.2));
	this->addChild(m_scoreSprite);

	m_labelScore = Label::createWithCharMap(
		"digital.png",
		20, 24,
		'0');
	m_labelScore->setString(String::createWithFormat("%d", CScore::getInstance()->getCurScore())->_string);
	m_labelScore->setAlignment(TextHAlignment::LEFT);
	m_labelScore->setAnchorPoint(Vec2(0, 0));
	m_labelScore->setPosition(Vec2(m_scoreSprite->getContentSize().width*1.1, visibleSize.height - m_labelGold->getContentSize().height*2.2));
	this->addChild(m_labelScore);	


	//Ŀ�������ǩ

	auto m_targetScoreSprite = Sprite::create("title_directScore.png");
	m_targetScoreSprite->setAnchorPoint(Vec2(0, 0));
	m_targetScoreSprite->setPosition(Vec2(0, visibleSize.height - m_targetScoreSprite->getContentSize().height*3.4));
	this->addChild(m_targetScoreSprite);

	m_labelTargetScore = Label::createWithCharMap(
		"digital.png",
		20, 24,
		'0');
	m_labelTargetScore->setString(String::createWithFormat("%d", CScore::getInstance()->getNextScore())->_string);
	m_labelTargetScore->setAlignment(TextHAlignment::LEFT);
	m_labelTargetScore->setAnchorPoint(Vec2(0, 0));
	m_labelTargetScore->setPosition(Vec2(m_targetScoreSprite->getContentSize().width*1.1, visibleSize.height - m_labelGold->getContentSize().height*3.4));
	this->addChild(m_labelTargetScore);


	//��߷�����ǩ

	auto m_highScoreSprite = Sprite::create("title_highScore.png");
	m_highScoreSprite->setAnchorPoint(Vec2(0, 0));
	m_highScoreSprite->setPosition(Vec2(0, visibleSize.height - m_highScoreSprite->getContentSize().height*4.6));
	this->addChild(m_highScoreSprite);
	
	m_labelHighScore = Label::createWithCharMap(
		"digital.png",
		20, 24,
		'0');
	
	m_labelHighScore->setString(String::createWithFormat("%d", CScore::getInstance()->getHighScore())->_string);
	m_labelHighScore->setAlignment(TextHAlignment::LEFT);
	m_labelHighScore->setAnchorPoint(Vec2(0, 0));
	m_labelHighScore->setPosition(Vec2(m_highScoreSprite->getContentSize().width*1.1, visibleSize.height - m_labelGold->getContentSize().height * 4.6));
	this->addChild(m_labelHighScore);

	//��Ϸ�Ѷ�
	Sprite* m_degreeSprite;
	
	if (1==CScore::getInstance()->getGameDegree())
	{
		m_degreeSprite = Sprite::create("title_easy.png");
	}
	else if(2 == CScore::getInstance()->getGameDegree())
	{
		m_degreeSprite = Sprite::create("title_normal.png");
	}
	else if (3 == CScore::getInstance()->getGameDegree())
	{
		m_degreeSprite = Sprite::create("title_hard.png");
	}


	m_degreeSprite->setAnchorPoint(Vec2(1, 0));
	m_degreeSprite->setPosition(Vec2(visibleSize.width, visibleSize.height - m_scoreSprite->getContentSize().height*2.2));
	this->addChild(m_degreeSprite);

	//�Ƿ�ʹ�� �����ӱ� ����
	if (CScore::getInstance()->getIsScore() && CScore::getInstance()->getMultScore()>0)
	{
		auto m_scorePropSprite = Sprite::create("title_mutilScore.png");
		m_scorePropSprite->setAnchorPoint(Vec2(1, 0));
		m_scorePropSprite->setPosition(Vec2(visibleSize.width, visibleSize.height - m_targetScoreSprite->getContentSize().height*3.4));
		this->addChild(m_scorePropSprite);
	}
	else
	{
		CScore::getInstance()->setIsScore(false);
	}

	//�Ƿ�ʹ�� ��Ҽӱ� ����
	if (CScore::getInstance()->getIsGold() && CScore::getInstance()->getMultGold()>0)
	{
		auto m_goldPropSprite = Sprite::create("title_mutilGold.png");
		m_goldPropSprite->setAnchorPoint(Vec2(1, 0));
		m_goldPropSprite->setPosition(Vec2(visibleSize.width, visibleSize.height - m_highScoreSprite->getContentSize().height*4.6));
		this->addChild(m_goldPropSprite);
	}
	else
	{
		CScore::getInstance()->setIsGold(false);
	}

	return true;
}

void ScoreLevel::RefreshData()
{
	char buf[64];

	//���¹ؿ���ǩ

	sprintf(buf, "%d", CScore::getInstance()->getNextLevel());
	m_labelTollgate->setString(buf);

	//���½�ұ�ǩ

	sprintf(buf, "%d", CScore::getInstance()->getGold());
	m_labelGold->setString(buf);

	//���·�����ǩ

	sprintf(buf, "%d", CScore::getInstance()->getCurScore());
	m_labelScore->setString(buf);

	//����Ŀ�������ǩ
	
	sprintf(buf, "%d", CScore::getInstance()->getNextScore());
	m_labelTargetScore->setString(buf);

	//������߷�����ǩ
	sprintf(buf, "%d", CScore::getInstance()->getHighScore());
	m_labelHighScore->setString(buf);
}

void ScoreLevel::RefreshScore()
{
	char buf[64];

	//���¹ؿ���ǩ
	sprintf(buf, "%d", CScore::getInstance()->getCurScore());
	m_labelScore->setString(buf);
}