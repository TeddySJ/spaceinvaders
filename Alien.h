#pragma once

#include "raylib.h"
#include "SpaceInvadersDefinitions.h"
#include "CollisionInterface.h"

struct Alien : ICollidable
{
public:

	static constexpr float speed = 2;
	static constexpr Vector2 collider_size{ 60, 30 };
	static constexpr Vector2 render_size{ 100, 100 };
	static constexpr Vector2 render_offset { 50, 50 };
	static constexpr float row_height = 50;

	Vector2 position;

	bool active = true;
	float x_direction = 1;

	explicit Alien(Vector2 position) noexcept;

	void Update();
	void MoveToNextRow();
	void Render(Texture2D texture);

	Rectangle GetCollisionRect() const override;
	void OnCollision() override;
};