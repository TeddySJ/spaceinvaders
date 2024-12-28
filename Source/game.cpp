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
		ChangeState(std::move(current_state->next_state.value()->ConstructState(resources))); // TODO: Refactor to follow law of demeter
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

void Game::ChangeState(std::unique_ptr<GameState> new_state)
{
	current_state = std::move(new_state);
}
