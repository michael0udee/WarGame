#ifndef WEAPON_H
#define WEAPON_H
#include <QSound>
#include <QPainter>
#include <QRect>
#include <QPoint>
#include <QObject>
#include "object.h"

class WeaponFire : public Object
{
    Q_OBJECT
public:
    WeaponFire();
    ~WeaponFire();

    void setTargetPosition(QPoint targetPos);
    void setSound(bool soundOn);
    void setBoom();
    void stopTimer();
    void move();
    void exec();

public slots:
    void boomFrame();

protected:
    QString soundSrc;
    QTimer * timer;
    QPoint targetPos;
    QPixmap boomImage;
    QPoint currentFrame;
    QTimer *boomTimer;
    int time_coeff;

    // pxy - side pixels, m - rows/columns
    int pxy, m;

};

class PPSzBullet : public WeaponFire
{
    Q_OBJECT
public:
    PPSzBullet();

public slots:
    void updateBullet();

};

class Grenade : public WeaponFire
{
    Q_OBJECT
public:
    Grenade();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

public slots:
    void updateGrenade();

};

class MolotovCocktail : public WeaponFire
{
    Q_OBJECT
public:
    MolotovCocktail();
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

public slots:
    void updateMCocktail();

};

#endif // WEAPON_H
