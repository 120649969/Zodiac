/*
************************************************************************
*
*	GameStart.h
*	Author: ���Ƿ�
*   describe: ��Ϸ��ʼ����
*
************************************************************************
*/
#ifndef __GameStart_H__
#define __GameStart_H__

#include "cocos2d.h"

USING_NS_CC;

class GameStart : public cocos2d::Layer
{
public:
	~GameStart();

	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(GameStart);

public:
	void moveWithBezier(Node* node,Vec2 point1, Vec2 point2);

	//��ʼ��Ϸ
	void startGame(Ref* pSender);

	//��Ϸ˵��
	void aboutGame(Ref* pSender);

	//�Ѷ�����
	void degreeUtil(Ref* pSender);
/*

	//��������
	void musicUtil(Ref* pSender);

*/
	//�˳���Ϸ
	void menuCloseCallback(cocos2d::Ref* pSender);

	//��ȡ���
//	void buyGold(Ref* pSender);

	//���а�
	void highScore(Ref* pSender);

	//��Ϸ�̳�
	void gameShoping(Ref* pSender);

	//��Ӧ����(��Ҫ���Android)
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	virtual void onEnterTransitionDidFinish();

	virtual void onExit();
private:
	EventListenerKeyboard* m_listener;
};
#endif