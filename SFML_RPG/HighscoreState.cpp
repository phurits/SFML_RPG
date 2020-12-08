#include "stdafx.h"
#include "HighscoreState.h"

//Initializer functions
void HighscoreState::initVariables()
{

}

void HighscoreState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Triforce.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void HighscoreState::initKeybinds()
{
	std::ifstream ifs("Config/mainmenustate_keybinds.ini");

	if (ifs.is_open())
	{
		std::string key = "";
		std::string key2 = "";

		while (ifs >> key >> key2)
		{
			this->keybinds[key] = this->supportedKeys->at(key2);
		}
	}

	ifs.close();
}

void HighscoreState::initGui()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;

	//Background
	this->background.setSize(sf::Vector2f(
		static_cast<float>(vm.width),
		static_cast<float>(vm.height)
	));

	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/Mainmenu.png"))
	{
		throw "ERROR::MAIN_MENU_STATE::FAILED_TO_LOAD_BACKGROUND_TEXTURE";
	}

	this->background.setTexture(&this->backgroundTexture);

	//Buttons
	this->buttons["BACK"] = new gui::Button(
		gui::p2pX(78.12f, vm), gui::p2pY(81.48f, vm),
		gui::p2pX(13.02f, vm), gui::p2pY(6.01f, vm),
		&this->font, "Back", gui::calcCharSize(vm),
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

}

void HighscoreState::resetGui()
{
	/*
	* Clears the GUI elements and re-initialises the GUI.
	*
	* @return void
	*
	*/
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.begin(); ++it)
	{
		delete it->second;
	}
	this->buttons.clear();

	this->initGui();
}


HighscoreState::HighscoreState(StateData* state_data)
	:State(state_data)
{
	this->initVariables();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
	this->resetGui();
}

HighscoreState::~HighscoreState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.begin(); ++it)
	{
		delete it->second;
	}
}


void HighscoreState::updateInput(const float& dt)
{

}

void HighscoreState::updateButtons()
{
	/*Updates all the button in the state and handles their functionality.*/
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}

	//Quit the game
	if (this->buttons["BACK"]->isPressed())
	{
		this->endState();
	}
}

void HighscoreState::update(const float& dt)
{
	this->updateMousePositions();
	this->updateInput(dt);

	this->updateButtons();

}

void HighscoreState::renderButttons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}

void HighscoreState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderButttons(*target);

}

