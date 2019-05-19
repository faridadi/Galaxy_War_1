#ifndef _GRAPHICS_H
#define _GRAPHICS_H
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_Image.h>
#include <string>
#include <stdio.h>
namespace Galaxy {
	class Graphics {
	public:
		static const int SCREEN_WIDTH = 800;
		static const int SCREEN_HEIGHT = 600;
		const char* WINDOW_TITLE = "Galaxy War I";

	private:
		static Graphics* sInstance;
		static bool sInitialized;
		SDL_Window* mWindow;
		SDL_Surface* mBackBuffer;
		SDL_Renderer* mRenderer;

	public:
		static Graphics* Instance();
		static void Release();
		static bool Initialized();
		SDL_Texture* LoadTexture(std::string path);
		SDL_Texture* CreateTextTexture(TTF_Font* fonts, std::string text);
		SDL_Texture* CreateTextTexture(TTF_Font* font, std::string text, SDL_Color color);
		void ClearBackBuffer();
		void DrawTexture(SDL_Texture* tex, SDL_Rect* clip = NULL, SDL_Rect* rend = NULL, float angel = 0.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);
		void Render();

	private:
		Graphics();
		~Graphics();
		bool Init();
	};
}
#endif
