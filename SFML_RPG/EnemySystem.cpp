#include "stdafx.h"
#include "EnemySystem.h"

EnemySystem::EnemySystem(std::vector<Enemy*>& activeEnemies,
	std::map<std::string, sf::Texture>& textures)
	: textures(textures), activeEnemies(activeEnemies)
{

}

EnemySystem::~EnemySystem()
{

}


//Functions

void EnemySystem::createEnemy(const short type, const float xPos, const float yPos)
{
	switch (type)
	{
	case EnemyTypes::SLIME:
		this->activeEnemies.push_back(new Slime(xPos, yPos, this->textures["SLIME_SHEET"]));
		break;
	default:
		std::cout << "ERROR::ENEMYSYSTEM::CREATEENEMY::TYPE DOES NOT EXIST" << "\n";
		break;
	}
}

void EnemySystem::update(const float& dt)
{

}

void EnemySystem::render(sf::RenderTarget* target)
{

}
