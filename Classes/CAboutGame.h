/*
************************************************************************
*
*	CAboutGame.h
*	Author: ���Ƿ�
*   describe: ��Ϸ�淨����Ϸ����
*
************************************************************************
*/
#ifndef __CAboutGame_H__
#define __CAboutGame_H__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
using namespace cocos2d::extension;

class CAboutGame : public cocos2d::Layer
{
public:
	
	virtual bool init();

	static cocos2d::Scene* createScene();
	
	CREATE_FUNC(CAboutGame);

	//�л������˵�
	void backToMenu(Ref* pSender, Control::EventType controlEvent);

	//�л�ҳ��
	void tbChange0(Node * node, void * a);

	//�л�����
	void tbChange(Node * node, void * a);
	
	//��ť��Ч��
	void disable();
	//�ָ���ť
	void enable();

	//����¼�
	void upInsideAction(Ref * sender, Control::EventType controlEvent);

	//��������
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();

public:
	Sprite* ptb;
	Sprite* ptc;
};

#endif