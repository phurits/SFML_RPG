#pragma once
#include "Entity.h"
#include "EnemySpawner.h"

class Entity;
class EnemySpawner;

class Enemy :
    public Entity
{
private:
    //Variables
    EnemySpawner& enemySpawner;

    //initializer functions
    void initVariables();
    void initAnimations();
public:
    Enemy(EnemySpawner& enemy_spawner,float x, float y, sf::Texture& texture_sheet);
    virtual ~Enemy();

    //Functions
    void updateAnimation(const float& dt);

    void update(const float& dt, sf::Vector2f& mouse_pos_view);
    void render(sf::RenderTarget& target, const bool show_hitbox);
};

