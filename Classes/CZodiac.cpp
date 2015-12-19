/*
************************************************************************
*
*	CZodiac.cpp
*	Author: ���Ƿ�
*   describe: ���������࣬�����������͡�λ�á�״̬(�Ƿ񽻻�������)
*
************************************************************************
*/

#include "CZodiac.h"

CZodiac* CZodiac::create(int type, Vec2 pos)
{
	CZodiac* m_zodiac = new CZodiac();

	if (m_zodiac && m_zodiac->init(type, pos))
	{
		m_zodiac->autorelease();
		return m_zodiac;
	}
	else
	{
		CC_SAFE_DELETE(m_zodiac);
		return nullptr;
	}
}

bool CZodiac::init(int type, Vec2 pos)
{
	Sprite::init();

	m_type = type;
	m_pos = pos;
	m_bSwap = false;
	m_bDestory = false;

	//////////////////////////////////���ؾ���//////////////////////////////////////////
	auto str = __String::createWithFormat("%d.png", m_type);
	this->initWithTexture(TextureCache::getInstance()->getTextureForKey(str->getCString()));

	this->setAnchorPoint(Vec2(0, 0));

	return true;
}

//����Ϊ����״̬������
void CZodiac::fDestory()
{
	m_bDestory = true;

	auto action = FadeOut::create(0.2f);
	auto m_call = CallFunc::create([this]()
	{
		this->removeFromParentAndCleanup(true);
		m_bDestory = false;
	}
	);
	this->runAction(Sequence::create(action, m_call, nullptr));
}