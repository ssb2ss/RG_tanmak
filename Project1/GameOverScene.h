#pragma once
#include "IScene.h"
#include "Sprite.h"
class GameOverScene :
	public IScene
{
public:
	CSprite *background;
	CSprite *logo;
	CSprite *clicktorestart;
	int bgRed, bgGreen, bgBlue;
	bool watchDir;
	bool isTxtOpUp;
	double degree, rightdeg, leftdeg;
	float start1, end1, start2, end2, present, easings;
	int cnt, duration;

	GameOverScene(int bgR, int bgG, int bgB);
	~GameOverScene();

	void Update(float eTime);
	void Render();
	float Lerp(float start, float end, float change);
	float Cubic(float cnt, float change, float duration);
};

