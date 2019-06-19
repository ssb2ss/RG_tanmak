#include "soundMgr.h"

FMOD_SYSTEM *g_System;
FMOD_SOUND *g_Sound[MaxSound];//���� ������ŭ
FMOD_CHANNEL *g_Channel[MaxChannel];//ä�� ������ŭ

SoundMgr::SoundMgr()
{
	FMOD_System_Create(&g_System);
	FMOD_System_Init(g_System, MaxSound, FMOD_INIT_NORMAL, NULL);

	FMOD_System_CreateSound(g_System,"sounds/BGM.mp3",FMOD_LOOP_NORMAL,0,&g_Sound[BGM]);
	/*���� �븻�� ��� ���ư��°� ex)�������<FMOD_LOOP_NORMAL>
	����Ʈ�� �ѹ� ����� �� ex)ȿ����<FMOD_DEFAULT>
	*/
	//FMOD_System_PlaySound(g_System,FMOD_CHANNEL_FREE,g_Sound[0],0,&g_Channel[0]);//��� ���� ���
	/*FMOD_CHANNEL_FREE�� ���� ���� FREE�� ä�� �˾Ƽ� ��Ƽ� ��������*/
	loopVolume = 0.5f;
	effectVolume = 0.8f;//���� �ʱ�ȭ
	playLoopSound(BGM);
}
SoundMgr::~SoundMgr()
{
	for (int i = 0; i < MaxSound; i++)
	{
		FMOD_Sound_Release(g_Sound[i]);//����� �����ֱ�
	}
	FMOD_System_Release(g_System);
	FMOD_System_Close(g_System);
}
void SoundMgr::Update()//�������Ӿ� �о���°Ŷ� ��� ���� �������
{
	FMOD_System_Update(g_System);
	FMOD_Channel_SetVolume(g_Channel[0], loopVolume);
	FMOD_Channel_SetVolume(g_Channel[1], effectVolume);
}

void SoundMgr::playLoopSound(int soundNum)//��ӹݺ���� ������ ���� ���
{
	FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[soundNum], 0, &g_Channel[0]);
}

void SoundMgr::playEffectSound(int soundNum)//�� �� ��� ������ ���� ���
{
	FMOD_System_PlaySound(g_System, FMOD_CHANNEL_FREE, g_Sound[soundNum], 0, &g_Channel[1]);
}

void SoundMgr::upVolume(int mode)//mode 0=loop 1=effect
{
	if (!mode)
	{
		if (loopVolume < 1.0f)
			loopVolume += 0.1f;
	}
	else
	{
		if (effectVolume < 1.0f)
			effectVolume += 0.1f;
	}
}
void SoundMgr::downVolume(int mode)//mode 0=loop 1=effect
{
	if (!mode)
	{
		if (loopVolume > 0.1f)
			loopVolume -= 0.1f;
	}
	else
	{
		if (effectVolume > 1.0f)
			effectVolume -= 0.1f;
	}
}
void SoundMgr::stopSound(int mode)
{
	FMOD_Channel_Stop(g_Channel[mode]);
}
int SoundMgr::isPlaying(int mode)
{
	FMOD_BOOL IsPlaying;
	FMOD_Channel_IsPlaying(g_Channel[0], &IsPlaying);
	return IsPlaying;
}

