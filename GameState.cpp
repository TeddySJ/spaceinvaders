#include "GameState.h"
#include "Gameplay.h"
#include "PostGame.h"
#include <stdexcept>

void GameState::HandleInput()
{
	// Default empty virtual implementation - a state does not necessarily require input handling
}

void GameState::Update()
{
	// Default empty virtual implementation - a state does not necessarily require running an Update
}

void GameState::QueueStateChange(std::unique_ptr<StateChangeTransition> new_state) noexcept
{
	next_state = std::move(new_state);
}

bool GameState::StateShouldChange() const noexcept
{
	return next_state.has_value();
}

const StateChangeTransition& GameState::GetStateTransition() const
{
	return *next_state.value();
}

