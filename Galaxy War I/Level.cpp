#include "Level.h"
#include <array>
//file ini digunakan untuk menghandle game saat bermain, seperti mendeteksi tabrakan, ketika player mati, dan menghandle saat game over
Level::Level(int stage, PlaySideBar* sidebar, Player* player) {
	mTimer = Timer::Instance();
	mColl = new Collider();
	mSideBar = sidebar;
	mStars = BackgroundStars::Instance();
	mAudio = AudioManager::Instance();
	mStage = stage;
	mStageStarted = false;
	mLabelTimer = 0.0f;
	mStageLabel = new Texture("STAGE", "ARCADE_N.ttf", 32, { 75, 75, 200 });
	mStageLabel->Parent(this);
	mStageLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.35f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));
	mStageNumber = new Scoreboard({ 75, 75, 200 });
	mStageNumber->Score(mStage);
	mStageNumber->Parent(this);
	mStageNumber->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));
	mStageLabelOnScreen = 0.0f;
	mStageLabelOffScreen = 1.5f;

	mReadyLabel = new Texture("READY", "ARCADE_N.ttf", 32, { 150, 0, 0 });
	mReadyLabel->Parent(this);
	mReadyLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.4f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));

	mReadyLabelOnScreen = mStageLabelOffScreen;
	mReadyLabelOffScreen = mReadyLabelOnScreen + 3.0f;
	
	mPlayer = player;
	mPlayerHit = false;
	mPlayerRespawnDelay = 3.0f;
	mPlayerRespawnTimer = 0.0f;
	mPlayerRespawnLabelOnScreen = 2.0f;
	
	mGameOverLabel = new Texture("GAME OVER", "ARCADE_N.ttf", 32, { 150, 0, 0 });
	mGameOverLabel->Parent(this);
	mGameOverLabel->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.5f));

	mGameOver = false;
	mGameOverDelay = 6.0f;
	mGameOverTimer = 0.0f;
	mGameOverLabelOnScreen = 1.0f;

	mCurrentState = running;

	for (int i = 0; i < MAX_ENEMY; i++)
	{
		mEnemys[i] = NULL;
	}

}

Level::~Level() {

	mTimer = NULL;
	mSideBar = NULL;
	mStars = NULL;
	mAudio = NULL;


	delete mStageLabel;
	mStageLabel = NULL;
	delete mStageNumber;
	mStageNumber = NULL;

	delete mReadyLabel;
	mReadyLabel = NULL;

	mPlayer = NULL;

	delete mGameOverLabel;
	mGameOverLabel = NULL;

}


void Level::StartStage() {

	mStageStarted = true;
	EnemyRespawn(100,9);
}

void Level::HandleStartLabels() {
	mLabelTimer += mTimer->DeltaTime();
	if (mLabelTimer >= mStageLabelOffScreen) {
		mStars->Scroll(true);
		if (mStage > 1) {
			StartStage();
		}
		else {
			if (mLabelTimer >= mReadyLabelOffScreen) {
				StartStage();
				mPlayer->Active(true);
				mPlayer->Visible(true);
			}
		}
	}
}

void Level::HandleCollisions(){
	if (!mPlayerHit)
	{
		//cek collision kapal dengan musuh
		for (int i = 0; i < MAX_ENEMY; i++)
		{
			if (!(mEnemys[i] == NULL))
			{
				//cek collision player terhadap musuh
				if (mColl->checkCollision(mPlayer->mShip->mRenderRect, mEnemys[i]->mTextures[0]->mRenderRect))
				{
					mEnemys[i]->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * (rand() % 9) / 10, 2 - (rand() % -500)));;
					mPlayer->WasHit();
					mSideBar->SetShips(mPlayer->Lives());
					mPlayerHit = true;
					mPlayerRespawnTimer = 0.0f;
					mPlayer->Active(false);
					mStars->Scroll(false);
				}
				//cek collision peluru terhadap musuh
					for (int j = 0; j < mPlayer->MAX_BULLETS; j++)
					{
						if (!(mPlayer->mBullets[j]==NULL))
						{
							if (mColl->checkCollision(mPlayer->mBullets[j]->mTexture->mRenderRect, mEnemys[i]->mTextures[0]->mRenderRect))
							{
								mEnemys[i]->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * (rand() % 70) / 100, 2 - (rand() % -400)));
								mEnemys[i]->mSpeed = rand() % (GameSpeed - (GameSpeed - difSpeed) + 1) + (GameSpeed - difSpeed);
								mPlayer->mBullets[j]->Active(false);
								mAudio->PlaySFX("explosion.ogg", 0, 4);
							}
						}
					}
				
				
			}
		}
	}
}

void Level::HandlePlayerDeath() {
	if (!mPlayer->IsAnimating()) {
		if (mPlayer->Lives() > 0) {
			if (mPlayerRespawnTimer == 0.0f) {
				mPlayer->Visible(false);
			}
			mPlayerRespawnTimer += mTimer->DeltaTime();
			printf("death");
			if (mPlayerRespawnTimer >= mPlayerRespawnDelay) {
				mPlayer->Active(true);
				mPlayer->Visible(true);
				mPlayerHit = false;
				mStars->Scroll(true);
			}
		}
		else {
			if (mGameOverTimer == 0.0f)
				mPlayer->Visible(false);
			mGameOverTimer += mTimer->DeltaTime();
			if (mGameOverTimer >= mGameOverDelay) {
				mCurrentState = gameover;
			}
		}
	}
}

Level::LEVEL_STATES Level::State() {
	return mCurrentState;
}

void Level::EnemyRespawn(int speed = 100, int count=2) {
	if (count > MAX_ENEMY)
	{
		count = MAX_ENEMY;
	}
	for (int i = 0; i < count; i++)
	{
		mEnemys[i] = new Enemy((90+(rand() % speed)), rand()%70 ,count);
	}
}

void Level::Update() {
	if (!mStageStarted)
	{
		HandleStartLabels();
	}
	else {		

		HandleCollisions();
		if (mPlayerHit)
		{
			HandlePlayerDeath();
		}
		else {
			speedUpDeltaTime += Timer::Instance()->DeltaTime();
			if (speedUpDeltaTime > speedUpTimeLimit)
			{
				GameSpeed += speedUp;
				speedUpDeltaTime = 0;
			}

			for (int i = 0; i < MAX_ENEMY; i++)
			{
				if (!(mEnemys[i] == NULL))
				{
					if (mEnemys[i]->Pos().y >= Graphics::Instance()->SCREEN_HEIGHT + 50)
					{
						mEnemys[i]->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * (rand() % 70) / 100, 2 - (rand() % -400)));
						mEnemys[i]->mSpeed = rand() % (GameSpeed - (GameSpeed-difSpeed) + 1) + (GameSpeed - difSpeed);
					}
					mEnemys[i]->Update();
				}
			}
		}
		if (InputManager::Instance()->KeyPressed(SDL_SCANCODE_N))
		{
			mCurrentState = finished;
		}
	}
}

void Level::Render() {
	if (!mStageStarted)
	{
		if (mLabelTimer > mStageLabelOnScreen && mLabelTimer < mStageLabelOffScreen)
		{
			mStageLabel->Render();
			mStageNumber->Render();
		}
		else if (mLabelTimer > mReadyLabelOnScreen && mLabelTimer < mReadyLabelOffScreen) {
			mReadyLabel->Render();
		}
	}
	else {
		for (int i = 0; i < MAX_ENEMY; i++)
		{
			if (!(mEnemys[i] == NULL))
			{
				mEnemys[i]->Render();
			}
		}
		if (mPlayerHit)
		{
			if (mPlayerRespawnTimer >= mPlayerRespawnLabelOnScreen)
			{
				mReadyLabel->Render();
			}

			if (mGameOverTimer >= mGameOverLabelOnScreen)
			{
				mGameOverLabel->Render();
			}
		}
	}
}
