/*
************************************************************************
*
*	CZodiac.h
*	Author: ���Ƿ�
*   describe: ���������࣬�����������͡�λ�á�״̬(�Ƿ񽻻�������)
*
************************************************************************
*/
#ifndef __CZodiac_H__
#define __CZodiac_H__

#include "cocos2d.h"

USING_NS_CC;

class CZodiac : public Sprite
{
public:
	static CZodiac* create(int type, Vec2 pos);
	bool init(int type, Vec2 pos);

public:
	//��ȡ��Ф����
	int getType()
	{
		return m_type;
	};

	//��ȡ��Фλ��
	Vec2 getPos()
	{
		return m_pos;
	};

	//������Фλ��
	void setPos(Vec2 pos)
	{
		m_pos = pos;
	};

	//�ж��Ƿ��ڽ���״̬
	bool isSwaping()
	{
		return m_bSwap;
	};

	//�ж��Ƿ�������״̬
	bool isDestory()
	{
		return m_bDestory;
	};

	//����Ϊ����״̬
	void setSwaping(bool state)
	{
		m_bSwap = state;
	};

	//����Ϊ����״̬������
	void fDestory();

private:
	int m_type;
	Vec2 m_pos;
	bool m_bSwap;
	bool m_bDestory;
};
#endif