#include "ScreenManager.h"
//file ini digubakan untuk menghandle Scean Manager agar mudah berpindah sceen
ScreenManager* ScreenManager::sInstance = NULL;
ScreenManager* ScreenManager::Instance() {
	if (sInstance == NULL)
		sInstance = new ScreenManager();
	return sInstance;
}

void ScreenManager::Release() {
	delete sInstance;
	sInstance = NULL;
}

ScreenManager::ScreenManager() {
	mInput = InputManager::Instance();
	mBackgroundStars = BackgroundStars::Instance();
	mStartScreen = new StartScreen();
	mPlayScreen = new PlayScreen();
	mCurrentScreen = start;
}

ScreenManager::~ScreenManager() {
	mInput = NULL;
	BackgroundStars::Release();
	mBackgroundStars = NULL;

	delete mStartScreen;
	mStartScreen = NULL;

	delete mPlayScreen;
	mPlayScreen = NULL;
}


void ScreenManager::Update() {
	mBackgroundStars->Update();
	switch (mCurrentScreen) {
	case start:
		mStartScreen->Update();
		//Start game
		if (mInput->KeyPressed(SDL_SCANCODE_RETURN) && mStartScreen->SelectedMode() == 0) {
			mCurrentScreen = play;
			mPlayScreen->StartNewGame();
			printf("Play GAME\n");
		}
		//Exitgame
		if (mInput->KeyPressed(SDL_SCANCODE_RETURN)&&mStartScreen->SelectedMode()==1) {
			printf("EXIT GAME\n");
		
		}
		break;
	case play:
		mPlayScreen->Update();
		//Exit To Main Menu
		if (mInput->KeyPressed(SDL_SCANCODE_ESCAPE)) {
			mCurrentScreen = start;
			delete mPlayScreen;
			mPlayScreen = new PlayScreen();
			mStartScreen->BackToStart();
			mBackgroundStars->Scroll(false);
		}
		break;
	}

}

void ScreenManager::Render() {
	mBackgroundStars->Render();
	switch (mCurrentScreen) {
	case start:
		mStartScreen->Render();
		break;
	case play:
		mPlayScreen->Render();
		break;
	}
}
