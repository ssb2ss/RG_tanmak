#pragma once
#pragma once
#include "inc/fmod.hpp"
#pragma comment(lib,"fmodex_vc.lib")
using namespace FMOD;
#include <windows.h>
#define MaxSound 2	//소리 갯수
#define MaxChannel 2//0번채널 루프음 1번채널 효과음




enum//음악들
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