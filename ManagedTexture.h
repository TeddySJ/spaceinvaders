#pragma once
#include "raylib.h"
#include <string_view>

class ManagedTexture2D final
{
	Texture2D texture;

public:

	ManagedTexture2D(const ManagedTexture2D&) = delete;
	ManagedTexture2D& operator=(const ManagedTexture2D&) = delete;

	ManagedTexture2D(ManagedTexture2D&&) = default;
	ManagedTexture2D& operator=(ManagedTexture2D&&) = default;

	explicit ManagedTexture2D(std::string_view path);
	~ManagedTexture2D();
	
	const Texture2D& GetTexture() const noexcept;
};