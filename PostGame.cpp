#include "PostGame.h"
#include "StartScreen.h"

PostGame::PostGame(int score)
	: highscore_manager{ score }
{
}

void PostGame::Render(SpaceInvadersResourceManager& resources)
{
	if (highscore_manager.entering_new_highscore)
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
	if (highscore_manager.entering_new_highscore)
	{
		highscore_manager.NewHighscoreInput();
	}
	else if (IsKeyReleased(KEY_ENTER))
	{
		Continue();
	}
}

void PostGame::Continue()
{
	QueueStateChange(std::make_unique<TransitionToStartScreen>());
}

std::unique_ptr<GameState> TransitionToPostGame::ConstructState(SpaceInvadersResourceManager& resources) const
{
	return std::make_unique<PostGame>(score);
}

TransitionToPostGame::TransitionToPostGame(int score)
	: score{ score }
{
}
