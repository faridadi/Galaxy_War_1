#include "GameManager.h"
//file untuk menjalankan game
	int main(int argc, char* argv[]) {
		Galaxy::GameManager* game = Galaxy::GameManager::Instance();
		game->Run();
		Galaxy::GameManager::Release();
		game = NULL;
		return 0;
	};