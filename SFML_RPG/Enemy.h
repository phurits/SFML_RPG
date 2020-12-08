#pragma once
#include "Entity.h"
#include "EnemySpawnerTile.h"

class Entity;
class EnemySpawnerTile;

class Enemy :
    public Entity
{
private:
    //Variables
    //EnemySpawner& enemySpawner;

    //initializer functions
    virtual void initVariables() = 0;
    virtual void initAnimations() = 0;

public:
    Enemy();
    virtual ~Enemy();

    //Functions
    virtual void updateAnimation(const float& dt) = 0;

    virtual void update(const float& dt, sf::Vector2f& mouse_pos_view) = 0;
    virtual void render(sf::RenderTarget& target, const bool show_hitbox) = 0;
};

