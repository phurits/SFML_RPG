#include "stdafx.h"
#include "Slime.h"



//Initializer functions
void Slime::initVariables()
{

}


void Slime::initAnimations()
{
	// "NAME",F speed,Xstart,Ystart,posFX,posFY,Width,Height
	this->animationComponent->addAnimation("IDLE", 10.f, 0, 0 * 27, 2, 0, 36, 27);
	this->animationComponent->addAnimation("WALK_LEFT", 10.f, 0, 1 * 27, 2, 1, 36, 27);
	this->animationComponent->addAnimation("WALK_RIGHT", 10.f, 0, 2 * 27, 2, 2, 36, 27);
	this->animationComponent->addAnimation("WALK_UP", 10.f, 0, 3 * 27, 2, 3, 36, 27);
	this->animationComponent->addAnimation("WALK_DOWN", 10.f, 0, 0 * 27, 2, 0, 36, 27);


}

Slime::Slime(float x, float y, sf::Texture& texture_sheet)
	:Enemy()
{
	this->initVariables();

	this->createHitboxComponent(this->sprite, 0.f, 0.f, 36.f, 27.f);
	this->createMovementComponent(100.f, 1600.f, 1000.f);
	this->createAnimationComponent(texture_sheet);

	this->setPosition(x, y);
	this->initAnimations();

}

Slime::~Slime()
{
}

void Slime::updateAnimation(const float& dt)
{
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

void Slime::update(const float& dt, sf::Vector2f& mouse_pos_view)
{
	this->movementComponent->update(dt);

	//this->updateAttack();

	this->updateAnimation(dt);

	this->hitboxComponent->update();
}

void Slime::render(sf::RenderTarget& target, const bool show_hitbox)
{
	target.draw(this->sprite);

	if (show_hitbox)
		this->hitboxComponent->render(target);
}
