#include "GameState.h"
#include "Gameplay.h"
#include "PostGame.h"


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

bool GameState::StateShouldChange()
{
	return next_state.has_value();
}

const StateChangeTransition& GameState::GetStateTransition() const
{
	if (!next_state.has_value())
	{
		throw std::exception(); // TODO: Improve exception
	}

	return *next_state.value();
}

