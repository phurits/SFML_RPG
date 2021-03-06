#pragma once

#include "GameState.h"
#include "HighscoreState.h"
#include "EditorState.h"
#include "SettingState.h"
#include "Game.h"
#include "Gui.h"

class MainMenuState :
    public State
{
private:
    //Variables
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;
    sf::Text text;

    sf::Event nameEvent;
    sf::RectangleShape textHolder;
    sf::String input;
    std::string nameString;

    std::map<std::string, gui::Button*>buttons;

    //Functions
    void initVariables();
    void initFonts();
    void initTexts();
    void initKeybinds();
    void initGui();
    void resetGui();

public:
    MainMenuState(StateData* state_data);
    virtual ~MainMenuState();

    //Functions

    void updateInput(const float& dt);
    void updateButtons();

    void update(const float& dt);
    void renderButttons(sf::RenderTarget& target);

    void render(sf::RenderTarget* target = NULL);



};

