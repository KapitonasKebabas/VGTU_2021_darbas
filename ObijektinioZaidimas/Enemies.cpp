#include "Enemies.h"


Enemies::Enemies()
{

}

Enemies::~Enemies()
{

}

sf::RectangleShape Enemies::Enemy()
{
	int a = rand() % sizeMax + sizeMin;
	if (a == 1)
	{
		Enemy1();
	}
	else if (a == 2)
	{
		Enemy2();
	}
	else
	{
		Enemy3();
	}

	return this->enemy;

}

void Enemies::Enemy1()
{
	this->enemy.setSize(sf::Vector2f(5.f, 5.f));
	this->enemy.setFillColor(sf::Color::Cyan);
	this->enemy.setOutlineColor(sf::Color::Red);
	this->enemy.setOutlineThickness(1.f);
}

void Enemies::Enemy2()
{
	this->enemy.setSize(sf::Vector2f(10.f, 10.f));
	this->enemy.setFillColor(sf::Color::Blue);
	this->enemy.setOutlineColor(sf::Color::Magenta);
	this->enemy.setOutlineThickness(1.f);
}

void Enemies::Enemy3()
{
	this->enemy.setSize(sf::Vector2f(20.f, 20.f));
	this->enemy.setFillColor(sf::Color::Red);
	this->enemy.setOutlineColor(sf::Color::White);
	this->enemy.setOutlineThickness(1.f);
}
