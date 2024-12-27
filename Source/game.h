#pragma once
#include "raylib.h"
#include "WindowHandle.h"
#include "AudioDeviceHandle.h"
#include "SpaceInvaderResourceManager.h"
#include "Highscore.h"
#include "Player.h"
#include "Projectile.h"
#include "Wall.h"
#include "Alien.h"
#include "Background.h"
#include "SpaceInvadersDefinitions.h"
#include <vector>
#include <string>
#include <GameState.h>
#include <Gameplay.h>
#include <PostGame.h>
#include <memory>

struct Game
{
	static constexpr int screenWidth = 1920;
	static constexpr int screenHeight = 1080;

	RaylibWindowHandle window_handle{screenWidth, screenHeight, "SPACE INVADERS"};
	RaylibAudioDeviceHandle audio_handle{};
	SpaceInvadersResourceManager resources{};

	Game();

	void Run();

	void Update();
	void HandleInput();
	void Render();

	void ChangeState(std::unique_ptr<GameState> new_state);
	std::unique_ptr<GameState> current_state;
};