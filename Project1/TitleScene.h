#pragma once
#include "IScene.h"
#include "Sprite.h"
class TitleScene :
	public IScene
{
public:
	CSprite *background;
	CSprite *clicktostart;
	CSprite *titleLogo;
	bool isTxtOpUp;
	int bgRed, bgGreen, bgBlue;

	TitleScene(int bgR, int bgG, int bgB);
	~TitleScene();

	void Update(float eTime);
	void Render();
};