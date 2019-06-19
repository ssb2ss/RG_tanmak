#include "GameScene.h"
#include "TitleScene.h"
#include "GameOverScene.h"
#include "ClearScene.h"
#include <string>

#define M_PI 3.14159265358979323846


GameScene::GameScene(int bgR, int bgG, int bgB)
{
	background = new CSprite("images/background.png");
	background->scalingCenter.x = background->width / 2;
	background->scalingCenter.y = background->height / 2;
	nowScore = 0.f;
	bgScale = D3DXVECTOR2(1, 1);
	bgRed = background->red = bgR;
	bgGreen = background->green = bgG;
	bgBlue = background->blue = bgB;
	enemyManager = new EnemyManager();
	player = new Player();
	spawnTimer = new Timer(3.f, false); //new Timer(1.f);
	scoring = new CSprite("images/scoring.png");
	nowScore = 0.f;
	isSpawnTimer = true;
	for (int i = 0; i < 10; i++) {
		isPattern[i] = false;
		pattern[i] = new Timer(5.f, false);
		breakTime[i] = new Timer(2.f, false);
		isBreakTime[i] = false;
		isPrintStage[i] = false;
	}
	isPrintStage[0] = true;
	pat5Timer = new Timer(2.5f, false);
	attackDir = 0.f;
	grav = 0.01f;
	attackCnt = attackCnt__ = 0;
	isPat5Attack = false;
	printStage[0] = new CSprite("images/number/1.png");
	printStage[1] = new CSprite("images/number/2.png");
	printStage[2] = new CSprite("images/number/3.png");
	printStage[3] = new CSprite("images/number/4.png");
	printStage[4] = new CSprite("images/number/5.png");
	printStage[5] = new CSprite("images/number/6.png");
	printStage[6] = new CSprite("images/number/7.png");
	printStage[7] = new CSprite("images/number/8.png");
	printStage[8] = new CSprite("images/number/9.png");
	printStage[9] = new CSprite("images/number/0.png");
	for (int i = 0; i < 9; i++) {
		printStage[i]->pos.x = 40;
		printStage[i]->pos.y = -2;
	}
	printStage[9]->pos.x = 70;
	printStage[9]->pos.y = -2;
	for (int i = 0; i < 50; i++) {
		isPat5DirSet[i] = false;
	}
	for (int i = 0; i < 8; i++){
		isPat8xy[i] = false;
	}
	for (int j = 0; j < 10; j++) {
		for (int i = 0; i < 30; i++) {
			pat9Dir[j][i] = (2 * M_PI / 30) * i;
		}
	}
	isPatternEnd = false;
	clearGameWait = new Timer(5.f);
}


GameScene::~GameScene()
{
	delete background;
	delete player;
	delete enemyManager;
	delete spawnTimer;
	delete scoring;
	for (int i = 0; i < 10; i++) {
		delete pattern[i];
		delete breakTime[i];
		delete printStage[i];
	}
	delete clearGameWait;
}

void GameScene::Update(float eTime){
	player->Update(eTime);
	enemyManager->Update(eTime);
	if (isSpawnTimer) {
		spawnTimer->Update(eTime);
		if (spawnTimer->isDone) {
			isSpawnTimer = false;
			isPattern[0] = true;
			attackCnt = 0;
			grav = 0.f;
		}
	}
	for (int i = 0; i < 10; i++) {
		if (isPattern[i]) {
			pattern[i]->Update(eTime);
			if (pattern[i]->isDone) {
				isPattern[i] = false;
				isBreakTime[i] = true;
				attackCnt = 0;
				grav = 0.f;
				attackCnt__ = 0;
			}
		}
		if (isBreakTime[i]) {
			breakTime[i]->Update(eTime);
			if (breakTime[i]->isDone) {
				isBreakTime[i] = false;
				isPrintStage[i] = false;
				if (i == 9) {
					isPatternEnd = true;
				}
				else {
					isPattern[i + 1] = true;
					isPrintStage[i + 1] = true;
				}
			}
		}
	}
	CollisionCheck();
	if (player->isDelete){
		ChangeScene(new GameOverScene(background->red, background->green, background->blue));
		return;
	}
	backgroundState();
	scoring->red += (bgRed - scoring->red) / 10;
	scoring->green += (bgGreen - scoring->green) / 10;
	scoring->blue += (bgBlue - scoring->blue) / 10;
	nowScore += eTime;
	SetPattern(eTime);
	if (isPatternEnd) {
		clearGameWait->Update(eTime);
	}
	if (clearGameWait->isDone) {
		ChangeScene(new ClearScene());
		return;
	}
}

void GameScene::Render(){
	background->Render(NULL);
	player->Render(NULL);
	enemyManager->Render(NULL);
	scoring->Render(NULL);
	for (int i = 0; i < 9; i++) {
		if (isPrintStage[i]) {
			printStage[i]->Render(NULL);
		}
	}
	if (isPrintStage[9]) {
		printStage[0]->Render(NULL);
		printStage[9]->Render(NULL);
	}
}

void GameScene::CollisionCheck(){
	EnemyList::iterator eiter;
	for (eiter = enemyManager->eList.begin(); eiter != enemyManager->eList.end(); eiter++){
		if (GetDistance((*eiter)->pos + D3DXVECTOR2((*eiter)->sprite->width / 2, (*eiter)->sprite->height / 2),
		player->pos + D3DXVECTOR2(player->sprite->width / 2, player->sprite->height / 2)) < 15){
			(*eiter)->isDelete = true;
			player->isDelete = true;
		}
	}
}

void GameScene::backgroundState() {
	background->scale += (bgScale - background->scale) / 10;
	background->red += (bgRed - background->red) / 10;
	background->green += (bgGreen - background->green) / 10;
	background->blue += (bgBlue - background->blue) / 10;
	if (MyKeyState(VK_LBUTTON) > 0) {
		bgScale = D3DXVECTOR2(1.1, 1.1);
	}
	else {
		bgScale = D3DXVECTOR2(1, 1);
	}
	if (MyKeyState(VK_LBUTTON) == 1) {
		bgRed = rand() % 155 + 100;
		bgGreen = rand() % 155 + 100;
		bgBlue = rand() % 155 + 100;
	}
}

void GameScene::SetPattern(float eTime) {
	double degree = M_PI / 180;
	if (isPattern[0]) {
		enemyManager->PushEnemy(new Enemy(WIDTH / 2, HEIGHT / 2, attackDir, 200));
		attackDir += 0.4f;
	}
	else if (isPattern[1]) {
		enemyManager->PushEnemy(new Enemy(WIDTH / 2, HEIGHT / 2, attackDir, 300));
		enemyManager->PushEnemy(new Enemy(WIDTH / 2, HEIGHT / 2, attackDir + M_PI, 300));
		attackDir += grav;
		grav += 0.01f;
	}
	else if (isPattern[2]) {
		attackCnt++;
		if (attackCnt > 1) {
			int randX = rand() % WIDTH;
			enemyManager->PushEnemy(new Enemy(randX, -20, 90 * degree, 300));
			attackCnt = 0;
		}
	}
	else if (isPattern[3]) {
		attackCnt++;
		if (attackCnt > 30) {
			float temDir = rand() % 2 * M_PI / 40;
			for (int i = 0; i < 40; i++) {
				enemyManager->PushEnemy(new Enemy(WIDTH / 2, HEIGHT / 2, temDir, 400));
				temDir += 2 * M_PI / 40;
			}
			attackCnt = 0;
		}
	}
	else if (isPattern[4]) {
		float temDir = atan2(player->pos.y - HEIGHT / 2, player->pos.x - WIDTH / 2);
		float ran = rand() % 4 - 2;
		enemyManager->PushEnemy(new Enemy(WIDTH / 2, HEIGHT / 2, temDir + ran/10, 700));
	}
	else if (isPattern[5]) {
		float temDir = 0;
		float temp = 0;
		pat5Timer->Update(eTime);
		if (!isPat5Attack) {
			for (int i = 0; i < 50; i++) {
				en[i] = new Enemy(WIDTH / 2, HEIGHT / 2, temDir, 100);
				enemyManager->PushEnemy(en[i]);
				temDir += 2 * M_PI / 50;
			}
			isPat5Attack = true;
		}
		if (pat5Timer->isDone) {
			for (int i = 0; i < 50; i++) {
				if (!isPat5DirSet[i]) {
					temp = atan2(player->pos.y - en[i]->pos.y, player->pos.x - en[i]->pos.x);
					en[i]->dir = temp;
					en[i]->moveSpeed = 700;
					isPat5DirSet[i] = true;
				}
			}
		}
	}
	else if (isPattern[6]) {
		float temDir = 0, temp = 0;
		attackCnt++;
		if (attackCnt > 40 && attackCnt__ <= 7) {
			temDir = rand() % 2 * M_PI / 15;
			for (int i = 0; i < 15; i++) {
				en_[attackCnt__][i] = new Enemy(WIDTH / 2, HEIGHT / 2, temDir, 200);
				enemyManager->PushEnemy(en_[attackCnt__][i]);
				temDir += 2 * M_PI / 15;
			}
			attackCnt = 0;
			attackCnt__++;
		}
		for (int i = 0; i < attackCnt__; i++) {
			for (int j = 0; j < 15; j++) {
				if (en_[i][j]->pos.x < 0) {
					en_[i][j]->pos.x = 0;
					en_[i][j]->dir = M_PI - en_[i][j]->dir;
				}
				if (en_[i][j]->pos.x > WIDTH - en_[i][j]->sprite->width) {
					en_[i][j]->pos.x = WIDTH - en_[i][j]->sprite->width;
					en_[i][j]->dir = M_PI - en_[i][j]->dir;
				}
				if (en_[i][j]->pos.y < 0) {
					en_[i][j]->pos.y = 0;
					en_[i][j]->dir = (2 * M_PI) - en_[i][j]->dir;
				}
				if (en_[i][j]->pos.y > HEIGHT - en_[i][j]->sprite->height) {
					en_[i][j]->pos.y = HEIGHT - en_[i][j]->sprite->height;
					en_[i][j]->dir = (2 * M_PI) - en_[i][j]->dir;
				}
			}
		}
	}
	else if (isPattern[7]) {
		attackCnt++;
		for (int i = 0; i < 4; i++){
			enemyManager->PushEnemy(new Enemy(WIDTH / 2, HEIGHT / 2, attackDir + (i * 90 * degree), 600));
		}
		attackDir += grav;
		if (attackCnt > 60 && attackCnt < 180 && grav < 0.04f){
			grav += 0.005f;
		}
		if (attackCnt > 180 && attackCnt < 300 && grav > -0.04f){
			grav -= 0.005f;
		}
	}
	else if (isPattern[8]){
		attackCnt++;
		if (attackCnt >= 45){
			if (!isPat8xy[0]){
				pat8Y[0] = player->pos.y + 20;
				isPat8xy[0] = true;
			}
			enemyManager->PushEnemy(new Enemy(-20, pat8Y[0], 0, 1500));
		}
		if (attackCnt >= 60){
			if (!isPat8xy[1]){
				pat8X[0] = player->pos.x + 20;
				isPat8xy[1] = true;
			}
			enemyManager->PushEnemy(new Enemy(pat8X[0], -20, 90 * degree, 1500));
		}
		if (attackCnt >= 105){
			if (!isPat8xy[2]){
				pat8Y[1] = player->pos.y + 20;
				isPat8xy[2] = true;
			}
			enemyManager->PushEnemy(new Enemy(-20, pat8Y[1], 0, 1500));
		}
		if (attackCnt >= 120){
			if (!isPat8xy[3]){
				pat8X[1] = player->pos.x + 20;
				isPat8xy[3] = true;
			}
			enemyManager->PushEnemy(new Enemy(pat8X[1], -20, 90 * degree, 1500));
		}
		if (attackCnt >= 165){
			if (!isPat8xy[4]){
				pat8Y[2] = player->pos.y + 20;
				isPat8xy[4] = true;
			}
			enemyManager->PushEnemy(new Enemy(-20, pat8Y[2], 0, 1500));
		}
		if (attackCnt >= 180){
			if (!isPat8xy[5]){
				pat8X[2] = player->pos.x + 20;
				isPat8xy[5] = true;
			}
			enemyManager->PushEnemy(new Enemy(pat8X[2], -20, 90 * degree, 1500));
		}
		if (attackCnt >= 225){
			if (!isPat8xy[6]){
				pat8Y[3] = player->pos.y + 20;
				isPat8xy[6] = true;
			}
			enemyManager->PushEnemy(new Enemy(-20, pat8Y[3], 0, 1500));
		}
		if (attackCnt >= 240){
			if (!isPat8xy[7]){
				pat8X[3] = player->pos.x + 20;
				isPat8xy[7] = true;
			}
			enemyManager->PushEnemy(new Enemy(pat8X[3], -20, 90 * degree, 1500));
		}
	}
	else if (isPattern[9]){
		float temSpeed = 100;
		float temDir = (rand() % 360) * degree;
		attackCnt++;
		if (attackCnt > 60) {
			for (int i = 0; i < 40; i++) {
				for (int j = 0; j < 4; j++) {
					enemyManager->PushEnemy(new Enemy(WIDTH / 2, HEIGHT / 2, temDir, temSpeed));
					temDir += 90 * degree;
				}
				temDir += 7 * degree;
				temSpeed += 2;
			}
			attackCnt = 0;
		}
	}
}