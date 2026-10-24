#pragma once
#include "ItemEffect.h"
//Nikola Savic, 20.12.2024.

//Fog of war effect, makes only 3x3 area around player visible
class FogOfWarEffect :public ItemEffect
{
public:
	FogOfWarEffect() :ItemEffect() { name = "Fog of War"; }
	void gotMessage() override;
	void currentMessage() override;
	void lostMessage() override;
};

