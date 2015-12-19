/*
************************************************************************
*
*	CZodiacManager.h
*	Author: ���Ƿ�
*   describe:��������Ĳ��������������� �Լ� ��Ϸ״̬
*
************************************************************************
*/
#ifndef __CZodiacManager_H__
#define __CZodiacManager_H__

#include "cocos2d.h"
#include "CZodiac.h"
#include "CScore.h"
#include "ScoreLevel.h"
#include "ui/cocosGUI.h"
#include <vector>

USING_NS_CC;
using namespace ui;
using namespace std;


const int Grid_Width = 40;
const int Move_Speed = 0.2;
const int First_Zodiac_Id = 1;
//const int Second_Zodiac_Id = 3;
//const int Third_Zodiac_Id = 5;
const int Easy_Zodiac_Id = 6;
const int Normal_Zodiac_Id = 9;
const int Hard_Zodiac_Id = 12;


class CZodiacManager : public Node
{
public:

	static CZodiacManager* create(int row, int col);
	bool init(int row, int col);

	//���� ��Ф������
	void updateZodiacGroup();

	//��� ��Ф������
	void deleteZodiacGroup();

	//�ж� ��Ф������ �Ƿ� �Ѳ����ƶ�
	bool isDeadZodiacGroup();

	//��ȡ����
	int getRow()
	{
		return m_row;
	}

	int getCol()
	{
		return m_col;
	}

private:
	/////////////////////������Ф����/////////////////////////

	//������Ф����
	CZodiac* createZodiac(int row, int col);

	//�ж���������Ф�����Ƿ�Ϸ�
	bool isWellZodiac(CZodiac* zodiac, int row, int col);

	//������Ф�����λ��
	void setZodiacPos(CZodiac* zodiac, float row, float col);


	////////////////////������Ф����////////////////////////////////

	//������Ф����λ��
	void swapZodiacPos(CZodiac* lhs, CZodiac* rhs);

	//�ƶ���Ф����λ��
	void moveZodiacToNewPos(CZodiac* zodiac);

	//ˢ����Ф������
	void refreshZodiacGrid();

	//�� �� ˢ����Ф������
	void refreshZodiacByCol(int col);

public:
	virtual bool onTouchBegan(Touch* touch, Event* unused_event);
	virtual void onTouchMoved(Touch* touch, Event* unused_event);

private:

	/////////////////������Ф����////////////////////////

	//�ж��Ƿ��ܹ�����
	bool isZodiacDestory();

	//����
	void zodiacDestory();

	/////////////////��Ϸ״̬////////////////////////
	
	//���ڽ�����Ф����
	void onZodiacSwaping(float dt);

	//������Ф�������
	void onZodiacSwapingBack(float dt);

	//����������Ф����
	void onZodiacDestory(float dt);

	//����&֮��ˢ��
	void onZodiacRefreshing(float dt);

public:
	/////////////��ȡ��Ϸ����/////////////////////

	int getReducing();


	/////////////�趨��Ϸ����/////////////////////
	void addReducing();

	/////////////������Ϸ������/////////////////////
	void onReducingBonus(float dt);

	////////////////��Ϸ���ơ�����ʹ��//////////////////
	void onPauseItemCallback(Ref* ref);	//��ͣ��Ϸ

	void onDelayItemCallback(Ref* ref);	//ʹ�õ��� ��ʱ

	void onHintItemCallback(Ref* ref);	//ʹ�õ��� ��ʾ

	void useDelayProp();
	void useHintProp();

private:
	int m_row;
	int m_col;

	LoadingBar* m_bar;	//������

	CZodiac* m_zodiacSelected;
	CZodiac* m_zodiacSwaped;

	vector<vector<CZodiac*>> m_zodiacBox;
	Vector<CZodiac*> m_destoryZodiacBox;
	Vector<CZodiac*> m_newZodiacBox;

	ScoreLevel* m_scoreLevel;	//�����͹ؿ�

	MenuItemSprite* delayItem;	//��ʱ
	Label* m_labelDelay;	//��ʱ��������

	MenuItemSprite* hintItem;	//��ʾ
	Label* m_labelHint;	//��ʾ��������

	int m_delayNum;
	int m_hintNum;
};

#endif