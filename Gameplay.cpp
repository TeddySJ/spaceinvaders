#include "Gameplay.h"

Gameplay::Gameplay(SpaceInvadersResourceManager& resources)
	: GameState{ State::GAMEPLAY }, player{ resources }
{
	float window_width = (float)GetScreenWidth();
	float window_height = (float)GetScreenHeight();
	int wallCount = 5;
	float wall_distance = window_width / (wallCount + 1);

	for (int i = 0; i < wallCount; i++)
	{
		walls.emplace_back(resources, Vector2{ wall_distance * (i + 1) , window_height - 250 });
	}

	//creating aliens
	//SpawnAliens();

	//reset score
	score = 0;
}

void Gameplay::Render(const SpaceInvadersResourceManager& resources)
{
}

void Gameplay::HandleInput()
{

}

void Gameplay::Update()
{
}
