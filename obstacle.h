#ifndef OBSTACLE_H
#define OBSTACLE_H
#include <QPoint>
#include "object.h"

class Obstacle : public Object
{
public:
    Obstacle();
    virtual ~Obstacle(){}

};

class Tree : public Obstacle
{
public:
    Tree();
};

class Rock : public Obstacle
{
public:
    Rock();
};
#endif // OBSTACLE_H
