#include<iostream>
#include "Game.h"
#include "Main.h"


int main()
{
	//Init srand
	srand(static_cast<unsigned>(time(NULL)));
	//Init Game Engine
	Game game;

	while (game.getWindowIsOpen() && game.playing())
	{
		//Update
		game.update();

		//Render
		game.render();
	}

	return 0;
}