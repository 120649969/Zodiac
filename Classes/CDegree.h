/*
************************************************************************
*
*	CDegree.h
*	Author: ���Ƿ�
*   describe:ѡ����Ϸ�Ѷ�
*
************************************************************************
*/
#ifndef __CDegree_H__
#define __CDegree_H__

#include "cocos2d.h"

USING_NS_CC;

class CDegree : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	virtual void onExit();

	// implement the "static create()" method manually
	CREATE_FUNC(CDegree);

	void onEasyItemCallback(Ref* ref);	//ѡ�ؿ� ��
	void onNormalItemCallback(Ref* ref);	//ѡ�ؿ� һ��
	void onHardItemCallback(Ref* ref);	//ѡ�ؿ� ����

	void onScoreItemCallback(Ref* ref);	//ʹ�õ��� ˫������
	void onGoldItemCallback(Ref* ref);	//ʹ�õ��� ˫�����
	void onMusicItemCallback(Ref* ref);	//���ֿ���

	void onReturnItemCallback(Ref* ref);	//����������

private:
	MenuItemSprite* easyItem;
	MenuItemSprite* normalItem;
	MenuItemSprite* hardItem;

	MenuItemSprite* scoreItem;
	MenuItemSprite* goldItem;
	MenuItemSprite* musicItem;
};

#endif