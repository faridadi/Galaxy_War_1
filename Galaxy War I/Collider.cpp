#include"Collider.h"
//file ini digunakan untuk menghandle collision
/*
Collider::Collider(ColliderType type):mType(type){
	mDebugTexture = nullptr;
}*/
Collider::Collider(){
}

Collider::~Collider() {
	if (mDebugTexture)
	{
		delete mDebugTexture;
		mDebugTexture = nullptr;
	}
}

void Collider::setDebugTexture(Texture* texture) {
	delete mDebugTexture;
	mDebugTexture = texture;
	mDebugTexture->Parent(this);
}


bool Collider::checkCollision(SDL_Rect a, SDL_Rect b) {
	int leftA, leftB;
	int rightA, rightB;
	int topA, topB;
	int bottomA, bottomB;

	//Calculate the sides of rect A
	leftA = a.x;
	rightA = a.x + a.w;
	topA = a.y;
	bottomA = a.y + a.h;

	//Calculate the sides of rect B
	leftB = b.x;
	rightB = b.x + b.w;
	topB = b.y;
	bottomB = b.y + b.h;
	//If any of the sides from A are outside of B
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	//If none of the sides from A are outside B
	return true;
}
void Collider::Render() {
	if (DEBUG_COlliDERS)
	{
		mDebugTexture->Render();
	}
}