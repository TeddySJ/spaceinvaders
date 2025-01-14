#include "Gameplay.h"
#include "PostGame.h"
#include <format>
#include <random>
#include <ranges>

/* SUPPRESSED WARNING: 
*  "The C++ Core Guidelines suggest that default constructors shouldn't do anything that can throw. When the default constructor can throw, all code that relies on a properly instantiated object may also throw."
*  This warning is geared towards objects of "smaller" responsibilities - constructing a game state is something where exceptions can be expected to possibly occur
*/ 
[[gsl::suppress(26455)]]
Gameplay::Gameplay()
{
	SpawnWalls();
	SpawnAliens();
}

void Gameplay::Render(const RaylibResourceManager& resources) const
{
	background.Render();

	DrawText(std::format("Score: {}", score).c_str(), 50, 20, 40, YELLOW);
	DrawText(std::format("Lives: {}", player.GetLives()).c_str(), 50, 70, 40, YELLOW);

	player.Render(resources);

	for (const auto& projectile : player_projectiles) 
	{
		projectile.Render(resources);
	}

	for (const auto& projectile : enemy_projectiles)
	{
		projectile.Render(resources);
	}

	for (const auto& wall : walls)
	{
		wall.Render(resources);
	}

	for (const auto& alien : aliens)
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

	if (IsKeyDown(KEY_LEFT))
	{
		player.SetDirection(-1);
	}
	else if (IsKeyDown(KEY_RIGHT))
	{
		player.SetDirection(1);
	}
	else
	{
		player.SetDirection(0);
	}

	if (IsKeyPressed(KEY_SPACE))
	{
		player_projectiles.emplace_back(player.GetPosition(), -15.f);
	}
}

void Gameplay::Update()
{
	player.Update();

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
	shoot_timer += 1;
	if (shoot_timer == 60)
	{
		const int randomAlienIndex = std::rand() % aliens.size();
		enemy_projectiles.emplace_back(aliens[randomAlienIndex].GetPosition(), 15.f);
		shoot_timer = 0;
	}
}

bool Gameplay::CheckGameOverCriteria() const
{
	if (player.IsDead())
	{
		return true;
	}
	
	if (std::ranges::any_of(aliens, [this](const auto& alien)
		noexcept { return alien.GetPosition().y >= player.GetPosition().y; } ))
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
	std::erase_if(player_projectiles, [](const auto& e) noexcept { return !e.IsActive(); });
	std::erase_if(enemy_projectiles, [](const auto& e) noexcept { return !e.IsActive(); });
	std::erase_if(walls, [](const auto& e) noexcept { return !e.IsActive(); });

	const size_t removed_aliens = std::erase_if(aliens, [](const auto& e) noexcept { return !e.IsActive(); });
	score += 100 * removed_aliens;
}

void Gameplay::SpawnAliens()
{
	for (const int row : std::views::iota(0, alien_formation_height)) 
	{
		for (const int col : std::views::iota(0, alien_formation_width))
		{
			aliens.emplace_back(Vector2{alien_formation_start_x + (col * alien_formation_spacing), alien_formation_start_y + (row * alien_formation_spacing)});
		}
	}
}

void Gameplay::SpawnWalls()
{
	const auto window_width = static_cast<float>(GetScreenWidth());
	const auto window_height = static_cast<float>(GetScreenHeight());
	const float wallCount = 5;
	const auto wall_distance = window_width / (wallCount + 1.f);

	for (const int i : std::views::iota(0, wallCount))
	{
		walls.emplace_back(Vector2{ wall_distance * (i + 1) , window_height - 250 });
	}
}

std::unique_ptr<GameState> TransitionToGameplay::ConstructState() const
{
	return std::make_unique<Gameplay>();
}
