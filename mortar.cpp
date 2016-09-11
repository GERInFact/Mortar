#include "mortar.h"


Mortar::Mortar(int armour, int health, int shellType, int range, int blastRadius, int damage, int reloadTime) : mArmour(armour),mHealth(health)
				,mShellType(shellType), mRange(range),mBlastRadius(blastRadius),mDamageDealt(damage),mReloadTime(reloadTime){}

Mortar::Mortar() {}


void Mortar::applyDamage(Mortar* mEnemy)
{	
	int damage = mDamageDealt - mEnemy->mArmour;	
	
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
	return new Mortar(5,100,1,3,1,200,3);
	else return 0;

}
void Mortar::displayStats()
{
	std::cout << "-----------------------------\n"<<"Health: " << mHealth << "\nArmour: " << mArmour << "\nDamage: " 
		<< mDamageDealt << "\nPosition: " << mPosition[0] << " | " << mPosition[1] << std::endl << std::endl;
}
int Mortar::getHealth()
{
	return mHealth;
}