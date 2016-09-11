#include "mortar.h"
#include <time.h>



int main()
{
	bool gameOver = 0;
	int input = 0;
	Mortar* enemy = 0;
	Mortar myMortar(10,200,1,10,3,30,3);

	srand(time(0));

	SETCMDCOLOR(TURQUOISE)
	std::cout << "\nWelcome to Mortar, a design by Fabio Anthony!\n\n";
	SETCMDCOLOR(LIGHTGRAY)


	while (!gameOver)
	{
		std::cout << "1) Move mortar 2) Send scouts 3) Show stats 4) Quit game\n";
		std::cin >> input;
		switch (input)
		{
		case 1: std::cout << "1) Move north 2) Move south 3) Move east 4) Move west\n";
			std::cin >> input;
			switch (input)
			{
			case 1: myMortar.mPosition[1] += 1;
				break;
			case 2: myMortar.mPosition[1] -= 1;
				break;
			case 3:myMortar.mPosition[0] += 1;
				break;
			case 4:
				myMortar.mPosition[0] -= 1;
				break;
			default:
				SETCMDCOLOR(RED)
				std::cout << "Invalid input!\n";
				SETCMDCOLOR(LIGHTGRAY)
				break;
				
			}
			SETCMDCOLOR(GREEN)
			std::cout << "Position: " << myMortar.mPosition[0] << " | " << myMortar.mPosition[1] << std::endl;
			SETCMDCOLOR(LIGHTGRAY)
			break;
		case 2:
			if(!enemy)
			enemy = enemy->sendScouts();

			while (enemy)
			{
				SETCMDCOLOR(RED) 
				std::cout << "Enemy stats:\n";
				enemy->displayStats();
				SETCMDCOLOR(GREEN)
				std::cout << "My stats:\n";
				myMortar.displayStats();
				
				SETCMDCOLOR(LIGHTGRAY)
				std::cout << "Attacking enemy...";
				myMortar.applyDamage(enemy);
				if (enemy->getHealth() <= 0)
				{
					std::cout << "Emeny died!\n";
					delete enemy;
					enemy = 0;
					break;
				}
				std::cout << "Enemy strikes back...";
				enemy->applyDamage(&myMortar);				
				if (myMortar.getHealth() <= 0)
				{
					std::cout << "Game over!\n";
					gameOver = 1;
					break;
				}

			}
			break;
		case 3:
			SETCMDCOLOR(GREEN)
			std::cout << "My stats:\n";
			myMortar.displayStats();
			SETCMDCOLOR(LIGHTGRAY)
			break;
		}
	}
	

}