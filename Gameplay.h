#pragma once
#include "GameState.h"
#include "Player.h"
#include "Projectile.h"
#include "Wall.h"
#include "Alien.h"
#include "Background.h"
#include "SpaceInvadersDefinitions.h"
#include <vector>
#include <string>

class Gameplay : public GameState
{
public:
	Gameplay(SpaceInvadersResourceManager& resources);

	int score;
	float shootTimer = 0;

	std::vector<Projectile> player_projectiles;
	std::vector<Projectile> enemy_projectiles;
	std::vector<Wall> walls;
	std::vector<Alien> aliens;
	Background background{ 600 };

	Player player;
	bool player_shot_queued = false;

	void Render(SpaceInvadersResourceManager& resources) override;
	void HandleInput() override;
	void Update(SpaceInvadersResourceManager& resources) override;

	void End();
	void HandleCollisions();
	void PruneEntities();
	void SpawnAliens(SpaceInvadersResourceManager& resources);
};
