#include <iostream>
#include "Game.h"



using namespace sf;
using namespace std;


int main(int argc, char** argv[])
{



	std::srand(static_cast<unsigned>(time(NULL)));

	
	Game game;



	while (game.Running())
	{

		//Update

		game.Update();


		//Render
		game.Render();



	}




	system("pause");


	//end

	return 0;
}

