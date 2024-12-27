#pragma once
#include "SpaceInvaderResourceManager.h"
#include "SpaceInvadersDefinitions.h"
#include <memory>
#include <optional>

class IRenderable
{
public:
	virtual ~IRenderable() = default;
	virtual void Render(const SpaceInvadersResourceManager& resources) = 0;
};

class IUpdateable
{
public:
	virtual ~IUpdateable() = default;
	virtual void Update() = 0;
};

class ICanHandleInput
{
public:
	virtual ~ICanHandleInput() = default;
	virtual void HandleInput() = 0;
};

class GameState : public IRenderable, public IUpdateable, public ICanHandleInput
{
public:

	GameState(State AsEnum);
	~GameState() override = default;

	State StateAsEnum; // TODO: Refactor this away when no longer needed

	void Render(const SpaceInvadersResourceManager& resources) override;
	void HandleInput() override;
	void Update() override;

	std::optional<std::unique_ptr<GameState>> next_state;
	void QueueStateChange(std::unique_ptr<GameState> new_state);
	bool StateShouldChange();
};

class StartScreen : public GameState
{
public:
	StartScreen();

	void Render(const SpaceInvadersResourceManager& resources) override;
	void HandleInput() override;
};

class Gameplay : public GameState
{
public:
	Gameplay();

	void Render(const SpaceInvadersResourceManager& resources) override;
	void HandleInput() override;
	void Update() override;
};

class PostGame : public GameState
{
public:
	PostGame();

	void Render(const SpaceInvadersResourceManager& resources) override;
	void HandleInput() override;
};