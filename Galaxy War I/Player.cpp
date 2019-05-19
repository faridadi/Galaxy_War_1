#include "Player.h"
//file ini digunakan untuk menghandle player dimana untuk meload gambarm meload animasi meledeak, menembak, dan menggerakkan nya
Player::Player() {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();
	mAudio = AudioManager::Instance();
	

	mVisible = false;
	mAnimating = false;
	mScore = 0;
	mLives = 6;
	//Texture Ship
	mShip = new Texture("Ship.png");
	mShip->Scale(Vector2(1.6f, 1.6f));
	mShip->Parent(this);
	mShip->Pos(VEC2_ZERO);

	mMoveSpeed = 200.f;
	//Bounds
	mMoveBoundsx = Vector2(30.0f, 610.0f);
	mMoveBoundsy = Vector2(30.0f, 570.0f);

	mDeathAnimation = new AnimatedTexture("playerexp.png",0,0,125,128,4,1.0f, AnimatedTexture::horizontal);
	mDeathAnimation->Parent(this);
	mDeathAnimation->Pos(VEC2_ZERO);
	mDeathAnimation->WrapMode(AnimatedTexture::once);

	for (int i = 0; i < MAX_BULLETS; i++)
	{
		mBullets[i] = new Bullet();
	}
}

Player::~Player() {
	mTimer = NULL;
	mInput = NULL;
	delete mShip;
	mShip = NULL;
	delete mDeathAnimation;
	mDeathAnimation = NULL;

	for (int i = 0; i < MAX_BULLETS; i++)
	{
		delete mBullets[i];
		mBullets[i] = NULL;
	}


}

void Player::HandleMovement() {
	if (mInput->KeyDown(SDL_SCANCODE_RIGHT))
	{
		Translate(VEC2_RIGHT * mMoveSpeed * mTimer->DeltaTime());
	}
	else if(mInput->KeyDown(SDL_SCANCODE_LEFT))
	{
		Translate(-VEC2_RIGHT * mMoveSpeed * mTimer->DeltaTime());
	}
	if (mInput->KeyDown(SDL_SCANCODE_UP))
	{
		Translate(-VEC2_UP * mMoveSpeed * mTimer->DeltaTime());
	}
	else if (mInput->KeyDown(SDL_SCANCODE_DOWN))
	{
		Translate(VEC2_UP * mMoveSpeed * mTimer->DeltaTime());
	}


	Vector2 pos = Pos(local);
	if (pos.x < mMoveBoundsx.x)
	{
		pos.x = mMoveBoundsx.x;
	}
	else if (pos.x > mMoveBoundsx.y) {
		pos.x = mMoveBoundsx.y;
	}

	if (pos.y < mMoveBoundsy.x)
	{
		pos.y = mMoveBoundsy.x;
	}
	else if (pos.y > mMoveBoundsy.y) {
		pos.y = mMoveBoundsy.y;
	}
	Pos(pos);
}

void Player::HandleFiring() {
	if (mInput->KeyPressed(SDL_SCANCODE_SPACE))
	{
		for (int i = 0; i < MAX_BULLETS; i++)
		{
			if (!mBullets[i]->Active())
			{
				mBullets[i]->Fire(Pos());
				mAudio->PlaySFX("fire.wav", 0, 1);
				break;
			}
		}

	}
}

void Player::Visible(bool visible) {
	mVisible = visible;
}
bool Player::IsAnimating() {
	return mAnimating;
}

int Player::Score() {
	return mScore;
}

int Player::Lives() {
	return mLives;
}


void Player::WasHit() {
	mLives--;
	mDeathAnimation->ResetAnimation();
	mAnimating = true;
	mAudio->PlaySFX("explosion.ogg");
}

void Player::Update() {
	if (mAnimating)
	{
		mDeathAnimation->Update();
		mAnimating = mDeathAnimation->IsAnimation();
	}
	else {
		if (Active())
		{
			HandleMovement();
			HandleFiring();
		}
	}

	for (int i = 0; i < MAX_BULLETS; i++)
	{
		mBullets[i]->Update();
	}
}

void Player::Render() {
	if (mVisible)
	{
		if (mAnimating)
		{
			mDeathAnimation->Render();
		}
		else
		{
			mShip->Render();
		}
	}
	for (int i = 0; i < MAX_BULLETS; i++)
	{
		mBullets[i]->Render();
	}

}