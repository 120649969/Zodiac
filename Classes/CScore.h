/*
************************************************************************
*
*	CScore.h
*	Author: ���Ƿ�
*   describe: ��������������ѳɼ�/���ֳɼ�,�Լ��㼶����
*
************************************************************************
*/
#ifndef __CScore_H__
#define __CScore_H__

#include "cocos2d.h"

USING_NS_CC;

class CScore
{
public:
	static CScore* getInstance();

	////////////////////��������/////////////////////

	//��ȡ��ǰ����
	int getCurScore()
	{
		return m_curScore;
	}

	//���ӵ�ǰ����
	void addCurScore()
	{
		if (getIsScore())
		{
			m_curScore += 16;
		}
		else
		{
			m_curScore += 8;
		}
	}

	//��ȡ֮ǰ����
	int getPreScore()
	{
		return m_preScore;
	}

	//�趨֮ǰ����
	void setPreScore(int preScore)
	{
		m_preScore = preScore;
	}

	//��ȡ��߷���
	int getHighScore()
	{
		return m_highScore;
	}

	//�趨��߷���
	void setHighScore(int highScore)
	{
		if (highScore < 0)
		{
			return;
		}
		m_highScore=highScore;
	}

	//������߷���
	void storeHighScore()
	{
		UserDefault::getInstance()->setIntegerForKey("highestScore", getHighScore());
	}

	//��ȡ��һ�ؿ�����
	int getNextScore()
	{
		return m_nextScore;
	}

	////////////////////�ؿ��㼶����/////////////////////

	//��ȡ��ǰ�ؿ�
	int getCurLevel()
	{
		return m_curLevel;
	}

	//��ȡ��һ�ؿ�
	int getNextLevel()
	{
		return m_nextLevel;
	}

	//�趨��ǰ�ؿ�
	void setCurLevel(int level);

	//ͨ���ؿ����趨����
	int setScoreByLevel(int level);

	////////////////////��Ҳ���/////////////////////

	//��ȡ�����
	int getGold()
	{
		return m_gold;
	}

	//���ӽ����
	void addGold(int gold)
	{
		if (getIsGold())
		{
			m_gold += (gold<<1);
		}
		else
		{
			m_gold += gold;
		}
	}

	//ʹ�ý�ҹ�����Ʒ
	void useGold(int gold)
	{
		if (m_gold < gold)
		{
			return;
		}
		m_gold -= gold;
	}

	//��������
	void storeGold()
	{
		UserDefault::getInstance()->setIntegerForKey("Gold", getGold());
	}

	////////////////////˫���������߲���/////////////////////

	//��ȡ ˫������ ��������
	int getMultScore()
	{
		return m_multScore;
	}

	//���� ˫������ ��������
	void addMultScore(int num)
	{
		m_multScore += num;
	}

	//���� ˫������ ��������
	void useMultScore(int num)
	{
		if (m_multScore< num)
		{
			return;
		}

		m_multScore -= num;
	}

	//���� ˫������ ��������
	void storeMultScore()
	{
		UserDefault::getInstance()->setIntegerForKey("MultScore", getMultScore());
	}

	//��ȡ �Ƿ�ʹ��˫������ ����
	bool getIsScore()
	{
		return m_bScore;
	}

	//���� �Ƿ�ʹ��˫������ ����
	void setIsScore(bool isScore)
	{
		m_bScore = isScore;
	}

	//���� �Ƿ�ʹ��˫������ ����
	void storeIsScore()
	{
		UserDefault::getInstance()->setBoolForKey("IsScore", getIsScore());
	}


	////////////////////˫����ҵ��߲���/////////////////////
	//��ȡ ˫����� ��������
	int getMultGold()
	{
		return m_multGold;
	}

	//���� ˫����� ��������
	void addMultGold(int num)
	{
		m_multGold += num;
	}

	//���� ˫����� ��������
	void useMultGold(int num)
	{
		if (m_multGold < num)
		{
			return;
		}

		m_multGold -= num;
	}

	//���� ˫����� ��������
	void storeMultGold()
	{
		UserDefault::getInstance()->setIntegerForKey("MultGold", getMultGold());
	}

	//��ȡ �Ƿ�ʹ��˫����� ����
	bool getIsGold()
	{
		return m_bGold;
	}

	//���� �Ƿ�ʹ��˫����� ����
	void setIsGold(bool isGold)
	{
		m_bGold = isGold;
	}

	//���� �Ƿ�ʹ��˫����� ����
	void storeIsGold()
	{
		UserDefault::getInstance()->setBoolForKey("IsGold", getIsGold());
	}


	////////////////////��ʱ���߲���/////////////////////
	//��ȡ ��ʱ���� ����
	int getPropDelay()
	{
		return m_propDelay;
	}

	//���� ��ʱ���� ����
	void addPropDelay(int num)
	{
		m_propDelay += num;
	}

	//���� ��ʱ���� ����
	void usePropDelay(int num)
	{
		if (m_propDelay < num)
		{
			return;
		}

		m_propDelay -= num;
	}

	//���� ��ʱ���� ����
	void storePropDelay()
	{
		UserDefault::getInstance()->setIntegerForKey("PropDelay", getPropDelay());
	}


	////////////////////��ʾ���߲���/////////////////////
	//��ȡ ��ʾ���� ����
	int getPropHint()
	{
		return m_propHint;
	}

	//���� ��ʱ���� ��������
	void addPropHint(int num)
	{
		m_propHint += num;
	}

	//���� ��ʱ���� ��������
	void usePropHint(int num)
	{
		if (m_propHint < num)
		{
			return;
		}

		m_propHint -= num;
	}

	//���� ��ʱ���� ��������
	void storePropHint()
	{
		UserDefault::getInstance()->setIntegerForKey("PropHint", getPropHint());
	}

	////////////////////������С����/////////////////////

	//��ȡ ������С
	float getMusicVolume()
	{
		return m_volume;
	}

	//�趨 ������С
	void setMusicVolume(float volume)
	{
		m_volume=volume;
	}

	//���� ������С 
	void storeMusicVolume()
	{
		UserDefault::getInstance()->setFloatForKey("MusicVolume", getMusicVolume());
	}

	////////////////////���ֿ��ز���/////////////////////

	//��ȡ ���ֿ���
	bool getIsMusic()
	{
		return m_bMusci;
	}

	//���� ���ֿ���
	void setIsMusic(bool isMusci)
	{
		m_bMusci=isMusci;
	}

	//���� ���ֿ��� 
	void storeIsMusic()
	{
		UserDefault::getInstance()->setBoolForKey("IsMusic", getIsMusic());
	}

	////////////////////��Ϸ�ѶȲ���/////////////////////

	//��ȡ ��Ϸ�Ѷ�
	int getGameDegree()
	{
		return m_degree;
	}

	//�趨 ��Ϸ�Ѷ�
	void setGameDegree(int degree)
	{
		m_degree = degree;
	}

	//���� ��Ϸ�Ѷ�
	void storeGameDegree()
	{
		UserDefault::getInstance()->setIntegerForKey("GameDegree", getGameDegree());
	}


	////////////////////����һ��&&���¿�ʼ/////////////////////
	void reAgain();
	void reStart();

	////////////////////������Ϸ����/////////////////////
	void updateRank(int score, std::string degreeName);

	static bool fCmp(const int& lhs, const int& rhs)
	{
		return lhs > rhs;
	};
private:
	CScore();
	void init();

private:
	static CScore* m_score;

	int m_curScore;	//��ǰ����
	int m_preScore;	//֮ǰ����

	int m_nextScore;	//��һ�ط���(Ŀ�����)
	int m_highScore;	//��߷���
	
	int m_curLevel;	//��ǰ�ؿ�
	int m_nextLevel;	//��һ�ؿ�

	int m_gold;	//���

	int m_multScore; //��������
	bool m_bScore;	//�Ƿ�ʹ�� �����ӱ� ����

	int m_multGold;	//��ұ���
	bool m_bGold;	//�Ƿ�ʹ�� ��Ҽӱ� ����

	int m_propDelay;	//��ʱ
	int m_propHint;	//��ʾ

	float m_volume;	//������С
	bool m_bMusci;	//���ֿ���

	int m_degree;	//��Ϸ�Ѷȵȼ�

	int rk[1000];	//��Ϸ���а�
};

#endif