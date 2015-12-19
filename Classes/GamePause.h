/*
************************************************************************
*
*	GamePause.h
*	Author: ���Ƿ�
*   describe: ��Ϸ��ͣ����
*
************************************************************************
*/
#ifndef __GamePause_H__
#define __GamePause_H__

#include "cocos2d.h"

USING_NS_CC;

class GamePause : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	virtual void onExit();

	// implement the "static create()" method manually
	CREATE_FUNC(GamePause);

	static cocos2d::Scene* createScene(RenderTexture* sqr);

	//������Ϸ
	void returnGame(Ref* pSender);

	//����������
	void mianGame(Ref* pSender);

private:
};

#endif