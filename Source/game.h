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
#include <memory>

struct Game
{
	static constexpr int screenWidth = 1920;
	static constexpr int screenHeight = 1080;

	RaylibWindowHandle window_handle{screenWidth, screenHeight, "SPACE INVADERS"};
	RaylibAudioDeviceHandle audio_handle{};
	SpaceInvadersResourceManager resources{};

	Game();

	// Gamestate
	State gameState = State::STARTSCREEN;

	// Score
	int score;

	//Aliens shooting
	float shootTimer = 0;

	void Start();
	void End();

	void Continue();
	void Run();

	void Update();
	void UpdateGameplay();
	void HandleInput();
	void HandleInput_EndScreen();
	void HandleCollisions();
	void PruneEntities();

	void Render();
	void Render_StartScreen();
	void Render_Gameplay();
	void Render_EndScreen();

	void SpawnAliens();

	bool CheckCollision(Vector2 circlePos, float circleRadius, Vector2 lineTop, Vector2 lineBottom);

	void ChangeState(std::unique_ptr<GameState> new_state);
	std::unique_ptr<GameState> current_state;

	HighscoreManager highscore_manager;

	Player player{resources};

	std::vector<Projectile> player_projectiles;
	std::vector<Projectile> enemy_projectiles;
	std::vector<Wall> walls;
	std::vector<Alien> aliens;
	Background background{ 600 };
};