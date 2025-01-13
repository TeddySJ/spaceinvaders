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

class Gameplay final : public GameState
{
public:
	Gameplay();

	void Render(const RaylibResourceManager& resources) const override;
	void HandleInput() override;
	void Update() override;

private:
	static constexpr auto alien_formation_width = 8;
	static constexpr auto alien_formation_height = 5;
	static constexpr auto alien_formation_spacing = 80;
	static constexpr float alien_formation_start_x = 550;
	static constexpr float alien_formation_start_y = 50;

	static constexpr auto background_star_amount = 600;

	size_t score;
	float shoot_timer = 0;

	std::vector<Projectile> player_projectiles;
	std::vector<Projectile> enemy_projectiles;
	std::vector<Wall> walls;
	std::vector<Alien> aliens;
	Background background{ background_star_amount };

	Player player{};

	void UpdateAliensShooting();

	bool CheckGameOverCriteria() const;

	void GameOver();
	void HandleCollisions();
	void PruneEntities();
	void SpawnAliens();
	void SpawnWalls();
};

class TransitionToGameplay final : public StateChangeTransition
{
public:
	std::unique_ptr<GameState> ConstructState() const override;
};

