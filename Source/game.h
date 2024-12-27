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

	// for later, make a file where you can adjust the number of walls (config file) 
	int wallCount = 5;

	//Aliens shooting
	float shootTimer = 0;

	//Aliens stuff? (idk cause liv wrote this)
	Rectangle rec = { 0, 0 ,0 ,0 }; 

	int formationWidth = 8;
	int formationHeight = 5;
	int alienSpacing = 80;
	float formationX = 100;
	float formationY = 50;

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

	void LoadLeaderboard();
	void SaveLeaderboard();

	Player player{resources};

	std::vector<Projectile> player_projectiles;
	std::vector<Projectile> enemy_projectiles;
	std::vector<Wall> walls;
	std::vector<Alien> aliens;

	Background background{ 600 };

	HighscoreManager highscore_manager;

	Vector2 playerPos;
	Vector2 alienPos; 
	Vector2 cornerPos;
	float offset;

	int framesCounter = 0;

};