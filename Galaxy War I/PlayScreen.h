#ifndef _PLAYSCREEN_H
#define _PLAYSCREEN_H
#include "InputManager.h";
#include "BackgroundStars.h"
#include "PlaySideBar.h"
#include "Level.h"
#include "Player.h"
#include "Enemy.h"

class PlayScreen : public GameEntity {
private:
	Timer* mTimer;
	InputManager* mInput;
	BackgroundStars* mStars;
	PlaySideBar* mSideBar;
	AudioManager* mAudio;
	Texture* mStartLabel;

	float mLevelStartTimer;
	float mLevelStarDelay;
	bool mGameStarted;

	Level* mLevel;
	bool mLevelStarted;
	int mCurrentStage;

	Player* mPlayer;

private:

	void StartNextLevel();

public:

	PlayScreen();
	~PlayScreen();

	void StartNewGame();
	bool GameOver();
	void Update();

	void Render();



};


#endif
