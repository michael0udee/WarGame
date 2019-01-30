#ifndef STATISTICS_H
#define STATISTICS_H

#include <QGraphicsTextItem>

class Statistics : public QGraphicsTextItem
{
public:
    Statistics(QGraphicsTextItem * parent = nullptr);
    int getScore() const;
    int getPeopleAlive() const;
    void addPoints(int points);
    void peopleKilled(int dead);
    void updateText();

private:
    int score;
    int peopleAlive;
};

#endif // STATISTICS_H
