#include "Gameplay.h"
#include "PostGame.h"
#include <format>
#include <random>
#include <ranges>

Gameplay::Gameplay()
{
	SpawnWalls();
	SpawnAliens();
}

void Gameplay::Render(const SpaceInvadersResourceManager& resources) const
{
	background.Render();

	DrawText(std::format("Score: {}", score).c_str(), 50, 20, 40, YELLOW);
	DrawText(std::format("Lives: {}", player.lives).c_str(), 50, 70, 40, YELLOW);

	player.Render(resources);

	// TODO: Make the below const auto& when const-refactoring of the render pipeline is completed!
	for (auto& projectile : player_projectiles) 
	{
		projectile.Render(resources);
	}

	for (auto& projectile : enemy_projectiles) 
	{
		projectile.Render(resources);
	}

	for (auto& wall : walls) 
	{
		wall.Render(resources);
	}

	for (auto& alien : aliens) 
	{
		alien.Render(resources);
	}
}

void Gameplay::HandleInput()
{
	if (IsKeyReleased(KEY_Q))
	{
		GameOver();
	}

	if (IsKeyPressed(KEY_SPACE))
	{
		player_shot_queued = true;
	}
}

void Gameplay::Update()
{
	player.Update();

	if (player_shot_queued)
	{
		player_projectiles.emplace_back(player.position, -15, EntityType::PLAYER_PROJECTILE);
		player_shot_queued = false;
	}

	std::ranges::for_each(aliens, &Alien::Update);
	std::ranges::for_each(player_projectiles, &Projectile::Update);
	std::ranges::for_each(enemy_projectiles, &Projectile::Update);

	UpdateAliensShooting();

	HandleCollisions();

	PruneEntities();

	if (aliens.empty())
	{
		SpawnAliens();
	}

	if (CheckGameOverCriteria())
	{
		GameOver();
	}
}

void Gameplay::UpdateAliensShooting()
{
	shootTimer += 1;
	if (shootTimer == 60)
	{
		int randomAlienIndex = std::rand() % aliens.size();
		enemy_projectiles.emplace_back(aliens[randomAlienIndex].position, 15, EntityType::ENEMY_PROJECTILE);
		shootTimer = 0;
	}
}

bool Gameplay::CheckGameOverCriteria() const
{
	if (player.lives <= 0)
	{
		return true;
	}
	
	if (std::ranges::any_of(aliens, [this](const auto& alien)
		{ return alien.position.y >= player.position.y; }))
	{
		return true;
	}

	return false;
}

void Gameplay::GameOver()
{
	QueueStateChange(std::make_unique<TransitionToPostGame>(score));
}

void Gameplay::HandleCollisions()
{
	ICollidable::CheckCollisions(player_projectiles, walls);
	ICollidable::CheckCollisions(player_projectiles, aliens);
	ICollidable::CheckCollisions(enemy_projectiles, player);
	ICollidable::CheckCollisions(enemy_projectiles, walls);
}

void Gameplay::PruneEntities()
{
	std::erase_if(player_projectiles, [](const auto& e) { return !e.active; });
	std::erase_if(enemy_projectiles, [](const auto& e) { return !e.active; });
	std::erase_if(walls, [](const auto& e) { return !e.active; });

	size_t removed_aliens = std::erase_if(aliens, [](const auto& e) { return !e.active; });
	score += 100 * removed_aliens;
}

void Gameplay::SpawnAliens()
{
	const AlienFormationConfig alien_formation_config{};

	for (int row : std::views::iota(0, alien_formation_config.height)) 
	{
		for (int col : std::views::iota(0, alien_formation_config.width)) 
		{
			aliens.emplace_back(Vector2{alien_formation_config.start_x + (col * alien_formation_config.spacing), alien_formation_config.start_y + (row * alien_formation_config.spacing)});
		}
	}
}

void Gameplay::SpawnWalls()
{
	auto window_width = static_cast<float>(GetScreenWidth());
	auto window_height = static_cast<float>(GetScreenHeight());
	float wallCount = 5;
	auto wall_distance = window_width / (wallCount + 1.f);

	for (int i : std::views::iota(0, wallCount))
	{
		walls.emplace_back(Vector2{ wall_distance * (i + 1) , window_height - 250 });
	}
}

std::unique_ptr<GameState> TransitionToGameplay::ConstructState() const
{
	return std::make_unique<Gameplay>();
}
