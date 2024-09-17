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
#include "Bullet.h"




using namespace sf;
using namespace std;

class Player
{

private:

	//private variables
	RectangleShape shape;

	int MovementSpeed;


	




	//private functions
	void InitShape();

	void InitVariables();

	void UpdateInput(sf::RenderTarget* Target);

	Vector2i TargetCollision(sf::RenderTarget* Target);

	 


public:


	Player(float x, float y);

	Player();
	
	virtual ~Player();

	

	bool IsCollision(FloatRect bound);
	

	void Update(sf::RenderTarget* Target);
	void Render(sf::RenderTarget* Target);

	Vector2f GetPlayerPosition();
	

	

};

