#pragma once
#include "ItemEffect.h"
//Nikola Savic, 20.12.2024.

//Sword effect, makes player able to kill the enemy
class Sword : public ItemEffect
{
public:
	Sword() :ItemEffect() { name = "Sword"; }
	void gotMessage() override;
	void currentMessage() override;
	void lostMessage() override;
};

