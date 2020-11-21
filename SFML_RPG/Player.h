#pragma once

#include "Entity.h"

#include "Sword.h"

class Entity;

class Player :
    public Entity
{
private:
    //Variables
    bool attacking;
    Sword sword;

    //Initializer Functions
    void initVariables();
    void initComponents();
    void initAnimation();


public:
    Player(float x, float y, sf::Texture& texture_sheet);
    virtual ~Player();

    //Accessors
    AttributeComponent* getAttributeComponent();

    //Functions
    void loseHP(const int hp);
    void gainHP(const int hp);
    void loseEXP(const int exp);
    void gainEXP(const int exp);
    void updateAttack();
    void updateAnimation(const float& dt);
    void update(const float& dt, sf::Vector2f& mouse_pos_view);

    void render(sf::RenderTarget& target, const bool show_hitbox = false);
};

