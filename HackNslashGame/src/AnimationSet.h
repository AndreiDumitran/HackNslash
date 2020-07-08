#ifndef ANIMATIONSET
#define ANIMATIONSET

#include "Animation.h"

class AnimationSet
{
public:
	string imageName;
	SDL_Texture* spriteSheet;
	SDL_Texture* whiteSpriteSheet = NULL;
	list<Animation> animations;

	~AnimationSet();

	Animation* GetAnimation(string name);

	void LoadAnimationSet(string fileName, list<DataGroupType>& groupTypes, bool setColourKey = false, int transparentPixelIndex = 0, bool createWhiteTexture = false);

};

#endif