#ifndef  _STARTSCREEN_H
#define  _STARTSCREEN_H
#include "AnimatedTexture.h"
#include "InputManager.h"
#include "BackgroundStars.h"
#include "AudioManager.h"
using namespace Galaxy;
class StartScreen : public GameEntity {
private:

	InputManager* mInput;
	GameEntity* mTopBar;
	Texture* mPlayer1;
	Texture* mHighScore;
	Texture* mPlayer2;
	AudioManager* mAudio;

	Texture* mLogo;
	GameEntity* mPlayModes;
	Texture* mOnePlayerMode;
	Texture* mTwoPlayerMode;
	Texture* mCursor;
	Vector2 mCursorStartPos;
	Vector2 mcursorOffset;
	int mSelectedMode;

	GameEntity* mBotbar;
	Texture* mName;
	Texture* mTitle;

	BackgroundStars* mStars;
public:
	StartScreen();
	~StartScreen();
	int SelectedMode();
	void ChangeSelectedMode(int change);
	void BackToStart();
	void Update();
	void Render();

};
#endif