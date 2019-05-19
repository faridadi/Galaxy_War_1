#ifndef _TEXTURE_H
#define _TEXTURE_H
#include "GameEntity.h"
#include "AssetManager.h"
namespace Galaxy {
	class Texture : public GameEntity {
	protected:

		SDL_Texture* mTex;
		Graphics* mGraphics;
		
		bool mClipped;
		
		

	public:
		int mWidth;
		int mHeight;
		SDL_Rect mClipRect;
		SDL_Rect mRenderRect;
		Texture(std::string filename, int x, int y, int w, int h);
		Texture(std::string text, std::string fontpath, int size);
		Texture(std::string text, std::string fontpath, int size, SDL_Color color);
		Texture(std::string filename);
		~Texture();
		virtual void Render();
	};
}
#endif
