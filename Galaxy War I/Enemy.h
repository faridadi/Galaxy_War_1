#ifndef Enemy_h
#define Enemy_h
#include "Animatedtexture.h"
namespace Galaxy {
	class Enemy : public GameEntity {

	public:

		enum STATES { flyIn, dead };
		enum TYPES { butterfly, wasp, boss };
		int health;
		Timer* mTimer;
		Texture* mTextures[2];
		STATES mCurrentState;

		float mSpeed;
		TYPES mType;
		int mIndex;

	public:

		void FlyInComplete();
		void HandleFlyInState();
		//void HandleDeadState();
		void HandleStates();

		void RenderFlyInState();
		//void RenderDeadState();
		void RenderStates();

		Enemy(int speed, int pos, int type);
		~Enemy();
		STATES CurrentState();
		TYPES Type();
		void Update();
		void Render();



	};



}
#endif /* Enemy_h */
