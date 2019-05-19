#include "PlaySideBar.h"
//file ini dibuat untuk menghandle sidebar saay=t gameplay
PlaySideBar::PlaySideBar() {

	mTimer = Timer::Instance();
	mAudio = AudioManager::Instance();

	mBackground = new Texture("black.png");
	mBackground->Parent(this);
	//mBackground->Pos(Vector2(20.0f, 380.0f));
	mBackground->Scale(Vector2(2.0f, 10.0f));

	mPlayerOneLabel = new Texture("LIFE", "ARCADE_N.ttf", 32, { 150, 0, 0 });
	mPlayerOneLabel->Pos(Vector2(-5.0f, -Graphics::Instance()->SCREEN_HEIGHT * 0.44f));
	mPlayerOneLabel->Parent(this);

	mShips = new GameEntity();
	mShips->Parent(this);
	mShips->Pos(Vector2(-55.0f, -Graphics::Instance()->SCREEN_HEIGHT * 0.32f));

	//live ship texture
	for (int i = 0; i < MAX_SHIP_TEXTURE; i++)
	{
		mShipTextures[i] = new Texture("Ship.png");
		mShipTextures[i]->Scale(Vector2(1.6f, 1.6f));
		mShipTextures[i]->Parent(mShips);
		mShipTextures[i]->Pos(Vector2(48.0f * (i % 3), 64.0f * (i / 3)));
	}
	//mTotalShips = 2;
	//live ship
	mTotalShipsLabel = new Scoreboard();
	mTotalShipsLabel->Parent(mShips);
	//mTotalShipsLabel->Score(mTotalShips);
	mTotalShipsLabel->Pos(Vector2(48.0f, 128.0f));

	
}

PlaySideBar::~PlaySideBar() {

	mTimer = NULL;
	mAudio = NULL;

	delete mBackground;
	mBackground = NULL;

	delete mPlayerOneLabel;
	mPlayerOneLabel = NULL;

	delete mShips;
	mShips = NULL;

	for (int i = 0; i < MAX_SHIP_TEXTURE; i++) {
		delete mShipTextures[i];
		mShipTextures[i] = NULL;
	}
	delete mTotalShipsLabel;
	mTotalShipsLabel = NULL;
}

void PlaySideBar::SetShips(int ships) {
	mTotalShips = ships;
	mTotalShipsLabel->Score(mTotalShips);
}

void PlaySideBar::Update() {


}

void PlaySideBar::Render() {

	mBackground->Render();
	mPlayerOneLabel->Render();

	for (int i = 0; i < MAX_SHIP_TEXTURE && i < mTotalShips;i++) {
		mShipTextures[i]->Render();
	}

	if (mTotalShips <= MAX_SHIP_TEXTURE)
	{
		mTotalShipsLabel->Render();
	}
}
