#pragma once
#include "HitboxComponent.h"
class Bullet
{
private:

public:
	Bullet(float radius = 20.f);
	virtual ~Bullet();
	HitboxComponent* hitbox;

	sf::CircleShape shape;
	sf::Vector2f currVelocity;
	float maxSpeed;
};

