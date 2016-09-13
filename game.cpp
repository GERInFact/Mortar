#include "mortar.h"
#include <time.h>


void displayMap(Mortar* myMortar, Mortar* enemy, int* battleField)
{

	for (int x = 1; x <= (battleField[0]); x++)
	{
		for (int y = 1; y <= (battleField[1]); y++)
		{
			if (!(y % 10))
			{
				std::cout << std::endl;
			}
			else if (y == myMortar->mPosition[0] && x == myMortar->mPosition[1])
			{
				SETCMDCOLOR(GREEN)
					std::cout << " O ";
				SETCMDCOLOR(LIGHTGRAY)
			}
			else if (enemy && y == enemy->mPosition[0] && x == enemy->mPosition[1])
			{
				SETCMDCOLOR(RED)
				std::cout << " E ";
				SETCMDCOLOR(LIGHTGRAY)

			}
			else
				std::cout << " _ ";
		}
		std::cout << std::endl;
	}

}
int main()
{
	bool gameOver = 0;
	bool showMap = 0;
	int input = 0;
	int battleField[2] = { 10,10 };
	Mortar* enemy = 0;
	Mortar myMortar(10,200,1,3,3,30,3,0);

	srand(time(0));

	SETCMDCOLOR(TURQUOISE)
	std::cout << "\nWelcome to Mortar, a game design by Fabio Anthony!\n\n";
	SETCMDCOLOR(LIGHTGRAY)


	while (!gameOver)
	{
		if(showMap)
		{
			displayMap(&myMortar,enemy, battleField);
		}
		std::cout << "1) Move mortar 2) Send scouts 3) Show stats 4)Show map 5) Attack enemy 6)Quit game\n";
		std::cin >> input;
		switch (input)
		{
		case 1: std::cout << "1) Move north 2) Move south 3) Move east 4) Move west\n";
			std::cin >> input;
			myMortar.moveMortar(input, battleField);
			if(enemy)
			enemy->moveMortar(1 + rand() % (5 - 1), battleField);
			SETCMDCOLOR(GREEN)
			std::cout << "Position: " << myMortar.mPosition[0] << " | " << myMortar.mPosition[1] << std::endl;
			SETCMDCOLOR(LIGHTGRAY)
			break;
		case 2:
			if (!enemy)
			{
				enemy = enemy->sendScouts();
				if (enemy)
				{
					SETCMDCOLOR(RED)
					std::cout << "Enemy detected..\n";
					SETCMDCOLOR(LIGHTGRAY)
				}
			}
			break;
		case 3:
			SETCMDCOLOR(GREEN)
			std::cout << "My stats:\n";
			myMortar.displayStats();
			SETCMDCOLOR(LIGHTGRAY)
			break;
		case 4:
			showMap = !showMap;
			break;
		case 5:
			if (myMortar.isEnemyInRange(enemy))
			{
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
						myMortar.setExp(enemy->getExp());
						myMortar.setShellLevel();
						delete enemy;
						enemy = 0;
						break;
					}

					std::cout << "Enemy strikes back...";
					enemy->applyDamage(&myMortar);
						
					if (myMortar.getHealth() <= 0)
					{
						SETCMDCOLOR(RED)
						std::cout << "				***********GAME OVER!***********\n";
						gameOver = 1;
						break;
					}
					Sleep(2500);
				}
				
			}
			else
			{
				std::cout << "Enemy out of range!\n";
				break;
			}
		}
	}
	

}