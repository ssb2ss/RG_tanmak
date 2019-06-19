#include "ClearScene.h"
#include "myFunction.h"
#include "TitleScene.h"
#define M_PI 3.14159265358979323846

ClearScene::ClearScene()
{
	background = new CSprite("images/background.png");
	clearLogo = new CSprite("images/clearLogo.png");
	clicktorestart = new CSprite("images/clicktorestart.png");
	clicktorestart->pos.x = 640 - clicktorestart->width / 2;
	clicktorestart->pos.y = 500;
	clearLogo->rotationCenter.x = clearLogo->width / 2;
	clearLogo->rotationCenter.y = clearLogo->height / 2;
	clearLogo->pos.x = 0;
	clearLogo->pos.y = 300 - clearLogo->height / 2;
	bgRed = rand() % 255;
	bgGreen = rand() % 255;
	bgBlue = rand() % 255;
	isTxtOpUp = false;
	colorTime = new Timer(0.5f);
	watchDir = false;
	degree = M_PI / 180;
	rightdeg = 10 * degree;
	leftdeg = -10 * degree;
	clearLogo->rot = rightdeg;
	start1 = rightdeg;
	end1 = leftdeg;
	start2 = leftdeg;
	end2 = rightdeg;
	cnt = 0;
	duration = 30;
}


ClearScene::~ClearScene()
{
	delete background;
	delete clearLogo;
	delete clicktorestart;
	delete colorTime;
}

void ClearScene::Update(float eTime) {
	background->Update(eTime);
	clearLogo->Update(eTime);
	clicktorestart->Update(eTime);
	colorTime->Update(eTime);
	if (watchDir) {
		cnt++;
		easings = Cubic(cnt, cnt / (float)duration, duration);
		present = Lerp(start1, end1, easings);
		clearLogo->rot = present;
		if (cnt >= duration) {
			cnt = 0;
			watchDir = false;
		}
	}
	else {
		cnt++;
		easings = Cubic(cnt, cnt / (float)duration, duration);
		present = Lerp(start2, end2, easings);
		clearLogo->rot = present;
		if (cnt >= duration) {
			cnt = 0;
			watchDir = true;
		}
	}
	if (colorTime->isDone) {
		bgRed = rand() % 155 + 100;
		bgGreen = rand() % 155 + 100;
		bgBlue = rand() % 155 + 100;
	}
	background->red += (bgRed - background->red) / 10;
	background->green += (bgGreen - background->green) / 10;
	background->blue += (bgBlue - background->blue) / 10;
	if (background->red + 50 <= 255) {
		clearLogo->red = background->red + 50;
		clicktorestart->red = background->red + 50;
	}
	else {
		clearLogo->red = 255;
		clicktorestart->red = 255;
	}
	if (background->green + 50 <= 255) {
		clearLogo->green = background->green + 50;
		clicktorestart->green = background->green + 50;
	}
	else {
		clearLogo->green = 255;
		clicktorestart->green = 255;
	}
	if (background->blue + 50 <= 255) {
		clearLogo->blue = background->blue + 50;
		clicktorestart->blue = background->blue + 50;
	}
	else {
		clearLogo->blue = 255;
		clicktorestart->blue = 255;
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
	if (MyKeyState(VK_LBUTTON) == 1 &&
		MyGetCursorPos().x >= 0 &&
		MyGetCursorPos().x <= WIDTH &&
		MyGetCursorPos().y >= 0 &&
		MyGetCursorPos().y <= HEIGHT) {
		ChangeScene(new TitleScene(background->red, background->green, background->blue));
		return;
	}
}

void ClearScene::Render() {
	background->Render(NULL);
	clearLogo->Render(NULL);
	clicktorestart->Render(NULL);
}

float ClearScene::Lerp(float start, float end, float change) {
	float gap;
	float result;
	gap = end - start;
	result = gap * change + start;
	return result;
}

float ClearScene::Cubic(float cnt, float change, float duration) {
	float tem = 2 * cnt / duration;
	if (tem < 1) {
		return change * 0.5 * pow(tem, 3);
	}
	return change * 0.5 * (pow(tem - 2, 3) + 2);
}