#pragma once

#include "raylib.h"
#include "SpaceInvadersDefinitions.h"
#include "CollisionInterface.h"
#include "AnimatedSprite.h"
#include "AnimatedSpriteRenderer.h"
#include <functional>

class Player final : public ICollidable
{
public:
	Player() noexcept;

	void Render(const SpaceInvadersResourceManager& resources) const;
	void Update();
	void SetDirection(float new_direction) noexcept;

	Rectangle GetCollisionRect() const noexcept override;
	void OnCollision() noexcept override;

	Vector2 GetPosition() const noexcept;
	bool IsDead() const noexcept;
	int GetLives() const noexcept;

private:
	static constexpr Vector2 RENDER_SIZE{ 100, 100 };
	static constexpr Vector2 RENDER_OFFSET{ 50, 50 };
	static constexpr std::string_view PLAYER_TEXTURE_PATH = "./Assets/ship_spritesheet.png";
	static constexpr Vector2 TEXTURE_SIZE{ 1056, 352 };
	static constexpr uint16_t ANIMATION_FRAMES = 3;
	static constexpr double SECONDS_PER_FRAME = 0.1;

	static constexpr float PLAYER_DISTANCE_FROM_BOTTOM = 70;
	static constexpr float PLAYER_SPEED = 7;
	static constexpr float PROJECTILE_SPEED = 15;

	static constexpr Vector2 COLLIDER_SIZE{ 60, 30 };

	AnimatedSprite animated_sprite{ PLAYER_TEXTURE_PATH, TEXTURE_SIZE, RENDER_SIZE, RENDER_OFFSET, ANIMATION_FRAMES, SECONDS_PER_FRAME };
	AnimatedSpriteRenderer animated_sprite_renderer{};

	Rectangle playfield_rect;
	Vector2 position;
	float direction = 0;
	int lives = 3;
};