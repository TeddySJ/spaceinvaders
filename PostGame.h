#pragma once
#include "GameState.h"
#include "Highscore.h"

class PostGame : public GameState
{
public:
	PostGame(int score);

	HighscoreManager highscore_manager;

	void Render(SpaceInvadersResourceManager& resources) override;
	void HandleInput() override;
	void Continue();

};