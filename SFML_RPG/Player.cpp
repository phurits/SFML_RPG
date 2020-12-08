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

void Player::initAnimations()
{
	// "NAME",F speed,Xstart,Ystart,posFX,posFY,Width,Height
	this->animationComponent->addAnimation("IDLE", 11.f, 0, 4 * 126, 5, 4, 126, 126);
	this->animationComponent->addAnimation("WALK_LEFT", 7.f, 0, 1 * 126, 5, 1, 126, 126);
	this->animationComponent->addAnimation("WALK_RIGHT", 7.f, 0, 3 * 126, 5, 3, 126, 126);
	this->animationComponent->addAnimation("WALK_UP", 7.f, 0, 0 * 126, 5, 0, 126, 126);
	this->animationComponent->addAnimation("WALK_DOWN", 7.f, 0, 2 * 126, 5, 2, 126, 126);
	//this->animationComponent->addAnimation("ATTACK", 5.f, 0, 650, 6, 5, 160, 176); //Error


}

//Constructors / Destructors
Player::Player(float x,float y, sf::Texture& texture_sheet)
{
	this->initVariables();

	this->createHitboxComponent(this->sprite, 30.f, 15.f,66.f, 90.f);
	this->createMovementComponent(300.f, 1600.f, 1000.f);
	this->createAnimationComponent(texture_sheet);
	this->createAttributeComponent(1);
	this->createSkillComponent();

	this->setPosition(x, y);
	this->initAnimations();

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
	this->attributeComponent->loseHP(hp);
}

void Player::gainHP(const int hp)
{
	this->attributeComponent->gainHP(hp);
}

void Player::loseEXP(const int exp)
{
	this->attributeComponent->loseEXP(exp);
}

void Player::gainEXP(const int exp)
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
	if (this->attacking)
	{

	}

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
		this->animationComponent->play("WALK_LEFT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		this->animationComponent->play("WALK_RIGHT", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_UP))
	{
		this->animationComponent->play("WALK_UP", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_DOWN))
	{
		this->animationComponent->play("WALK_DOWN", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
}

void Player::update(const float& dt, sf::Vector2f& mouse_pos_view)
{
	this->movementComponent->update(dt);
	
	this->updateAttack();

	this->updateAnimation(dt);
	
	this->hitboxComponent->update();

	//this->sword.update(mouse_pos_view,this->getCenter());
}

void Player::render(sf::RenderTarget& target, const bool show_hitbox)
{
	//this->sword.render(target);
	target.draw(this->sprite);

	if(show_hitbox)
		this->hitboxComponent->render(target);
}
