#include "statistics.h"
#include <QFont>

Statistics::Statistics(QGraphicsTextItem *parent) : QGraphicsTextItem(parent)
{
    setZValue(4);

    // initialize the score to 0 and people to 20
    score = 0;
    peopleAlive = 20;

    // draw the score and number of people alive
    setDefaultTextColor(Qt::yellow);
    QFont font;
    font.setStretch(125);
    font.setBold(1);
    font.setFamily("Segoe Marker");
    font.setPointSize(18);
    setFont(font);

    updateText(); // Score: 0, Alive: 20
}

int Statistics::getScore() const
{
    return score;
}

int Statistics::getPeopleAlive() const
{
    return peopleAlive;
}

void Statistics::addPoints(int points)
{
    score += points;
    updateText(); // Score: +points
}

void Statistics::peopleKilled(int dead)
{
    peopleAlive -= dead;
    updateText(); // People alive: -dead
}

void Statistics::updateText()
{
    setPlainText(QString("Points: ") + QString::number(score) +
                 QString("\t Civilians: ") + QString::number(peopleAlive) + QString("\t Weapon: "));
}
