#pragma once


#include <SFML/Graphics.hpp>
#include <SFML/window.hpp>
#include <random> // random is needed to generate random numbers for the dice.
#include <iostream>
#include <string>
#include <cstdlib>
#include <vector>
#include <sstream>
#include <ctime>
#include "player.h"
#include "Bullet.h"



class clsGlobal
{


public:


	static int GetRandomNumber(int from, int to)
	{
		// Generate a random number within the specified range
		int randomNum = from + (std::rand() % (to - from + 1));
		return randomNum;
	}

	static bool IsOutOfTargetBound(RectangleShape shape, RenderTarget *Target)
	{
		if (shape.getPosition().x + shape.getSize().x > Target->getSize().x ||
			shape.getPosition().x < 0)
		{
			return true;
		}
		else if (shape.getPosition().y + shape.getSize().y > Target->getSize().y ||
			shape.getPosition().y < 0)
		{
			return true;
		}

		return false;
	}



	

};

