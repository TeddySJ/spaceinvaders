#pragma once
#include "AnimatedSprite.h"

class AnimatedSpriteRenderer
{
public:
	uint16_t current_frame;
	double time_accumulated;

	void Update(const AnimatedSprite& sprite, double delta_time) noexcept;
	void Render(SpaceInvadersResourceManager& resources, const AnimatedSprite& sprite, Vector2 position) const;
};