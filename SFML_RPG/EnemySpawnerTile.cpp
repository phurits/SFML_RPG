#include "stdafx.h"
#include "EnemySpawnerTile.h"

//Constructor / Deconstrucor

EnemySpawnerTile::EnemySpawnerTile(int grid_x, int grid_y, float gridSizeF,
	const sf::Texture& texture, const sf::IntRect& texture_rect,
	 int enemy_type, int enemy_amount, int enemy_time_to_spawn, float enemy_max_distance)
	:Tile(TileTypes::ENEMYSPAWNER,grid_x,grid_y,gridSizeF,texture,texture_rect,false)
{
	this->enemyType = enemy_type;
	this->enemyAmount = enemy_amount;
	this->enemyTimeToSpawn = enemy_time_to_spawn;
	this->enemyMaxDistance = enemy_max_distance;
	this->spawned = false;
}

EnemySpawnerTile::~EnemySpawnerTile()
{
}

const std::string EnemySpawnerTile::getAsString() const
{
	std::stringstream ss;

	/*
	x,y,z (done in tilemap save)
	types,
	rect x,rect y,
	enemy type,
	enemy amount,
	enemy time to spawn,
	enemy max distance
	*/

	ss << this->type << " " << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top << " "
		<< this->enemyType << " " << this->enemyAmount << " " << this->enemyTimeToSpawn << " " << this->enemyMaxDistance;

	std::cout << ss.str() << "\n";

	return ss.str();
}

const bool& EnemySpawnerTile::getSpawned() const
{
	return this->spawned;
}

//Functions

void EnemySpawnerTile::setSpawned(const bool spawned)
{
	this->spawned = spawned;
}

void EnemySpawnerTile::update()
{

}

void EnemySpawnerTile::render(sf::RenderTarget& target)
{
	target.draw(shape);
}
