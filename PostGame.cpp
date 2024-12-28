#include "PostGame.h"
#include "StartScreen.h"

PostGame::PostGame(int score) noexcept
	: highscore_manager{ score }
{
}

void PostGame::Render(const SpaceInvadersResourceManager&) const
{
	if (highscore_manager.IsInNameEntry())
	{
		highscore_manager.RenderNameEntry();
	}
	else
	{
		highscore_manager.RenderList();
	}
}

void PostGame::HandleInput()
{
	if (highscore_manager.IsInNameEntry())
	{
		highscore_manager.NewHighscoreInput();
	}
	else if (IsKeyReleased(KEY_ENTER))
	{
		GoToStartScreen();
	}
}

void PostGame::GoToStartScreen()
{
	QueueStateChange(std::make_unique<TransitionToStartScreen>());
}

std::unique_ptr<GameState> TransitionToPostGame::ConstructState() const
{
	return std::make_unique<PostGame>(score);
}

TransitionToPostGame::TransitionToPostGame(int score) noexcept
	: score{ score }
{
}
