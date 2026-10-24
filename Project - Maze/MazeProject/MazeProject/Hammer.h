#pragma once
#include "ItemEffect.h"
//Nikola Savic, 20.12.2024.

//Hammer effect, makes player able to destroy the wall
class Hammer :public ItemEffect
{
public:
	Hammer() :ItemEffect() { name = "Hammer"; }
	void gotMessage() override;
	void currentMessage() override;
	void lostMessage() override;
};