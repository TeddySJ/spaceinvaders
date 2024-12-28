#include "GameState.h"
#include "Gameplay.h"
#include "PostGame.h"
#include <stdexcept>

void GameState::Render(const SpaceInvadersResourceManager&) const
{
}

void GameState::HandleInput()
{
}

void GameState::Update()
{
}

void GameState::QueueStateChange(std::unique_ptr<StateChangeTransition> new_state)
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

