/*
************************************************************************
*
*	CMusic.h
*	Author: ���Ƿ�
*   describe:�������ֵĿ��� �Լ� ���ñ������ֵ����ࡢ������С
*
************************************************************************
*/
#ifndef __CMusic_H__
#define __CMusic_H__

#include "cocos2d.h"

USING_NS_CC;

class CMusic : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	virtual void onExit();

	// implement the "static create()" method manually
	CREATE_FUNC(CMusic);

private:
};

#endif