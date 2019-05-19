#include "Enemy.h"
using namespace Galaxy;

Enemy::Enemy(int speed, int pos, int type) {

	mTimer = Timer::Instance();
	mCurrentState = flyIn; 
	mTextures[0] = new Texture("enemy.png");
	mTextures[0]->Scale(Vector2(0.08f, 0.08f));
	mTextures[0]->Parent(this);
	float posx = (float)pos /100;
	this->Pos(Vector2(Graphics::Instance()->SCREEN_WIDTH * posx, -2.0f));
	Rotate(180);
	mTextures[1] = NULL;
	mSpeed = speed;
}

Enemy::~Enemy() {

	mTimer = NULL;

	for (int i = 0; i < 2; i++) {

		delete mTextures[i];
		mTextures[i] = NULL;

	}
	printf("Enemy destructor called\n");

}



void Enemy::FlyInComplete() {
		mCurrentState = dead;
}


void Enemy::HandleFlyInState() {
		Translate(VEC2_UP * mTimer->DeltaTime() * mSpeed, world);
}


void Enemy::HandleStates() {


	switch (mCurrentState) {

	case flyIn:

		HandleFlyInState();
		break;

	case dead:

		//HandleDeadState();
		break;
	}
}

void Enemy::RenderFlyInState() {
	if (mCurrentState == flyIn)
	{
		mTextures[0]->Render();
	}
	else {
		mTextures[1]->Render();
	}
	
}



void Enemy::RenderStates() {

	switch (mCurrentState) {

	case flyIn:
		RenderFlyInState();
		break;

	case dead:

		//RenderDeadState();
		break;


	}

}


Enemy::STATES Enemy::CurrentState() {

	return mCurrentState;
}

Enemy::TYPES Enemy::Type() {

	return mType;
}




void Enemy::Update() {

	if (Active())
		HandleStates();


	if (Pos().y >= Graphics::Instance()->SCREEN_HEIGHT+100)
	{
		Enemy::~Enemy();
	}

}

void Enemy::Render() {

	if (Active())
		RenderStates();
}


