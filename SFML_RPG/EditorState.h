#pragma once

#include "State.h"
#include "Gui.h"
#include "PauseMenu.h"
#include "TileMap.h"
#include "EditorMode.h"

class State;
class StateData;
class Gui;
class PauseMenu;
class TileMap;
class EditorMode;

enum EditorModes {DEFAULT = 0, ENEMY};

class EditorState :
    public State
{
private:
    //Variables
    sf::View view;

    sf::Font font;
    sf::Text cursorText;
    PauseMenu* pmenu;

    std::map<std::string, gui::Button*>buttons;

    TileMap* tileMap;

    sf::RectangleShape sidebar;

    sf::RectangleShape selectorRect;

    gui::TextureSelector* textureSelector;

    sf::IntRect textureRect;

    bool collision;
    short type;
    float cameraSpeed;
    int layer;
    bool tileAddLock;

    //Functions
    void initVariables();
    void initView();
    void initBackground();
    void initFonts();
    void initText();
    void initKeybinds();
    void initPauseMenu();
    void initButtons();
    void initTileMap();
    void initGui();

public:
    EditorState(StateData* state_data);
    virtual ~EditorState();

    //Functions
    void updateInput(const float& dt);
    void updateEditorInput(const float& dt);
    void updateButtons();
    void updateGui(const float& dt);
    void updatePauseMenuButtons();
    void update(const float& dt);
    void renderButttons(sf::RenderTarget& target);
    void renderGui(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = NULL);
};

