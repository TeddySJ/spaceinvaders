#pragma once

#include "raylib.h"
#include "SpaceInvadersDefinitions.h"
#include "CollisionInterface.h"
#include "Sprite.h"
#include "SpriteRenderer.h"

class Wall : public ICollidable
{
public:
	explicit Wall(Vector2 position) noexcept;

	void Render(const SpaceInvadersResourceManager& resources) const;

	Rectangle GetCollisionRect() const noexcept override;
	void OnCollision() noexcept override;

	bool IsActive() const noexcept;

private:
	static constexpr Vector2 RENDER_SIZE{ 200, 200 };
	static constexpr Vector2 RENDER_OFFSET{ 100, 100 };
	static constexpr std::string_view PROJECTILE_TEXTURE_PATH = "./Assets/Barrier.png";
	static constexpr Vector2 TEXTURE_SIZE{ 704, 704 };

	static constexpr Vector2 COLLIDER_SIZE{ 140, 20 };

	Sprite sprite{ PROJECTILE_TEXTURE_PATH, TEXTURE_SIZE, RENDER_SIZE, RENDER_OFFSET };
	SpriteRenderer sprite_renderer;

	Vector2 position;
	int health = 50;
};
