#include "Animation.h"


Animation::Animation(int maxFrame, float speed) : IObject()
{
	this->maxFrame = maxFrame;
	this->speed = speed;
	currentFrame = 0;
	frame = (CSprite**)calloc(maxFrame, sizeof(CSprite));
}


Animation::~Animation()
{
	for (int i = 0; i < maxFrame; i++)	{
		if (frame[i] != NULL) delete frame[i];
	}
	delete frame;
}

void Animation::PushFrame(char *path, int prior)
{
	if (frame[prior] != NULL)
		delete frame[prior];
	frame[prior] = new CSprite(path);
}
void Animation::Update(float eTime)
{
	currentFrame += speed*eTime;
	if (currentFrame >= maxFrame)	{
		currentFrame -= maxFrame;
	}
}
void Animation::Render(D3DXMATRIX *pmat)
{
	IObject::Render(pmat);
	frame[(int)currentFrame]->Render(&mat);
}