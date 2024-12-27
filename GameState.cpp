#include "GameState.h"

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

void PreGame::Render(const SpaceInvadersResourceManager& resources)
{
	DrawText("SPACE INVADERS", 200, 100, 160, YELLOW);
	DrawText("PRESS SPACE TO BEGIN", 200, 350, 40, YELLOW);
}

void PreGame::HandleInput()
{
	if (IsKeyReleased(KEY_A))
	{
		next_state = std::make_unique<InGame>();
	}
}

void InGame::Render(const SpaceInvadersResourceManager& resources)
{
	DrawText("SPEEECH INVADERS", 100, 200, 160, YELLOW);
}

void InGame::HandleInput()
{
	
}

void InGame::Update()
{
}
