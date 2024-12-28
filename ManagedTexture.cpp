#include "ManagedTexture.h"
#include "CustomExceptions.h"

ManagedTexture2D::ManagedTexture2D(std::string_view path)
{
	texture = LoadTexture(path.data());
	if (texture.id <= 0)
	{
		throw RaylibTextureCreationError(path);
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