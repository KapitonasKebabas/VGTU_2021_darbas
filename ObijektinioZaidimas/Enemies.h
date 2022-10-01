#pragma once
#include<iostream>

#include<SFML\Graphics.hpp>
#include<SFML\System.hpp>
#include<SFML\Window.hpp>
#include<SFML\Audio.hpp>
#include<SFML\Network.hpp>
class Enemies
{

private:
	
	//Kintamieji
	int sizeMin = 1, sizeMax = 3;
	sf::RectangleShape enemy;

public:
	
	Enemies();
	virtual ~Enemies();
	sf::RectangleShape Enemy();
	void Enemy1();
	void Enemy2();
	void Enemy3();


};

