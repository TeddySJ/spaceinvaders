#pragma once
#include "GameState.h"
#include "Gameplay.h"


class StartScreen final : public GameState
{
public:
	void Render(const SpaceInvadersResourceManager& resources) const override;
	void HandleInput() override;
};

class TransitionToStartScreen final : public StateChangeTransition
{
public:
	std::unique_ptr<GameState> ConstructState() const override;
};
