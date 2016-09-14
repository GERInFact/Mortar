#include "mortar.h"
#include <time.h>




int rando_Mize(int min, int max)
{
	return (min + rand() % (max - min) + 1);
}
int _2DTo1D(int* position, int width)
{
	return position[0] + position[1] * width;
}
void displayMap(Mortar* myMortar, Mortar* enemy, int* battleField)
{

	for (int x = 1; x <= (battleField[0]* battleField[1]); x++)
	{
			
			if (x == _2DTo1D(myMortar->mPosition,battleField[0]))
			{
				SETCMDCOLOR(GREEN)
					if(myMortar->mIsFacingRight)
					std::cout << " > ";
					else
					std::cout << " < ";
				SETCMDCOLOR(LIGHTGRAY)
					if (myMortar->mPosition[0] == battleField[0])
						std::cout << std::endl;
			}
			else if (enemy && x == _2DTo1D(enemy->mPosition,battleField[0]))
			{
				
				SETCMDCOLOR(RED)
				std::cout << " X ";
				SETCMDCOLOR(LIGHTGRAY)
					if (enemy->mPosition[0] == battleField[0])
						std::cout << std::endl;
			}
			else if (!(x % (battleField[0])))
			{
				std::cout << " _ " << std::endl;
			}			
			else
				std::cout << " _ ";		
	}
	std::cout << std::endl << std::endl << std::endl;

}
int main()
{
	Mortar myMortar(rando_Mize(10, 15), rando_Mize(160, 400), 1, rando_Mize(3, 10), rando_Mize(1, 4), 0, 0, 1);
	Mortar* enemy = 0;
	int input = 0;
	int battleField[2] = { 10,10 };
	bool gameOver = 0;
	bool showMap = 0;
	

	
	
	

	srand(time(0));

	SETCMDCOLOR(TURQUOISE)
	std::cout << "\nWelcome to Mortar, a game design by Fabio Anthony!\n\n";
	SETCMDCOLOR(LIGHTGRAY)


	while (!gameOver)
	{
		if (myMortar.getHealth() <= 0)
		{
			SETCMDCOLOR(RED)
				std::cout << "						    YOU DIED!\n";
			Sleep(2500);
			std::cout << "					***********GAME OVER!***********\n";
			gameOver = 1;

		}

		SETCMDCOLOR(LIGHTGRAY)
		
		if(showMap)
		{
			displayMap(&myMortar,enemy, battleField);
		}
		SETCMDCOLOR(RED | TURQUOISE)
		std::cout << "1) Move mortar 2) Send scouts 3) Show stats 4)Show map 5) Attack enemy 6) Try to escape fight 7)Quit game\n";
		std::cin >> input;
		if (std::cin.fail())
		{
			SETCMDCOLOR(RED)
				std::cout << "Invalid operation! GAME CRASHED!\n";
			return 1;
		}
		SETCMDCOLOR(RED | BLUE)
			switch (input)
			{
			
			case 1: std::cout << "1) Move north 2) Move south 3) Move east 4) Move west 5) Align mortar \n";
				std::cin >> input;
				if (std::cin.fail())
				{
					SETCMDCOLOR(RED)
						std::cout << "Invalid operation! GAME CRASHED!\n";
					return 1;
				}
				myMortar.moveMortar(input, battleField);
				if (enemy && _2DTo1D(myMortar.mPosition, battleField[0]) == _2DTo1D(enemy->mPosition, battleField[0]))
				{
					std::cout << "						FATAL COLLISION! GAME OVER\n";
					return 0;
				}
				if (enemy)
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
				if (enemy)
				{
					SETCMDCOLOR(RED)

						std::cout << "Enemy stats:\n";
					enemy->displayStats();
					SETCMDCOLOR(GREEN)
						std::cout << "My stats:\n";
					myMortar.displayStats();

					std::cout << "Attacking enemy...\n";
					SETCMDCOLOR(LIGHTGRAY)
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

					Sleep(2500);
					SETCMDCOLOR(RED)
						std::cout << "Enemy strikes back...\n";
					SETCMDCOLOR(LIGHTGRAY)
					enemy->applyDamage(&myMortar);
								
				}
						break;
			case 6:
				if (enemy)
				{
					if (rando_Mize(0, 3) == 1)
					{
						std::cout << "YOU ESCAPED...\n";
						delete[] enemy;
						enemy = 0;
					}
					else
					{
						enemy->applyDamage(&myMortar);
					
				}
				break;
			default:
			{	SETCMDCOLOR(RED)
				std::cout << "Invalid input!\n";
			SETCMDCOLOR(LIGHTGRAY)
				break;;

			}
		}
	}
}
	

}