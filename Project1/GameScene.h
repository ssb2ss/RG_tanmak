#pragma once
#include "IScene.h"
#include "Player.h"
#include "EnemyManager.h"
#include "Timer.h"
#include "Def.h"	
#include "myFunction.h"

class GameScene :
	public IScene
{
public:
	CSprite *background, *scoring;
	CSprite *printStage[10];
	Player *player;
	EnemyManager *enemyManager;
	Timer *spawnTimer;
	Timer *pattern[10];
	Timer *breakTime[10];
	Timer *pat5Timer;
	D3DXVECTOR2 bgScale;
	int bgRed, bgGreen, bgBlue;
	float nowScore;
	bool isSpawnTimer, isPattern[10], isBreakTime[10], isPrintStage[10];
	float attackDir, grav;
	int attackCnt,attackCnt__;
	Enemy *en[50];
	Enemy *en_[10][15];
	bool isPat5Attack;
	bool isPat5DirSet[50];
	bool isPat8xy[8];
	float pat8X[4], pat8Y[4];
	float pat9Dir[10][30];
	Enemy *pat9En[10][30];
	bool isPatternEnd;
	Timer *clearGameWait;

	GameScene(int bgR, int bgG, int bgB);
	~GameScene();

	void Update(float eTime);
	void Render();
	void CollisionCheck();
	void backgroundState();
	void SetPattern(float eTime);
};