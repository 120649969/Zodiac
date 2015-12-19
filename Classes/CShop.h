/*
************************************************************************
*
*	CShop.h
*	Author: ���Ƿ�
*   describe: ��Ϸ�̳ǣ����� �����ӱ�����Ҽӱ�����ʱ����ʾ
*
************************************************************************
*/
#ifndef __CShop_H__
#define __CShop_H__

#include "cocos2d.h"

USING_NS_CC;

class CShop : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	virtual void onExit();

	// implement the "static create()" method manually
	CREATE_FUNC(CShop);

	void onScoreItemCallback(Ref* pSender);	//ѡ���� �����ӱ�
	void onGoldItemCallback(Ref* pSender);	//ѡ���� ��Ҽӱ�
	void onDelayItemCallback(Ref* pSender);	//ѡ���� ��ʱ
	void onHintItemCallback(Ref* pSender);	//ѡ���� ��ʾ

//	void onChangeItemCallback(Ref* pSender);	//��һ��ֶһ�

	void onReturnItemCallback(Ref* ref);	//����������

private:
//	Label* totalLabel;
};


#endif