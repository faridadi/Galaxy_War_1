#ifndef _LEVEL_H
#define _LEVEL_H
#include "InputManager.h"
#include "PlaySideBar.h"
#include "BackgroundStars.h"
#include "Player.h"
#include "Enemy.h"
#include "Collider.h";
#include "AudioManager.h"

class Level : public GameEntity {
public:
	enum LEVEL_STATES { running, finished, gameover };

private:
	Timer* mTimer;
	PlaySideBar* mSideBar;
	BackgroundStars* mStars;
	AudioManager* mAudio;

	int mStage;
	bool mStageStarted;

	float mLabelTimer;

	Texture* mStageLabel;
	Scoreboard* mStageNumber;
	float mStageLabelOnScreen;
	float mStageLabelOffScreen;

	Collider* mColl;

	Texture* mReadyLabel;
	float mReadyLabelOnScreen;
	float mReadyLabelOffScreen;

	Player* mPlayer;

	bool mPlayerHit;
	float mPlayerRespawnDelay;
	float mPlayerRespawnTimer;
	float mPlayerRespawnLabelOnScreen;

	Texture* mGameOverLabel;
	bool mGameOver;
	float mGameOverDelay;
	float mGameOverTimer;
	float mGameOverLabelOnScreen;

	LEVEL_STATES mCurrentState;

	int GameSpeed = 100;
	int difSpeed = 59;

	float speedUp = 20;
	float speedUpTimeLimit = 20;
	float speedUpDeltaTime = 0;

	static const int MAX_ENEMY = 5;
	Enemy* mEnemys[MAX_ENEMY];

private:
	void StartStage();
	void HandleStartLabels();
	void HandleCollisions();
	void HandlePlayerDeath();
	void EnemyRespawn(int speed, int count);

public:
	Level(int stage, PlaySideBar* sideBar, Player* player);
	~Level();
	LEVEL_STATES State();
	void Update();
	void Render();
};

#endif
