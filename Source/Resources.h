#pragma once
#include "raylib.h"
#include "vector"
#include "RaylibHandle.h"

struct Resources 
{
	void Load();
	//void Unload();

	std::vector<Texture2D> shipTextures;
	Texture2D alienTexture;
	Texture2D barrierTexture;
	Texture2D laserTexture;

};