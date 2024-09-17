#include "Enemy.h"

void Enemy::InitShape()
{
	this->shape.setFillColor(Color::Cyan);
	this->shape.setSize(Vector2f(30.f, 30.f));
	this->shape.setPosition(this->SpawnPosition);

}

void Enemy::InitVariables()
{
	this->Target = nullptr;
	this->TargetPosition = Vector2f(0,0);
	this->MovementSpeed = 3.f;
}

void Enemy::GetSpawnPosition()
{
	/*this variable stores a random number that represents the spawn side 1-right 2-down 3-left 4-up*/
	short SpawnSide = clsGlobal::GetRandomNumber(1, 4);

	switch (SpawnSide)
	{
	case 1 :
	{
		SpawnPosition = Vector2f(this->Target->getSize().x - this->shape.getSize().x, clsGlobal::GetRandomNumber(0, this->Target->getSize().y));
		break;
	}
	case 2:
	{
		SpawnPosition = Vector2f(clsGlobal::GetRandomNumber(0, this->Target->getSize().x), this->Target->getSize().y - this->shape.getSize().y);
		break;
	}
	case 3:
	{
		SpawnPosition = Vector2f(0, clsGlobal::GetRandomNumber(0, this->Target->getSize().y));
		break;
	}
	case 4:
	{
		SpawnPosition = Vector2f(clsGlobal::GetRandomNumber(0, this->Target->getSize().x), 0);
		break;
	}


	default:
		break;
	}


	this->shape.setPosition(this->SpawnPosition);

}

void Enemy::UpdatePosition(Vector2f TargetPos)
{
	sf::Vector2f slope = sf::Vector2f(TargetPos.x - this->shape.getPosition().x,
		TargetPos.y - this->shape.getPosition().y);
	//fix this fucking bug where the bullets destination should be tha edge of the window


	float magnitude = std::sqrt(slope.x * slope.x + slope.y * slope.y);


	sf::Vector2f normalizedSlope = sf::Vector2f(slope.x / magnitude, slope.y / magnitude);

	this->shape.move(Vector2f(normalizedSlope.x * this->MovementSpeed, normalizedSlope.y * this->MovementSpeed));
}

Enemy::Enemy(Vector2f TargetPosition, RenderTarget* Target)
{
	this->InitVariables();
	this->InitShape();

	this->TargetPosition = TargetPosition;
	this->Target = Target;
	//GetSpawnPosition();
}

Enemy::Enemy()
{
	
}

Enemy::~Enemy()
{
}

bool Enemy::IsOutofTargetBound(RenderTarget* RendTarget)
{
	if (shape.getPosition().x + shape.getSize().x > RendTarget->getSize().x ||
		shape.getPosition().x < 0)
	{
		return true;
	}
	else if (shape.getPosition().y + shape.getSize().y > RendTarget->getSize().y ||
		shape.getPosition().y < 0)
	{
		return true;
	}

	return false;
}

Vector2f Enemy::GetPosition()
{
	return this->shape.getPosition();
}

Vector2f Enemy::GetSize()
{
	return this->shape.getSize();
}

sf::FloatRect Enemy::GetEnemyBound()
{
	return this->shape.getGlobalBounds();
}

void Enemy::IncreaseSpeed(float IncreaseBy)
{
	this->MovementSpeed += IncreaseBy;
}



void Enemy::Update(Vector2f TargetPos)
{
	this->UpdatePosition(TargetPos);
}

void Enemy::Render(sf::RenderTarget* Target)
{
	Target->draw(this->shape);
}
