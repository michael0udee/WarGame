#ifndef SCENEGUI_H
#define SCENEGUI_H

#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QMediaPlayer>
#include <QWidget>
#include <QTimer>
#include <QImage>
#include <QList>
#include "obstacle.h"
#include "statistics.h"
#include "playerinfo.h"
#include "player.h"
#include "enemy.h"

class sceneGUI : public QGraphicsView
{
    Q_OBJECT

public:
    explicit sceneGUI(QWidget *parent = 0);
    ~sceneGUI();

    void setEnemyTimer(int t);

    void startGameTimer();
    void stopGameTimer();
    void setMusic(bool musicOn);
    void setSoundEffect(bool soundOn);
    void setObstacle(Obstacle *obs);
    void setEnemy(Enemy *e, int randomEnemyPos);
    void setEnemyLive(int live);
    void setPlayerInfoPointer(playerInfo *pt);
    void addObjectForDelete(Object *p_object);
    void addObjectToList(Object *p_object);

public slots:

    void gameUpdate();
    void createEnemy();

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void closeEvent(QCloseEvent *event);

private:
    QGraphicsScene *scene;
    QMediaPlayer * music;
    QGraphicsPixmapItem *weaponItem;
    Statistics *stats;
    playerInfo *playerInf;
    Player *player;
    QList<Object *> sceneObjects;
    QList<Object *> objectsforDelete;
    QList<QGraphicsItem *> colliding_items;
    QImage playerImage;
    QTimer *gameTimer, *enemyCreateTimer;
    int randomEnemy, randomEnemyPos;
    int enemyLive;
    int enemyTimer;
    QPoint targetPos;
    int wScene, hScene;
    double angle;
    bool musicOn;
    bool soundOn;

};

#endif // SCENEGUI_H
