#ifndef __ATTRIBUTES_
#define __ATTRIBUTES_

/*********************//*
 * @author Original Development Team
 * @author Jon McKee
 * @brief these are the default stats for a tank object.
 * All values default to 0 but can be set by users or the
 * game map via constructor
 *
 ***********************/
struct attributes
{
  int tankHealth = 0; /*!<Amount of health the tank has*/
	int tankDamage = 0;/*!<Amount of Damage the tank has*/
	int tankAP = 0;/*!<Amount of AP points the tank has*/
	int tankShots = 0;/*!<Amount of ammo the tank has LEFT*/
	int tankAmmo = 0;/*!<Amount of ammo the tank has TOTAL*/
	int tankRadar = 0;/*!<The radar of the tank*/
	int tankRange = 0;/*!<The range the tank can shoot*/
	attributes ( int tH = 0, int tD = 0, int tR = 0, int tS = 0, int tA = 0, int tV = 0, int tRa = 0 )
	{
		tankHealth = tH;
		tankDamage = tD;
		tankAP = tR;
		tankShots = tS;
		tankAmmo = tA;
		tankRadar = tV;
		tankRange = tRa;
	}

};

#endif
