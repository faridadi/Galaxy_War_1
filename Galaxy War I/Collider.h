#ifndef _COLLIDER_H
#define _COLLIDER_H
#include "Texture.h";

using namespace Galaxy;
	class Collider : public GameEntity {
	public:
		enum class ColliderType {
			Box,
			Circle
		};

	protected:
		ColliderType mType;
		static const bool DEBUG_COlliDERS = true;
		Texture* mDebugTexture;
	public:
		bool checkCollision(SDL_Rect a, SDL_Rect b);
		//Collider(ColliderType type);
		Collider();
		virtual ~Collider();
		virtual void Render();

	protected:
		void setDebugTexture(Texture* texture);

	};
#endif

