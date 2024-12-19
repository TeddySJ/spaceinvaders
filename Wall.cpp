#include "Wall.h"

Wall::Wall(Vector2 position)
	: position{ position }
{
}

void Wall::Render(Texture2D texture)
{
	DrawTexturePro(texture,
		{
			0,
			0,
			704,
			704,
		},
		{
			position.x,
			position.y,
			200,
			200,
		}, { 100 , 100 },
		0,
		WHITE);


	DrawText(TextFormat("%i", health), position.x - 21, position.y + 10, 40, RED);

}

void Wall::Update()
{

	// set walls as inactive when out of health
	if (health < 1)
	{
		active = false;
	}


}

Rectangle Wall::GetCollisionRect() const
{
	return { position.x - collider_size.x / 2, position.y - collider_size.y / 2, collider_size.x, collider_size.y };
}

void Wall::OnCollision()
{
	health--;
}