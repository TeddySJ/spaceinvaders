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

	struct AlienFormationConfig {
		int width = 8;
		int height = 5;
		int spacing = 80;
		float start_x = 550;
		float start_y = 50;
	};

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

	void UpdateAliensShooting(SpaceInvadersResourceManager& resources);

	bool CheckGameOverCriteria() const;

	void GameOver();
	void HandleCollisions();
	void PruneEntities();
	void SpawnAliens(SpaceInvadersResourceManager& resources);
	void SpawnWalls(SpaceInvadersResourceManager& resources);
};

class TransitionToGameplay : public StateChangeTransition
{
public:
	std::unique_ptr<GameState> ConstructState(SpaceInvadersResourceManager& resources) const override;
};

