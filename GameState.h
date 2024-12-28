#pragma once
#include "SpaceInvaderResourceManager.h"
#include "SpaceInvadersDefinitions.h"
#include <memory>
#include <optional>

class StateChangeTransition;

class GameState
{
public:
	virtual ~GameState() = default;

	virtual void Render(const SpaceInvadersResourceManager& resources) const;
	virtual void HandleInput();
	virtual void Update();

	bool StateShouldChange();
	const StateChangeTransition& GetStateTransition() const;

protected:
	GameState() = default;
	void QueueStateChange(std::unique_ptr<StateChangeTransition> new_state);

private:
	std::optional<std::unique_ptr<StateChangeTransition>> next_state;
};

class StateChangeTransition
{
public:
	virtual ~StateChangeTransition() = default;

	virtual std::unique_ptr<GameState> ConstructState() const = 0;
};