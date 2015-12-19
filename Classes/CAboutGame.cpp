/*
************************************************************************
*
*	CAboutGame.cpp
*	Author: ���Ƿ�
*   describe: ��Ϸ�淨����Ϸ����
*
************************************************************************
*/

#include "CAboutGame.h"
#include "GameStart.h"
#include "AudioController.h"


// ����һ����̬�ĳ�������
Scene* CAboutGame::createScene()
{
	// ��scene��������
	Scene *myscene = Scene::create();

	// ����һ��layer
	CAboutGame *mylayer = CAboutGame::create();

	// �����layer���뵽scene��
	myscene->addChild(mylayer);

	// ����scene
	return myscene;
}


// ��ʼ��
bool CAboutGame::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visible = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto m_textureCache = TextureCache::getInstance();

	//����
	auto bg = Sprite::createWithTexture(
		m_textureCache->getTextureForKey("select_degree.jpg"));
	bg->setPosition(Vec2(visible.width / 2, visible.height / 2));
	this->addChild(bg);

	//��ʾ���ݵľ��� tag = 1005
	ptb = Sprite::create("game_explain1.png");
	ptb->setPosition(Vec2(visible.width/2,visible.height*0.4));
	this->addChild(ptb, 1, 1005);

	//��ʾҳ��
	ptc = Sprite::create("page1.png");
	ptc->setPosition(Vec2(visible.width-ptc->getContentSize().width*0.5, origin.y+ptc->getContentSize().height*0.5));
//	ptc->setAnchorPoint(Vec2(1.2,-0.2));
	this->addChild(ptc, 1,2005);


	//ǰһҳ tag = 1001
	Scale9Sprite *sp1 = Scale9Sprite::create("left.png");
	ControlButton *pbt1 = ControlButton::create(sp1);
	pbt1->setEnabled(false);
	pbt1->setPosition(Vec2(visible.width/4,visible.height*3/4));
	pbt1->setPreferredSize(Size(37, 42));

	//��һҳ tag = 1002
	Scale9Sprite *sp2 = Scale9Sprite::create("right.png");
	ControlButton *pbt2 = ControlButton::create(sp2);
	pbt2->setPosition(Vec2(visible.width *3/ 4, visible.height * 3 / 4));
	pbt2->setPreferredSize(Size(37, 42));

	//���¼�
	pbt1->addTargetWithActionForControlEvents(
		this,
		cccontrol_selector(CAboutGame::upInsideAction),
		Control::EventType::TOUCH_UP_INSIDE);
	pbt2->addTargetWithActionForControlEvents(
		this,
		cccontrol_selector(CAboutGame::upInsideAction),
		Control::EventType::TOUCH_UP_INSIDE);


	this->addChild(pbt1, 1, 1001);
	this->addChild(pbt2, 1, 1002);


	//���ذ�ť
	Scale9Sprite *spback = Scale9Sprite::create("return.png");
	ControlButton *pbtbk = ControlButton::create(spback);
	pbtbk->setPosition(Vec2(visible.width/8,visible.height*7/8));
	pbtbk->setPreferredSize(Size(64, 54));
	pbtbk->addTargetWithActionForControlEvents(
		this,
		cccontrol_selector(CAboutGame::backToMenu),
		Control::EventType::TOUCH_UP_INSIDE);
	this->addChild(pbtbk, 2);


	//����������Ч, CCParticleRain
	auto *p1 = ParticleRain::create();
	p1->setAutoRemoveOnFinish(true);
	p1->setSpeed(1.0f);
	p1->setStartSize(8);
	p1->setPositionType(ParticleSystem::PositionType::FREE);
	p1->setPosition(Vec2(visible.width/2,visible.height/2));
	this->addChild(p1,1);

	return true;
}


void CAboutGame::upInsideAction(Ref * sender, Control::EventType controlEvent)
{

	if (AudioController::getInstance()->isMusicOpen())
	{
		AudioController::getInstance()->clickOk();
	}

	Size mysize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	int tb = 1001;
	if (sender == this->getChildByTag(1001))  //��һҳ
	{
		tb = 1001;
	}
	else if (sender == this->getChildByTag(1002))  //��һҳ
	{
		tb = 1002;
	}

	//����
	auto *ac1 = SkewTo::create(0.2f, 67.2f, -67.2f);
	auto *ac2 = ScaleTo::create(0.2f,0.1);
	auto *act1 = Spawn::createWithTwoActions(ac1, ac2);

	//�л�, ��Ч��/�ָ���ť
	auto * change0 = CallFuncN::create(CC_CALLBACK_1(CAboutGame::tbChange0, this, (void *)tb));
	auto * change = CallFuncN::create(CC_CALLBACK_1(CAboutGame::tbChange, this, (void *)tb));
	CallFunc * no = CallFunc::create(CC_CALLBACK_0(CAboutGame::disable, this));
	CallFunc * yes = CallFunc::create(CC_CALLBACK_0(CAboutGame::enable, this));

	//����
	auto *ac3 = SkewTo::create(0.3f, 0, 0);
	auto *ac4 = ScaleTo::create(0.3f, 1.0);
	auto *act2 = Spawn::createWithTwoActions(ac3, ac4);

	auto *act3 = Sequence::create(no, act1, change, act2, yes, NULL);	
	ptb->runAction(act3);

	//���뵭���Ķ���
	auto *act4 = Sequence::create(FadeOut::create(0.3f), change0, FadeIn::create(0.2f), nullptr);
	ptc->runAction(act4);
}

//�л�ҳ��
void CAboutGame::tbChange0(Node * node, void *a)
{
	int op = (int)a;
	char tc[111];
	if (op == 1001) //��������
	{
		if (ptc->getTag() <= 2005)
		{
			return;
		}
		else
		{
			switch (ptc->getTag())
			{
			case 2008:
			{
						 strcpy(tc, "page3.png");
						 ptc->setTag(2007);
						 break;
			}
			case 2007:
			{
						 strcpy(tc, "page2.png");
						 ptc->setTag(2006);
						 break;
			}
			case 2006:
			{
						 strcpy(tc, "page1.png");
						 ptc->setTag(2005);
						 break;
			}
			default:
				break;
			}
		}
	}
	else if (op == 1002) //��Ϸ����
	{
		if (ptc->getTag() >= 2008)
		{
			return;
		}
		else
		{
			switch (ptc->getTag())
			{
			case 2007:
			{
						 strcpy(tc, "page4.png");
						 ptc->setTag(2008);
						 break;
			}
			case 2006:
			{
						 strcpy(tc, "page3.png");
						 ptc->setTag(2007);
						 break;
			}
			case 2005:
			{
						 strcpy(tc, "page2.png");
						 ptc->setTag(2006);
						 break;
			}
			default:
				break;
			}
		}
	}

	Texture2D *text2d1 = Director::getInstance()->getTextureCache()->addImage(tc);
	ptc->setTexture(text2d1);
}

//�л�����
void CAboutGame::tbChange(Node * node, void *a)
{
	int op = (int)a;
	char tb[111];
	if (op == 1001)
	{
		if (ptb->getTag()<=1005)
		{
			return;
		}
		else
		{
			switch (ptb->getTag())
			{
				case 1008:
				{
					strcpy(tb, "game_explain3.png");
					ptb->setTag(1007);
					break;
				}
				case 1007:
				{
					strcpy(tb, "game_explain2.png");
					ptb->setTag(1006);
					break;
				}
				case 1006:
				{
					strcpy(tb, "game_explain1.png");
					ptb->setTag(1005);
					break;
				}
				default:
					break;
				}
		}
	}
	else if (op == 1002) //��Ϸ����
	{
		if (ptb->getTag() >= 1008)
		{
			return;
		}
		else
		{
			switch (ptb->getTag())
			{
				case 1007:
				{
					strcpy(tb, "game_explain4.png");
					ptb->setTag(1008);
					break;
				}
				case 1006:
				{
					strcpy(tb, "game_explain3.png");
					ptb->setTag(1007);
					break;
				}
				case 1005:
				{
					strcpy(tb, "game_explain2.png");
					ptb->setTag(1006);
					break;
				}
				default:
					break;
				}
		}
	}

	// �л�
	Texture2D *text2d = Director::getInstance()->getTextureCache()->addImage(tb);
	ptb->setTexture(text2d);
}

//ʹ��ť��Ч��
void CAboutGame::disable()
{
	for (int i = 1001; i <= 1002; i++)
	{
		ControlButton *bt = (ControlButton *)this->getChildByTag(i);
		bt->setEnabled(false);
	}
}

//�ָ���ť
void CAboutGame::enable()
{
	for (int i = 1001; i <= 1002; i++)
	{
		ControlButton *bt = (ControlButton *)this->getChildByTag(i);
		bt->setEnabled(true);
	}
}



//�������˵�
void CAboutGame::backToMenu(Ref* pSender, Control::EventType controlEvent)
{
	if (AudioController::getInstance()->isMusicOpen())
	{
		AudioController::getInstance()->changeScene();
	}

	//��ҳ�л�
	Scene *menuscene = GameStart::createScene();
	auto *tt = TransitionPageTurn::create(0.5f, menuscene, true);
	Director::getInstance()->replaceScene(tt);
}




//��������
void CAboutGame::onEnter()
{
	Layer::onEnter();
}

void CAboutGame::onEnterTransitionDidFinish()
{
	Layer::onEnterTransitionDidFinish();
}

void CAboutGame::onExit()
{
	Layer::onExit();
	this->removeAllChildrenWithCleanup(true);
}
