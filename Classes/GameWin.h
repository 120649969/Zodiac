/*
************************************************************************
*
*	GameWin.h
*	Author: ���Ƿ�
*   describe: ��Ϸͨ�س���
*
************************************************************************
*/
#ifndef __GameWin_H__
#define __GameWin_H__

#include "cocos2d.h"

USING_NS_CC;

class GameWin : public Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(GameWin);

	void onMainItemCallback(Ref*);	//����������
	void onExitItemCallback(Ref*);	//�˳���Ϸ
	
};

#endif