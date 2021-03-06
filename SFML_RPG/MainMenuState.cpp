#include "stdafx.h"
#include "MainMenuState.h"

//Initializer functions
void MainMenuState::initVariables()
{
}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Triforce.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void MainMenuState::initTexts()
{
	this->input = "";
	this->text.setFont(this->font);
	this->text.setCharacterSize(25.f);
	this->text.setPosition(sf::Vector2f(this->view->getCenter().x - 100, 310.f));
}

void MainMenuState::initKeybinds()
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

void MainMenuState::initGui()
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
	this->buttons["GAME_STATE"] = new gui::Button(
		gui::p2pX(45.83f,vm), gui::p2pY(35.18f,vm),
		gui::p2pX(13.02f, vm), gui::p2pY(6.01, vm),
		&this->font, "New Game", gui::calcCharSize(vm),
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["HIGHSCORE_STATE"] = new gui::Button(
		gui::p2pX(45.83f, vm), gui::p2pY(44.44f, vm),
		gui::p2pX(13.02f, vm), gui::p2pY(6.01, vm),
		&this->font, "Highscore", gui::calcCharSize(vm),
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["SETTINGS_STATE"] = new gui::Button(
		gui::p2pX(45.83f, vm), gui::p2pY(53.7f, vm),
		gui::p2pX(13.02f, vm), gui::p2pY(6.01, vm),
		&this->font, "Setting", gui::calcCharSize(vm),
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
		sf::Color(70, 70, 70, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["EDITOR_STATE"] = new gui::Button(
		gui::p2pX(45.83f, vm), gui::p2pY(62.96f, vm),
		gui::p2pX(13.02f, vm), gui::p2pY(6.01, vm),
		&this->font, "Editor", gui::calcCharSize(vm),
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	this->buttons["EXIT_STATE"] = new gui::Button(
		gui::p2pX(45.83f, vm), gui::p2pY(81.48f, vm),
		gui::p2pX(13.02f, vm), gui::p2pY(6.01, vm),
		&this->font, "Quit", gui::calcCharSize(vm),
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 250), sf::Color(20, 20, 20, 50),
		sf::Color(100, 100, 100, 0), sf::Color(150, 150, 150, 0), sf::Color(20, 20, 20, 0));

	//Top Left Name
	this->text.setFont(this->font);
	this->text.setString("63010769 | PHURIT SARARATTANAKUL");
	this->text.setFillColor(sf::Color::Black);
	this->text.setCharacterSize(30);
	this->text.setPosition(0, 0);
}

void MainMenuState::resetGui()
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


MainMenuState::MainMenuState(StateData* state_data)
	:State(state_data)
{
	this->initVariables();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
	this->resetGui();
	
	
	
}

MainMenuState::~MainMenuState()
{
	auto it = this->buttons.begin();
	for (it = this->buttons.begin(); it != this->buttons.begin(); ++it)
	{
		delete it->second;
	}

}


void MainMenuState::updateInput(const float& dt)
{

}

void MainMenuState::updateButtons()
{
	/*Updates all the button in the state and handles their functionality.*/
	for (auto& it : this->buttons)
	{
		it.second->update(this->mousePosWindow);
	}

	//New Game
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new GameState(this->stateData));
	}

	//Highscore
	if (this->buttons["HIGHSCORE_STATE"]->isPressed())
	{
		this->states->push(new HighscoreState(this->stateData));
	}

	//Settings
	if (this->buttons["SETTINGS_STATE"]->isPressed())
	{
		this->states->push(new SettingState(this->stateData));
	}

	//Editor
	if (this->buttons["EDITOR_STATE"]->isPressed())
	{
		this->states->push(new EditorState(this->stateData));
	}

	//Quit the game
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->endState();
	}

	
}

void MainMenuState::update(const float& dt)
{

	while (this->window->pollEvent(this->nameEvent))
	{
		if (this->nameEvent.type == sf::Event::TextEntered)
		{
			if (this->nameEvent.text.unicode < 128)
			{
				std::cout << "Text entered: " << (this->nameEvent.text.unicode) << std::endl;
				if (this->nameEvent.text.unicode == static_cast<sf::Uint32>(8) && this->input.getSize() > 0)
				{
					this->input.erase(this->input.getSize() - 1);
					this->nameString.erase(this->nameString.size() - 1);
				}
				else
				{
					if (this->input.getSize() < 13 && this->nameEvent.text.unicode != 13)
					{
						if (this->nameEvent.text.unicode >= 97 && this->nameEvent.text.unicode <= 122)
						{
							this->nameEvent.text.unicode -= 32;
						}
						this->input += this->nameEvent.text.unicode;
						this->nameString += this->nameEvent.text.unicode;
					}
				}

			}
		}
	}
	this->updateMousePositions();
	this->updateInput(dt);
	this->updateButtons();
	
}

void MainMenuState::renderButttons(sf::RenderTarget& target)
{
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}
}



void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background);

	this->renderButttons(*target);

	target->draw(this->textHolder);
	target->draw(this->text);

	////REMOVE LATER!!!
	//sf::Text mouseText;
	//mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
	//mouseText.setFont(this->font);
	//mouseText.setCharacterSize(12);
	//std::stringstream ss;
	//ss << this->mousePosView.x << " " << this->mousePosView.y;
	//mouseText.setString(ss.str());
	//target->draw(mouseText);
}

