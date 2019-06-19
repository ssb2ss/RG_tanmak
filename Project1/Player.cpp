#include "Player.h"
#include "myFunction.h"


Player::Player() : IObject()
{
	sprite = new CSprite("images/player.png");
	pos.x = 200;
	pos.y = 400;
	sprite->rotationCenter.x = sprite->width / 2;
	sprite->rotationCenter.y = sprite->height / 2;
	sprite->scalingCenter.x = sprite->width / 2;
	sprite->scalingCenter.y = sprite->height / 2;
	moveSpeed = 200.f;
	clickMouseX = pos.x;
	clickMouseY = pos.y;
	goalScale = D3DXVECTOR2(0.5, 0.5);
	goalRed = goalGreen = goalBlue = 0;
	sprite->red = sprite->green = sprite->blue = 0;
}


Player::~Player()
{
	delete sprite;
}

void Player::Update(float eTime){
	sprite->Update(eTime);
	playerState();
	if (pos.x < 0) {
		pos.x = 0;
	}
	else if (pos.x > WIDTH - sprite->width) {
		pos.x = WIDTH - sprite->width;
	}
	if (pos.y < 0) {
		pos.y = 0;
	}
	else if (pos.y > HEIGHT - sprite->height) {
		pos.y = HEIGHT - sprite->height;
	}
}

void Player::Render(D3DXMATRIX *pmat){
	IObject::Render(pmat);
	sprite->Render(&(this->mat));
}

void Player::playerState() {
	pos.x += (clickMouseX - (pos.x + sprite->width / 2)) / 20;
	pos.y += (clickMouseY - (pos.y + sprite->height / 2)) / 20;
	sprite->scale += (goalScale - sprite->scale) / 10;
	sprite->red += (goalRed - sprite->red) / 10;
	sprite->green += (goalGreen - sprite->green) / 10;
	sprite->blue += (goalBlue - sprite->blue) / 10;
	if (MyKeyState(VK_LBUTTON) > 0) {
		sprite->rot = atan2(MyGetCursorPos().y - (pos.y + sprite->height / 2), MyGetCursorPos().x - (pos.x + sprite->width / 2));
		clickMouseX = MyGetCursorPos().x;
		clickMouseY = MyGetCursorPos().y;
		goalScale = D3DXVECTOR2(0.8, 0.8);
	}
	else {
		goalScale = D3DXVECTOR2(0.5, 0.5);
	}
	if (MyKeyState(VK_LBUTTON) == 1 &&
		MyGetCursorPos().x >= 0 &&
		MyGetCursorPos().x <= WIDTH &&
		MyGetCursorPos().y >= 0 &&
		MyGetCursorPos().y <= HEIGHT) {
		goalRed = rand() % 200;
		goalGreen = rand() % 200;
		goalBlue = rand() % 200;
	}
}