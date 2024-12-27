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
	current_state->Update(resources);

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
	
}

void Game::HandleInput()
{
	current_state->HandleInput();

	if (current_state->StateAsEnum == State::GAMEPLAY)
	{
		
	}
	else if (current_state->StateAsEnum == State::STARTSCREEN)
	{
		
	}
	else if (current_state->StateAsEnum == State::ENDSCREEN)
	{
		//HandleInput_EndScreen();
	}
}

void Game::HandleInput_EndScreen()
{
	
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
		//Render_Gameplay();
	}
	else if (current_state->StateAsEnum == State::ENDSCREEN)
	{
		//Render_EndScreen();
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
	
}

void Game::Render_EndScreen()
{
	
}

void Game::ChangeState(std::unique_ptr<GameState> new_state)
{
	current_state = std::move(new_state);
}
