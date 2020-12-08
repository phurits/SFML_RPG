#include "stdafx.h"
#include "Fairy.h"
//Initializer functions
void Fairy::initVariables()
{

}


void Fairy::initAnimations()
{
	// "NAME",F speed,Xstart,Ystart,posFX,posFY,Width,Height
	this->animationComponent->addAnimation("IDLE", 10.f, 0, 0 ,3, 0, 96, 40);
}

Fairy::Fairy(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();

	this->createHitboxComponent(this->sprite, 0.f, 0.f, 96.f,40.f);
	this->createMovementComponent(100.f, 1600.f, 1000.f);
	this->createAnimationComponent(texture_sheet);

	this->setPosition(x, y);
	this->initAnimations();

}

Fairy::~Fairy()
{
}

void Fairy::updateAnimation(const float& dt)
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

void Fairy::updateBulletLine(sf::Vector2f& mouse_pos_view)
{
	this->aimDir = mouse_pos_view - this->sprite.getPosition();
	this->aimDirNorm = this->aimDir / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));
	//std::cout << aimDirNorm.x << " " << aimDirNorm.y << std::endl;
}

void Fairy::update(const float& dt, sf::Vector2f& mouse_pos_view)
{
	this->movementComponent->update(dt);

	this->updateAnimation(dt);

	this->updateBulletLine(mouse_pos_view);

	this->hitboxComponent->update();
}

void Fairy::render(sf::RenderTarget& target, const bool show_hitbox)
{
	target.draw(this->sprite);

	if (show_hitbox)
		this->hitboxComponent->render(target);
}