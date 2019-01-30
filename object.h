#ifndef OBJECT_H
#define OBJECT_H

#include <QGraphicsPixmapItem>
#include <QGraphicsItem>
#include <QObject>

class Object : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    explicit Object(QGraphicsItem *parent = nullptr);
     ~Object();
    QImage getSprite() const;
    QPoint getPosition() const;
    QSize getSize() const;

    void setLive(int live);
    void setSprite(QString imagePath, int w, int h);
    void setPosition(QPoint pos);

    void setObjectToDelete();
    bool objectToDelete();
    int getLive() const;

protected:
    QImage sprite;
    QPoint position;
    QSize size;
    bool toDelete;
    int objectLive;

};

#endif // OBJECT_H
