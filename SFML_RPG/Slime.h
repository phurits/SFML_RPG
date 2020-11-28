#pragma once
#include "Enemy.h"
class Slime :
    public Enemy
{
private:

    void initVariables();
    void initAnimations();
public:
    Slime(float x, float y, sf::Texture& texture_sheet);
    virtual ~Slime();

    //Functions
    void updateAnimation(const float& dt);
    void update(const float& dt, sf::Vector2f& mouse_pos_view);

    void render(sf::RenderTarget& target, const bool show_hitbox);
};

