#pragma once
#include "IObject.h"
#include "Sprite.h"
#include "Timer.h"
class Enemy :
	public IObject
{
public:
	CSprite *sprite;
	float dir;
	int moveSpeed;

	Enemy(int x, int y, float dir, int moveSpeed);
	virtual ~Enemy();

	void Update(float eTime);
	void Render(D3DXMATRIX *pmat);
};