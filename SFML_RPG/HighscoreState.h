#pragma once

#include "State.h"
#include "Gui.h"

class HighscoreState :
    public State
{
private:
    //Variables
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;

    std::map<std::string, gui::Button*> buttons;

    //Functions
    void initVariables();
    void initFonts();
    void initKeybinds();
    void initGui();
    void resetGui();

public:
    HighscoreState(StateData* state_data);
    virtual ~HighscoreState();

    //Functions
    void updateInput(const float& dt);
    void updateButtons();
    void update(const float& dt);
    void renderButttons(sf::RenderTarget& targe);
    void render(sf::RenderTarget* target = NULL);

};

