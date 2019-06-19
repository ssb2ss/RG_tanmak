#pragma once
#include "IObject.h"
#include "Sprite.h"
class Animation :
	public IObject
{
public:
	int maxFrame;
	float currentFrame;
	float speed;
	CSprite **frame;

	Animation(int maxFrame, float speed);
	~Animation();

	void PushFrame(char *path, int prior);
	void Update(float eTime);
	void Render(D3DXMATRIX *pmat);
};