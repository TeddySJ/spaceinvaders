#pragma once
#include "GameState.h"
#include "Highscore.h"

class PostGame : public GameState
{
public:
	PostGame(int score);

	HighscoreManager highscore_manager;

	void Render(const SpaceInvadersResourceManager& resources) const override;
	void HandleInput() override;
	void Continue();

};

class TransitionToPostGame : public StateChangeTransition
{
public:
	TransitionToPostGame(int score);
	int score;

	std::unique_ptr<GameState> ConstructState() const override;
};
