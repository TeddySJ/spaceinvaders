#pragma once
#include "GameState.h"

class PostGame : public GameState
{
public:
	PostGame();

	void Render(SpaceInvadersResourceManager& resources) override;
	void HandleInput() override;
};