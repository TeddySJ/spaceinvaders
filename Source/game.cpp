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

	if (current_state->StateShouldChange())
	{
		ChangeState(current_state->GetStateTransition());
	}
}

void Game::HandleInput()
{
	current_state->HandleInput();
}

void Game::Render()
{
	BeginDrawing();
	ClearBackground(BLACK);

	current_state->Render(resources);

	EndDrawing();
}

void Game::ChangeState(const StateChangeTransition& new_state)
{
	current_state = new_state.ConstructState(resources);
}
