#include "LivingEntity.h"

void LivingEntity::UpdateHitBox()
{
	damage = 0;

	GroupBox* hitlBoxes = (GroupBox*)GroupBuilder::findGroupByName("hitBox", currentFrame->frameData);

	if (hitlBoxes != NULL && hitlBoxes->numberOfDataInGroup() > 0)
	{
		SDL_Rect hb = hitlBoxes->data.front();
		hitBox.x = x - currentFrame->offSet.x + hb.x;
		hitBox.y = y - currentFrame->offSet.y + hb.y;

		hitBox.w = hb.w;
		hitBox.h = hb.h;

		GroupNumber* damages = (GroupNumber*)GroupBuilder::findGroupByName("damage", currentFrame->frameData);
		if (damages != NULL && damages->numberOfDataInGroup() > 0)
			damage = damages->data.front();
	}

}

void LivingEntity::UpdateInvincibleTimer()
{
	if (invincibleTimer > 0)
		invincibleTimer -= TimeController::timeController.dT;
}

void LivingEntity::Draw()
{
	if (currentFrame != nullptr && active)
		currentFrame->Draw(animSet->spriteSheet, x, y);
	if (solid && Globals::debugging)
	{
		SDL_SetRenderDrawColor(Globals::renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawRect(Globals::renderer, &lastCollisionBox);

		SDL_SetRenderDrawColor(Globals::renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawRect(Globals::renderer, &collisionBox);

		SDL_SetRenderDrawColor(Globals::renderer, 255, 0, 255, SDL_ALPHA_OPAQUE);
		SDL_RenderDrawRect(Globals::renderer, &hitBox);
	}
}

