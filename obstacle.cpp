#include "obstacle.h"

Obstacle::Obstacle()
{
    size = QSize(50,50);
}

Tree::Tree()
{
    setSprite(":/images/images/tree.png", size.width(), size.height());
    setZValue(2);
}

Rock::Rock()
{
    setSprite(":/images/images/rock.png", size.width(), size.height());
}
