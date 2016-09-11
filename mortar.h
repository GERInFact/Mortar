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
	friend std::ostream& operator << (std::ostream& out, Mortar mortar);
	Mortar(int armour, int health, int shellType, int range, int blastRadius, int damage, int reloadTime, int exp);
	Mortar();
	void displayStats();
	void applyDamage(Mortar* mEnemy);
	unsigned int mPosition[2] = {0,0};
	int getHealth();
	void setExp(int exp);
	int getExp();
	void setShellLevel();
	void moveMortar(int input);
	Mortar* sendScouts();
private:
	int mHealth;
	int mArmour;
	int mShellType;
	int mRange;
	int mBlastRadius;
	int mDamageDealt;
	int mReloadTime;
	int mExperience;


};


#endif