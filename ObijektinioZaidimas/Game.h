#pragma once

#include<iostream>
#include<vector>
#include<ctime>
#include<string>
#include<cmath>
#include "Enemies.h"

#include<SFML\Graphics.hpp>
#include<SFML\System.hpp>
#include<SFML\Window.hpp>
#include<SFML\Audio.hpp>
#include<SFML\Network.hpp>

class Game : public Enemies
{
private:
	//Kintamieji 
	
	//window
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event ev;

	//Time
	sf::Clock clock;
	sf::Clock clock2;

	//UI
	sf::Text text;
	sf::Font font;

	//MousePos
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Zaidimo Obijektai
	std::vector<sf::RectangleShape> enemies;
	sf::RectangleShape enemy;
	sf::CircleShape player;
	std::vector<sf::CircleShape> shoots;
	std::vector<sf::Vector2f> shootsMove;
	sf::CircleShape shoot;

	//Zaidimo logika
	int time;
	int points;
	int speedShoot;
	float enemySpawnTimer;
	float enemySpawnTimerMax;
	int maxEnemies;
	bool inGame;



	//Private functions
	void initializeVeriables();
	void initWindow();
	void initEnemy();
	void initPlayer();
	void initShoot();

public:
	Game();
	virtual ~Game();
	//Aksesuarai
	const bool getWindowIsOpen() const;
	bool playing() ;

	//Funkcijos
	void endGame();
	void spawnEnemy();
	void spawnPlayer();
	void spawnShoot();
	void timer();
	void pollEvent();
	void updateMouse();
	void updateEnemy();
	void updatePlayer();
	void updateShoot();
	void update();
	void renderEnemy();
	void renderPlayer();
	void renderShoots();
	void renderUI();
	void render();
};

