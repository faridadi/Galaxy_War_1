#include "GameManager.h"
	int main(int argc, char* argv[]) {
		Galaxy::GameManager* game = Galaxy::GameManager::Instance();
		game->Run();
		Galaxy::GameManager::Release();
		game = NULL;
		return 0;
	};