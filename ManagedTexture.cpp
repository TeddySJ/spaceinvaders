#include "ManagedTexture.h"
#include "CustomExceptions.h"

ManagedTexture2D::ManagedTexture2D(std::string_view path)
{
	texture = LoadTexture(path.data());
	if (!IsValid())
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

bool ManagedTexture2D::IsValid() const noexcept
{
	return texture.id > 0;
}

ManagedTexture2D::ManagedTexture2D(ManagedTexture2D&& other) noexcept {
    texture = other.texture;
    other.texture.id = 0;
}