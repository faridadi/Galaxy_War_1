#include "StartScreen.h"
//file ini digunakan untuk menghandle sceen saat di Main menu
StartScreen::StartScreen() {

	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();
	BackToStart();

	//Top Bar
	mTopBar = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, 80.0f));
	mPlayer1 = new Texture(">>>", "ARCADE_N.TTF", 32, {200,0,0});
	mHighScore = new Texture("SPACE SHOOTER", "ARCADE_N.TTF", 32, { 200,0,0 });
	mPlayer2 = new Texture("<<<", "ARCADE_N.TTF", 32, { 200,0,0 });

	mPlayer1->Parent(mTopBar);
	mHighScore->Parent(mTopBar);
	mPlayer2->Parent(mTopBar);

	mPlayer1->Pos(Vector2(-Graphics::Instance()->SCREEN_WIDTH*0.35f, 0.0f));
	mHighScore->Pos(VEC2_ZERO);
	mPlayer2->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.35f, 0.0f));

	mTopBar->Parent(this);

	//Logo
	mLogo = new Texture("tenlevelflag.PNG");
	mLogo->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.3f));
	//mLogo->Parent(this);

	//Top Bar
	mCursor = new Texture(">>    <<", "ARCADE_N.TTF", 32, { 255,255,255 });
	mPlayModes = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT*0.55f));
	mOnePlayerMode = new Texture("PLAY", "ARCADE_N.TTF", 32, { 200,0,0 });
	mTwoPlayerMode = new Texture("EXIT", "ARCADE_N.TTF", 32, { 200,0,0 });
	
	mOnePlayerMode->Parent(mPlayModes);
	mTwoPlayerMode->Parent(mPlayModes);
	mCursor->Parent(mPlayModes);

	//Menu
	mOnePlayerMode->Pos(Vector2(0.0f, -35.0f));
	mTwoPlayerMode->Pos(Vector2(0.0f, 35.0f));
	mCursor->Pos(Vector2(0.0f, -35.0f));

	mPlayModes->Parent(this);

	//set menu option
	mCursorStartPos = mCursor->Pos(local);
	mcursorOffset = Vector2(0.0f, 70.0f);
	mSelectedMode = 0;

	//bottom bar
	mBotbar = new GameEntity(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.8f));
	mTitle = new Texture("GALAXY WAR I", "ARCADE_N.TTF", 30, { 200,200,0 });
	mName = new Texture("PROJECT PEMROGRAMAN GAME", "ARCADE_N.TTF", 25, { 200,0,200 });
	mTitle->Parent(mBotbar);
	mName->Parent(mBotbar);

	mTitle->Pos(Vector2(0.0f, -35.0f));
	mName->Pos(Vector2(0.0f, 35.0f));

	mStars = BackgroundStars::Instance();
	mStars->Scroll(false);
}

StartScreen::~StartScreen() {
	delete mTopBar;
	mTopBar = NULL;
	delete mPlayer1;
	mPlayer1 = NULL;
	delete mHighScore;
	mHighScore = NULL;
	delete mPlayer2;
	mPlayer2 = NULL;

	delete mLogo;
	mLogo = NULL;

	delete mOnePlayerMode;
	mOnePlayerMode = NULL;
	delete mTwoPlayerMode;
	mTwoPlayerMode = NULL;
	delete mPlayModes;
	mPlayModes = NULL;
	delete mCursor;
	mCursor = NULL;

	delete mBotbar;
	mBotbar = NULL;
	delete mTitle;
	mTitle = NULL;
	delete mName;
	mName = NULL;
}


int StartScreen::SelectedMode() {
	return mSelectedMode;
}

void StartScreen::ChangeSelectedMode(int change) {
	mSelectedMode += change;
	mAudio->PlaySFX("flagsound.wav",0,3);
	if (mSelectedMode < 0)
	{
		mSelectedMode = 1;
	}
	if (mSelectedMode > 1)
	{
		mSelectedMode = 0;
	}

	mCursor->Pos(mCursorStartPos + mcursorOffset * mSelectedMode);
}
void StartScreen::BackToStart() {
	//mAudio = NULL;
	//mAudio = AudioManager::Instance();
	mAudio->PlayMusic("SpaceBGM.ogg", -1);
	printf("Back TO Main Menu\n");
	
}
void StartScreen::Update() {
	if (mInput->KeyPressed(SDL_SCANCODE_UP))
	{
		ChangeSelectedMode(-1);
	}
	else if (mInput->KeyPressed(SDL_SCANCODE_DOWN)) {
		ChangeSelectedMode(1);
	}
}

void StartScreen::Render() {
	mPlayer1->Render();
	mPlayer2->Render();
	mHighScore->Render();

	mLogo->Render();

	mCursor->Render();
	mOnePlayerMode->Render();
	mTwoPlayerMode->Render();

	mTitle->Render();
	mName->Render();

}