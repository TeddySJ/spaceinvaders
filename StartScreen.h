#pragma once
#include "GameState.h"
#include "Gameplay.h"


class StartScreen : public GameState
{
public:
	void Render(SpaceInvadersResourceManager& resources) override;
	void HandleInput() override;
};

class TransitionToStartScreen : public StateChangeTransition
{
public:
	std::unique_ptr<GameState> ConstructState(SpaceInvadersResourceManager& resources) const override;
};
