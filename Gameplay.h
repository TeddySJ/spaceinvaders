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
	Gameplay();

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

	Player player{};

	void Render(const SpaceInvadersResourceManager& resources) const override;
	void HandleInput() override;
	void Update() override;

	void UpdateAliensShooting();

	bool CheckGameOverCriteria() const;

	void GameOver();
	void HandleCollisions();
	void PruneEntities();
	void SpawnAliens();
	void SpawnWalls();
};

class TransitionToGameplay : public StateChangeTransition
{
public:
	std::unique_ptr<GameState> ConstructState() const override;
};

