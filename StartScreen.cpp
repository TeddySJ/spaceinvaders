#include "StartScreen.h"

void StartScreen::Render(SpaceInvadersResourceManager& resources)
{
	DrawText("SPACE INVADERS", 200, 100, 160, YELLOW);
	DrawText("PRESS SPACE TO BEGIN", 200, 350, 40, YELLOW);
}

void StartScreen::HandleInput()
{
	if (IsKeyReleased(KEY_SPACE))
	{
		next_state = std::make_unique<TransitionToGameplay>();
	}
}

std::unique_ptr<GameState> TransitionToStartScreen::ConstructState(SpaceInvadersResourceManager& resources)
{
	return std::make_unique<StartScreen>();
}