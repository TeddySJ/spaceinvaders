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

	gameState = State::GAMEPLAY;

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
	gameState = State::ENDSCREEN;
}

void Game::Continue()
{
	gameState = State::STARTSCREEN;
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
	if (gameState == State::GAMEPLAY)
	{
		UpdateGameplay();
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
	if (gameState == State::GAMEPLAY)
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
	else if (gameState == State::STARTSCREEN)
	{
		if (IsKeyReleased(KEY_SPACE))
		{
			Start();
		}
	}
	else if (gameState == State::ENDSCREEN)
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

	if (gameState == State::STARTSCREEN)
	{
		Render_StartScreen();
	}
	else if (gameState == State::GAMEPLAY)
	{
		Render_Gameplay();
	}
	else if (gameState == State::ENDSCREEN)
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

bool Game::CheckCollision(Vector2 circlePos, float circleRadius, Vector2 lineStart, Vector2 lineEnd)
{
	// our objective is to calculate the distance between the closest point on the line to the centre of the circle, 
	// and determine if it is shorter than the radius.

	// check if either edge of line is within circle
	if (pointInCircle(circlePos, circleRadius, lineStart) || pointInCircle(circlePos, circleRadius, lineEnd))
	{
		return true;
	}

	// simplify variables
	Vector2 A = lineStart;
	Vector2 B = lineEnd;
	Vector2 C = circlePos;

	// calculate the length of the line
	float length = lineLength(A, B);

	// calculate the dot product
	float dotP = (((C.x - A.x) * (B.x - A.x)) + ((C.y - A.y) * (B.y - A.y))) / pow(length, 2);

	// use dot product to find closest point
	float closestX = A.x + (dotP * (B.x - A.x));
	float closestY = A.y + (dotP * (B.y - A.y));

	//find out if coordinates are on the line.
	// we do this by comparing the distance of the dot to the edges, with two vectors
	// if the distance of the vectors combined is the same as the length the point is on the line

	//since we are using floating points, we will allow the distance to be slightly innaccurate to create a smoother collision
	float buffer = 0.1;

	float closeToStart = lineLength(A, { closestX, closestY }); //closestX + Y compared to line Start
	float closeToEnd = lineLength(B, { closestX, closestY });	//closestX + Y compared to line End

	float closestLength = closeToStart + closeToEnd;

	if (closestLength == length + buffer || closestLength == length - buffer)
	{
		//Point is on the line!

		//Compare length between closest point and circle centre with circle radius

		float closeToCentre = lineLength(A, { closestX, closestY }); //closestX + Y compared to circle centre

		if (closeToCentre < circleRadius)
		{
			//Line is colliding with circle!
			return true;
		}
		else
		{
			//Line is not colliding
			return false;
		}
	}
	else
	{
		// Point is not on the line, line is not colliding
		return false;
	}

}