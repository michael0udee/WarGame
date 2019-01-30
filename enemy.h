#ifndef ENEMY_H
#define ENEMY_H
#include <QSound>
#include <QTimer>
#include "object.h"

class Enemy : public Object
{
    Q_OBJECT
public:
    Enemy();

    enum Direction
    {
        MoveUp,
        MoveDown,
        MoveRight,
        MoveLeft,
    };
    int getHitPoints() const;
    int  getPeopleKilled() const;
    void setTimer(int t);
    void setSound(bool soundOn);
    void stopTimer();

    void dead(int size, QString path);
    void deleteDeadEnemy(QGraphicsPixmapItem *dead);

    void moveDirection(int direction, int step);
    void createHealthBar();

    void hitEnemy();
 
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    QRectF boundingRect() const;


public slots:
    virtual void move() = 0;

protected:
    QList<QGraphicsItem *> colliding_items;
    QPixmap healthBarPixmap;
    QPixmap spritePixmap;
    QSound *sound;
    QString soundSrc;
    QTimer *timer;
    bool soundOn;
    int peopleDead;
    int hitPoints;
    int offset;
    int coeff_t;

};

class Tank : public Enemy
{
    Q_OBJECT
public:
    Tank();
    ~Tank();

public slots:
    void move();

};

class Soldier : public Enemy
{
    Q_OBJECT
public:
    Soldier();
    ~Soldier();

public slots:
    void move();

};

class Junkers : public Enemy
{
    Q_OBJECT
public:
    Junkers();
    ~Junkers();

public slots:
    void move();

};

#endif // ENEMY_H
