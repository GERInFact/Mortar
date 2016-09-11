#ifndef MORTAR_H
#define MORTAR_H
#include <iostream>

#include <windows.h>
#define RED 12
#define LIGHTGRAY 7
#define GREEN 10
#define TURQUOISE 11

#define SETCMDCOLOR(ColorValue) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ColorValue);

class Mortar
{
public:
	Mortar(int armour, int health, int shellType, int range, int blastRadius, int damage, int reloadTime);
	Mortar();
	void displayStats();
	void applyDamage(Mortar* mEnemy);
	int mPosition[2] = {0,0};
	int getHealth();
	Mortar* sendScouts();
private:
	int mHealth;
	int mArmour;
	int mShellType;
	int mRange;
	int mBlastRadius;
	int mDamageDealt;
	int mReloadTime;


};


#endif