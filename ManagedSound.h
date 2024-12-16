#pragma once
#include "raylib.h"
#include <string_view>

class ManagedSound
{
	Sound sound;

public:

	ManagedSound(const ManagedSound&) = delete;
	ManagedSound& operator=(const ManagedSound&) = delete;

	ManagedSound(ManagedSound&&) = default;
	ManagedSound& operator=(ManagedSound&&) = default;

	const Sound& GetSound() const noexcept;

	explicit ManagedSound(std::string_view path);

	~ManagedSound();
};