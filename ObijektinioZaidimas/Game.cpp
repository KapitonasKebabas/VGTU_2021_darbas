#include "Game.h"

//Private funkcijos
void Game::initializeVeriables()
{
	this->window = nullptr;

	//Zaidimo logika
	this->points = 0;
	this->time = 0;
	this->enemySpawnTimerMax = 10.f;
	this->enemySpawnTimer = enemySpawnTimerMax;
	this->maxEnemies = 5;
	this->inGame = true;
	this->speedShoot = 15;

}
void Game::initWindow()
{
	//Rezoliucija
	this->videoMode.height = 600;
	this->videoMode.width = 800;

	this->window = new sf::RenderWindow(this->videoMode, "Game Name", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

void Game::initEnemy()
{
	/*
	this->enemy.setPosition(10.f, 10.f);
	this->enemy.setSize(sf::Vector2f(20.f, 20.f));
	this->enemy.setFillColor(sf::Color::Cyan);
	this->enemy.setOutlineColor(sf::Color::Red);
	this->enemy.setOutlineThickness(1.f);
	*/
	
}

void Game::initPlayer()
{
	this->player.setPosition(this->window->getSize().x / 2, this->window->getSize().y / 2);
	this->player.setRadius(20.f);
	this->player.setFillColor(sf::Color::Green);
	this->player.setOutlineColor(sf::Color::Red);
	this->player.setOutlineThickness(1.f);

}

void Game::initShoot()
{
	this->shoot.setRadius(5.f);
	this->shoot.setFillColor(sf::Color::Green);
	this->shoot.setOutlineColor(sf::Color::Red);
	this->shoot.setOutlineThickness(1.f);
}



//Kontsruktoriai Destruktoriai
Game::Game()
{
	//tvarka svarbi
	this->initializeVeriables();
	this->initWindow();
	this->initEnemy();
	this->initPlayer();
	this->initShoot();
	//End tvarka
}
Game::~Game()
{
	delete this->window;
}




//Aksesuarai
const bool Game::getWindowIsOpen() const
{
	return this->window->isOpen();
}

bool Game::playing()
{
	return inGame;
}


//Funkcijos
void Game::spawnEnemy()
{

	this->enemy = Enemy();
	this->enemy.setPosition(
		static_cast<float>(rand() % static_cast<int>(this->window->getSize().x - this->enemy.getSize().x)), 0.f);

	float xy = static_cast<float>(rand() % 80 + 20);
	this->enemy.setSize(sf::Vector2f(xy, xy));

	//this->enemy.setFillColor(sf::Color::Green);

	this->enemies.push_back(this->enemy);
}

void Game::spawnShoot()
{
	this->shoot.setPosition(
		this->player.getPosition().x + (this->player.getRadius() / 2) + (this->shoot.getRadius() / 2),
		this->player.getPosition().y + (this->player.getRadius() / 2) + (this->shoot.getRadius() / 2)
	);

	//this->enemy.setFillColor(sf::Color::Green);
	//Normalaizing
	float c;
	float x, y, proc;
	x = mousePosView.x - this->player.getPosition().x;
	y = mousePosView.y - this->player.getPosition().y;
	c = sqrt(x * x + y * y);
	
	x = x / c;
	y = y / c;
	std::cout << "Shoot made" << " " << mousePosView.x << " " << mousePosView.y << "\n";
	std::cout << x << " " << y << "\n";

	this->shoots.push_back(this->shoot);
	this->shootsMove.push_back(sf::Vector2f(x* speedShoot,y* speedShoot));
}

//Funkcijos
void Game::endGame()
{
	this->window->clear();
	this->inGame = false;
	this->text.setString("Game over! Points: " + std::to_string(this->points));
	this->text.setPosition(sf::Vector2f(
		static_cast<float>((this->window->getSize().x / 2) - int(this->text.getGlobalBounds().width / 2)),
		static_cast<float>(this->window->getSize().y / 2)
	));
	this->window->draw(text);
	this->text.setString("Press R to restart, press E to exit ");
	this->text.setPosition(sf::Vector2f(
		static_cast<float>((this->window->getSize().x / 2) - int(this->text.getGlobalBounds().width /2)),
		static_cast<float>((this->window->getSize().y / 2) + 50)
	));
	this->window->draw(text);
	this->window->display();
	bool buttonPressed = false;
	while (!buttonPressed)
	{
		while (this->window->pollEvent(this->ev))
		{
			switch (this->ev.type)
			{
			case sf::Event::KeyPressed:
				if (this->ev.key.code == sf::Keyboard::E) {
					buttonPressed = true;
				}
				if (this->ev.key.code == sf::Keyboard::R) {
					buttonPressed = true;
					this->inGame = true;
					this->points = 0;
					this->time = 0;
					enemies.clear();
					shoots.clear();
					shootsMove.clear();
					initPlayer();
				}
				break;
			}
		}
	}

}

void Game::timer()
{
	//Laiko skaiciavimas ir isvedimas i ekrana
	while (time <= 3)
	{
	sf::Time tls = clock.getElapsedTime();
	this->time += int(tls.asSeconds());
		std::cout << time << "\n";
	}
}

void Game::pollEvent()
{
	while (this->window->pollEvent(this->ev))
	{
		switch (this->ev.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void Game::updateMouse()
{
	//updateMousePossition
	//Ekrano sf::Mouse::getPosition()
	//Aplikacijos
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(this->mousePosWindow);
}
void Game::updateShoot()
{
	//Timer Auto fire
	float timeShoot = 0.25f; // Timer for auto fire
	sf::Time elT2 = clock2.getElapsedTime();
	sf::Time elT3 = clock2.getElapsedTime();
	if (elT2.asSeconds() >= timeShoot)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->spawnShoot();
			clock2.restart();
		}
	}
	int kiek = 0;
	for (auto& e : this->shoots)
	{
		if (e.getPosition().y >= (this->window->getSize().y + e.getRadius()))
		{
			shoots.erase(shoots.begin() + kiek);
			shootsMove.erase(shootsMove.begin() + kiek);
		}
		else if (e.getPosition().x >= (this->window->getSize().x + e.getRadius()))
		{
			shoots.erase(shoots.begin() + kiek);
			shootsMove.erase(shootsMove.begin() + kiek);
		}
		else if (e.getPosition().y <= e.getRadius())
		{
			shoots.erase(shoots.begin() + kiek);
			shootsMove.erase(shootsMove.begin() + kiek);
		}
		else if (e.getPosition().x <= e.getRadius())
		{
			shoots.erase(shoots.begin() + kiek);
			shootsMove.erase(shootsMove.begin() + kiek);
		}
		kiek++;
	}


	for (int i = 0; i < shoots.size(); i++)
	{
		shoots[i].move(shootsMove[i]);

		//check to destroy object
		int kiek2 = 0;
		for (auto& ee : this->enemies)
		{
			if (ee.getGlobalBounds().contains(shoots[i].getPosition()))
			{
				std::cout << "Hit" << "\n";
				shoots.erase(shoots.begin() + i);
				shootsMove.erase(shootsMove.begin() + i);
				enemies.erase(enemies.begin() + kiek2);
				this->points += 1;
				break;
				i--;
			}
			kiek2++;

		}
	}
}

void Game::updateEnemy()
{
	if (this->enemies.size() < this->maxEnemies) 
	{
		if (this->enemySpawnTimer >= this->enemySpawnTimerMax) 
		{
			this->spawnEnemy();
			this->enemySpawnTimer = 0.f;
		}
		else
		{
			this->enemySpawnTimer += 1.f;
		}
	}
	
	//Move enemies
	int kiek = 0;
	for (auto &e : this->enemies)
	{
		e.move(0.f, 5.f);
		if (e.getPosition().y >= (this->window->getSize().y + e.getSize().y))
		{
			enemies.erase(enemies.begin() + kiek);
			//Time LOST kodas
			this->time -= 5;

		}


		kiek++;
	}
}

void Game::spawnPlayer()
{
	this->renderPlayer();
}

void Game::update()
{
	this->timer();
	this->pollEvent();
	this->updateMouse();
	this->updateEnemy();
	this->updatePlayer();
	this->updateShoot();

	//check if lost
	for (auto& e : this->enemies)
	{
		if (e.getGlobalBounds().contains(player.getPosition())) //DEBUG ON
		{
			this->time = 0;
			this->endGame();
		}
	}
	
}

void Game::renderEnemy()
{
	for (auto &e : this->enemies)
	{
		this->window->draw(e);
	}
}
void Game::renderShoots()
{
	for (auto& e : this->shoots)
	{
		this->window->draw(e);
	}
}

void Game::renderPlayer()
{
	this->window->draw(this->player);
}

void Game::renderUI()
{
	if (!this->font.loadFromFile("arial.ttf"))
	{
		// handle error
	}
	
	//Bendri options
	this->text.setFont(font);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(24);


	//Isvedimas su tekstu
	//Time
	this->text.setString("Time: " + std::to_string(this->time));
	this->text.setPosition(sf::Vector2f(0.f, 0.f));
	this->window->draw(text);

	//Points
	this->text.setString("Points: " + std::to_string(this->points));
	this->text.setPosition(sf::Vector2f(this->window->getSize().x - this->text.getGlobalBounds().width - 10, 0.f));
	this->window->draw(text);
}

void Game::render()
{
	this->window->clear();
	
	//Vaizdavimas
	this->renderEnemy();
	this->renderPlayer();
	this->renderShoots();
	this->renderUI();

	this->window->display();
}

void Game::updatePlayer()
{
	//Moving
	float x = 0, y = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		y -= 5.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		y += 5.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		x -= 5.f;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		x += 5.f;
	}
	this->player.move(x,y);
}
