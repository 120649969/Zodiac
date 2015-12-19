/*
************************************************************************
*
*	GameOver.h
*	Author: ���Ƿ�
*   describe: ��Ϸ��������
*
************************************************************************
*/
#ifndef __GameOver_H__
#define __GameOver_H__

#include "cocos2d.h"

USING_NS_CC;

class GameOver : public Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(GameOver);

	virtual void onExit();

	void onBackItemCallback(Ref*);	//����һ��
	void onReStartItemCallback(Ref*);	//���¿�ʼ
	void onMainItemCallback(Ref*);	//����������
	void onExitItemCallback(Ref*);	//�˳���Ϸ
};

#endif