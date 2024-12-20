#pragma once

#include "raylib.h"
#include "SpaceInvadersDefinitions.h"
#include "CollisionInterface.h"
#include "SpaceInvaderResourceManager.h"

struct Alien : ICollidable
{
public:

	static constexpr float speed = 2;
	static constexpr Vector2 collider_size{ 60, 30 };
	static constexpr Vector2 render_size{ 100, 100 };
	static constexpr Vector2 render_offset { 50, 50 };
	static constexpr float row_height = 50;
	static constexpr std::string_view texture_path = "./Assets/Alien.png";

	Vector2 position;

	bool active = true;
	float x_direction = 1;

	explicit Alien(Vector2 position) noexcept;

	void Update();
	void MoveToNextRow();
	void Render(const Texture2D& texture);
	void Render(SpaceInvadersResourceManager& resources);

	Rectangle GetCollisionRect() const override;
	void OnCollision() override;
};