#include "PlayScreen.h"
using namespace Galaxy;
PlayScreen::PlayScreen() {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mStars = BackgroundStars::Instance();
	mSideBar = new PlaySideBar();
	mSideBar->Parent(this);
	mSideBar->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.9, Graphics::Instance()->SCREEN_HEIGHT*0.5f));
	mAudio = AudioManager::Instance();
	mStartLabel = new Texture("START", "ARCADE_N.ttf", 32, { 255,255,255 });
	mStartLabel->Parent(this);
	mStartLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH*0.4f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));

	mLevel = NULL;
	mLevelStarDelay = 2.0f;
	mLevelStarted = false;
	
}

void PlayScreen::StartNextLevel() {
	mCurrentStage++;
	mLevelStartTimer = 0.0f;
	mLevelStarted = true;
	delete mLevel;
	mLevel = new Level(mCurrentStage, mSideBar, mPlayer);


}


void PlayScreen::StartNewGame() {
	delete mPlayer;
	mPlayer = new Player();
	mPlayer->Parent(this);
	mPlayer->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.4f, Graphics::Instance()->SCREEN_HEIGHT * 0.9f));
	mPlayer->Active(false);	

	mSideBar->SetShips(mPlayer->Lives());
	mStars->Scroll(true);
	mAudio->PlayMusic("gamestart.wav", 0);
	mGameStarted = false;
	mLevelStarted = false;
	mLevelStartTimer = 0.0f;
	mCurrentStage = 0;
}

bool PlayScreen::GameOver() {
	if (!mLevelStarted)
	{
		return false;
	}
	return(mLevel->State() == Level::gameover);
}

PlayScreen::~PlayScreen() {

	mTimer = NULL;
	mInput = NULL;

	mStars = NULL;
	delete mSideBar;
	mSideBar = NULL;
	mAudio = NULL;

	delete mStartLabel;
	mStartLabel = NULL;

	delete mLevel;
	mLevel = NULL;

	delete mPlayer;
	mPlayer = NULL;
}


void PlayScreen::Update() {
	if (mGameStarted)
	{
		if (!mLevelStarted)
		{
			mLevelStartTimer += mTimer->DeltaTime();
			if (mLevelStartTimer >= mLevelStarDelay)
			{
				StartNextLevel();
			}
		}
	}
	else {
		if (!Mix_PlayingMusic())
		{
			mGameStarted = true;
		}
	}

	if (mGameStarted)
	{
		if (mCurrentStage > 0)
		{
			mSideBar->Update();
		}
		if (mLevelStarted)
		{
			mLevel->Update();
		}
		mPlayer->Update();
		
	}
	
}

void PlayScreen::Render() {
	mSideBar->Render();
	if (!mGameStarted)
	{
		mStartLabel->Render();
	}
	if (mGameStarted)
	{
		if (mLevelStarted)
		{
			mLevel->Render();
		}
		mPlayer->Render();
		
	}
}
