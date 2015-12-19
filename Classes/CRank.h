/*
************************************************************************
*
*	CRank.h
*	Author: ���Ƿ�
*   describe: ��Ϸ������а� �ɲ鿴�� �򵥡����������� ģʽ�µ�����
*
************************************************************************
*/
#ifndef __CRank_H__
#define __CRank_H__

#include "cocos2d.h"
#include "cocos-ext.h"

USING_NS_CC;
using namespace cocos2d::extension;

class CRank : public Layer, public TableViewDataSource, public TableViewDelegate
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(CRank);

	//�������¼������Լ�����������һ������
	void tableCellTouched(TableView* table, TableViewCell* cell)
	{

	};

	//�����б�ÿһ�������
	TableViewCell * tableCellAtIndex(TableView *table, ssize_t idx);

	//һ��������
	ssize_t numberOfCellsInTableView(TableView *table);

	//ÿһ��Ŀ�Ⱥ͸߶�
	Size cellSizeForTable(TableView *table);

	Size tableCellSizeForIndex(TableView *table, ssize_t idx);

/*
	virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view)
	{

	};
	virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view)
	{

	}; */
	virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view) override{}
	virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view) override{}

	//������Ϸ
	void backToMenu(Ref* pSender, Control::EventType controlEvent);

	//��ʾ���а� ��
	void onEasyItemCallback(Ref* ref);	

	//��ʾ���а� һ��
	void onNormalItemCallback(Ref* ref);	

	//��ʾ���а� ����
	void onHardItemCallback(Ref* ref);	

	//��������
	virtual void onEnter();
	virtual void onEnterTransitionDidFinish();
	virtual void onExit();

private:
	//��ʾ����
	std::string m_sDegreeName;
	int m_nowDegree;

	MenuItemSprite* easyItem;
	MenuItemSprite* normalItem;
	MenuItemSprite* hardItem;
};
#endif