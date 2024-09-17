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
#include "enemy.h"



using namespace sf;
using namespace std;

/*
class that acts like the game engine
*/
class Game
{

private :

	//Variables
	sf::RenderWindow* Window;
	sf::VideoMode videoMode;
	sf::Event ev;
	bool EndGame;
	int Points;
	int MaxPoints;
	Text uiText;
	Font font;

	float EnemiesSpeedIncrementByTime;

	//entities
	Player player;
	Bullet bullet;
	Enemy enemy;

	float BulletSpawnTimer;
	float BulletSpawnTimerMax;

	float EnemeySpawnTimer;
	float EnemeySpawnTimerMax;

	vector<Bullet> Bullets;
	vector<Enemy> Enemies;


	//mouse position
	sf::Vector2i MousePosWindow;
	sf::Vector2f MousePosView;

	
	//private functions
	void InitVariables();
	void InitWindow();
	void InitBullet(float Speed, Vector2f StartingPosition, Vector2f EnemyPosition);
	void InitEnemey(Vector2f TargetPosition, RenderTarget* RendTarget);
	void InitPlayer();

	void InitText();
	void RenderText();
	void UpdateText();

	//Accessers
	int GetRandomNumber(int From, int To);



public:

	//Constructor and Destructure
	Game();
	virtual ~Game();



	//Accessers
	const bool Running() const;


	//Functions
	void pollEvents();
	void UpdateMousePosition();

	//bullets functions
	void SpawnBullet();
	void UpdateBullets();
	void RenderBullets();
	
	//enemies functions
	void SpawnEnemy();
	void UpdateEnemies();
	void RenderEnemies();


	void Update();
	void Render();


};

