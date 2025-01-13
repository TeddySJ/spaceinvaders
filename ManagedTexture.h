#pragma once
#include "raylib.h"
#include <string_view>

class ManagedTexture2D final
{
	Texture2D texture;

public:

	ManagedTexture2D(const ManagedTexture2D&) = delete;
	ManagedTexture2D& operator=(const ManagedTexture2D&) = delete;

	ManagedTexture2D(ManagedTexture2D&&) noexcept;
	ManagedTexture2D& operator=(ManagedTexture2D&&) = delete;

	explicit ManagedTexture2D(std::string_view path);
	~ManagedTexture2D();
	
	[[nodiscard]] const Texture2D& GetTexture() const noexcept;
	[[nodiscard]] bool IsValid() const noexcept;
};