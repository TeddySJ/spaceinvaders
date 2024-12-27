#include "GameState.h"
#include "Gameplay.h"
#include "PostGame.h"

GameState::GameState(State AsEnum)
	: StateAsEnum{ AsEnum }
{
}

void GameState::Render(SpaceInvadersResourceManager&)
{
}

void GameState::HandleInput()
{
}

void GameState::Update(SpaceInvadersResourceManager&)
{
}

void GameState::QueueStateChange(std::unique_ptr<StateChangeTransition> new_state)
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

void StartScreen::Render(SpaceInvadersResourceManager& resources)
{
	DrawText("SPACE INVADERS", 200, 100, 160, YELLOW);
	DrawText("PRESS SPACE TO BEGIN", 200, 350, 40, YELLOW);
}

void StartScreen::HandleInput()
{
	if (IsKeyReleased(KEY_SPACE))
	{
		next_state = std::make_unique<TransitionToGameplay>();
	}
}

std::unique_ptr<GameState> TransitionToGameplay::ConstructState(SpaceInvadersResourceManager& resources)
{
	return std::make_unique<Gameplay>(resources);
}

TransitionToPostGame::TransitionToPostGame(int score)
	: score{ score }
{
}

std::unique_ptr<GameState> TransitionToPostGame::ConstructState(SpaceInvadersResourceManager& resources)
{
	return std::make_unique<PostGame>(score);
}

std::unique_ptr<GameState> TransitionToStartScreen::ConstructState(SpaceInvadersResourceManager& resources)
{
	return std::make_unique<StartScreen>();
}
