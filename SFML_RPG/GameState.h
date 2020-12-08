#pragma once

#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "PlayerGUI.h"
#include "Sword.h"
#include "Bow.h"
#include "Fairy.h"

class PauseMenu;
class Player;
class TileMap;
class Enemy;
class PlayerGUI;

class sf::View;
class sf::Font;
class sf::RenderTexture;

class GameState :
    public State
{
private:
    sf::View view;
    sf::Vector2i viewGridPosition;
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;

    sf::Vector2f aimDir;
    sf::Vector2f aimDirNorm;

    sf::Font font;
    PauseMenu* pmenu;

    Player* player;
    Fairy* fairy;
    PlayerGUI* playerGUI;
    sf::Texture texture;

    std::vector<Enemy*> activeEnemies;
    EnemySystem *enemySystem;
    
    TileMap* tileMap;

    Bullet b1;
    std::vector<Bullet> bullets;
  


    //Functions
    void initDeferredRender();
    void initView();
    void initKeybinds();
    void initFonts();
    void initTextures();
    void initPauseMenu();
    void initPlayers();
    void initFairy();
    void initPlayerGUI();
    void initEnemySystem();
    void initTileMap();

public:
    GameState(StateData* state_data);
    virtual ~GameState();

    //Functions
    void updateView(const float& dt);
    void updateInput(const float& dt);
    void updatePlayerInput(const float& dt);
    void updatePlayerGUI(const float& dt);
    void updatePauseMenuButtons();
    void updateTileMap(const float& dt);
    void updatePlayer(const float& dt);
    void updateEnemies(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target = NULL);

};

