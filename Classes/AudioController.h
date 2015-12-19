/*
************************************************************************
*
*	AudioController.h
*	Author: ���Ƿ�
*   describe: �������ּ���Ч
*
************************************************************************
*/
#ifndef __AudioController_H__
#define __AudioController_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

class AudioController 
{
public:

	//��ȡʵ��
	static AudioController* getInstance();

	/////////Ԥ���ر������ּ���Ч///////
	void preLoadingAudio();

	/////////�����ܿ���///////
	bool isMusicOpen()
	{
		return m_b;
	}

	void musicOpen()
	{
		m_b = true;
	}

	void musicOff()
	{
		m_b = false;
	}

	/////////���� & ֹͣ ��������///////

	//���ű�������
	void playBackgroundMusic()
	{
		
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("sound/bg.mp3",true);
	}

	//ֹͣ���ű�������
	void stopBackgroundMusic()
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	}

	//��ͣ���ű�������
	void pauseBackgroundMusic()
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
	}

	//�ָ����ű�������
	void resumeBackgroundMusic()
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	}


	/////////������Ч///////

	//������Ϸ
	void loadingMusic()
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/shake.wav");
	}

	//�л�����
	void changeScene()
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/pageChange.wav");
	}

	//�����ɹ�
	void clickOk()
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/click.wav");
	}

	//����ʧ��
	void clickNo()
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/click_error.wav");
	}

	//��Ϸ��ʼ
	void gameStart()
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/start.wav");
	}

	//ʹ�õ���
	void useProp()
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/props.wav");
	}

	//��Ϸʤ��
	void gameWin()
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/win.wav");
	}

	//��Ϸʧ��
	void gameLose()
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/lose.wav");
	}

	//�����ɹ�
	void changeYes()
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/destory.mp3");
	}

	//����ʧ��
	void changeNo()
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound/swapBack.mp3");
	}

	/////////������Ч����///////



private:
	static AudioController* m_audioController;
	bool m_b;
};

#endif