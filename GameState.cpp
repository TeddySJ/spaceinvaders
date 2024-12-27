#include "GameState.h"

GameState::GameState(State AsEnum)
	: StateAsEnum{ AsEnum }
{
}

void GameState::Render(const SpaceInvadersResourceManager&)
{
}

void GameState::HandleInput()
{
}

void GameState::Update()
{
}

void GameState::QueueStateChange(std::unique_ptr<GameState> new_state)
{
	next_state = std::move(new_state);
}

bool GameState::StateShouldChange()
{
	return next_state.has_value();
}

StartScreen::StartScreen()
	: GameState{State::STARTSCREEN}
{
}

void StartScreen::Render(const SpaceInvadersResourceManager& resources)
{
	DrawText("SPACE INVADERS", 200, 100, 160, YELLOW);
	DrawText("PRESS SPACE TO BEGIN", 200, 350, 40, YELLOW);
}

void StartScreen::HandleInput()
{
	if (IsKeyReleased(KEY_SPACE))
	{
		next_state = std::make_unique<Gameplay>();
	}
}

Gameplay::Gameplay()
	: GameState{ State::GAMEPLAY }
{
}

void Gameplay::Render(const SpaceInvadersResourceManager& resources)
{
}

void Gameplay::HandleInput()
{
	
}

void Gameplay::Update()
{
}

PostGame::PostGame()
	: GameState{ State::ENDSCREEN }
{
}

void PostGame::Render(const SpaceInvadersResourceManager& resources)
{
}

void PostGame::HandleInput()
{
}
