#include "TitleScene.h"
#include "myFunction.h"
#include "GameScene.h"
#include "ClearScene.h"
#include <string>
#include "SoundMgr.h"

extern SoundMgr *soundMgr;

TitleScene::TitleScene(int bgR, int bgG, int bgB)
{
	background = new CSprite("images/background.png");
	clicktostart = new CSprite("images/clicktostart.png");
	titleLogo = new CSprite("images/title.png");
	clicktostart->pos.x = 640 - clicktostart->width / 2;
	clicktostart->pos.y = 500;
	titleLogo->pos.x = 640 - titleLogo->width / 2;
	titleLogo->pos.y = 100;
	bgRed = background->red = bgR;
	bgGreen = background->green = bgG;
	bgBlue = background->blue = bgB;
	isTxtOpUp = false;
}


TitleScene::~TitleScene()
{
	delete background;
	delete clicktostart;
	delete titleLogo;
}

void TitleScene::Update(float eTime){
	background->Update(eTime);
	clicktostart->Update(eTime);
	titleLogo->Update(eTime);
	if (background->red + 50 <= 255) {
		titleLogo->red = background->red + 50;
		clicktostart->red = background->red + 50;
	}
	else {
		titleLogo->red = 255;
		clicktostart->red = 255;
	}
	if (background->green + 50 <= 255) {
		titleLogo->green = background->green + 50;
		clicktostart->green = background->green + 50;
	}
	else {
		titleLogo->green = 255;
		clicktostart->green = 255;
	}
	if (background->blue + 50 <= 255) {
		titleLogo->blue = background->blue + 50;
		clicktostart->blue = background->blue + 50;
	}
	else {
		titleLogo->blue = 255;
		clicktostart->blue = 255;
	}
	if (isTxtOpUp) {
		clicktostart->opacity += 4;
		if (clicktostart->opacity > 255) {
			clicktostart->opacity = 255;
			isTxtOpUp = false;
		}
	}
	else {
		clicktostart->opacity -= 4;
		if (clicktostart->opacity < 0) {
			clicktostart->opacity = 0;
			isTxtOpUp = true;
		}
	}
	if (MyKeyState(VK_LBUTTON) == 1 &&
		MyGetCursorPos().x >= 0 &&
		MyGetCursorPos().x <= WIDTH &&
		MyGetCursorPos().y >= 0 &&
		MyGetCursorPos().y <= HEIGHT) {
		ChangeScene(new GameScene(background->red, background->green, background->blue));
		return;
	}
}

void TitleScene::Render(){
	background->Render(NULL);
	clicktostart->Render(NULL);
	titleLogo->Render(NULL);
}