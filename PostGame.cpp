#include "PostGame.h"
#include "StartScreen.h"

PostGame::PostGame(size_t score)
	: highscore_manager{ score }
{
}

void PostGame::Render(const RaylibResourceManager&) const
{
	if (highscore_manager.IsInNameEntry())
	{
		highscore_manager.RenderNameInput();
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

TransitionToPostGame::TransitionToPostGame(size_t score) noexcept
	: score{ score }
{
}
