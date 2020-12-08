#include "stdafx.h"
#include "PlayerGUI.h"

void PlayerGUI::initFont()
{
	this->font.loadFromFile("Fonts/Triforce.ttf");
}

void PlayerGUI::initLevelBar()
{
	float width = gui::p2pX(2.f, this->vm);
	float height = gui::p2pY(4.f, this->vm);
	float x = gui::p2pX(1.f, this->vm);
	float y = gui::p2pY(1.f, this->vm);

	this->levelBarBack.setSize(sf::Vector2f(width, height));
	this->levelBarBack.setFillColor(sf::Color(50, 50, 50, 200));
	this->levelBarBack.setPosition(x, y);

	this->levelBarText.setFont(this->font);
	this->levelBarText.setCharacterSize(gui::calcCharSize(this->vm, 100));
	this->levelBarText.setPosition(
		this->levelBarBack.getPosition().x + gui::p2pX(0.53f, this->vm) ,
		this->levelBarBack.getPosition().y + gui::p2pY(0.1f, this->vm)
	);
}

void PlayerGUI::initEXPBar()
{
	this->expBar = new gui::ProgressBar(
		1.f, 10.18f, 10.41f, 2.31f,
		this->player->getAttributeComponent()->expNext,
		sf::Color::Blue, 180,
		this->vm, &this->font
	);

}

void PlayerGUI::initHPBar()
{
	this->hpBar = new gui::ProgressBar(
		1.f, 5.55f, 15.62f, 3.7f,
		this->player->getAttributeComponent()->hpMax,
		sf::Color::Red,120,
		this->vm, &this->font
	);
}

void PlayerGUI::initScore()
{
	this->score = new gui::ProgressBar(
		920.f, 1.f, 0.f, 0.f,
		this->player->getAttributeComponent()->expNext,
		sf::Color::Black, 120,
		this->vm, &this->font
	);
}

PlayerGUI::PlayerGUI(Player* player, sf::VideoMode& vm)
	:vm(vm)
{
	this->player = player;

	this->initFont();
	this->initLevelBar();
	this->initEXPBar();
	this->initHPBar();
}

PlayerGUI::~PlayerGUI()
{
	delete this->hpBar;
	delete this->expBar;
}

//Functions

void PlayerGUI::updateLevelBar()
{
	this->levelBarString = std::to_string(this->player->getAttributeComponent()->level);
	this->levelBarText.setString(this->levelBarString);
}

void PlayerGUI::updateEXPBar()
{
	this->expBar->update(this->player->getAttributeComponent()->exp);
}

void PlayerGUI::updateHPBar()
{
	this->hpBar->update(this->player->getAttributeComponent()->hp);
}

void PlayerGUI::update(const float& dt)
{
	this->updateLevelBar();
	this->updateEXPBar();
	this->updateHPBar();
}

void PlayerGUI::renderLevelBar(sf::RenderTarget& target)
{
	target.draw(this->levelBarBack);
	target.draw(this->levelBarText);
}

void PlayerGUI::renderEXPBar(sf::RenderTarget& target)
{
	this->expBar->render(target);
}

void PlayerGUI::renderHPBar(sf::RenderTarget& target)
{
	this->hpBar->render(target);
}

void PlayerGUI::render(sf::RenderTarget& target)
{
	this->renderLevelBar(target);
	//this->renderEXPBar(target);
	this->renderHPBar(target);
}
