#pragma once
#include "GameState.h"
#include "Highscore.h"

class PostGame : public GameState
{
public:
	explicit PostGame(size_t score) noexcept;

	void Render(const SpaceInvadersResourceManager& resources) const override;
	void HandleInput() override;

private:
	HighscoreManager highscore_manager;
	void GoToStartScreen();

};

class TransitionToPostGame : public StateChangeTransition
{
public:
	explicit TransitionToPostGame(size_t score) noexcept;

	std::unique_ptr<GameState> ConstructState() const override;
private:
	size_t score;

};
