#include "GameManager.h"
//file ini digunakan untuk mengandle game loop, game render dan game update dari seluruh game
namespace Galaxy {
	GameManager* GameManager::sInstance = NULL;
	GameManager* GameManager::Instance() {
		if (sInstance == NULL)
			sInstance = new GameManager();
		return sInstance;
	}

	void GameManager::Release() {
		delete sInstance;
		sInstance = NULL;
	}

	GameManager::GameManager() {
		mQuit = false;
		mGraphics = Graphics::Instance();
		if (!Graphics::Initialized())
			mQuit = true;
		mAssetMgr = AssetManager::Instance();
		mInputMgr = InputManager::Instance();
		mAudioMgr = AudioManager::Instance();
		mTimer = Timer::Instance();
		mScreenMgr = ScreenManager::Instance();

	}

	GameManager::~GameManager() {
		ScreenManager::Release();
		mScreenMgr = NULL;

		AudioManager::Release();
		mAudioMgr = NULL;

		AssetManager::Release();
		mAssetMgr = NULL;

		Graphics::Release();
		mGraphics = NULL;

		InputManager::Release();
		mInputMgr = NULL;

		Timer::Release();
		mTimer = NULL;
	}

	void GameManager::EarlyUpdate() {
		mInputMgr->Update();
	}

	void GameManager::Update() {
		mScreenMgr->Update();

	}

	void GameManager::LateUpdate() {
		mInputMgr->UpdatePrevInput();
		mTimer->Reset();
	}

	void GameManager::Render() {
		mGraphics->ClearBackBuffer();
		mScreenMgr->Render();
		mGraphics->Render();
	}

	void GameManager::Run() {

		while (!mQuit) {
			mTimer->Update();
			while (SDL_PollEvent(&mEvents) != 0) {
				if (mEvents.type == SDL_QUIT || mInputMgr->KeyPressed(SDL_SCANCODE_0)) {
					mQuit = true;
				}
			}

			if (mTimer->DeltaTime() >= (1.0f / FRAME_RATE))
			{
				printf("DeltaTime : %F \n", mTimer->DeltaTime());
				EarlyUpdate();
				Update();
				LateUpdate();
				Render();
				//delay fps to Optimize CPU performance
				SDL_Delay(1.0f / FRAME_RATE * 1000);
			}
		}
	}
}