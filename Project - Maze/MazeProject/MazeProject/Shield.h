#pragma once
#include "ItemEffect.h"
//Nikola Savic, 20.12.2024.

//Shield effect, makes player invulnerable to enemy
class Shield :public ItemEffect
{
public:
	Shield() :ItemEffect() { name = "Shield"; }
	void gotMessage() override;
	void currentMessage() override;
	void lostMessage() override;
};

