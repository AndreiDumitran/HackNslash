#ifndef ENTITY
#define ENTITY

#include "globals.h"
#include "TimeController.h"
#include "AnimationSet.h"

class Entity
{
public:
	static const int DIR_UP, DIR_DOWN, DIR_LEFT, DIR_RIGHT, DIR_NONE;
	int state;

	float x, y;
	int direction;
	bool solid = true;
	bool collideWithSolids = true;
	bool active = true;
	string type = "entity";
	bool moving;
	float angle;
	float moveSpeed;
	float moveSpeedMax;
	float slideAngle;
	float slideAmount;
	float moveLerp = 4;
	float totalXMove, totalYMove;

	SDL_Rect collisionBox;
	SDL_Rect lastCollisionBox;
	int collisionBoxW, collisionBoxH;
	float collisionBoxYOffset;

	AnimationSet* animSet;
	Animation* currentAnimation;
	Frame* currentFrame;

	float frameTimer;

	virtual void Update();
	virtual void Draw();

	virtual void Move(float angle);
	virtual void UpdateMovement();
	virtual void UpdateCollisionBox();

	virtual void ChangeAnimation(int newState, bool resetFrameToBeginning) = 0;
	virtual void UpdateCollisions();

	static float DistanceBetweenTwoRect(SDL_Rect &r1, SDL_Rect &r2);
	static float DistanceBetweenTwoEntities(Entity* e1, Entity* e2);
	static float AngleBetweenTwoEntities(Entity* e1, Entity* e2	);
	static bool  CheckCollision(SDL_Rect cbox1, SDL_Rect cbox2);
	static int   AngleToDirection(float angle);
	static float AngleBetweenTwoPoints(float cx1, float cy1, float cx2, float cy2);
	static float AngleBetweenTwoRects(SDL_Rect& r1, SDL_Rect& r2);

	static list<Entity*> entities;
	static bool EntityCompare(const Entity* const& a, const Entity* const& b);
	static void RemoveInactiveEntitiesFromList(list<Entity*>* entityList, bool deleteEntities);
	static void RemoveAllFromList(list<Entity*>* entityList, bool deleteEntities);
};

#endif // !ENTITY
