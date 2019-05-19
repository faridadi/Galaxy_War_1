#ifndef _GAMEMANAGER_H
#define _GAMEMANAGER_H
#include "Timer.h"
#include "InputManager.h"
#include "Texture.h"
#include "AnimatedTexture.h"
#include "AudioManager.h"
#include "ScreenManager.h"
namespace Galaxy {

	class GameManager {
	private:
		static GameManager* sInstance;
		const int FRAME_RATE = 60;
		bool mQuit;
		Graphics* mGraphics;
		AssetManager* mAssetMgr;
		InputManager* mInputMgr;
		AudioManager* mAudioMgr;
		Timer* mTimer;
		SDL_Event mEvents;

		ScreenManager* mScreenMgr;
	public:
		static GameManager* Instance();
		static void Release();

		void Run();
	private:
		GameManager();
		~GameManager();

		void EarlyUpdate();
		void Update();
		void LateUpdate();
		void Render();
	};
}
#endif
