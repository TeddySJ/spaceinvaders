#include "game.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <fstream>
#include <ranges>


// MATH FUNCTIONS
float lineLength(Vector2 A, Vector2 B) //Uses pythagoras to calculate the length of a line
{
	float length = sqrtf(static_cast<float>(pow(B.x - A.x, 2) + pow(B.y - A.y, 2)));

	return length;
}

bool pointInCircle(Vector2 circlePos, float radius, Vector2 point) // Uses pythagoras to calculate if a point is within a circle or not
{
	float distanceToCentre = lineLength(circlePos, point);

	if (distanceToCentre < radius)
	{
		return true;
	}
	else
	{
		return false;
	}
}

Game::Game()
	: current_state{ std::make_unique<StartScreen>() }
{
	window_handle.SetTargetFPS(60);
}

void Game::Start()
{
	// creating walls 
	float window_width = (float)GetScreenWidth();
	float window_height = (float)GetScreenHeight();
	int wallCount = 5;
	float wall_distance = window_width / (wallCount + 1);

	for (int i = 0; i < wallCount; i++)
	{
		walls.emplace_back(resources, Vector2{ wall_distance * (i + 1) , window_height - 250 });
	}

	//creating aliens
	SpawnAliens();

	//reset score
	score = 0;
}

void Game::End()
{
	//SAVE SCORE AND UPDATE SCOREBOARD
	player_projectiles.clear();
	enemy_projectiles.clear();
	walls.clear();
	aliens.clear();
	highscore_manager.Enter(score);
	score = 0;
	player.lives = 3;
	current_state->QueueStateChange(std::make_unique<TransitionToPostGame>());
}

void Game::Continue()
{
	current_state->QueueStateChange(std::make_unique<TransitionToStartScreen>());
}

void Game::Run()
{
	while (!WindowShouldClose())
	{
		HandleInput();

		Update();

		Render();
	}
}

void Game::Update()
{
	current_state->Update();

	if (current_state->StateAsEnum == State::GAMEPLAY)
	{
		UpdateGameplay();
	}

	if (current_state->StateShouldChange())
	{
		ChangeState(std::move(current_state->next_state.value()->ConstructState(resources))); // TODO: Refactor to follow law of demeter
	}
}

void Game::UpdateGameplay()
{
	//Update Player
	player.Update();

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
		SpawnAliens();
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

void Game::HandleInput()
{
	current_state->HandleInput();

	if (current_state->StateAsEnum == State::GAMEPLAY)
	{
		if (IsKeyReleased(KEY_Q))
		{
			End();
		}

		//MAKE PROJECTILE
		if (IsKeyPressed(KEY_SPACE))
		{
			// TODO: Base this on player pos when it has become a Vector2
			player_projectiles.emplace_back(resources, Vector2{ player.position.x, (float)GetScreenHeight() - 130 }, -15, EntityType::PLAYER_PROJECTILE);
		}
	}
	else if (current_state->StateAsEnum == State::STARTSCREEN)
	{
		if (IsKeyReleased(KEY_SPACE))
		{
			Start();
		}
	}
	else if (current_state->StateAsEnum == State::ENDSCREEN)
	{
		HandleInput_EndScreen();
	}
}

void Game::HandleInput_EndScreen()
{
	if (highscore_manager.entering_new_highscore)
	{
		highscore_manager.NewHighscoreInput();
	}
	else if (IsKeyReleased(KEY_ENTER))
	{
		Continue();
	}
}

void Game::HandleCollisions()
{
	ICollidable::CheckCollisions(player_projectiles, walls);
	ICollidable::CheckCollisions(player_projectiles, aliens);
	ICollidable::CheckCollisions(enemy_projectiles, player);
	ICollidable::CheckCollisions(enemy_projectiles, walls);
}

void Game::PruneEntities()
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

void Game::Render()
{
	BeginDrawing();
	ClearBackground(BLACK);

	current_state->Render(resources);

	if (current_state->StateAsEnum == State::STARTSCREEN)
	{
		//Render_StartScreen();
	}
	else if (current_state->StateAsEnum == State::GAMEPLAY)
	{
		Render_Gameplay();
	}
	else if (current_state->StateAsEnum == State::ENDSCREEN)
	{
		Render_EndScreen();
	}

	EndDrawing();
}

void Game::Render_StartScreen()
{
	//Code
	DrawText("SPACE INVADERS", 200, 100, 160, YELLOW);

	DrawText("PRESS SPACE TO BEGIN", 200, 350, 40, YELLOW);
}

void Game::Render_Gameplay()
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

void Game::Render_EndScreen()
{
	if (highscore_manager.entering_new_highscore)
	{
		highscore_manager.RenderNameEntry();
	}
	else 
	{
		highscore_manager.RenderList();
	}
}

void Game::SpawnAliens()
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

void Game::ChangeState(std::unique_ptr<GameState> new_state)
{
	current_state = std::move(new_state);
}
