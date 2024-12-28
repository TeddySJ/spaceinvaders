#pragma once
#include "AnimatedSprite.h"

class AnimatedSpriteRenderer final
{
public:
	void Update(const AnimatedSprite& sprite, double delta_time) noexcept;
	void Render(const SpaceInvadersResourceManager& resources, const AnimatedSprite& sprite, Vector2 position) const;

private:
	uint16_t current_frame;
	double time_accumulated;
};