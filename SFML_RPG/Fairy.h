#pragma once
#include "Entity.h"
#include "Bullet.h"
class Fairy :
    public Entity
{
private:
    //Variables
    bool attacking;

    sf::Vector2f getCenter;
    sf::Vector2f mousePosWindow;
    sf::Vector2f aimDir;
    sf::Vector2f aimDirNorm;

    //Initializer Functions
    void initVariables();
    void initAnimations();


public:
    Fairy(float x, float y, sf::Texture& texture_sheet);
    virtual ~Fairy();

    //Functions
    void updateAnimation(const float& dt);
    void updateBulletLine(sf::Vector2f& mouse_pos_view);
    void update(const float& dt, sf::Vector2f& mouse_pos_view);

    void render(sf::RenderTarget& target, const bool show_hitbox = false);
};

