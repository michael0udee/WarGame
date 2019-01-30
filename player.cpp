#include "player.h"

Player::Player()
{
    setSprite(":/images/images/player.png", 50, 50);
    type = PPSz;
}

QImage Player::getWeaponImage()
{
    switch(type)
    {
        case PPSz : weaponImage.load(":/images/images/ppsz_gun.gif");
                 weaponImage = weaponImage.scaled(90, 90, Qt::KeepAspectRatio); break;
        case Grenades : weaponImage.load(":/images/images/grenade.png");
                 weaponImage = weaponImage.scaled(30, 30, Qt::KeepAspectRatio); break;
        case MolotovCocktails : weaponImage.load(":/images/images/molotov-cocktail.png");
                 weaponImage = weaponImage.scaled(30, 30, Qt::KeepAspectRatio); break;
    }
    return weaponImage;
}

void Player::changeWeaponType()
{
    type++;
    if(type == COUNT) type = PPSz;
}

void Player::chooseWeapon()
{
    switch(type)
    {
        case PPSz : wFire = new PPSzBullet();  break;
        case Grenades : wFire = new Grenade(); break;
        case MolotovCocktails : wFire = new MolotovCocktail(); break;
    }
}

WeaponFire *Player::getCurrentFire()
{
    return wFire;
}

void Player::fire(QPoint targetPos)
{
    wFire->setPosition(QPoint(position.x(),position.y()));
    wFire->setTargetPosition(targetPos);
    wFire->setRotation(rotation() + 15); //+15
    wFire->exec();
}
