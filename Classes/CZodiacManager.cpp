/*
************************************************************************
*
*	CZodiacManager.cpp
*	Author: ���Ƿ�
*   describe: ��������Ĳ��������������� �Լ� ��Ϸ״̬
*
************************************************************************
*/

#include "CZodiacManager.h"
#include "AudioController.h"
#include "ZodiacParticle.h"
#include "GamePause.h"

using namespace CocosDenshion;

CZodiacManager* CZodiacManager::create(int row, int col)
{
	auto m_zodiacManager = new CZodiacManager();
	if (m_zodiacManager && m_zodiacManager->init(row,col))
	{
		m_zodiacManager->autorelease();
		return m_zodiacManager;
	}
	else
	{
		CC_SAFE_DELETE(m_zodiacManager);
		return nullptr;
	}
}

bool CZodiacManager::init(int row, int col)
{
	if (!Node::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
/*
	
	this->ignoreAnchorPointForPosition(false);
	this->setAnchorPoint(Vec2(1,0));
	this->setPosition(Vec2(visibleSize.width/2,0));
*/

	auto m_textureCache = TextureCache::getInstance();

	//��ʼ������
	m_row = row;
	m_col = col;

	//��ʼ��ѡ�С���������Ф����Ϊ��
	m_zodiacSelected = nullptr;
	m_zodiacSwaped = nullptr;

	//��ʼ����Ф������Ĵ�С
	m_zodiacBox.resize(m_row);
	for (auto &vec : m_zodiacBox)
	{
		vec.resize(m_col);
	}

	//������Ф������
	for (int i = 0; i < m_row; i++)
	{
		for (int j = 0; j < m_col;j++)
		{
			m_zodiacBox[i][j] = createZodiac(i, j);
		}
	}

	//�ж���Ф�������Ƿ�Ϸ������Ϸ��Ļ���������
	while (isDeadZodiacGroup())
	{
		updateZodiacGroup();
	}

	//�����¼���Ӧ����
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(CZodiacManager::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(CZodiacManager::onTouchMoved, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	log("CZodiacManager init.");

	//��ǰ�����͹ؿ�����Ϸ�Ѷȡ�����ʹ��
	m_scoreLevel = ScoreLevel::create();
	m_scoreLevel->RefreshData();
	this->addChild(m_scoreLevel);

	//���������
	//����ʱ�����
	auto m_bounusbar_frame = Sprite::createWithTexture(m_textureCache->getTextureForKey("bonusbar.png"));
	m_bounusbar_frame->setPosition(Vec2(visibleSize.width, m_row*Grid_Width));
	m_bounusbar_frame->setAnchorPoint(Vec2(1,0));
//	m_bounusbar_frame->setVisible(false);

	this->addChild(m_bounusbar_frame);

	//��������ʼ��
	m_bar = LoadingBar::create("bonusbar_fill.png");
	m_bar->setPercent(100);
	m_bar->setDirection(LoadingBar::Direction::DOWN);
	m_bar->setPosition(m_bounusbar_frame->getPosition());
	m_bar->setAnchorPoint(Vec2(1,0));
	this->addChild(m_bar);

	this->schedule(schedule_selector(CZodiacManager::onReducingBonus), 0.5);

	//��ͣ��Ϸ
	Sprite* spriteNor4;
	Sprite* spriteSel4;

	spriteNor4 = Sprite::create("pause.png");
	spriteSel4 = Sprite::create("pause.png");

	spriteSel4->setScale(1.2);

	auto pauseItem = MenuItemSprite::create(
		spriteNor4,
		spriteSel4
		);
	pauseItem->setCallback(CC_CALLBACK_1(CZodiacManager::onPauseItemCallback, this));

	////////////ʹ����ʱ����ʾ ����/////////////

	auto m_score = CScore::getInstance();

	//ʹ�õ��ߵ���������
	m_delayNum = std::min(m_score->getInstance()->getPropDelay(), 5);
	m_hintNum = std::min(m_score->getInstance()->getPropHint(), 5);

	//��ʱ����
	Sprite* spriteNor5;
	Sprite* spriteSel5;

	if (m_score->getPropDelay() > 0)
	{
		spriteNor5 = Sprite::createWithTexture(m_textureCache->getTextureForKey("prop_delay.png"));
		spriteSel5 = Sprite::createWithTexture(m_textureCache->getTextureForKey("prop_delay.png"));
	}
	else
	{
		spriteNor5 = Sprite::createWithTexture(m_textureCache->getTextureForKey("prop_delay1.png"));
		spriteSel5 = Sprite::createWithTexture(m_textureCache->getTextureForKey("prop_delay1.png"));
	}

	spriteSel5->setScale(1.2);

	delayItem = MenuItemSprite::create(
		spriteNor5,
		spriteSel5
		);
	delayItem->setCallback(CC_CALLBACK_1(CZodiacManager::onDelayItemCallback, this));

	//��ʱ��������
	m_labelDelay = Label::createWithCharMap(
		"digital.png",
		20, 24,
		'0');
	m_labelDelay->setString(String::createWithFormat("%d", m_score->getPropDelay())->_string);
	m_labelDelay->setAlignment(TextHAlignment::LEFT);
	m_labelDelay->setAnchorPoint(Vec2(0, 0));
	m_labelDelay->setPosition(Vec2(delayItem->getContentSize().width*1.5, m_row*Grid_Width));
	this->addChild(m_labelDelay);

	//��ʾ����
	Sprite* spriteNor6;
	Sprite* spriteSel6;

	if (m_score->getPropHint() > 0)
	{
		spriteNor6 = Sprite::createWithTexture(m_textureCache->getTextureForKey("prop_hint.png"));
		spriteSel6 = Sprite::createWithTexture(m_textureCache->getTextureForKey("prop_hint.png"));
	}
	else
	{
		spriteNor6 = Sprite::createWithTexture(m_textureCache->getTextureForKey("prop_hint1.png"));
		spriteSel6 = Sprite::createWithTexture(m_textureCache->getTextureForKey("prop_hint1.png"));
	}

	spriteSel6->setScale(1.2);

	hintItem = MenuItemSprite::create(
		spriteNor6,
		spriteSel6
		);
	hintItem->setCallback(CC_CALLBACK_1(CZodiacManager::onHintItemCallback, this));

	//��ʾ��������
	m_labelHint = Label::createWithCharMap(
		"digital.png",
		20, 24,
		'0');
	m_labelHint->setString(String::createWithFormat("%d", m_score->getPropHint())->_string);
	m_labelHint->setAlignment(TextHAlignment::LEFT);
	m_labelHint->setAnchorPoint(Vec2(0, 0));
	m_labelHint->setPosition(Vec2(delayItem->getContentSize().width * 3, m_row*Grid_Width));
	this->addChild(m_labelHint);

	auto menu1 = Menu::create(pauseItem, delayItem, hintItem, nullptr);
	menu1->alignItemsHorizontallyWithPadding(hintItem->getContentSize().width / 2);
	menu1->setAnchorPoint(Vec2(0, 0));
	menu1->setPosition(Vec2(hintItem->getContentSize().width * 2, m_row*Grid_Width+m_labelHint->getContentSize().height*2));
	addChild(menu1);

	return true;
}

/////////////��ȡ��Ϸ����/////////////////////

int CZodiacManager::getReducing()
{
	return m_bar->getPercent();
}

/////////////�趨��Ϸ����/////////////////////
void CZodiacManager::addReducing()
{
	if (m_bar->getPercent()<100)
	{
		m_bar->setPercent(m_bar->getPercent() + 2);
	}
}

//������Ϸ������
void CZodiacManager::onReducingBonus(float dt)
{
	m_bar->setPercent(m_bar->getPercent() - 1);
	log("Percent %lf", m_bar->getPercent());

	auto m_upScore = CScore::getInstance();
	//����ʱ��������Ϸ������������Ϸ����
	if (m_bar->getPercent() == 0 || m_upScore->getCurScore() >= m_upScore->getNextScore())
	{
		this->unschedule(schedule_selector(CZodiacManager::onReducingBonus));

		log("game over!");
	}
}

//��� ��Ф������
void CZodiacManager::deleteZodiacGroup()
{
	for (int i = 0; i < m_row; i++)
	{
		for (int j = 0; j < m_col; j++)
		{
			m_zodiacBox[i][j]->removeFromParent();
		}
	}

	log("delete a CZodiacManager!");
}

//���� ��Ф������
void CZodiacManager::updateZodiacGroup()
{
	for (int i = 0; i < m_row; i++)
	{
		for (int j = 0; j < m_col; j++)
		{
			m_zodiacBox[i][j]->removeFromParent();
			m_zodiacBox[i][j] = createZodiac(i, j);
		}
	}
	log("update a new CZodiacManager!");
}

//�ж� ��Ф������ �Ƿ� �Ѳ����ƶ�
bool CZodiacManager::isDeadZodiacGroup()
{
	bool bRect = true;

	//�������� lambda���ʽ
	auto swap = [](CZodiac** lhs, CZodiac** rhs)
	{
		auto temp = *lhs;
		*lhs = *rhs;
		*rhs = temp;
	};

	for (int i = 0; i < m_row; i++)
	{
		if (isZodiacDestory())
		{
			bRect = false;
			break;;
		}
		
		for (int j = 0; j < m_col; j++)
		{
			//����߽���
			if (i>0)
			{
				swap(&m_zodiacBox[i][j], &m_zodiacBox[i-1][j]);
				if (isZodiacDestory())
				{
					bRect = false;
					swap(&m_zodiacBox[i][j], &m_zodiacBox[i-1][j]);
					break;;
				}
				swap(&m_zodiacBox[i][j], &m_zodiacBox[i-1][j]);
			}

			//���ұ߽���
			if (i<m_col-1)
			{
				swap(&m_zodiacBox[i][j], &m_zodiacBox[i+1][j]);
				if (isZodiacDestory())
				{
					bRect = false;
					swap(&m_zodiacBox[i][j], &m_zodiacBox[i+1][j]);
					break;;
				}
				swap(&m_zodiacBox[i][j], &m_zodiacBox[i+1][j]);
			}

			//���±߽���
			if (j > 0)
			{
				swap(&m_zodiacBox[i][j], &m_zodiacBox[i][j - 1]);
				if (isZodiacDestory())
				{
					bRect = false;
					swap(&m_zodiacBox[i][j], &m_zodiacBox[i][j - 1]);
					break;;
				}
				swap(&m_zodiacBox[i][j], &m_zodiacBox[i][j - 1]);
			}

			//���ϱ߽���
			if (j < m_row-1)
			{
				swap(&m_zodiacBox[i][j], &m_zodiacBox[i][j + 1]);
				if (isZodiacDestory())
				{
					bRect = false;
					swap(&m_zodiacBox[i][j], &m_zodiacBox[i][j + 1]);
					break;;
				}
				swap(&m_zodiacBox[i][j], &m_zodiacBox[i][j + 1]);
			}
		}
	}

	m_destoryZodiacBox.clear();

	return bRect;
}
/////////////////////������Ф����/////////////////////////

//������Ф����
CZodiac* CZodiacManager::createZodiac(int row, int col)
{
	CZodiac* m_zodiac = nullptr;

	//����һ���Ϸ�����Ф����
	while (1)
	{
		if (1==CScore::getInstance()->getGameDegree())
		{
			m_zodiac = CZodiac::create(cocos2d::random(First_Zodiac_Id, Easy_Zodiac_Id), Vec2(row, col));
		}
		else if (2 == CScore::getInstance()->getGameDegree())
		{
			m_zodiac = CZodiac::create(cocos2d::random(First_Zodiac_Id, Normal_Zodiac_Id), Vec2(row, col));
		}
		else if (3 == CScore::getInstance()->getGameDegree())
		{
			m_zodiac = CZodiac::create(cocos2d::random(First_Zodiac_Id, Hard_Zodiac_Id), Vec2(row, col));
		}
		if (isWellZodiac(m_zodiac,row,col))
		{
			break;
		}
	}

	//������Ф�����λ��
	setZodiacPos(m_zodiac, row, col);

	this->addChild(m_zodiac);

	return m_zodiac;
}

//�ж���������Ф�����Ƿ�Ϸ�
bool CZodiacManager::isWellZodiac(CZodiac* zodiac, int row, int col)
{
	/***************************************************************************/
	/*������Ф������Ĵ���˳��ֻ���ж��´�����Ф������ �������·����Ƿ�Ϸ�*/
	/*������x�ᡢy�� �������жϼ���                                            */
	/***************************************************************************/

	bool m_bWellRow = true;
	bool m_bWellCol = true;

	if (row>1)
	{
		if ((zodiac->getType() == m_zodiacBox[row - 1][col]->getType()) && (zodiac->getType() == m_zodiacBox[row - 2][col]->getType()))
		{
			m_bWellRow = false;
		}
	}

	if (col>1)
	{
		if ((zodiac->getType() == m_zodiacBox[row][col - 1]->getType()) && (zodiac->getType() == m_zodiacBox[row][col - 2]->getType()))
		{
			m_bWellCol = false;
		}
	}

	return m_bWellCol&&m_bWellRow;
}

//������Ф�����λ��
void CZodiacManager::setZodiacPos(CZodiac* zodiac, float row, float col)
{
	zodiac->setPosition(Vec2(row*Grid_Width, col*Grid_Width));
}


////////////////////������Ф����////////////////////////////////

//������Ф����λ��
void CZodiacManager::swapZodiacPos(CZodiac* lhs, CZodiac* rhs)
{
	//��ͣ�¼�����
	_eventDispatcher->pauseEventListenersForTarget(this);

	//������Ф��������Ф�������λ��
	auto m_temp1 = m_zodiacBox[lhs->getPos().x][lhs->getPos().y];
	m_zodiacBox[lhs->getPos().x][lhs->getPos().y] = m_zodiacBox[rhs->getPos().x][rhs->getPos().y];
	m_zodiacBox[rhs->getPos().x][rhs->getPos().y] = m_temp1;

	//����������Ф�����λ��
	auto m_temp2 = lhs->getPos();
	lhs->setPos(rhs->getPos());
	rhs->setPos(m_temp2);

	//�ƶ���Ф�����λ��
	moveZodiacToNewPos(lhs);
	moveZodiacToNewPos(rhs);
}

//�ƶ���Ф����λ��
void CZodiacManager::moveZodiacToNewPos(CZodiac* zodiac)
{
	zodiac->setSwaping(true);
	auto m_action = MoveTo::create(Move_Speed, Vec2(zodiac->getPos().x*Grid_Width,zodiac->getPos().y*Grid_Width));
	auto m_call = CallFunc::create([zodiac]()
	{
		zodiac->setSwaping(false);
	}
	);

	zodiac->runAction(Sequence::create(m_action, m_call, nullptr));
}

//ˢ����Ф������
void CZodiacManager::refreshZodiacGrid()
{
	int m_count;
	for (int i = 0; i < m_row; i++)
	{
		m_count = 0;
		for (int j = 0; j < m_col; j++)
		{
			if (!m_zodiacBox[i][j])
			{
				++m_count;
				break;
			}
		}
		if (m_count)
		{
			refreshZodiacByCol(i);
		}
	}
}

//�� �� ˢ����Ф������
void CZodiacManager::refreshZodiacByCol(int col)
{
	int m_count = 0;	
	auto m_pZodiacBox = &m_zodiacBox;

	//֮ǰ����Ф��������
	for (int i = 0; i < m_col; i++)
	{
		auto m_zodiac = m_zodiacBox[col][i];
		if (!m_zodiac)
		{
			++m_count;
		}
		else if (m_count)
		{
			m_zodiac->setPos(Vec2(m_zodiac->getPos().x, m_zodiac->getPos().y - m_count));

			auto m_action = MoveBy::create(Move_Speed, Vec2(0, -m_count*Grid_Width));
			auto m_call = CallFunc::create([m_pZodiacBox,m_zodiac]()
			{
				(*m_pZodiacBox)[m_zodiac->getPos().x][m_zodiac->getPos().y] = m_zodiac;
			}
			);

			m_zodiac->runAction(Sequence::create(m_action,m_call,nullptr));
		}
	}

	//�µ���Ф��������
	int m_delta = 1;
	for (auto m_zodiac : m_newZodiacBox)
	{
		if (col==m_zodiac->getPos().x)
		{
			m_zodiac->setPos(Vec2(m_zodiac->getPos().x, m_col - m_count));

			auto m_action = MoveBy::create(Move_Speed*m_delta++, Vec2(0,-m_count--*Grid_Width));
			auto m_call = CallFunc::create([m_zodiac,m_pZodiacBox,this]()
			{
				(*m_pZodiacBox)[m_zodiac->getPos().x][m_zodiac->getPos().y] = m_zodiac;
				m_newZodiacBox.eraseObject(m_zodiac);
			}
			);

			m_zodiac->runAction(Sequence::create(DelayTime::create(Move_Speed),m_action, m_call, nullptr));
		}
	}


}

bool CZodiacManager::onTouchBegan(Touch* touch, Event* unused_event)
{
	auto m_beganPos = this->convertToNodeSpace(touch->getLocation());

	//�ж� ������ �Ƿ�����Ф����������
	if (Rect(0,0,m_row*Grid_Width,m_col*Grid_Width).containsPoint(m_beganPos))
	{
		int m_beganPosX = m_beganPos.x / Grid_Width;
		int m_beganPosY = m_beganPos.y / Grid_Width;

		m_zodiacSelected = m_zodiacBox[m_beganPosX][m_beganPosY];

		log("touch coordinate: x=%d,y=%d jewel's type:%d", m_beganPosX, m_beganPosY, m_zodiacSelected->getType());

		return true;
	}
	
	return false;
}

void CZodiacManager::onTouchMoved(Touch* touch, Event* unused_event)
{
	if (!m_zodiacSelected)
	{
		return;
	}

	auto m_beganPos = m_zodiacSelected->getPos();
	auto m_movePos = this->convertToNodeSpace(touch->getLocation());
	int m_movePosX = m_movePos.x / Grid_Width;
	int m_movePosY = m_movePos.y / Grid_Width;
	auto m_touchedPos = Vec2(m_movePosX, m_movePosY);

	//�ж� ������ �Ƿ��� ��Ф������ �� && �ж� ��ǰ������ �� ֮ǰ������ �Ƿ���ͬһ����
	if (!Rect(0, 0, m_row*Grid_Width, m_col*Grid_Width).containsPoint(m_movePos) || (m_touchedPos == m_beganPos))
	{
		return;
	}

	//�ж� ��ǰ������ �� ֮ǰ������ �Ƿ�ͬ�С���
	if (abs(m_beganPos.x - m_touchedPos.x) + abs(m_beganPos.y - m_touchedPos.y)!=1)
	{
		return;
	}

	m_zodiacSwaped = m_zodiacBox[m_touchedPos.x][m_touchedPos.y];

	//������Ф����
	swapZodiacPos(m_zodiacSelected, m_zodiacSwaped);

	//���� ��Ф���齻��״̬
	this->schedule(schedule_selector(CZodiacManager::onZodiacSwaping));
	
}

/////////////////������Ф����////////////////////////

//�ж��Ƿ��ܹ�����
bool CZodiacManager::isZodiacDestory()
{
	int m_count = 0;
	int i, j;
	CZodiac* m_zodiacFirst = nullptr;
	CZodiac* m_zodiacNext = nullptr;
	//���б���
	for (i = 0; i < m_row; i++)
	{
		for (j = 0; j < m_col-2;)
		{
			m_count = 1;
			m_zodiacFirst = m_zodiacBox[i][j];
			m_zodiacNext = m_zodiacBox[i][j+1];
			while (m_zodiacFirst->getType()==m_zodiacNext->getType())
			{
				++m_count;
				if (j+m_count>m_col-1)
				{
					break;
				}

				m_zodiacNext = m_zodiacBox[i][j + m_count];
			}

			if (m_count>=3)
			{
				for (int y = 0; y < m_count;y++)
				{
					auto m_zoidac = m_zodiacBox[i][j + y];
					m_destoryZodiacBox.pushBack(m_zoidac);
				}
			}

			j += m_count;
		}
	}

	//���б���
	for (i = 0; i < m_row; i++)
	{
		for (j = 0; j < m_col - 2;)
		{
			m_count = 1;
			m_zodiacFirst = m_zodiacBox[j][i];
			m_zodiacNext = m_zodiacBox[j+1][i];
			while (m_zodiacFirst->getType() == m_zodiacNext->getType())
			{
				++m_count;
				if (j + m_count>m_col - 1)
				{
					break;
				}

				m_zodiacNext = m_zodiacBox[j + m_count][i];
			}

			if (m_count >= 3)
			{
				for (int y = 0; y < m_count; y++)
				{
					auto m_zoidac = m_zodiacBox[j + y][i];

					//��ֹ�ظ����
					if (m_destoryZodiacBox.find(m_zoidac) != m_destoryZodiacBox.end())
					{
						continue;
					}

					m_destoryZodiacBox.pushBack(m_zoidac);
				}
			}

			j += m_count;
		}
	}

	if (m_destoryZodiacBox.empty())
	{
		return false;
	}

	return true;

}

//����
void CZodiacManager::zodiacDestory()
{
	for (auto m_zodiac : m_destoryZodiacBox)
	{
		CZodiac* newZodiac = nullptr;
		if (1 == CScore::getInstance()->getGameDegree())
		{
			newZodiac = CZodiac::create(cocos2d::random(First_Zodiac_Id, Easy_Zodiac_Id), Vec2(m_zodiac->getPos().x, m_col));
		}
		else if (2 == CScore::getInstance()->getGameDegree())
		{
			newZodiac = CZodiac::create(cocos2d::random(First_Zodiac_Id, Normal_Zodiac_Id), Vec2(m_zodiac->getPos().x, m_col));
		}
		else if (3 == CScore::getInstance()->getGameDegree())
		{
			newZodiac = CZodiac::create(cocos2d::random(First_Zodiac_Id, Hard_Zodiac_Id), Vec2(m_zodiac->getPos().x, m_col));
		}
//		auto newZodiac = CZodiac::create(random(First_Zodiac_Id, Last_Zodiac_Id), Vec2(m_zodiac->getPos().x, m_col));
		setZodiacPos(newZodiac, newZodiac->getPos().x, m_col);
		this->addChild(newZodiac);

		m_newZodiacBox.pushBack(newZodiac);

		m_zodiacBox[m_zodiac->getPos().x][m_zodiac->getPos().y] = nullptr;

		//������Ч
		showParticleEffect(m_zodiac->getPosition(), this);

		//����
		m_zodiac->fDestory();	
		
		//���·���
		CScore::getInstance()->addCurScore();

		//���½���
		this->addReducing();

	}

	//���·�����ʾ
	m_scoreLevel->RefreshScore();

	//�������� �ɹ�
	if (AudioController::getInstance()->isMusicOpen())
	{
		AudioController::getInstance()->changeYes();
	}
}

/////////////////��Ϸ״̬////////////////////////

//���ڽ�����Ф����
void CZodiacManager::onZodiacSwaping(float dt)
{
	//��� ��ǰѡ���� �� ������ ��û������ϣ��� ���ؼ�������
	if (m_zodiacSelected->isSwaping() || m_zodiacSwaped->isSwaping())
	{
		return;
	}
	else
	{
		//ֹͣ ����״̬
		this->unschedule(schedule_selector(CZodiacManager::onZodiacSwaping));

		log("swap over!");

		//�������֮���Ƿ��������
		if (isZodiacDestory())
		{
			/////////////����///////////////

			log("yes,crush!");

			m_zodiacSelected = nullptr;

			//���� ��Ф����
			zodiacDestory();

			//���� ����״̬
			this->schedule(schedule_selector(CZodiacManager::onZodiacDestory));
		}
		else
		{
			log("no, cant crush!");

			//�������� ʧ��
			if (AudioController::getInstance()->isMusicOpen())
			{
				AudioController::getInstance()->changeNo();
			}

			//�ָ�Ϊ ����֮ǰ��״̬
			swapZodiacPos(m_zodiacSelected, m_zodiacSwaped);

			//���� ����״̬
			this->schedule(schedule_selector(CZodiacManager::onZodiacSwapingBack));
		}
	}

}

//������Ф�������
void CZodiacManager::onZodiacSwapingBack(float dt)
{
	if (m_zodiacSelected->isSwaping() || m_zodiacSwaped->isSwaping())
	{
		return;
	}
	else
	{
		log("swap back!");

		//ֹͣ ��������״̬
		this->unschedule(schedule_selector(CZodiacManager::onZodiacSwapingBack));

		m_zodiacSelected = nullptr;

		//�ָ��¼�����
		_eventDispatcher->resumeEventListenersForTarget(this);
	}

}

//����������Ф����
void CZodiacManager::onZodiacDestory(float dt)
{
	//�������Ф���������������� ���ؼ�������
	for (auto m_zodiac : m_destoryZodiacBox)
	{
		if (m_zodiac->isDestory())
		{
			return;
		}
	}

	this->unschedule(schedule_selector(CZodiacManager::onZodiacDestory));

	//��� ������Ф��������
	m_destoryZodiacBox.clear();

	log("crush over!");
	log("begin to refresh!");

	//ˢ����Ф������
	refreshZodiacGrid();

	//����ˢ��״̬
	this->schedule(schedule_selector(CZodiacManager::onZodiacRefreshing));
}

//����֮��ˢ��
void CZodiacManager::onZodiacRefreshing(float dt)
{
	if (0==m_newZodiacBox.size())
	{
		this->unschedule(schedule_selector(CZodiacManager::onZodiacRefreshing));

		if (isZodiacDestory())
		{
			zodiacDestory();

			this->schedule(schedule_selector(CZodiacManager::onZodiacDestory));
		}
		else
		{
			if (isDeadZodiacGroup())
			{
				log("Dead!");

				auto m_pos = Director::getInstance()->getWinSize();

				auto m_label = Label::createWithTTF("Now is a Dead Group, Change...", "fonts/DFPShaoNvW5-GB.ttf", 35);
				m_label->setTextColor(Color4B::BLACK);
				m_label->setPosition(Vec2(m_pos.width/2,m_pos.height/3*2));
				this->getParent()->addChild(m_label);

				auto m_action1 = FadeIn::create(Move_Speed);
				auto m_action2 = FadeOut::create(Move_Speed);

				auto m_call = CallFunc::create([this,m_label]()
				{
					do 
					{
						updateZodiacGroup();
					} while (isDeadZodiacGroup());

					m_label->removeFromParent();

					_eventDispatcher->resumeEventListenersForTarget(this);
				}
				);

				m_label->runAction(Sequence::create(m_action1, m_action2, m_call, nullptr));

			}
			else
			{
				_eventDispatcher->resumeEventListenersForTarget(this);
			}
		}

	}
	else
	{
		return;
	}
}


//��ͣ��Ϸ
void CZodiacManager::onPauseItemCallback(Ref* ref)
{
	if (AudioController::getInstance()->isMusicOpen())
	{
		AudioController::getInstance()->changeScene();
	}

	RenderTexture *renderTexture = RenderTexture::create(320, 540);
	renderTexture->begin();
	this->getParent()->visit();
	renderTexture->end();

	//����������
	auto scene = GamePause::createScene(renderTexture);
	Director::getInstance()->pushScene(scene);
}

void CZodiacManager::useDelayProp()
{
	if (m_bar->getPercent() < 100)
	{
		m_bar->setPercent(m_bar->getPercent() + 20);
	}
}


void CZodiacManager::useHintProp()
{
	//�������� lambda���ʽ
	auto swap = [](CZodiac** lhs, CZodiac** rhs)
	{
		auto temp = *lhs;
		*lhs = *rhs;
		*rhs = temp;
	};

	CZodiac* m_zodiac1 = nullptr;
	CZodiac* m_zodiac2 = nullptr;

	for (int i = 0; i < m_row; i++)
	{

		for (int j = 0; j < m_col; j++)
		{
			//����߽���
			if (i>0)
			{
				swap(&m_zodiacBox[i][j], &m_zodiacBox[i - 1][j]);
				if (isZodiacDestory())
				{
					swap(&m_zodiacBox[i][j], &m_zodiacBox[i - 1][j]);

					m_zodiac1 = m_zodiacBox[i][j];
					m_zodiac1->runAction(Blink::create(0.5, 3));

					m_zodiac2 = m_zodiacBox[i - 1][j];
					m_zodiac2->runAction(Blink::create(0.5, 3));

					m_destoryZodiacBox.clear();
					return;
				}
				swap(&m_zodiacBox[i][j], &m_zodiacBox[i - 1][j]);
			}

			//���ұ߽���
			if (i < m_col - 1)
			{
				swap(&m_zodiacBox[i][j], &m_zodiacBox[i + 1][j]);
				if (isZodiacDestory())
				{
					swap(&m_zodiacBox[i][j], &m_zodiacBox[i + 1][j]);
					
					m_zodiac1 = m_zodiacBox[i][j];
					m_zodiac1->runAction(Blink::create(0.5, 3));

					m_zodiac2 = m_zodiacBox[i + 1][j];
					m_zodiac2->runAction(Blink::create(0.5, 3));

					m_destoryZodiacBox.clear();

					return;
				}
				swap(&m_zodiacBox[i][j], &m_zodiacBox[i + 1][j]);
			}

			//���±߽���
			if (j > 0)
			{
				swap(&m_zodiacBox[i][j], &m_zodiacBox[i][j - 1]);
				if (isZodiacDestory())
				{
					swap(&m_zodiacBox[i][j], &m_zodiacBox[i][j - 1]);

					m_zodiac1 = m_zodiacBox[i][j];
					m_zodiac1->runAction(Blink::create(0.5, 3));

					m_zodiac2 = m_zodiacBox[i][j-1];
					m_zodiac2->runAction(Blink::create(0.5, 3));

					m_destoryZodiacBox.clear();

					return;
				}
				swap(&m_zodiacBox[i][j], &m_zodiacBox[i][j - 1]);
			}

			//���ϱ߽���
			if (j < m_row - 1)
			{
				swap(&m_zodiacBox[i][j], &m_zodiacBox[i][j + 1]);
				if (isZodiacDestory())
				{
					swap(&m_zodiacBox[i][j], &m_zodiacBox[i][j + 1]);
					
					m_zodiac1 = m_zodiacBox[i][j];
					m_zodiac1->runAction(Blink::create(0.5, 3));

					m_zodiac2 = m_zodiacBox[i][j+1];
					m_zodiac2->runAction(Blink::create(0.5, 3));

					m_destoryZodiacBox.clear();

					return;
				}
				swap(&m_zodiacBox[i][j], &m_zodiacBox[i][j + 1]);
			}
		}
	}
}

//ʹ�õ��� ��ʱ
void CZodiacManager::onDelayItemCallback(Ref* ref)
{
	auto m_score = CScore::getInstance();

	auto m_textureCache = TextureCache::getInstance();

	if (m_delayNum <= 0)
	{
		if (AudioController::getInstance()->isMusicOpen())
		{
			AudioController::getInstance()->clickNo();
		}

		return;
	}

	if (AudioController::getInstance()->isMusicOpen())
	{
		AudioController::getInstance()->useProp();
	}

	if (1 == m_delayNum)
	{
		m_score->usePropDelay(1);
		m_score->storePropDelay();

		auto spriteNor1 = Sprite::createWithTexture(m_textureCache->getTextureForKey("prop_delay1.png"));
		auto spriteSel1 = Sprite::createWithTexture(m_textureCache->getTextureForKey("prop_delay1.png"));
		spriteSel1->setScale(1.2);

		delayItem->setNormalImage(spriteNor1);
		delayItem->setSelectedImage(spriteSel1);
	}
	else
	{
		m_score->usePropDelay(1);
		m_score->storePropDelay();
	}

	--m_delayNum;
	m_labelDelay->setString(String::createWithFormat("%d", m_score->getPropDelay())->_string);

	//��ʱ
	useDelayProp();
}

//ʹ�õ��� ��ʾ
void CZodiacManager::onHintItemCallback(Ref* ref)
{
	auto m_score = CScore::getInstance();

	auto m_textureCache = TextureCache::getInstance();

	if (m_hintNum <= 0)
	{
		if (AudioController::getInstance()->isMusicOpen())
		{
			AudioController::getInstance()->clickNo();
		}

		return;
	}

	if (AudioController::getInstance()->isMusicOpen())
	{
		AudioController::getInstance()->useProp();
	}

	if (1 == m_hintNum)
	{
		m_score->usePropHint(1);
		m_score->storePropHint();

		auto spriteNor1 = Sprite::createWithTexture(m_textureCache->getTextureForKey("prop_hint1.png"));
		auto spriteSel1 = Sprite::createWithTexture(m_textureCache->getTextureForKey("prop_hint1.png"));
		spriteSel1->setScale(1.2);

		hintItem->setNormalImage(spriteNor1);
		hintItem->setSelectedImage(spriteSel1);
	}
	else
	{
		m_score->usePropHint(1);
		m_score->storePropHint();
	}

	--m_hintNum;
	m_labelHint->setString(String::createWithFormat("%d", m_score->getPropHint())->_string);

	//��ʾ
	useHintProp();
}