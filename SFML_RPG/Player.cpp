#include "stdafx.h"
#include "Player.h"
//Initializer functions
void Player::initVariables()
{
	this->attacking = false;
}

void Player::initComponents()
{
	
}

//Constructors / Destructors
Player::Player(float x,float y, sf::Texture& texture_sheet)
{
	this->initVariables();

	this->setPosition(x, y);

	this->createHitboxComponent(this->sprite, 20.f, 15.f,76.f, 90.f);
	this->createMovementComponent(350.f, 1500.f, 500.f);
	this->createAnimationComponent(texture_sheet);
	this->createAttributeComponent(1);

										// "NAME",F speed,Xstart,Ystart,posFX,posFY,Width,Height
	this->animationComponent->addAnimation("IDLE", 11.f, 0, 4*130, 5, 4, 126, 130);
	this->animationComponent->addAnimation("WALK_LEFT", 7.f, 0, 1*130, 5, 1, 126, 130);
	this->animationComponent->addAnimation("WALK_RIGHT", 7.f, 0, 3 * 130, 5, 3, 126, 130);
	this->animationComponent->addAnimation("WALK_UP", 7.f, 0, 0 * 130, 5, 0, 126, 130);
	this->animationComponent->addAnimation("WALK_DOWN", 7.f, 0, 2 * 130, 5, 2, 126, 130);
	this->animationComponent->addAnimation("ATTACK", 5.f, 0, 650, 6, 5, 160, 176); //Error

}

Player::~Player()
{

}

//Accessors

AttributeComponent* Player::getAttributeComponent()
{
	return this->attributeComponent;
}

//Functions

void Player::loseHP(const int hp)
{
	this->attributeComponent->hp -= hp;

	if (this->attributeComponent->hp < 0)
		this->attributeComponent->hp = 0;
}

void Player::gainHP(const int hp)
{
	this->attributeComponent->hp += hp;

	if (this->attributeComponent->hp > this->attributeComponent->hpMax)
		this->attributeComponent->hp = this->attributeComponent->hpMax;
}

void Player::loseEXP(const unsigned exp)
{
	this->attributeComponent->exp -= exp;

	if (this->attributeComponent->exp < 0)
		this->attributeComponent->exp = 0;
}

void Player::gainEXP(const unsigned exp)
{
	this->attributeComponent->gainExp(exp);
}

void Player::updateAttack()
{
	//if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	//{
	//	this->attacking = true;
	//}
}

void Player::updateAnimation(const float& dt)
{
	// Use when Sprite Sheet have attack or not need to use
	//if (this->attacking)
	//{
	//	//Set origin depending on direction
	//	if (this->sprite.getScale().x > 0.f) //Facing left
	//	{
	//		this->sprite.setOrigin(96.f, 0.f);
	//	}
	//	else//Facing right
	//	{
	//		this->sprite.setOrigin(258.f + 96.f, 0.f);
	//	}
	//	//Animate and check for animation end
	//	if (this->animationComponent->play("ATTACK", dt, true))
	//	{
	//		this->attacking = false;
	//		if (this->sprite.getScale().x > 0.f) //Facing left
	//		{
	//			this->sprite.setOrigin(0.f, 0.f);
	//		}
	//		else//Facing right
	//		{
	//			this->sprite.setOrigin(258.f, 0.f);
	//		}
	//	}
	//}

	if (this->attacking)
	{
		if (this->animationComponent->play("ATTACK", dt, true))
			this->attacking = false;
	}
	if (this->movementComponent->getState(IDLE))
	{
		this->animationComponent->play("IDLE", dt);
	}
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		//if (this->sprite.getScale().x < 0.f)
		//{
		//	this->sprite.setOrigin(0.f, 0.f);
		//	this->sprite.setScale(1.f, 1.f);
		//}
		this->animationComponent->play("WALK_LEFT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		//if (this->sprite.getScale().x > 0.f)
		//{
		//	this->sprite.setOrigin(125.f, 0.f);
		//	this->sprite.setScale(-1.f, 1.f);
		//}
		this->animationComponent->play("WALK_RIGHT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_UP))
		this->animationComponent->play("WALK_UP", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	else if (this->movementComponent->getState(MOVING_DOWN))
		this->animationComponent->play("WALK_DOWN", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());

}

void Player::update(const float& dt)
{
	this->movementComponent->update(dt);
	
	this->updateAttack();

	this->updateAnimation(dt);
	
	this->hitboxComponent->update();
}

void Player::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);

	this->hitboxComponent->render(target);
}
