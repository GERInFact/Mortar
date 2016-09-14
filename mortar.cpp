#include "mortar.h"



Mortar::Mortar(int armour, int health, int shellType, int range, int blastRadius, int reloadTime, int exp, bool isPlayer) : mArmour(armour),mHealth(health)
				,mShellType(shellType), mRange(range),mBlastRadius(blastRadius),mReloadTime(reloadTime), mExperience(exp), mIsPlayer(isPlayer){}

Mortar::Mortar() {}



int Mortar::Randomize(int min, int max)
{
	return (min + rand() % (max - min) + 1);
}

std::ostream& operator << (std::ostream& out, Mortar mortar)
{
	out << "------------------------\n";
	out << "Position:	" << mortar.mPosition[0] << " | " << mortar.mPosition[1] << std::endl;
	out << "ShellType:	" << mortar.mShellType << std::endl;
	out << "Health:		"<<mortar.mHealth<<std::endl;
	out << "Armour:		"<<mortar.mArmour<<std::endl;
	out << "Range:		"<<mortar.mRange<<std::endl;
	out << "BlastRadius:	"<<mortar.mBlastRadius<<std::endl;
	out << "ReloadTime:	"<<mortar.mReloadTime<<std::endl;
	out << "Experience:	"<<mortar.mExperience<<std::endl;
	out << "------------------------\n";

	return out;
}
int Mortar::distanceToTarget(Mortar* target)
{
	return sqrt((target->mPosition[0] - mPosition[0])*(target->mPosition[0] - mPosition[0]) + (target->mPosition[1] - mPosition[1]) * (target->mPosition[1] - mPosition[1]));
}
bool Mortar::isEnemyInRange(Mortar* mEnemy, int missileWeight)
{	 
	if (mRange + mBlastRadius - missileWeight >= distanceToTarget(mEnemy))
		return 1;
	else return 0;
}

void Mortar::setShellLevel()
{
	if (mExperience >= mShellType * 200)
	{
		mShellType++;
	}

}
int Mortar::getExp()
{
	return mExperience;
}
void Mortar::setExp(int exp)
{
	mExperience += exp;
}
void Mortar::applyDamage(Mortar* mEnemy)
{	
	if (mEnemy)
	{
		Missile missile(0, 0, 0, 0);
		int input;

		std::cout << "Distance to target: " << distanceToTarget(mEnemy) << std::endl;

		if (mIsPlayer)
		{
			while (true)
			{
				SETCMDCOLOR(RED | GREEN)
					std::cout << "Select a missile (1-3): ";
				std::cin >> input;
				switch (input)
				{
				case 1:
					missile.mShellType = 1;
					missile.mDamage = Randomize(15,20);
					missile.mWeight = 0;
					break;
				case 2:
					missile.mShellType = 2;
					missile.mDamage = Randomize(20,35);
					missile.mWeight = 1;
					break;
				case 3:
					missile.mShellType = 3;
					missile.mDamage = Randomize(45,70);
					missile.mWeight = 2;
					break;
				default:
					break;
				}
				SETCMDCOLOR(LIGHTGRAY)
					std::cout << "----------------\nShellType:	" << missile.mShellType << "\nDamage:		" << missile.mDamage << "\nWeight:		" << missile.mWeight << "\n----------------\n" << std::endl;
				std::cout << "Confirm (1) / deny (2) loading...";
				std::cin >> input;
				if (input == 1)
				{
					break;
				}
			}
		}
		else
		{
			missile.mShellType = 0;
			missile.mDamage = Randomize(10, 60);
			missile.mWeight = Randomize(0,4);

		}


		if (isEnemyInRange(mEnemy, missile.mWeight))
		{


			if ((mEnemy->mPosition[0] > mPosition[0] && mIsFacingRight) || (mEnemy->mPosition[0] < mPosition[0] && !mIsFacingRight) || !mIsPlayer)
			{
				int damage = missile.mDamage*mShellType - mEnemy->mArmour*mEnemy->mShellType;

				if (damage > 0 && mEnemy)
				{
					mEnemy->mHealth -= (damage);
					std::cout << damage << " damage dealt!\n";
				}
				else
				{
					SETCMDCOLOR(RED)
						std::cout << "Missle couldn't rend armour\n";
					SETCMDCOLOR(LIGHTGRAY)
				}
			}
			else if (mIsPlayer)
			{
				SETCMDCOLOR(RED | GREEN)
					std::cout << "Invalid command! Recheck turret alignment...\n";
				SETCMDCOLOR(LIGHTGRAY)
			}
		}
		else
		{
			SETCMDCOLOR(RED)
				std::cout << "Out of range...\n";
			SETCMDCOLOR(LIGHTGRAY)

		}
	}
	
}

Mortar* Mortar::sendScouts()
{
	int rnd = Randomize(0,4);

	if (rnd == 1)
		return new Mortar(Randomize(5, 20), Randomize(120, 280), Randomize(1, 3), Randomize(3, 8), Randomize(1, 4), 0, Randomize(35, 90), 0);
	else return 0;

}
void Mortar::displayStats()
{
	std::cout << *this;
}
int Mortar::getHealth()
{
	return mHealth;
}
void Mortar::moveMortar(int input, int* battleField)
{
	
	switch (input)
	{
	case 1:
		if (mPosition[1] > 0)
			mPosition[1] -= 1;
		else
		{
			SETCMDCOLOR(RED)
				std::cout << "Desertion impossible!\n";
			SETCMDCOLOR(LIGHTGRAY)
		}
		break;
	case 2:
		if (mPosition[1] < battleField[1]-1)
			mPosition[1] += 1;
		
		else
		{
			SETCMDCOLOR(RED)
				std::cout << "Desertion impossible!\n";
			SETCMDCOLOR(LIGHTGRAY)
		}
		break;
	case 3:
		if (mPosition[0] < battleField[0])
		{
			if (mIsFacingRight)
				mPosition[0] += 1;
			else
			{
				SETCMDCOLOR(RED)
				std::cout << "Align your mortar before movement!\n";
				SETCMDCOLOR(LIGHTGRAY)
			}
		}
		else
		{
			SETCMDCOLOR(RED)
				std::cout << "Desertion impossible!\n";
			SETCMDCOLOR(LIGHTGRAY)
		}
		break;
	case 4:
		if (mPosition[0] > 1)
		{
			if(!mIsFacingRight)
			mPosition[0] -= 1;
		else
		{
			SETCMDCOLOR(RED)
				std::cout << "Align your mortar before movement!\n";
			SETCMDCOLOR(LIGHTGRAY)
		}
		}
		else
		{
			SETCMDCOLOR(RED)
				std::cout << "Desertion impossible!\n";
			SETCMDCOLOR(LIGHTGRAY)
		}
		break;
	case 5:
		mIsFacingRight = !mIsFacingRight;
		break;
	default:
		SETCMDCOLOR(RED)
			std::cout << "Invalid input!\n";
		SETCMDCOLOR(LIGHTGRAY)
			break;

	}
}