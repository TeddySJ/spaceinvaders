#include "PostGame.h"

PostGame::PostGame(int score)
	: GameState{ State::ENDSCREEN }, highscore_manager{ score }
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
