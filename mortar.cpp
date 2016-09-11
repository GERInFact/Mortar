#include "mortar.h"


Mortar::Mortar(int armour, int health, int shellType, int range, int blastRadius, int damage, int reloadTime, int exp) : mArmour(armour),mHealth(health)
				,mShellType(shellType), mRange(range),mBlastRadius(blastRadius),mDamageDealt(damage),mReloadTime(reloadTime), mExperience(exp){}

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


void Mortar::setShellLevel()
{
	if (mExperience == mShellType * 300)
		mShellType++;

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
	int damage = mDamageDealt*mShellType - mEnemy->mArmour*mEnemy->mShellType;
	
	if (damage > 0 && mEnemy)
	{
		mEnemy->mHealth -= (damage);
		std::cout << damage << " damage dealt!\n";
	}
	else
	{
		SETCMDCOLOR(RED)
		std::cout << "Missle couldn't penetrate enemy's armour\n";
		SETCMDCOLOR(LIGHTGRAY)
	}
}

Mortar* Mortar::sendScouts()
{
	int rnd = rand() % 4;

	if(rnd == 1)
	return new Mortar(5,100,1+rand()%(4-1),3,1,5+rand()%(60-5),3, 30 + rand() % (101 - 30));
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
void Mortar::moveMortar(int input)
{
	switch (input)
	{
	case 1:
		mPosition[1] += 1;
		break;
	case 2:
		if (mPosition[1] > 0)
			mPosition[1] -= 1;
		else
		{
			SETCMDCOLOR(RED)
				std::cout << "Desertion will be punished!\n";
			SETCMDCOLOR(LIGHTGRAY)
		}
		break;
	case 3:
		mPosition[0] += 1;
		break;
	case 4:
		if (mPosition[0]>0)
		mPosition[0] -= 1;
		else
		{
			SETCMDCOLOR(RED)
				std::cout << "Desertion will be punished!\n";
			SETCMDCOLOR(LIGHTGRAY)
		}
		break;
	default:
		SETCMDCOLOR(RED)
			std::cout << "Invalid input!\n";
		SETCMDCOLOR(LIGHTGRAY)
			break;

	}
}