#pragma once
#include "IObject.h"
#include "Sprite.h"
class Player :
	public IObject
{
public:
	CSprite *sprite;
	float moveSpeed;
	float clickMouseX;
	float clickMouseY;
	D3DXVECTOR2 goalScale;
	int goalRed, goalGreen, goalBlue;

	Player();
	~Player();

	void Update(float eTime);
	void Render(D3DXMATRIX *pmat);
	void playerState();
};