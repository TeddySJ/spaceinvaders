#pragma once
#include "raylib.h"

enum struct State
{
	STARTSCREEN,
	GAMEPLAY,
	ENDSCREEN
};

enum struct EntityType
{
	PLAYER,
	ENEMY,
	PLAYER_PROJECTILE,
	ENEMY_PROJECTILE
};

template <class T, class R>
auto IsInRange(T value, R min, R max)
{
	return value >= min && value <= max;
}

static inline Rectangle GetTextureBoundsAsRectangle(Texture2D texture)
{
	return {0,0, static_cast<float>(texture.width), static_cast<float>(texture.height)};
}