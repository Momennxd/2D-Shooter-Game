#include "Player.h"






void Player::InitShape()
{
	this->shape.setFillColor(Color::Green);
	this->shape.setSize(Vector2f(50.f, 50.f));
}

void Player::InitVariables()
{
	this->MovementSpeed = 10.f;
}

Player::Player(float x, float y)
{
	this->InitVariables();
	this->InitShape();
	this->shape.setPosition(x, y);	
}

Player::Player()
{
	
}

Player::~Player()
{



	

}


bool Player::IsCollision(FloatRect bound)
{
	return this->shape.getGlobalBounds().intersects(bound);
}

void Player::Update(sf::RenderTarget* Target)
{
	this->UpdateInput(Target);
}

void Player::UpdateInput(sf::RenderTarget* Target)
{

	//movment input
	if (Keyboard::isKeyPressed(Keyboard::A) && this->TargetCollision(Target).x != 3)
	{
		//Left
		this->shape.move(-this->MovementSpeed, 0.f);
	}
    else if (Keyboard::isKeyPressed(Keyboard::D) && this->TargetCollision(Target).x != 1)
	{
		//right
		this->shape.move(this->MovementSpeed, 0.f);
	}

    if (Keyboard::isKeyPressed(Keyboard::W) && this->TargetCollision(Target).y != 4)
	{
		//up
		this->shape.move(0.f, -this->MovementSpeed);
	}
    else if (Keyboard::isKeyPressed(Keyboard::S) && this->TargetCollision(Target).y != 2)
	{
		//down
		this->shape.move(0.f, this->MovementSpeed);
	}

}

/*the returns represent the side that the palyer hit in the target
1 = right side
2 = down side
3 = left side
4 = upper side*/
Vector2i Player::TargetCollision(sf::RenderTarget* Target)
{


	//the vecSidesCollision is used for double collision with two sides of the window right and left is x
	//  and up and down is y
	
	Vector2i vecSidesCollision = Vector2i(0, 0);

	if (this->shape.getPosition().x + this->shape.getSize().x >= Target->getSize().x)
	{
		//setting up the col with the right side of the window
		vecSidesCollision.x = 1;
	}
    if (this->shape.getPosition().x <= 0)
	{
		//setting up the col with the left side of the window
		vecSidesCollision.x = 3;
	}
    if (this->shape.getPosition().y <= 0)
	{
		//setting up the col with the upper side of the window
		vecSidesCollision.y = 4;
	}
    if (this->shape.getPosition().y + this->shape.getSize().y >= Target->getSize().y)
	{
		//setting up the col with the down side of the window
		vecSidesCollision.y = 2;
	}
	
	return vecSidesCollision;

}

void Player::Render(sf::RenderTarget* Target)
{
	Target->draw(this->shape);
}

Vector2f Player::GetPlayerPosition()
{
	return this->shape.getPosition();
}
