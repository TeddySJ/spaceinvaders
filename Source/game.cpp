#include "game.h"
#include "StartScreen.h"
#include <iostream>
#include <vector>
#include <chrono>
#include <thread>
#include <fstream>
#include <ranges>

Game::Game()
	: current_state{ std::make_unique<StartScreen>() }
{
	window_handle.SetTargetFPS(60);

	resources.LoadTexture("./Assets/Alien.png");
	resources.LoadTexture("./Assets/ship_spritesheet.png");
	resources.LoadTexture("./Assets/Barrier.png");
	resources.LoadTexture("./Assets/Laser.png");
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
	if (current_state->StateShouldChange())
	{
		ChangeState(current_state->GetStateTransition());
	}
}

void Game::HandleInput()
{
	current_state->HandleInput();
}

void Game::Render() const
{
	BeginDrawing();
	ClearBackground(BLACK);

	current_state->Render(resources);

	EndDrawing();
}

void Game::ChangeState(const StateChangeTransition& new_state)
{
	current_state = new_state.ConstructState();
}
