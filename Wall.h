#pragma once

#include "raylib.h"
#include "SpaceInvadersDefinitions.h"
#include "CollisionInterface.h"
#include "Sprite.h"
#include "SpriteRenderer.h"

struct Wall : ICollidable
{
public:
	Vector2 position;
	Rectangle rec;
	bool active;
	Color color;
	int health = 50;

	static constexpr Vector2 RENDER_SIZE{ 200, 200 };
	static constexpr Vector2 RENDER_OFFSET{ 100, 100 };
	static constexpr std::string_view PROJECTILE_TEXTURE_PATH = "./Assets/Barrier.png";
	static constexpr Vector2 TEXTURE_SIZE{ 704, 704 };

	Sprite sprite{ PROJECTILE_TEXTURE_PATH, TEXTURE_SIZE, RENDER_SIZE, RENDER_OFFSET };
	SpriteRenderer sprite_renderer;

	Vector2 collider_size{ 140, 20 };

	Wall(Vector2 position);

	void Render(SpaceInvadersResourceManager& resources);

	Rectangle GetCollisionRect() const override;
	void OnCollision() override;
};
