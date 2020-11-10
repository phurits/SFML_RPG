#pragma once

#include "GameState.h"
#include "EditorState.h"
#include "SettingState.h"
#include "Gui.h"

class MainMenuState :
    public State
{
private:
    //Variables
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;

    std::map<std::string, gui::Button*>buttons;

    //Functions
    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initButtons();

public:
    MainMenuState(StateData* state_data);
    virtual ~MainMenuState();

    //Functions

    void updateInput(const float& dt);
    void updateButtons();
    void update(const float& dt);
    void renderButttons(sf::RenderTarget& targe);
    void render(sf::RenderTarget* target = NULL);



};
