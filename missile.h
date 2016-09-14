#ifndef MISSILE_H
#define MISSILE_H

struct Missile
{

	Missile() {}
	Missile(int shellType, int damage, int weight, int amount) : mShellType(shellType), mDamage(damage), mWeight(weight){}
	int mShellType;
	int mDamage;
	int mWeight;
	
	
};


#endif