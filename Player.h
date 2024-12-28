#pragma once

#include "raylib.h"
#include "SpaceInvadersDefinitions.h"
#include "CollisionInterface.h"
#include "AnimatedSprite.h"
#include "AnimatedSpriteRenderer.h"

struct Player : ICollidable
{
public:

	float player_base_height = 70.0f;
	Vector2 position;
	float speed = 7;
	Vector2 collider_size{ 60, 30 };
	int lives = 3;
	int direction = 0;
	int activeTexture = 0;
	float timer = 0;

	static constexpr Vector2 RENDER_SIZE{ 100, 100 };
	static constexpr Vector2 RENDER_OFFSET{ 50, 50 };
	static constexpr std::string_view PLAYER_TEXTURE_PATH = "./Assets/ship_spritesheet.png";
	static constexpr Vector2 TEXTURE_SIZE{ 1056, 352 };
	static constexpr uint16_t ANIMATION_FRAMES = 3;
	static constexpr double SECONDS_PER_FRAME = 0.1;

	AnimatedSprite animated_sprite{ PLAYER_TEXTURE_PATH, TEXTURE_SIZE, RENDER_SIZE, RENDER_OFFSET, ANIMATION_FRAMES, SECONDS_PER_FRAME };
	AnimatedSpriteRenderer animated_sprite_renderer{};

	EntityType type = EntityType::PLAYER;

	Player();

	void Render(SpaceInvadersResourceManager& resources);
	void Update();

	Rectangle GetCollisionRect() const override;
	void OnCollision() override;
};
