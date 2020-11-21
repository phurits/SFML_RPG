#pragma once

#include "State.h"

class State;
class StateData;

class EditorMode
{
private:
	StateData* stateData;

public:
	EditorMode(StateData* state_data);
	virtual ~EditorMode();

	//Functions
    void updateInput(const float& dt);
    void updateGui(const float& dt);
    void update(const float& dt);

    void renderButttons(sf::RenderTarget& target);
    void renderGui(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = NULL);
};

