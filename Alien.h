#pragma once

#include "raylib.h"
#include "SpaceInvadersDefinitions.h"
#include "CollisionInterface.h"
#include "SpaceInvaderResourceManager.h"
#include "Animation.h"

struct Alien : ICollidable
{
public:

	static constexpr float speed = 2;
	static constexpr float row_height = 50;

	static constexpr Vector2 collider_size{ 60, 30 };

	Animation animation;
	Vector2 position;

	bool active = true;
	float x_direction = 1;

	Alien(SpaceInvadersResourceManager& resources, Vector2 position) noexcept;

	void Update();
	void MoveToNextRow();
	void Render(SpaceInvadersResourceManager& resources);

	Rectangle GetCollisionRect() const override;
	void OnCollision() override;
};