#pragma once

#include "raylib.h"
#include "SpaceInvadersDefinitions.h"
#include "CollisionInterface.h"
#include "Sprite.h"
#include "SpriteRenderer.h"

struct Projectile : ICollidable
{
public:
	// INITIALIZE PROJECTILE WHILE DEFINING IF ITS PLAYER OR ENEMY 
	Vector2 position;
	int speed;
	bool active = true;
	EntityType type;

	static constexpr Vector2 RENDER_SIZE{ 50, 50 };
	static constexpr Vector2 RENDER_OFFSET{ 25, 25 };
	static constexpr std::string_view PROJECTILE_TEXTURE_PATH = "./Assets/Laser.png";
	static constexpr Vector2 TEXTURE_SIZE{ 176, 176 };

	Sprite sprite{ PROJECTILE_TEXTURE_PATH, TEXTURE_SIZE, RENDER_SIZE, RENDER_OFFSET };
	SpriteRenderer sprite_renderer;

	Vector2 collider_size{ 10, 20 };

	Projectile(Vector2 position, int speed, EntityType type);

	void Update();
	void Render(const SpaceInvadersResourceManager& resources) const;

	Rectangle GetCollisionRect() const override;
	void OnCollision() override;
};
