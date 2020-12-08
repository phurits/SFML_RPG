#include "stdafx.h"
#include "GameState.h"

void GameState::initDeferredRender()
{
	this->renderTexture.create(
		this->stateData->gfxSettings->resolution.width,
		this->stateData->gfxSettings->resolution.height
	);

	this->renderSprite.setTexture(this->renderTexture.getTexture());
	this->renderSprite.setTextureRect(
		sf::IntRect(
			0, 0, 
			this->stateData->gfxSettings->resolution.width, 
			this->stateData->gfxSettings->resolution.height
		)
	);

}

//Initializer Function
void GameState::initView()
{
	this->view.setSize(
		sf::Vector2f(
			static_cast<float>(this->stateData->gfxSettings->resolution.width),
			static_cast<float>(this->stateData->gfxSettings->resolution.height)
		)
	);

	this->view.setCenter(
		sf::Vector2f(
			static_cast<float>(this->stateData->gfxSettings->resolution.width) / 2.f,
				static_cast<float>(this->stateData->gfxSettings->resolution.height) / 2.f
		)
	);
}

void GameState::initKeybinds()
{
	std::ifstream ifs("Config/gamestate_keybinds.ini");

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

void GameState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Triforce.ttf"))
	{
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void GameState::initTextures()
{
	if (!this->textures["PLAYER_SHEET"].loadFromFile("Resources/Images/Sprites/Player/Full_Movement.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_PLAYER_PLAYER_TEXTURE";
	}
	if (!this->textures["SLIME_SHEET"].loadFromFile("Resources/Images/Sprites/Enemy/slime.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_ENEMY_SLIME_TEXTURE";
	}
	if(!this->textures["FAIRY_SHEET"].loadFromFile("Resources/Images/Sprites/Player/fairy2.png"))
	{
		throw "ERROR::GAME_STATE::COULD_NOT_LOAD_FAIRY_TEXTURE";
	}
}

void GameState::initPauseMenu()
{
	const sf::VideoMode& vm = this->stateData->gfxSettings->resolution;
	this->pmenu = new PauseMenu(this->stateData->gfxSettings->resolution, this->font);

	this->pmenu->addButton("QUIT", gui::p2pY(74.07f,vm), gui::p2pX(13.02f, vm), gui::p2pY(6.01, vm), gui::calcCharSize(vm), "Quit");
}

void GameState::initPlayers()
{
	this->player = new Player(2030, 200, this->textures["PLAYER_SHEET"]);
}

void GameState::initFairy()
{
	this->fairy = new Fairy(2030, 100, this->textures["FAIRY_SHEET"]);
}

void GameState::initPlayerGUI()
{
	this->playerGUI = new PlayerGUI(this->player, this->stateData->gfxSettings->resolution);
}

void GameState::initEnemySystem()
{
	this->enemySystem = new EnemySystem(this->activeEnemies, this->textures);
}

void GameState::initTileMap()
{
	//Change Tilemap here too (OWN COMMENT)
	this->tileMap = new TileMap("test.mp");
}

//Constructor / Destructor
GameState::GameState(StateData* state_data)
	:State(state_data)
{
	this->initDeferredRender();
	this->initView();
	this->initKeybinds();
	this->initFonts();
	this->initTextures();
	this->initPauseMenu();

	this->initPlayers();
	this->initFairy();
	this->initPlayerGUI();
	this->initEnemySystem();
	this->initTileMap();

	

}

GameState::~GameState()
{
	delete this->pmenu;
	delete this->player;
	delete this->fairy;
	delete this->playerGUI;
	delete this->enemySystem;
	delete this->tileMap;
	
	for (size_t i = 0; i < this->activeEnemies.size(); i++)
	{
		delete this->activeEnemies[i];
	}

}

//Functions
void GameState::updateView(const float& dt)
{
	//Addition View Setting here[OWN COMMENT]
	this->view.setCenter(
		std::floor(this->player->getPosition().x + (static_cast<float>(this->mousePosWindow.x) - static_cast<float>(this->stateData->gfxSettings->resolution.width / 2)) / 10.f), 
		std::floor(this->player->getPosition().y + (static_cast<float>(this->mousePosWindow.y) - static_cast<float>(this->stateData->gfxSettings->resolution.height / 2))/ 10.f)
	);											// + mouse Position

	if (this->tileMap->getMaxSizeF().x >= this->view.getSize().x)
	{
		if (this->view.getCenter().x - this->view.getSize().x / 2.f < 0.f)
		{
			this->view.setCenter(0.f + this->view.getSize().x / 2.f, this->view.getCenter().y);
		}
		else if (this->view.getCenter().x + this->view.getSize().x / 2.f > this->tileMap->getMaxSizeF().x )
		{
			this->view.setCenter(this->tileMap->getMaxSizeF().x  - this->view.getSize().x / 2.f, this->view.getCenter().y);
		}
	}
	if (this->tileMap->getMaxSizeF().y >= this->view.getSize().y)
	{
		if (this->view.getCenter().y - this->view.getSize().y / 2.f < 0.f)
		{
			this->view.setCenter(this->view.getCenter().x, 0.f + this->view.getSize().y / 2.f);
		}
		else if (this->view.getCenter().y + this->view.getSize().y / 2.f > this->tileMap->getMaxSizeF().y) //this->tileMap->getMaxSizeF().y
		{
			this->view.setCenter(this->view.getCenter().x, this->tileMap->getMaxSizeF().y - this->view.getSize().y / 2.f);
		}
	}

	this->viewGridPosition.x = static_cast<int>(this->view.getCenter().x) / static_cast<int>(this->stateData->gridSize);
	this->viewGridPosition.y = static_cast<int>(this->view.getCenter().y) / static_cast<int>(this->stateData->gridSize);

}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("CLOSE"))) && this->getKeytime())
	{
		if (!this->paused)
			this->pauseState();
		else
			this->unpauseState();
	}
}

void GameState::updatePlayerInput(const float& dt)
{
	//Update player input
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_LEFT"))))
		this->player->move(-1.f, 0.f,dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_RIGHT"))))
		this->player->move(1.f, 0.f,dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_UP"))))
		this->player->move(0.f, -1.f, dt);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(this->keybinds.at("MOVE_DOWN"))))
		this->player->move(0.f, 1.f, dt);

	//Update fairy Pos after player move;
	this->fairy->setPosition(this->player->getPosition().x-15, this->player->getPosition().y-40.f);

	//Shooting
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		//std::cout << "MOUSE CLICKED" << "\n";
		this->b1.shape.setPosition(this->fairy->getPosition());
		this->b1.currVelocity = this->aimDirNorm * this->b1.maxSpeed;

		this->bullets.push_back(Bullet(b1));
	}

	for (size_t i = 0; i < bullets.size(); i++)
	{
		std::cout << "Update Pos bullet" << "\n";
		this->bullets[i].shape.move(bullets[i].currVelocity);

		if (this->bullets[i].shape.getPosition().x < 0 || this->bullets[i].shape.getPosition().x > this->window->getSize().x
			|| this->bullets[i].shape.getPosition().y < 0 || this->bullets[i].shape.getPosition().y < this->window->getSize().y)
		{
			this->bullets.erase(bullets.begin() + i);
		}
	}

}

void GameState::updatePlayerGUI(const float& dt)
{
	this->playerGUI->update(dt);
}

void GameState::updatePauseMenuButtons()
{
	if (this->pmenu->isButtonPressed("QUIT"))
		this->endState();
}

void GameState::updateTileMap(const float& dt)
{
	this->tileMap->updateWorldBoundsCollision(this->player, dt);
	this->tileMap->updateTileCollision(this->player, dt);
	this->tileMap->updateTiles(this->player, dt, *this->enemySystem);

	for (auto* i : this->activeEnemies)
	{
		this->tileMap->updateWorldBoundsCollision(i, dt);
		this->tileMap->updateTileCollision(i, dt);
	}
}

void GameState::updatePlayer(const float& dt)
{
}

void GameState::updateEnemies(const float& dt)
{
	
}

void GameState::update(const float& dt)
{
	this->updateMousePositions(&this->view); 
	this->updateKeytime(dt);
	this->updateInput(dt);

	if (!this->paused) // Unpaused update
	{
		//HERE TO SET CAMERA VIEW AT ALL BORDER (OWN COMMENT)

		this->updateView(dt);

		this->updatePlayerInput(dt);

		this->updateTileMap(dt);

		this->player->update(dt, this->mousePosView);

		this->fairy->update(dt, this->mousePosView);

		this->playerGUI->update(dt);

		for (auto* i : this->activeEnemies)
		{
			i->update(dt, this->mousePosView);
		}

	}
	else // Paused update
	{
		this->pmenu->update(this->mousePosWindow);
		this->updatePauseMenuButtons();
	}
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	this->renderTexture.clear();

	this->renderTexture.setView(this->view);

	this->tileMap->render(
		this->renderTexture,
		this->viewGridPosition,
		this->player->getCenter(),
		false
	);

	for (auto* i : this->activeEnemies)
	{
		i->render(this->renderTexture, true);
	}

	this->player->render(this->renderTexture, false);

	this->fairy->render(this->renderTexture, false);

	for (size_t i = 0; i < this->bullets.size(); i++)
	{
		std::cout << this->bullets.size() << "\n";
		target->draw(this->bullets[i].shape);
	}

	this->tileMap->renderDeferred(this->renderTexture);

	//RENDER GUI
	this->renderTexture.setView(this->renderTexture.getDefaultView());
	this->playerGUI->render(this->renderTexture);

	if (this->paused) // paused menu render
	{
		//this->renderTexture.setView(this->renderTexture.getDefaultView());
		this->pmenu->render(this->renderTexture);
	}

	//FINAL RENDER
	this->renderTexture.display();
	//this->renderSprite.setTexture(this->renderTexture.getTexture());
	target->draw(this->renderSprite);
}

