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
	newHighScore = CheckNewHighScore();
	player.lives = 3;
	gameState = State::ENDSCREEN;
}

void Game::Continue()
{
	SaveLeaderboard();
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

	// Update background with offset
	playerPos = { player.position.x, (float)player.player_base_height };
	cornerPos = { 0, (float)player.player_base_height };
	offset = lineLength(playerPos, cornerPos) * -1;
	background.Update(offset / 15);


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

void Game::HandleInput_EndScreen() // TODO: Refactor
{
	if (newHighScore)
	{
		// TODO: Why would we want to involve the mouse here? Just have the textbox be constantly on - but first of course ask Ulf if we are allowed to change this behavior!
		if (CheckCollisionPointRec(GetMousePosition(), textBox)) mouseOnText = true;
		else mouseOnText = false;

		if (mouseOnText)
		{
			// Set the window's cursor to the I-Beam
			SetMouseCursor(MOUSE_CURSOR_IBEAM);

			// Get char pressed on the queue
			int key = GetCharPressed();

			// Check if more characters have been pressed on the same frame
			while (key > 0) // TODO: "key = GetCharPressed()"
			{
				// NOTE: Only allow keys in range [32..125]
				if ((key >= 32) && (key <= 125) && (letterCount < 9))
				{
					name[letterCount] = (char)key;
					name[letterCount + 1] = '\0'; // Add null terminator at the end of the string.
					letterCount++;
				}

				key = GetCharPressed();  // Check next character in the queue
			}

			//Remove chars 
			if (IsKeyPressed(KEY_BACKSPACE))
			{
				letterCount--;
				if (letterCount < 0) letterCount = 0;
				name[letterCount] = '\0';
			}
		}
		else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

		if (mouseOnText)
		{
			framesCounter++;
		}
		else
		{
			framesCounter = 0;
		}

		// If the name is right legth and enter is pressed, exit screen by setting highscore to false and add 
		// name + score to scoreboard
		if (letterCount > 0 && letterCount < 9 && IsKeyReleased(KEY_ENTER))
		{
			std::string nameEntry(name);

			InsertNewHighScore(nameEntry);

			newHighScore = false;
		}
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
	if (newHighScore)
	{
		DrawText("NEW HIGHSCORE!", 600, 300, 60, YELLOW);

		// BELOW CODE IS FOR NAME INPUT RENDER
		DrawText("PLACE MOUSE OVER INPUT BOX!", 600, 400, 20, YELLOW);

		DrawRectangleRec(textBox, LIGHTGRAY);
		if (mouseOnText)
		{
			// HOVER CONFIRMIATION
			DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, RED);
		}
		else
		{
			DrawRectangleLines((int)textBox.x, (int)textBox.y, (int)textBox.width, (int)textBox.height, DARKGRAY);
		}

		//Draw the name being typed out
		DrawText(name, (int)textBox.x + 5, (int)textBox.y + 8, 40, MAROON);

		//Draw the text explaining how many characters are used
		DrawText(TextFormat("INPUT CHARS: %i/%i", letterCount, 8), 600, 600, 20, YELLOW);

		if (mouseOnText)
		{
			if (letterCount < 9)
			{
				// Draw blinking underscore char
				if (((framesCounter / 20) % 2) == 0)
				{
					DrawText("_", (int)textBox.x + 8 + MeasureText(name, 40), (int)textBox.y + 12, 40, MAROON);
				}

			}
			else
			{
				//Name needs to be shorter
				DrawText("Press BACKSPACE to delete chars...", 600, 650, 20, YELLOW);
			}

		}

		// Explain how to continue when name is input
		if (letterCount > 0 && letterCount < 9)
		{
			DrawText("PRESS ENTER TO CONTINUE", 600, 800, 40, YELLOW);
		}

	}
	else {
		// If no highscore or name is entered, show scoreboard and call it a day
		DrawText("PRESS ENTER TO CONTINUE", 600, 200, 40, YELLOW);

		DrawText("LEADERBOARD", 50, 100, 40, YELLOW);

		for (int i = 0; i < Leaderboard.size(); i++)
		{
			char* tempNameDisplay = Leaderboard[i].name.data();
			DrawText(tempNameDisplay, 50, 140 + (i * 40), 40, YELLOW);
			DrawText(TextFormat("%i", Leaderboard[i].score), 350, 140 + (i * 40), 40, YELLOW);
		}
	}
}

void Game::SpawnAliens()
{
	for (int row = 0; row < formationHeight; row++) 
	{
		for (int col = 0; col < formationWidth; col++) 
		{
			aliens.emplace_back(resources, Vector2{ formationX + 450 + (col * alienSpacing) , formationY + (row * alienSpacing) });
		}
	}

}

bool Game::CheckNewHighScore()
{
	if (score > Leaderboard[4].score)
	{
		return true;
	}

	return false;
}

void Game::InsertNewHighScore(std::string name)
{
	HighscoreEntry newData;
	newData.name = name;
	newData.score = score;

	for (int i = 0; i < Leaderboard.size(); i++)
	{
		if (newData.score > Leaderboard[i].score)
		{

			Leaderboard.insert(Leaderboard.begin() + i, newData);

			Leaderboard.pop_back();

			i = Leaderboard.size();

		}
	}
}

void Game::LoadLeaderboard()
{
	// CLEAR LEADERBOARD

	// OPEN FILE

	// READ DATA

	// WRITE DATA ONTO LEADERBOARD

	//CLOSE FILE
}

void Game::SaveLeaderboard()
{
	// SAVE LEADERBOARD AS ARRAY

	// OPEN FILE
	std::fstream file;

	file.open("Leaderboard");

	if (!file)
	{
		std::cout << "file not found \n";

	}
	else
	{
		std::cout << "file found \n";
	}
	// CLEAR FILE

	// WRITE ARRAY DATA INTO FILE

	// CLOSE FILE
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