/*
************************************************************************
*
*	ScoreLevel.h
*	Author: ���Ƿ�
*   describe: ��ʾ�������ؿ�����ҵ���Ϣ
*
************************************************************************
*/
#ifndef __ScoreLevel_H__
#define __ScoreLevel_H__

#include "cocos2d.h"

USING_NS_CC;

class ScoreLevel : public Node
{
public:
	virtual bool init();

	CREATE_FUNC(ScoreLevel);

	void RefreshData();

	void RefreshScore();

private:
	Label* m_labelTollgate;	//�ؿ���ǩ

	Label* m_labelGold;	//��ұ�ǩ

	Label* m_labelScore;	//������ǩ
	Label* m_labelTargetScore;	//Ŀ�������ǩ
	Label* m_labelHighScore;	//��߷�����ǩ
};

#endif