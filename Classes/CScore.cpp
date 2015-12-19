/*
************************************************************************
*
*	CScore.cpp
*	Author: ���Ƿ�
*   describe: ��������������ѳɼ�/���ֳɼ�,�Լ��㼶����
*
************************************************************************
*/

#include "CScore.h"

CScore* CScore::m_score = nullptr;

CScore::CScore()
{
	this->init();
}

void CScore::init()
{
	m_preScore=m_curScore = 0;

	rk[1000] = { 0 };

	setHighScore(UserDefault::getInstance()->getIntegerForKey("highestScore", 0));
	setCurLevel(0);

	m_gold = UserDefault::getInstance()->getIntegerForKey("Gold", 0);

	m_multScore= UserDefault::getInstance()->getIntegerForKey("MultScore", 0);
	m_bScore = UserDefault::getInstance()->getBoolForKey("IsScore", false);

	m_multGold= UserDefault::getInstance()->getIntegerForKey("MultGold", 0);
	m_bGold = UserDefault::getInstance()->getBoolForKey("IsGold", false);

	m_propDelay = UserDefault::getInstance()->getIntegerForKey("PropDelay", 0);
	m_propHint = UserDefault::getInstance()->getIntegerForKey("PropHint", 0);

	m_volume = UserDefault::getInstance()->getFloatForKey("MusicVolume", 1.0f);
	m_bMusci = UserDefault::getInstance()->getBoolForKey("IsMusic", true);
	
	m_degree = UserDefault::getInstance()->getIntegerForKey("GameDegree", 1);
}

CScore* CScore::getInstance()
{
	if (m_score==nullptr)
	{
		m_score = new CScore();
	}

	return m_score;
}

//�趨��ǰ�ؿ�
void CScore::setCurLevel(int level)
{
	m_curLevel = level;
	m_nextLevel = level + 1;

	m_nextScore = setScoreByLevel(m_nextLevel);
}

//ͨ���ؿ����趨����
int CScore::setScoreByLevel(int level)
{
	int score = 0;
	if (level == 1)
	{
		score = 500;
	}
	else if (level == 2)
	{
		score = 1500;
	}
	else if ((level >= 3) && (level <= 10))
	{
		score = 1500 + 1500 * (level - 2);
	}
	else
	{
		score = 13500 + 2000 * (level - 10);
	}
	return score;
}

void CScore::reAgain()
{
	m_curScore = m_preScore;
}

void CScore::reStart()
{
	m_preScore=m_curScore = 0;
	setCurLevel(0);
}

////////////////////������Ϸ����/////////////////////
void CScore::updateRank(int score, std::string degreeName)
{
	int cnt = std::min(UserDefault::getInstance()->getIntegerForKey(degreeName.c_str(), 0),1000);

	//��ȡ֮ǰ����
	for (int i = 0; i < cnt; i++)
	{
		std::string id = degreeName + String::createWithFormat("%d", i + 1)->_string;
		rk[i]=UserDefault::getInstance()->getIntegerForKey(id.c_str(),0);		
	}

	//���뱾������
	rk[cnt] = score;
	cnt++;
	//����

	std::sort(rk, rk + cnt, fCmp);

	UserDefault::getInstance()->setIntegerForKey(degreeName.c_str(), cnt);
	for (int i = 0; i < cnt; i++)
	{
		std::string id = degreeName + String::createWithFormat("%d", i + 1)->_string;
		int val = rk[i];
		UserDefault::getInstance()->setIntegerForKey(id.c_str(), val);
	}
}