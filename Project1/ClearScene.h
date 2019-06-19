#pragma once
#include "IScene.h"
#include "Sprite.h"
#include "Timer.h"
class ClearScene :
	public IScene
{
public:
	CSprite *background;
	CSprite *clearLogo;
	CSprite *clicktorestart;
	int bgRed, bgGreen, bgBlue;
	bool isTxtOpUp;
	Timer *colorTime;
	double degree, rightdeg, leftdeg;
	float start1, end1, start2, end2, present, easings;
	int cnt, duration;
	bool watchDir;

	ClearScene();
	~ClearScene();

	void Update(float eTime);
	void Render();
	float Lerp(float start, float end, float change);
	float Cubic(float cnt, float change, float duration);
};

