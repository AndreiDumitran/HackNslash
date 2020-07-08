#ifndef LIVINGENTITY
#define LIVINGENTITY

#include "Entity.h"

class LivingEntity : public Entity
{
public:
	int hp, hpMax;
	int damage = 0;
	SDL_Rect hitBox;

	float invincibleTimer = 0;

	virtual void UpdateHitBox();
	virtual void UpdateDamages() = 0;
	virtual void Die() = 0;
	virtual void UpdateInvincibleTimer();

	void Draw();
};

#endif // !LIVINGENTITY
