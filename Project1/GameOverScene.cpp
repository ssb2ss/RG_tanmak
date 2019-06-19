#include "GameOverScene.h"
#include "Def.h"
#include "myFunction.h"
#include "TitleScene.h"
#include <math.h>
#define M_PI 3.14159265358979323846


GameOverScene::GameOverScene(int bgR, int bgG, int bgB)
{
	background = new CSprite("images/background.png");
	logo = new CSprite("images/gameover.png");
	clicktorestart = new CSprite("images/clicktorestart.png");
	clicktorestart->pos.x = 640 - clicktorestart->width / 2;
	clicktorestart->pos.y = 500;
	degree = M_PI / 180;
	rightdeg = 5 * degree;
	leftdeg = -5 * degree;
	logo->rotationCenter.x = logo->width / 2;
	logo->rotationCenter.y = logo->height / 2;
	logo->pos.x = 0;
	logo->pos.y = 300 - logo->height / 2;
	logo->rot = rightdeg;
	start1 = rightdeg;
	end1 = leftdeg;
	start2 = leftdeg;
	end2 = rightdeg;
	cnt = 0;
	duration = 60;
	bgRed = background->red = bgR;
	bgGreen = background->green = bgG;
	bgBlue = background->blue = bgB;
	watchDir = false;
	isTxtOpUp = false;
}


GameOverScene::~GameOverScene()
{
	delete background;
	delete logo;
	delete clicktorestart;
}

void GameOverScene::Update(float eTime) {
	background->Update(eTime);
	logo->Update(eTime);
	clicktorestart->Update(eTime);
	if (watchDir) {
		cnt++;
		easings = Cubic(cnt, cnt / (float)duration, duration);
		present = Lerp(start1, end1, easings);
		logo->rot = present;
		if (cnt >= duration) {
			cnt = 0;
			watchDir = false;
		}
	}
	else {
		cnt++;
		easings = Cubic(cnt, cnt / (float)duration, duration);
		present = Lerp(start2, end2, easings);
		logo->rot = present;
		if (cnt >= duration) {
			cnt = 0;
			watchDir = true;
		}
	}
	if (isTxtOpUp) {
		clicktorestart->opacity += 4;
		if (clicktorestart->opacity > 255) {
			clicktorestart->opacity = 255;
			isTxtOpUp = false;
		}
	}
	else {
		clicktorestart->opacity -= 4;
		if (clicktorestart->opacity < 0) {
			clicktorestart->opacity = 0;
			isTxtOpUp = true;
		}
	}
	if (background->red + 50 <= 255) {
		logo->red = background->red + 50;
		clicktorestart->red = background->red + 50;
	}
	else {
		logo->red = 255;
		clicktorestart->red = 255;
	}
	if (background->green + 50 <= 255) {
		logo->green = background->green + 50;
		clicktorestart->green = background->green + 50;
	}
	else {
		logo->green = 255;
		clicktorestart->green = 255;
	}
	if (background->blue + 50 <= 255) {
		logo->blue = background->blue + 50;
		clicktorestart->blue = background->blue + 50;
	}
	else {
		logo->blue = 255;
		clicktorestart->blue = 255;
	}
	if (MyKeyState(VK_LBUTTON) == 1 &&
		MyGetCursorPos().x >= 0 &&
		MyGetCursorPos().x <= WIDTH &&
		MyGetCursorPos().y >= 0 &&
		MyGetCursorPos().y <= HEIGHT) {
		ChangeScene(new TitleScene(background->red, background->green, background->blue));
		return;
	}
}

void GameOverScene::Render() {
	background->Render(NULL);
	logo->Render(NULL);
	clicktorestart->Render(NULL);
}

float GameOverScene::Lerp(float start, float end, float change) {
	float gap;
	float result;
	gap = end - start;
	result = gap * change + start;
	return result;
}

float GameOverScene::Cubic(float cnt, float change, float duration) {
	float tem = 2 * cnt / duration;
	if (tem < 1) {
		return change * 0.5 * pow(tem, 3);
	}
	return change * 0.5 * (pow(tem - 2, 3) + 2);
}