#include "Gameplay.h"

Gameplay::Gameplay(SpaceInvadersResourceManager& resources)
	: GameState{ State::GAMEPLAY }, player{ resources }
{
	float window_width = (float)GetScreenWidth();
	float window_height = (float)GetScreenHeight();
	int wallCount = 5;
	float wall_distance = window_width / (wallCount + 1);

	for (int i = 0; i < wallCount; i++)
	{
		walls.emplace_back(resources, Vector2{ wall_distance * (i + 1) , window_height - 250 });
	}

	SpawnAliens(resources);
}

void Gameplay::Render(SpaceInvadersResourceManager& resources)
{
	//background render LEAVE THIS AT TOP
	background.Render();

	//DrawText("GAMEPLAY", 50, 30, 40, YELLOW);
	DrawText(TextFormat("Score: %i", score), 50, 20, 40, YELLOW);
	DrawText(TextFormat("Lives: %i", player.lives), 50, 70, 40, YELLOW);

	//player rendering 
	player.Render(resources);

	//projectile rendering
	for (int i = 0; i < player_projectiles.size(); i++)
	{
		player_projectiles[i].Render(resources);
	}

	for (int i = 0; i < enemy_projectiles.size(); i++)
	{
		enemy_projectiles[i].Render(resources);
	}

	// wall rendering 
	for (int i = 0; i < walls.size(); i++)
	{
		walls[i].Render(resources);
	}

	//alien rendering  
	for (int i = 0; i < aliens.size(); i++)
	{
		//aliens[i].Render(resources.alien_texture.GetTexture());
		aliens[i].Render(resources);
	}
}

void Gameplay::HandleInput()
{
	if (IsKeyReleased(KEY_Q))
	{
		End();
	}

	//MAKE PROJECTILE
	if (IsKeyPressed(KEY_SPACE))
	{
		player_shot_queued = true;
	}
}

void Gameplay::Update(SpaceInvadersResourceManager& resources)
{
	//Update Player
	player.Update();
	if (player_shot_queued)
	{
		player_projectiles.emplace_back(resources, player.position, -15, EntityType::PLAYER_PROJECTILE);
		player_shot_queued = false;
	}

	//Update Aliens and Check if they are past player
	for (int i = 0; i < aliens.size(); i++)
	{
		aliens[i].Update();

		if (aliens[i].position.y > GetScreenHeight() - player.player_base_height)
		{
			End();
		}
	}

	//End game if player dies
	if (player.lives < 1)
	{
		End();
	}

	//Spawn new aliens if aliens run out
	if (aliens.size() < 1)
	{
		SpawnAliens(resources);
	}

	for (int i = 0; i < player_projectiles.size(); i++)
	{
		player_projectiles[i].Update();
	}

	for (int i = 0; i < enemy_projectiles.size(); i++)
	{
		enemy_projectiles[i].Update();
	}

	for (int i = 0; i < walls.size(); i++)
	{
		walls[i].Update();
	}

	//Aliens Shooting
	shootTimer += 1;
	if (shootTimer > 59) //once per second
	{
		int randomAlienIndex = 0;

		if (aliens.size() > 1)
		{
			randomAlienIndex = rand() % aliens.size();
		}

		Vector2 v2SpawnPos = aliens[randomAlienIndex].position;
		v2SpawnPos.y += 40;
		enemy_projectiles.emplace_back(resources, v2SpawnPos, 15, EntityType::ENEMY_PROJECTILE);
		shootTimer = 0;
	}

	HandleCollisions();

	PruneEntities();
}

void Gameplay::End()
{
	//SAVE SCORE AND UPDATE SCOREBOARD
	player_projectiles.clear();
	enemy_projectiles.clear();
	walls.clear();
	aliens.clear();
	//highscore_manager.Enter(score);
	score = 0;
	player.lives = 3;
	QueueStateChange(std::make_unique<TransitionToPostGame>());
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
	// REMOVE INACTIVE/DEAD ENITITIES
	for (int i = 0; i < player_projectiles.size(); i++)
	{
		if (player_projectiles[i].active == false)
		{
			player_projectiles.erase(player_projectiles.begin() + i--);
		}
	}
	for (int i = 0; i < enemy_projectiles.size(); i++)
	{
		if (enemy_projectiles[i].active == false)
		{
			enemy_projectiles.erase(enemy_projectiles.begin() + i--);
		}
	}
	for (int i = 0; i < aliens.size(); i++)
	{
		if (aliens[i].active == false)
		{
			score += 100;
			aliens.erase(aliens.begin() + i--);
		}
	}
	for (int i = 0; i < walls.size(); i++)
	{
		if (walls[i].active == false)
		{
			walls.erase(walls.begin() + i--);
		}
	}
}

void Gameplay::SpawnAliens(SpaceInvadersResourceManager& resources)
{
	// TODO: Move these to constexpr somewhere
	int formationWidth = 8;
	int formationHeight = 5;
	int alienSpacing = 80;
	float formationX = 100;
	float formationY = 50;

	for (int row = 0; row < formationHeight; row++)
	{
		for (int col = 0; col < formationWidth; col++)
		{
			aliens.emplace_back(resources, Vector2{ formationX + 450 + (col * alienSpacing) , formationY + (row * alienSpacing) });
		}
	}

}
