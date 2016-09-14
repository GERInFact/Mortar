#include "mortar.h"


Mortar::Mortar(int armour, int health, int shellType, int range, int blastRadius, int damage, int reloadTime, int exp, bool isPlayer) : mArmour(armour),mHealth(health)
				,mShellType(shellType), mRange(range),mBlastRadius(blastRadius),mDamageDealt(damage),mReloadTime(reloadTime), mExperience(exp), mIsPlayer(isPlayer){}

Mortar::Mortar() {}

std::ostream& operator << (std::ostream& out, Mortar mortar)
{
	out << "------------------------\n";
	out << "Position:	" << mortar.mPosition[0] << " | " << mortar.mPosition[1] << std::endl;
	out << "ShellType:	" << mortar.mShellType << std::endl;
	out << "Health:		"<<mortar.mHealth<<std::endl;
	out << "Armour:		"<<mortar.mArmour<<std::endl;
	out << "Range:		"<<mortar.mRange<<std::endl;
	out << "BlastRadius:	"<<mortar.mBlastRadius<<std::endl;
	out << "BaseDamage:	"<<mortar.mDamageDealt<<std::endl;
	out << "ReloadTime:	"<<mortar.mReloadTime<<std::endl;
	out << "Experience:	"<<mortar.mExperience<<std::endl;
	out << "------------------------\n";

	return out;
}
int Mortar::distanceToTarget(Mortar* target)
{
	return sqrt((target->mPosition[0] - mPosition[0])*(target->mPosition[0] - mPosition[0]) + (target->mPosition[1] - mPosition[1]) * (target->mPosition[1] - mPosition[1]));
}
bool Mortar::isEnemyInRange(Mortar* mEnemy)
{	 
	if (mRange + mBlastRadius >= distanceToTarget(mEnemy))
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
	std::cout << "Distance to target: " << distanceToTarget(mEnemy)<<std::endl;

	if (isEnemyInRange(mEnemy))
	{
		if ((mEnemy->mPosition[0] > mPosition[0] && mIsFacingRight) || (mEnemy->mPosition[0] < mPosition[0] && !mIsFacingRight) || !mIsPlayer)
		{
			int damage = mDamageDealt*mShellType - mEnemy->mArmour*mEnemy->mShellType;

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
			SETCMDCOLOR(RED|GREEN)			
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

Mortar* Mortar::sendScouts()
{
	int rnd = rand() % 4;

	if(rnd == 1)
	return new Mortar(5,100+rand()%(300-100),1+rand()%(4-1),1+rand()%4-1,1,5+rand()%(60-5),3, 30 + rand() % (101 - 30),0);
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
		if (mPosition[1] > 1)
			mPosition[1] -= 1;
		else
		{
			SETCMDCOLOR(RED)
				std::cout << "Desertion impossible!\n";
			SETCMDCOLOR(LIGHTGRAY)
		}
		break;
	case 2:
		if (mPosition[1] < battleField[1])
			mPosition[1] += 1;
		
		else
		{
			SETCMDCOLOR(RED)
				std::cout << "Desertion impossible!\n";
			SETCMDCOLOR(LIGHTGRAY)
		}
		break;
	case 3:
		if (mPosition[0] < battleField[0]-1)
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