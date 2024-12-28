#include "StartScreen.h"

void StartScreen::Render(const SpaceInvadersResourceManager&) const
{
	DrawText("SPACE INVADERS", 200, 100, 160, YELLOW);
	DrawText("PRESS SPACE TO BEGIN", 200, 350, 40, YELLOW);
}

void StartScreen::HandleInput()
{
	if (IsKeyReleased(KEY_SPACE))
	{
		QueueStateChange(std::make_unique<TransitionToGameplay>());
	}
}

std::unique_ptr<GameState> TransitionToStartScreen::ConstructState() const
{
	return std::make_unique<StartScreen>();
}
