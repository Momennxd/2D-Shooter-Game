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



using namespace sf;
using namespace std;


class Bullet
{
private:


	float Speed;
	Vector2f EnemyPosition;
	Vector2f BulletMovement;
	CircleShape shape;
	RenderTarget* Target;


	void InitShape();

	void UpdatePosition();

  


public:

	Bullet(float Speed, Vector2f StartingPosition, Vector2f EnemyPosition, RenderTarget* Target);

	Bullet();

	virtual ~Bullet();

	bool IsEnemyBulletCollision(sf::FloatRect enemyBounds);

	void SetEnemyPosition(Vector2f EnemyPosition);
	
	void SetStartingPosition(Vector2f StartuingPosition);

	Vector2f GetEnemyPosition();

	Vector2f GetStartingPosition();
	
	void CalcBulletMovement();



	bool IsOutOfTargetBound();

	void Update();

	void Render();




};




