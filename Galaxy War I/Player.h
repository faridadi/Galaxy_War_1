#ifndef _PLAYER_H
#define _PLAYER_H
#include "AnimatedTexture.h"
#include "InputManager.h"
#include "AudioManager.h"
#include "Bullet.h"
using namespace Galaxy;
class Player : public GameEntity {
public:
	Texture* mShip;
	static const int MAX_BULLETS = 1;
	Bullet* mBullets[MAX_BULLETS];
private:
	Timer* mTimer;
	InputManager* mInput;
	AudioManager* mAudio;
	bool mVisible;
	bool mAnimating;
	int mScore;
	int mLives;

	AnimatedTexture* mDeathAnimation;

	float mMoveSpeed;
	//limit move
	Vector2 mMoveBoundsx;
	Vector2 mMoveBoundsy;
	//static const int MAX_BULLETS = 2;
	
private:

	void HandleMovement();
	void HandleFiring();

public:
	Player();
	~Player();

	void Visible(bool visible);
	bool IsAnimating();

	int Score();
	int Lives();

	void AddScore(int change);
	
	void WasHit();
	void Update();
	void Render();
};

#endif
