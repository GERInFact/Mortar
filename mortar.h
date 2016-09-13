#ifndef MORTAR_H
#define MORTAR_H
#include <iostream>

#include <windows.h>
#define RED 12
#define GREEN 10
#define BLUE 9
#define LIGHTGRAY 7
#define TURQUOISE 11


#define SETCMDCOLOR(ColorValue) SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ColorValue);

class Mortar
{
public:
	friend std::ostream& operator << (std::ostream& out, Mortar mortar);
	Mortar(int armour, int health, int shellType, int range, int blastRadius, int damage, int reloadTime, int exp, bool isPlayer);
	Mortar();
	int getHealth();
	void setShellLevel();
	bool isEnemyInRange(Mortar* enemy);
	int distanceToTarget(Mortar* target);
	void applyDamage(Mortar* mEnemy);
	int getExp();
	void setExp(int exp);
	void displayStats();
	void moveMortar(int input, int* battleField);
	Mortar* sendScouts();

	int mPosition[2] = { 1 + rand() % (10 - 1),	1 + rand() % (10 - 1) };
	bool mIsFacingRight = 1;
	bool mIsPlayer;
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