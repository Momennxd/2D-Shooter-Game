#include "Bullet.h"




Bullet::Bullet(float speed, Vector2f StartingPosition, Vector2f EnemyPosition, RenderTarget* Target)
{
	this->InitShape();
	this->shape.setPosition(StartingPosition);
	this->EnemyPosition = EnemyPosition;
	this->Target = Target;
	this->Speed = speed;
}

Bullet::Bullet()
{

}

Bullet::~Bullet()
{
		
}

bool Bullet::IsEnemyBulletCollision(sf::FloatRect enemyBounds)
{
	sf::FloatRect bulletBounds = this->shape.getGlobalBounds();
	return bulletBounds.intersects(enemyBounds);
}

void Bullet::InitShape()
{
	this->shape.setFillColor(Color::Red);
	this->shape.setRadius(7.f);
}

void Bullet::UpdatePosition()
{
	this->shape.move(this->BulletMovement);
}

bool Bullet::IsOutOfTargetBound()
{
	if (this->shape.getPosition().x + (this->shape.getRadius() * 2) > Target->getSize().x ||
		this->shape.getPosition().x < 0)
	{
		return true;
	}
	else if (this->shape.getPosition().y + (this->shape.getRadius() * 2) > Target->getSize().y ||
		this->shape.getPosition().y < 0)
	{
		return true;
	}

	return false;
}

void Bullet::SetEnemyPosition(Vector2f EnemyPosition)
{
	this->EnemyPosition = EnemyPosition;
}

void Bullet::SetStartingPosition(Vector2f StartingPosition)
{
	this->shape.setPosition(StartingPosition);
}

Vector2f Bullet::GetEnemyPosition()
{
	return this->EnemyPosition;
}

Vector2f Bullet::GetStartingPosition()
{
	return this->shape.getPosition();
}

void Bullet::CalcBulletMovement()
{
	sf::Vector2f slope = sf::Vector2f(this->EnemyPosition.x - this->shape.getPosition().x,
		this->EnemyPosition.y - this->shape.getPosition().y);
	//fix this fucking bug where the bullets destination should be tha edge of the window


	float magnitude = std::sqrt(slope.x * slope.x + slope.y * slope.y);


	sf::Vector2f normalizedSlope = sf::Vector2f(slope.x / magnitude, slope.y / magnitude);

	this->BulletMovement = Vector2f(normalizedSlope.x * this->Speed, normalizedSlope.y * this->Speed);

}

void Bullet::Update()
{
	//CalcBulletMovement();
	this->UpdatePosition();
}

void Bullet::Render()
{
	Target->draw(this->shape);
}
