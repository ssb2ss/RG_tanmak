#pragma once
#pragma once
#include "inc/fmod.hpp"
#pragma comment(lib,"fmodex_vc.lib")
using namespace FMOD;
#include <windows.h>
#define MaxSound 2	//�Ҹ� ����
#define MaxChannel 2//0��ä�� ������ 1��ä�� ȿ����




enum//���ǵ�
{
	BGM
};

class SoundMgr
{
public:
	SoundMgr();
	~SoundMgr();

	float effectVolume;
	float loopVolume;

	void Update();
	void playLoopSound(int soundNum);
	void playEffectSound(int soundNum);
	void stopSound(int mode);

	int isPlaying(int mode);

	void upVolume(int mode);
	void downVolume(int mode);
};