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

	this->createHitboxComponent(this->sprite, 30.f, 15.f,66.f, 90.f);
	this->createMovementComponent(300.f, 1600.f, 1000.f);
	this->createAnimationComponent(texture_sheet);
	this->createAttributeComponent(1);

										// "NAME",F speed,Xstart,Ystart,posFX,posFY,Width,Height
	this->animationComponent->addAnimation("IDLE", 11.f, 0, 4*126, 5, 4, 126, 126);
	this->animationComponent->addAnimation("WALK_LEFT", 7.f, 0, 1*126, 5, 1, 126, 126);
	this->animationComponent->addAnimation("WALK_RIGHT", 7.f, 0, 3 * 126, 5, 3, 126, 126);
	this->animationComponent->addAnimation("WALK_UP", 7.f, 0, 0 * 126, 5, 0, 126, 126);
	this->animationComponent->addAnimation("WALK_DOWN", 7.f, 0, 2 * 126, 5, 2, 126, 126);
	this->animationComponent->addAnimation("ATTACK", 5.f, 0, 650, 6, 5, 160, 176); //Error

	//Visual Weapon
	if(!this->weapon_texture.loadFromFile("Resources/Images/Sprites/Player/bow.png"))
		throw "ERROR::PLAYER::COULD_NOT_LOAD_WEAPON_TEXTURE";
	this->weapon_sprite.setTexture(this->weapon_texture);
	this->weapon_sprite.setOrigin(
		this->weapon_sprite.getGlobalBounds().width / 2.f,
		this->weapon_sprite.getGlobalBounds().height
	);
	this->weapon_sprite.setScale(0.3, 0.3);
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
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		this->attacking = true;
	}
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

	//Update visual weapon
	this->weapon_sprite.setPosition(this->getCenter().x, this->getPosition().y + this->getGlobalBounds().height);

	float dX = mouse_pos_view.x - this->weapon_sprite.getPosition().x;
	float dY = mouse_pos_view.y - this->weapon_sprite.getPosition().y;

	const float PI = 3.14159265;
	float deg = atan2(dY, dX) * 180 / PI;

	this->weapon_sprite.setRotation(deg + 90);
}

void Player::render(sf::RenderTarget& target, const bool show_hitbox)
{
	target.draw(this->sprite);
	target.draw(this->weapon_sprite);

	if(show_hitbox)
		this->hitboxComponent->render(target);
}
