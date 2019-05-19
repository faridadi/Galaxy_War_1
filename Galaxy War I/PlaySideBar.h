#ifndef PlaySideBar_h
#define PlaySideBar_h
#include "Timer.h"
#include "GameEntity.h"
#include "Texture.h"
#include "AudioManager.h"
#include "Scoreboard.h"
using namespace Galaxy;
class PlaySideBar : public GameEntity {
private:
	Timer* mTimer;
	AudioManager* mAudio;
	Texture* mBackground;
	Texture* mPlayerOneLabel;

	static const int MAX_SHIP_TEXTURE = 6;
	GameEntity* mShips;
	Texture* mShipTextures[MAX_SHIP_TEXTURE];
	int mTotalShips;
	Scoreboard* mTotalShipsLabel;

public:

	PlaySideBar();
	~PlaySideBar();
	
	void SetShips(int ships);

	void Update();
	void Render();
};


#endif
