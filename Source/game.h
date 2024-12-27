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

	// Score
	int score;

	//Aliens shooting
	float shootTimer = 0;

	void Run();

	void Update();
	void UpdateGameplay();
	void HandleInput();
	void HandleInput_EndScreen();

	void Render();
	void Render_StartScreen();
	void Render_Gameplay();
	void Render_EndScreen();

	void ChangeState(std::unique_ptr<GameState> new_state);
	std::unique_ptr<GameState> current_state;


};