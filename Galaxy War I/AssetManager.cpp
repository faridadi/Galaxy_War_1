#include "AssetManager.h"
//File ini dogunakan untuk menghandle asset seperti Texture gambar, font,  agar terkontrol dana mudah saat penggunaannya
namespace Galaxy {
	AssetManager* AssetManager::sInstance = NULL;
	AssetManager* AssetManager::Instance() {
		if (sInstance == NULL)
			sInstance = new AssetManager();
		return sInstance;
	}

	void AssetManager::Release() {
		delete sInstance;
		sInstance = NULL;
	}

	AssetManager::AssetManager() {

	}

	AssetManager::~AssetManager() {
		for (auto tex : mTextures) {
			if (tex.second != NULL) {
				SDL_DestroyTexture(tex.second);
			}
		}
		mTextures.clear();

		for (auto text : mText) {
			if (text.second != NULL) {
				SDL_DestroyTexture(text.second);
			}
		}
		mText.clear();

		for (auto font : mFont) {
			if (font.second != NULL) {
				TTF_CloseFont(font.second);
			}
		}
		mFont.clear();

		/*
		for (auto music : mMusic) {
			if (music.second != NULL) {
				Mix_FreeMusic(music.second);
			}
		}
		mMusic.clear();
		*/

		for (auto sfx : mSFX) {
			if (sfx.second != NULL) {
				Mix_FreeChunk(sfx.second);
			}
		}
		mSFX.clear();
	}

	SDL_Texture* AssetManager::GetTexture(std::string filename) {
		
		std::string fullPath = SDL_GetBasePath();
		fullPath.append("Asset/" + filename);
		if (mTextures[fullPath] == nullptr)
			mTextures[fullPath] = Graphics::Instance()->LoadTexture(fullPath);
		return mTextures[fullPath];
	}

	TTF_Font* AssetManager::getFont(std::string filename, int size) {
		std::string fullpath = SDL_GetBasePath();
		fullpath.append("Asset/" + filename);
		std::string key = fullpath + (char)(size);
		if (mFont[key] == nullptr) {
			mFont[key] = TTF_OpenFont(fullpath.c_str(), size);
			if (mFont[key] == nullptr)
			{
				printf("Font Loading Font:%s  Error:%s\n", filename.c_str(), TTF_GetError());
			}
		}
		return mFont[key];
	}

	SDL_Texture* AssetManager::GetText(std::string text, std::string filename, int size) {
		TTF_Font* font = getFont(filename, size);
		std::string key = text + filename + (char)size;
		if (mText[key] == nullptr)
		{
			mText[key] = Graphics::Instance()->CreateTextTexture(font, text.c_str());
		}
		return mText[key];
	}

	SDL_Texture* AssetManager::GetText(std::string text, std::string filename, int size, SDL_Color color) {
		TTF_Font* font = getFont(filename, size);
		std::string key = text + filename + (char)size + (char)color.r + (char)color.b + (char)color.g;
		if (mText[key] == nullptr)
			mText[key] = Graphics::Instance()->CreateTextTexture(font, text, color);
		//returning the cached texture containing the text
		return mText[key];
	}


	Mix_Music* AssetManager::GetMusic(std::string filename) {
		std::string fullPath = SDL_GetBasePath();
		fullPath.append("Asset/" + filename);
		if (mMusic[fullPath] == nullptr) {
			mMusic[fullPath] = Mix_LoadMUS(fullPath.c_str());
			if (mMusic[fullPath] == NULL)
				printf("Music Loading Error: File-%s Error-%s", filename.c_str(), Mix_GetError());
		}
		return mMusic[fullPath];
	}

	Mix_Chunk* AssetManager::GetSFX(std::string filename) {
		std::string fullPath = SDL_GetBasePath();
		fullPath.append("Asset/" + filename);
		if (mSFX[fullPath] == nullptr) {
			mSFX[fullPath] = Mix_LoadWAV(fullPath.c_str());
			if (mSFX[fullPath] == NULL)
				printf("SFX Loading Error: File-%s Error-%s", filename.c_str(), Mix_GetError());
		}
		return mSFX[fullPath];
	}
}