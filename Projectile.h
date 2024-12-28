#pragma once

#include "raylib.h"
#include "SpaceInvadersDefinitions.h"
#include "CollisionInterface.h"
#include "Sprite.h"
#include "SpriteRenderer.h"

class Projectile : public ICollidable
{
public:
	Projectile(Vector2 position, float speed) noexcept;

	void Update();
	void Render(const SpaceInvadersResourceManager& resources) const;

	Rectangle GetCollisionRect() const noexcept override;
	void OnCollision() noexcept override;

	bool IsActive() const noexcept;

private:
	static constexpr Vector2 RENDER_SIZE{ 50, 50 };
	static constexpr Vector2 RENDER_OFFSET{ 25, 25 };
	static constexpr std::string_view PROJECTILE_TEXTURE_PATH = "./Assets/Laser.png";
	static constexpr Vector2 TEXTURE_SIZE{ 176, 176 };
	static constexpr Vector2 COLLIDER_SIZE{ 10, 20 };

	Sprite sprite{ PROJECTILE_TEXTURE_PATH, TEXTURE_SIZE, RENDER_SIZE, RENDER_OFFSET };
	SpriteRenderer sprite_renderer;

	Vector2 position;
	float speed;
	bool active = true;
};
