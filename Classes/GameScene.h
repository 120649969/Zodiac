/*
************************************************************************
*
*	GameScene.h
*	Author: ���Ƿ�
*   describe: ��Ϸ������
*
************************************************************************
*/
#ifndef __GameScene_H__
#define __GameScene_H__

#include "cocos2d.h"
#include "CZodiacManager.h"
#include "FlowWord.h"
#include "CScore.h"

USING_NS_CC;

class GameScene : public Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

	~GameScene();

private:
	//���±���
	void updateBG(float dt);

	//��ʾ�ؿ�Ʈ��
	void showLevel();

	//��ʾĿ�����Ʈ��
	void showTargetScore();

	//�Ƴ�Ʈ��
	void removeFlowWord();

	//������Ф������
	void newZodiacManager();

	////��Ӧ����(��Ҫ���Android)
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	//��������
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();

private:
	FlowWord* m_flowLevel;	//�ؿ�Ʈ��
	FlowWord* m_flowTargetScore;	//Ŀ�����Ʈ��

	Sprite* m_bgSprite;	//����

	CZodiacManager* m_zodiacManager;	//��Ф������
};

#endif