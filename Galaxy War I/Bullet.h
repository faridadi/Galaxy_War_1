#ifndef Bullet_h
#define Bullet_h

#include "Timer.h"
#include "Texture.h"

using namespace Galaxy;

class Bullet : public GameEntity {
public:
	Texture* mTexture;
private:
	const int OFFSCREEN_BUFFER = 10;
	Timer* mTimer;
	float mSpeed;
	

public:
	Bullet();
	~Bullet();
	void Fire(Vector2 pos);
	void Reload();
	void Update();
	void Render();

};

#endif
