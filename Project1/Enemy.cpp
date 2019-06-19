#include "Enemy.h"
#include "Def.h"

Enemy::Enemy(int x, int y, float dir, int moveSpeed) : IObject()
{
	sprite = new CSprite("images/enemy.png");
	pos.x = x - sprite->width / 2;
	pos.y = y - sprite->height / 2;
	this->dir = dir;
	this->moveSpeed = moveSpeed;
}


Enemy::~Enemy()
{
	delete sprite;
}

void Enemy::Update(float eTime){
	if (pos.x < -(sprite->width * 2)) {
		isDelete = true;
	}
	else if (pos.x > WIDTH + (sprite->width * 2)) {
		isDelete = true;
	}
	if (pos.y < -(sprite->height * 2)) {
		isDelete = true;
	}
	else if (pos.y > HEIGHT + (sprite->height * 2)) {
		isDelete = true;
	}
	pos.x += cos(dir)*moveSpeed*eTime;
	pos.y += sin(dir)*moveSpeed*eTime;
}

void Enemy::Render(D3DXMATRIX *pmat){
	IObject::Render(pmat);
	sprite->Render(&mat);
}