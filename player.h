#ifndef PLAYER_H
#define PLAYER_H

#include "object.h"
#include "weapon.h"

class Player : public Object
{
public:
    Player();

    enum Weapon
    {
        PPSz,
        Grenades,
        MolotovCocktails,
        COUNT
    };

    WeaponFire *getCurrentFire();
    QImage getWeaponImage();
    void changeWeaponType();
    void chooseWeapon();
    void fire(QPoint targetPos);

private:
    QImage weaponImage;
    WeaponFire *wFire;
    int type;
};

#endif // PLAYER_H
