#include "object.h"
#include <QDebug>

Object::Object(QGraphicsItem *parent) : QObject(), QGraphicsPixmapItem(parent)
{
    toDelete = false;
}

Object::~Object()
{
    qDebug() << "Delete object!";
}

QImage Object::getSprite() const
{
    return sprite;
}

QPoint Object::getPosition() const
{
    return position;
}

QSize Object::getSize() const
{
    return size;
}

void Object::setLive(int live)
{
    objectLive = live;
}

void Object::setSprite(QString imagePath,int w, int h)
{
    sprite.load(imagePath);
    sprite = sprite.scaled(w, h, Qt::KeepAspectRatio);
    setPixmap(QPixmap::fromImage(sprite));
}

void Object::setPosition(QPoint pos)
{
    position = pos;
    setPos(pos.x(), pos.y());
}
// set object to delete
void Object::setObjectToDelete()
{
    toDelete = true;
}
// return logical value if object is about to delete
bool Object::objectToDelete()
{
    return toDelete;
}

int Object::getLive() const
{
    return objectLive;
}
