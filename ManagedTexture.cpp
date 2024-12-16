#include "ManagedTexture.h"
#include <stdexcept>

ManagedTexture2D::ManagedTexture2D(std::string_view path)
{
	texture = LoadTexture(path.data());
	if (texture.id <= 0)
	{
		throw std::exception(); // TODO: Improve exception
	}
}

ManagedTexture2D::~ManagedTexture2D()
{
	UnloadTexture(texture);
}

const Texture2D& ManagedTexture2D::GetTexture() const noexcept
{
	return texture;
}