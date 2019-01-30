#include "weapon.h"
#include "scenegui.h"
#include <QtCore/QtMath>
#include <QTimer>
#include <QDebug>

WeaponFire::WeaponFire()
{
    timer = new QTimer();
}

WeaponFire::~WeaponFire()
{
    qDebug() << "Delete fire!";
}

void WeaponFire::setTargetPosition(QPoint targetPos)
{
    this->targetPos = targetPos;
}

void WeaponFire::setSound(bool soundOn)
{
    if(soundOn)
    {
        // play sound
        QSound::play(soundSrc);
    }
}

void WeaponFire::boomFrame()
{
    currentFrame.rx() += pxy;

    if(currentFrame.x() >= m*pxy && currentFrame.y() >= m*pxy)
    {
        boomTimer->stop();
        this->setObjectToDelete();
        return;
    }
    if (currentFrame.x() >= m*pxy ) {
        currentFrame.rx() = 0;
        currentFrame.ry() += pxy;
    }
    this->update(-pxy/2,-pxy/2,pxy,pxy);
}

void WeaponFire::setBoom()
{
    objectLive = 0;

    timer->stop();
    boomTimer = new QTimer();
    connect(boomTimer,SIGNAL(timeout()),this,SLOT(boomFrame()));
    boomTimer->start(20);
}

void WeaponFire::stopTimer()
{
    timer->stop();
}

void WeaponFire::move()
{
    int STEP_SIZE = 30;
    double theta = rotation()-90; // -90
    double dy = STEP_SIZE * qSin(qDegreesToRadians(theta));
    double dx = STEP_SIZE * qCos(qDegreesToRadians(theta));

    // move the weapon fire
    position = QPoint(position.x() + dx, position.y() + dy);
    setPosition(position);
    //qDebug() << "WeaponFire pos: " << position;
}

void WeaponFire::exec()
{
    timer->start(time_coeff);
}

//----------PPSzBullet-----------------

PPSzBullet::PPSzBullet()
{
    setSprite(":/images/images/bullet.png", 10, 10);
    soundSrc = ":/music/music/PPSzBullet.wav";
    time_coeff = 50;

    connect(timer,SIGNAL(timeout()),this,SLOT(updateBullet()));
}

void PPSzBullet::updateBullet()
{
    move();
}

//----------GRENADE----------------

Grenade::Grenade()
{
    setSprite(":/images/images/grenade.png", 10, 10);
    boomImage = QPixmap(":/images/images/grenadeBoom.png");
    soundSrc = ":/music/music/grenade.wav";
    time_coeff = 70;
    objectLive = 30;
    pxy = 128, m = 4;
    connect(timer,SIGNAL(timeout()),this,SLOT(updateGrenade()));
    currentFrame = QPoint(0,0);
}

void Grenade::updateGrenade()
{
    int d = sqrt(pow(x()-targetPos.x(),2)+pow(y()-targetPos.y(),2));
    if(y() > scene()->height()/3 && d > 80) move();
    else objectLive--;

    if(this->getLive() <= 0)
    {
        setBoom();
        setPixmap(QPixmap(pxy,pxy));
    }
}

void Grenade::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(this->getLive() <= 0)
    {
        painter->drawPixmap(-pxy/2, -pxy/2, boomImage, currentFrame.x(), currentFrame.y(), pxy, pxy);
    }
    else
        painter->drawImage(0, 0, sprite, 0, 0, sprite.width(), sprite.height());

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF Grenade::boundingRect() const
{
    return QRectF(-pxy/2, -pxy/2, pxy, pxy);
}

//--------MOLOTOV-COCKTAIL--------


MolotovCocktail::MolotovCocktail()
{
    setSprite(":/images/images/molotov-cocktail.png", 20, 20);
    boomImage = QPixmap(":/images/images/mCocktailBoom.png");
    soundSrc = ":/music/music/molotovCocktail.wav";
    time_coeff = 80;
    objectLive = 2;
    pxy = 128, m = 8;
    connect(timer,SIGNAL(timeout()),this,SLOT(updateMCocktail()));
    currentFrame = QPoint(0,0);
}

void MolotovCocktail::updateMCocktail()
{
    int d = sqrt(pow(x()-targetPos.x(),2)+pow(y()-targetPos.y(),2));
    if(y() > scene()->height()/2 && d > 60) move();
    else objectLive--;

    if(this->getLive() <= 0)
        setBoom();
}

void MolotovCocktail::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(this->getLive() <= 0){
        painter->drawPixmap(-pxy/2, -pxy/2, boomImage, currentFrame.x(), currentFrame.y(), pxy, pxy);
    }
    else
        painter->drawImage(0, 0, sprite, 0, 0, sprite.width(), sprite.height());

    Q_UNUSED(option);
    Q_UNUSED(widget);
}

QRectF MolotovCocktail::boundingRect() const
{
    return QRectF(-pxy/2, -pxy/2, pxy, pxy);
}
