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
#include "clsGlobal.h"



using namespace sf;
using namespace std;




class Enemy
{


private:

	//private variables
	sf::RectangleShape shape;
	RenderTarget* Target;
	Vector2f SpawnPosition;
	Vector2f TargetPosition;
	float MovementSpeed;
	



	//private functions
	void InitShape();

	void InitVariables();

	void UpdatePosition(Vector2f TargetPos);



public:

	Enemy(Vector2f TargetPosition, RenderTarget* RendTarget);

	Enemy();

	virtual ~Enemy();

	bool IsOutofTargetBound(RenderTarget* RendTarget);

	Vector2f GetPosition();
	Vector2f GetSize();
	sf::FloatRect GetEnemyBound();
	void IncreaseSpeed(float IncreaseBy);


	void Update(Vector2f TargetPos);
	void Render(sf::RenderTarget* Target);

	void GetSpawnPosition();




};

