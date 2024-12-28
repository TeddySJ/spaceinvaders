#pragma once
#include "SpaceInvaderResourceManager.h"
#include "SpaceInvadersDefinitions.h"
#include <memory>
#include <optional>

class IRenderable
{
public:
	virtual ~IRenderable() = default;
	virtual void Render(SpaceInvadersResourceManager& resources) = 0;
};

class IUpdateable
{
public:
	virtual ~IUpdateable() = default;
	virtual void Update(SpaceInvadersResourceManager& resources) = 0;
};

class ICanHandleInput
{
public:
	virtual ~ICanHandleInput() = default;
	virtual void HandleInput() = 0;
};

class StateChangeTransition;

class GameState : public IRenderable, public IUpdateable, public ICanHandleInput
{
public:

	~GameState() override = default;

	void Render(SpaceInvadersResourceManager& resources) override;
	void HandleInput() override;
	void Update(SpaceInvadersResourceManager& resources) override;

	bool StateShouldChange();
	const StateChangeTransition& GetStateTransition() const;

protected:
	void QueueStateChange(std::unique_ptr<StateChangeTransition> new_state);

private:
	std::optional<std::unique_ptr<StateChangeTransition>> next_state;
};

class StateChangeTransition
{
public:
	virtual ~StateChangeTransition() = default;

	virtual std::unique_ptr<GameState> ConstructState(SpaceInvadersResourceManager& resources) const = 0;
};