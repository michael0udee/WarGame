#include "enemy.h"
#include "scenegui.h"
#include <unistd.h>
#include <typeinfo>
#include <QPixmap>
#include <QBrush>
#include <QDebug>
#include <QFuture>
#include <QtConcurrent/QtConcurrent>

Enemy::Enemy()
{
    offset = -14;
    timer = new QTimer();
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
}

int Enemy::getHitPoints() const
{
    return hitPoints;
}

int Enemy::getPeopleKilled() const
{
    return peopleDead;
}
// Change the position of the enemy with given direction and step
void Enemy::moveDirection(int direction, int step)
{
    switch(direction)
    {
        case Direction::MoveUp : setPosition(QPoint(pos().x(), pos().y()-step)); break;
        case Direction::MoveRight :setPosition(QPoint(pos().x()+step, pos().y())); break;
        case Direction::MoveDown : setPosition(QPoint(pos().x(), pos().y()+step)); break;
        case Direction::MoveLeft : setPosition(QPoint(pos().x()-step, pos().y())); break;
    }
}
// Create the health bar
void Enemy::createHealthBar()
{
    QPixmap healthBarPix(2+6*objectLive,4);
    QPainter painter(&healthBarPix);
    QRect healthBar;
    healthBar.setSize(QSize(2+6*objectLive,4));
    QBrush brush(Qt::red);
    painter.setPen(QPen(Qt::black,2));
    painter.fillRect(healthBar, brush);
    painter.drawRect(healthBar);
    painter.end();

    healthBarPixmap = healthBarPix;
    //QImage hBar = pix.toImage();
    spritePixmap = QPixmap::fromImage(sprite);
    //QImage result(sprite.width(), sprite.height()+hBar.height()+10, QImage::Format_ARGB32);
//    QPixmap result(sprite.width(), sprite.height()+healthBarPixmap.height()+10);
//    QPainter painter2(&result);
//    painter2.drawPixmap(0, 0, healthBarPixmap);
//    painter2.drawPixmap(0, healthBarPixmap.height()+10, spritePixmap);
//    painter2.end();
//    setPixmap(result);
}
// Change the enemy status after getting shot
void Enemy::hitEnemy()
{
    objectLive--;
    createHealthBar();
}
// Paint the health bar
void Enemy::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(0, offset, healthBarPixmap);
    painter->drawPixmap(0, healthBarPixmap.height()+10+offset, spritePixmap);

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF Enemy::boundingRect() const
{
    return QRectF(0, offset, sprite.width(), healthBarPixmap.height()+sprite.height()+10);
}

void Enemy::setTimer(int t)
{
    // start the timer
    timer->start((11-t)*coeff_t);
}

void Enemy::setSound(bool soundOn)
{
    this->soundOn = soundOn;
    if(soundOn)
    {
        // play sound
        sound = new QSound(soundSrc);
        sound->play();
    }
}

void Enemy::stopTimer()
{
    timer->stop();
}
// Drawing dead enemy
void Enemy::dead(int size, QString path)
{
    QImage enemyIm(path);
    enemyIm = enemyIm.scaled(size,size, Qt::KeepAspectRatio);
    QGraphicsPixmapItem *dead = scene()->addPixmap(QPixmap::fromImage(enemyIm));
    dead->setPos(pos());

    QFuture<void> func = QtConcurrent::run(this, &Enemy::deleteDeadEnemy, dead);
}
// Removing dead enemy
void Enemy::deleteDeadEnemy(QGraphicsPixmapItem *dead)
{
    sleep(1);
    delete dead;
}

//-----------TANK---------------

Tank::Tank() : Enemy()
{
    qDebug() << "Tank created!";
    setSprite(":/images/images/nazi_tank.png",50,23);
    setZValue(1);
    peopleDead = 2;
    hitPoints = 10;
    size.setWidth(50);
    size.setHeight(23);
    coeff_t = 55;
}

Tank::~Tank()
{
    dead(50, ":/images/images/nazi_tank_dead.png");
}

void Tank::move()
{
    colliding_items = collidingItems();

    for (int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        if (typeid(*(colliding_items[i])) == typeid(Rock))
            moveDirection(Direction::MoveUp, 10);
        else moveDirection(Direction::MoveRight, 5);
    }

}

//-----------SOLDIER---------------

Soldier::Soldier() : Enemy()
{
    qDebug() << "Soldier created!";
    setSprite(":/images/images/soldier.png",20,20);
    setZValue(1);
    peopleDead = 1;
    hitPoints = 5;
    size.setWidth(20);
    size.setHeight(20);
    coeff_t = 50;
}

Soldier::~Soldier()
{
    dead(20, ":/images/images/deadSoldier.png");
}

void Soldier::move()
{
    colliding_items = collidingItems();

    for (int i = 0, n = colliding_items.size(); i < n; ++i)
    {
        if (typeid(*(colliding_items[i])) == typeid(Rock))
            moveDirection(Direction::MoveUp, 8);
        else moveDirection(Direction::MoveRight, 5);
    }

}

//-----------JUNKERS---------------

Junkers::Junkers() : Enemy()
{
    qDebug() << "Junkers created!";
    setSprite(":/images/images/junkers.png",67,90);
    setZValue(3);
    soundSrc = ":/music/music/junkers.wav";
    peopleDead = 3;
    hitPoints = 20;
    size.setWidth(67);
    size.setHeight(90);
    coeff_t = 10;
}

Junkers::~Junkers()
{
    dead(90, ":/images/images/junkers_dead.png");
    if(soundOn) delete sound;
}

void Junkers::move()
{
    moveDirection(Direction::MoveRight, 5);
}
