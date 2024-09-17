#include "Game.h"


//constructor
Game::Game()
{
	this->InitVariables();
	this->InitText();
	this->InitWindow();
	this->InitPlayer();
	this->InitBullet(10, this->player.GetPlayerPosition(), this->MousePosView);
	this->InitEnemey(this->player.GetPlayerPosition(), this->Window);
}

//Destructor
Game::~Game()
{
	delete this->Window;
	

}



//Private Functions
void Game::InitVariables()
{
	this->Window = nullptr;
	this->EndGame = false;
	this->BulletSpawnTimer = 0.f;
	this->BulletSpawnTimerMax = 10.f;

	this->EnemeySpawnTimer = 0.f;
	this->EnemeySpawnTimerMax = 30.f;

	this->Points = 0;
	this->MaxPoints = 0;

	this->EnemiesSpeedIncrementByTime = 0.05f;


}

void Game::InitWindow()
{
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->Window = new sf::RenderWindow(this->videoMode, "Game 2", sf::Style::Titlebar | sf::Style::Close);
	this->Window->setFramerateLimit(60);
}

void Game::InitBullet(float Speed, Vector2f StartingPosition, Vector2f EnemyPosition)
{
	this->bullet = Bullet(Speed, StartingPosition, EnemyPosition, this->Window);
}

void Game::InitEnemey(Vector2f TargetPosition, RenderTarget* RendTarget)
{
	this->enemy = Enemy(TargetPosition, RendTarget);
}

void Game::InitPlayer()
{
	this->player = Player(this->videoMode.width / 2, this->videoMode.height / 2);

}

void Game::InitText()
{
	this->font.loadFromFile("Fonts/college.ttf");
	this->uiText.setFont(this->font);
	this->uiText.setFillColor(sf::Color::White);
	this->uiText.setCharacterSize(20);
	this->uiText.setString("None");
}

void Game::RenderText()
{
	this->Window->draw(this->uiText);
}

void Game::UpdateText()
{
	std::stringstream ss;
	ss << "Points : " << this->Points;
	this->uiText.setString(ss.str());

	if (this->Points > this->MaxPoints)
	{
		this->MaxPoints = this->Points;
	}
}


int Game::GetRandomNumber(int from, int to)
{
	// Generate a random number within the specified range
	int randomNum = from + (std::rand() % (to - from + 1));
	return randomNum;
}

const bool Game::Running() const
{
	return this->Window->isOpen();
}

void Game::pollEvents()
{

	

	while (this->Window->pollEvent(this->ev))
	{
		switch (ev.type)
		{
		case sf::Event::Closed:
		{
			this->Window->close();
			break;
		}
		case sf::Event::KeyPressed:
		{
			if (ev.key.code == sf::Keyboard::Escape)
			{
				this->Window->close();
				break;
			}
		
		}
		

		default:
			break;
		}
	}
}

void Game::UpdateMousePosition()
{
	this->MousePosWindow = sf::Mouse::getPosition(*this->Window);
	this->MousePosView = this->Window->mapPixelToCoords(this->MousePosWindow);
}

void Game::SpawnBullet()
{
	this->bullet.SetStartingPosition(Vector2f(this->player.GetPlayerPosition()));
	this->bullet.SetEnemyPosition(Vector2f(this->MousePosView));

}

void Game::UpdateBullets()
{
	if (Mouse::isButtonPressed(Mouse::Left) && this->BulletSpawnTimer >= this->BulletSpawnTimerMax)
	{
		SpawnBullet();
		//calculating the bullet movement only once on click to make the bullet go out of the window bound
		this->bullet.CalcBulletMovement();
		this->bullet.Update();
		this->Bullets.push_back(this->bullet);
		BulletSpawnTimer = 0.f;
	}
	else
	{
		BulletSpawnTimer += 1.f;
	}



	//this loop updats all the bullets
	bool Delete = false;
	for (int i = 0; i < this->Bullets.size(); i++)
	{

		//this inner loop is for deleting the enemies who have collision with the current bullet
		Delete = false;
		for (int j = 0; j < this->Enemies.size(); j++)
		{
			if (this->Bullets[i].IsEnemyBulletCollision(this->Enemies[j].GetEnemyBound()))
			{
				this->Points += 10;
				Delete = true;
				this->Enemies.erase(this->Enemies.begin() + j);
			}
		}
		if (this->Bullets[i].IsOutOfTargetBound())
		{
			Delete = true;
		}
		else
		{
			this->Bullets[i].Update();
		}

		if (Delete)
			this->Bullets.erase(this->Bullets.begin() + i);

	}

}

void Game::RenderBullets()
{
	//Draw the Bullets

	for (auto& e : this->Bullets)
	{
		e.Render();
	}
}



void Game::SpawnEnemy()
{
	this->enemy.GetSpawnPosition();
}

void Game::UpdateEnemies()
{
	if (this->EnemeySpawnTimer >= this->EnemeySpawnTimerMax)
	{
		SpawnEnemy();
		this->enemy.IncreaseSpeed(this->EnemiesSpeedIncrementByTime);
		this->enemy.Update(this->player.GetPlayerPosition());
		this->Enemies.push_back(this->enemy);
		EnemeySpawnTimer = 0.f;
	}
	else
	{
		EnemeySpawnTimer += 1.f;
	}


	//this loop updats all the Enemies
	bool Delete = false;
	for (int i = 0; i < this->Enemies.size(); i++)
	{
		Delete = false;
		if (this->player.IsCollision(Enemies[i].GetEnemyBound()))
		{
			if (this->Points <=  0)
			{
				//end the game
				cout << "Max Score : " << this->MaxPoints << endl;
				this->Window->close();
			}


			Delete = true;
			this->Points -= 20;
		}
		else if (this->Enemies[i].IsOutofTargetBound(this->Window))
		{
			Delete = true;
		}
		else
		{
			this->Enemies[i].Update(this->player.GetPlayerPosition());
		}

		if (Delete)
			this->Enemies.erase(this->Enemies.begin() + i);

	}

}

void Game::RenderEnemies()
{
	for (auto& e : this->Enemies)
	{
		e.Render(this->Window);
	}
}





//Functions
void Game::Update()
{
	this->pollEvents();
	this->UpdateMousePosition();
	this->player.Update(this->Window);
	this->UpdateBullets();
	this->UpdateEnemies();
	this->UpdateText();
}

void Game::Render()
{
	this->Window->clear();

	this->player.Render(this->Window);
	this->RenderBullets();
	this->RenderEnemies();
	this->RenderText();
	this->Window->display();
}


