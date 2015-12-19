/*
************************************************************************
*
*	AudioController.cpp
*	Author: ���Ƿ�
*   describe: �������ּ���Ч
*
************************************************************************
*/

#include "AudioController.h"
#include "CScore.h"

AudioController* AudioController::m_audioController = nullptr;

//��ȡʵ��
AudioController* AudioController::getInstance()
{
	if (!m_audioController)
	{
		m_audioController = new AudioController();
	}
	return m_audioController;
}

/////////Ԥ���ر������ּ���Ч///////
void AudioController::preLoadingAudio()
{
	//Ԥ���������ļ�

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/shake.wav");

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/pageChange.wav");

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/click.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/click_error.wav");

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/start.wav");
	
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("sound/bg.mp3");

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/props.wav");

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/win.wav");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/lose.wav");

	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/swapBack.mp3");
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect("sound/destory.mp3");

	if (CScore::getInstance()->getIsMusic())
	{
		m_b = true;
	}
	else
	{
		m_b = false;
	}
}