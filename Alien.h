#pragma once

#include "raylib.h"
#include "SpaceInvadersDefinitions.h"
#include "CollisionInterface.h"
#include "SpaceInvaderResourceManager.h"
#include "Sprite.h"
#include "SpriteRenderer.h"

struct Alien : ICollidable
{
public:

	static constexpr float speed = 2;
	static constexpr float row_height = 50;

	static constexpr Vector2 collider_size{ 60, 30 };

	static constexpr Vector2 RENDER_SIZE{ 100, 100 };
	static constexpr Vector2 RENDER_OFFSET{ 50, 50 };
	static constexpr std::string_view ALIEN_TEXTURE_PATH = "./Assets/Alien.png";
	static constexpr Vector2 TEXTURE_SIZE{ 352, 352 };

	Vector2 position;
	Sprite sprite{ ALIEN_TEXTURE_PATH, TEXTURE_SIZE, RENDER_SIZE, RENDER_OFFSET };
	SpriteRenderer sprite_renderer{};

	bool active = true;
	float x_direction = 1;

	Alien(Vector2 position) noexcept;

	void Update();
	void MoveToNextRow();
	void Render(SpaceInvadersResourceManager& resources);

	Rectangle GetCollisionRect() const override;
	void OnCollision() override;
};