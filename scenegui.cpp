#include "scenegui.h"
#include <qt5/QtCore/QtMath>
#include <QMediaPlaylist>
#include <QMessageBox>
#include <QDebug>
#include <QTime>
#include <typeinfo>

sceneGUI::sceneGUI(QWidget *parent) : QGraphicsView(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);
    scene = new QGraphicsScene(this);

    // draw background
    QImage image(":/images/images/background.png");
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    setFixedSize(image.width()+2,image.height()+2);
    scene->setSceneRect(0,0,image.width(),image.height());
    scene->addItem(item);
    setScene(scene);

    // draw tower
    QImage towerImage(":/images/images/tower.png");
    QGraphicsPixmapItem* towerItem = new QGraphicsPixmapItem(QPixmap::fromImage(towerImage));
    scene->addItem(towerItem);
    towerItem->setPos((width()/4)+40,height()-72);

    // scene width and height
    wScene = scene->width();
    hScene = scene->height();

    // set random values
    QTime time = QTime::currentTime();
    qsrand((uint)time.msec());

    // set obstacles
    for(int i =0; i < 5; ++i)
    {
        Obstacle *pTree = new Tree();
        setObstacle(pTree);
        Obstacle *pRock = new Rock();
        setObstacle(pRock);
    }

    // create the stats
    stats = new Statistics();
    scene->addItem(stats);

    // create player
    player = new Player();
    player->setPosition(QPoint(scene->width()/2, scene->height()-60));
    qDebug() << "Scene width:" << scene->width();
    qDebug() << "Scene height:" << scene->height();
    scene->addItem(player);
    playerImage = player->getSprite();

    // weapon item
    weaponItem = new QGraphicsPixmapItem(QPixmap::fromImage(player->getWeaponImage()));
    scene->addItem(weaponItem);
    weaponItem->setPos(scene->width()-100, 40);

    // timers
    gameTimer = new QTimer();
    connect(gameTimer,SIGNAL(timeout()),this,SLOT(gameUpdate()));

    enemyCreateTimer = new QTimer();
    connect(enemyCreateTimer,SIGNAL(timeout()),this,SLOT(createEnemy()));

}

sceneGUI::~sceneGUI()
{
    qDeleteAll(sceneObjects);
    sceneObjects.clear();
    qDeleteAll(items());
    items().clear();
}

void sceneGUI::setEnemyTimer(int t)
{
    enemyTimer = t;
}

void sceneGUI::startGameTimer()
{
    gameTimer->start(45);
    enemyCreateTimer->start(2500);

    for (int i = 0; i < sceneObjects.size(); i++)
    {
            Enemy *p_Enemy = qobject_cast<Enemy *>(sceneObjects[i]);
            if(p_Enemy) p_Enemy->setTimer(enemyTimer);
    }
}

void sceneGUI::stopGameTimer()
{
    gameTimer->stop();
    enemyCreateTimer->stop();

    for (int i = 0; i < sceneObjects.size(); i++)
    {
            Enemy *p_Enemy = qobject_cast<Enemy *>(sceneObjects[i]);
            if(p_Enemy) p_Enemy->stopTimer();
    }
}

void sceneGUI::setEnemy(Enemy *e, int randomEnemyPos)
{
    e->setPosition(QPoint(0, randomEnemyPos));
    e->setTimer(enemyTimer);
    e->setLive(enemyLive);
    e->createHealthBar();
    scene->addItem(e);
    addObjectToList(e);
}

void sceneGUI::setEnemyLive(int live)
{
    enemyLive = live;
}

void sceneGUI::setPlayerInfoPointer(playerInfo *pt)
{
    playerInf = new playerInfo();
    playerInf = pt;
}

void sceneGUI::createEnemy()
{
    int enemyRange = (hScene)-50;
    randomEnemy = rand() % 100;
    randomEnemyPos = (rand() % enemyRange/2) + enemyRange/3;

    // set random type of enemy
    if (randomEnemy < 30)
    {
        Enemy *pTank = new Tank();
        setEnemy(pTank, randomEnemyPos);
    }
    else if(randomEnemy > 40)
    {
        Enemy *pSoldier = new Soldier();
        setEnemy(pSoldier, randomEnemyPos);
    }
    else
    {
        Enemy *pJunkers = new Junkers();
        pJunkers->setSound(soundOn);
        setEnemy(pJunkers, randomEnemyPos);
    }
}

void sceneGUI::addObjectForDelete(Object *p_object)
{
    objectsforDelete << p_object;
}

void sceneGUI::addObjectToList(Object *p_object)
{
    sceneObjects << p_object;
}

void sceneGUI::setMusic(bool musicOn)
{
    this->musicOn = musicOn;
    if(musicOn)
    {
        // play background sound
        QMediaPlaylist *playlist = new QMediaPlaylist();
        playlist->addMedia(QUrl("qrc:/music/music/background_music.mp3"));
        playlist->setPlaybackMode(QMediaPlaylist::Loop);
        music = new QMediaPlayer();
        music->setPlaylist(playlist);
        music->play();
    }
}

void sceneGUI::setSoundEffect(bool soundOn)
{
    this->soundOn = soundOn;
}

void sceneGUI::setObstacle(Obstacle *obs)
{
    int random_pos_x = qrand() % hScene;
    int random_pos_y = qrand() % wScene;
    obs->setPosition(QPoint(random_pos_x, random_pos_y));
    scene->addItem(obs);
    addObjectToList(obs);
}


void sceneGUI::gameUpdate()
{
    for (int i = 0; i < sceneObjects.size(); i++)
    {
        if(sceneObjects[i]->pos().x() > wScene)
        {
            Enemy *p_Enemy = qobject_cast<Enemy *>(sceneObjects[i]);
            if(p_Enemy)
            {
                // destroy enemy when it goes out of the screen and decrease the number of people alive
                stats->peopleKilled(p_Enemy->getPeopleKilled());
            }
            sceneObjects[i]->setObjectToDelete();
            continue;
        }

        WeaponFire *p_wFire = qobject_cast<WeaponFire *>(sceneObjects[i]);
        if(p_wFire)
        {
            // destroy weapon fire when it goes out of the screen
            if(p_wFire->pos().x() < 0 || p_wFire->pos().y() < 0 || p_wFire->pos().y() > hScene || p_wFire->pos().x() > wScene)
            {
                sceneObjects[i]->setObjectToDelete();
                continue;
            }

            // delete colliding objects with fires
            colliding_items = scene->collidingItems(p_wFire);
            //qDebug() << "Colliding items size:" << colliding_items.size();
            PPSzBullet *p_ppsz = qobject_cast<PPSzBullet *>(sceneObjects[i]);
            MolotovCocktail *p_mc = qobject_cast<MolotovCocktail *>(sceneObjects[i]);
            Grenade *p_grenade = qobject_cast<Grenade *>(sceneObjects[i]);

            for (int it = 0; it < colliding_items.size(); ++it)
            {
                if (typeid(*(colliding_items[it])) == typeid(Tank))
                {
                    Enemy *p_enemy = dynamic_cast<Enemy *>(colliding_items[it]);

                    if(!p_grenade) p_enemy->hitEnemy();
                    else if(p_grenade->getLive() <= 0) p_enemy->hitEnemy();
                    if(p_ppsz) p_ppsz->setObjectToDelete();
                    if(p_mc) p_mc->setBoom();

                    if(p_enemy->getLive() <= 0)
                    {
                        p_enemy->setObjectToDelete();
                        stats->addPoints(10);
                    }
                    qDebug() << "Tank fired!";
                }
                if (typeid(*(colliding_items[it])) == typeid(Soldier))
                {
                    Enemy *p_enemy = dynamic_cast<Enemy *>(colliding_items[it]);

                    if(!p_grenade) p_enemy->hitEnemy();
                    else if(p_grenade->getLive() <= 0) p_enemy->hitEnemy();
                    if(p_ppsz) p_ppsz->setObjectToDelete();
                    if(p_mc) p_mc->setBoom();

                    if(p_enemy->getLive() <= 0)
                    {
                        p_enemy->setObjectToDelete();
                        stats->addPoints(5);
                    }
                    qDebug() << "Soldier fired!";
                }
                if (typeid(*(colliding_items[it])) == typeid(Junkers))
                {
                    Enemy *p_enemy = dynamic_cast<Enemy *>(colliding_items[it]);

                    if(p_ppsz)
                    {
                        sceneObjects[i]->setObjectToDelete();
                        p_enemy->hitEnemy();
                        if(p_enemy->getLive() <= 0)
                        {
                            p_enemy->setObjectToDelete();
                            stats->addPoints(20);
                        }
                    }
                }
                if (typeid(*(colliding_items[it])) == typeid(Rock))
                {
                    if(p_ppsz)
                        sceneObjects[i]->setObjectToDelete();
                    else sceneObjects[i]->setLive(0);
                }
            }
        }
    }
    // move object selected to delete to another list
    for (int i = sceneObjects.size()-1; i >= 0; i--)
    {
        if(sceneObjects[i]->objectToDelete())
        {
            addObjectForDelete(sceneObjects[i]);
            sceneObjects.removeAt(i);
        }
    }
    // delete object selected to delete
    if (!objectsforDelete.empty())
    {
        for (int i = 0; i < objectsforDelete.size(); i++)
        {
            delete objectsforDelete[i];
        }
        objectsforDelete.clear();
    }

    // game over
    if(stats->getPeopleAlive() <= 0)
    {
        QMessageBox::StandardButton gameOverBtn = QMessageBox::information(this, "GAME OVER",
                                                  tr("Game over!\n Player: %1  Score: %2")
                                                  .arg(playerInf->getPlayerName(), QString::number(stats->getScore())),
                                                  QMessageBox::Ok,
                                                  QMessageBox::Ok);
        if ((gameOverBtn == QMessageBox::Ok) || (gameOverBtn == QMessageBox::Close)) close();
    }
}

void sceneGUI::closeEvent(QCloseEvent *event)
{   
    stopGameTimer();
    QMessageBox messageBox(QMessageBox::Question,
                tr("Exit"),
                tr("End the game?"),
                QMessageBox::Yes | QMessageBox::No,
                this);
    messageBox.exec();

    if (messageBox.result() == QMessageBox::No)
    {
        event->ignore();
        startGameTimer();
    }
    else
    {
        playerInf->setPlayerScore(stats->getScore());
        playerInf->saveResults();
        playerInf->close();
        delete playerInf;
        delete player;
        if(musicOn)delete music;
        event->accept();

        qDebug() << "Close!";
    }
}

void sceneGUI::mouseMoveEvent(QMouseEvent *event)
{
    angle = atan2(event->y() - player->y(), event->x() - player->x());
    player->setTransformOriginPoint(playerImage.width()/2, playerImage.height()/2);
    player->setRotation(qRadiansToDegrees(angle) + 75); //+75
}

void sceneGUI::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        // choose weapon
        // create fire!
        targetPos = QPoint(event->x(),event->y());
        player->chooseWeapon();
        player->fire(targetPos);
        player->getCurrentFire()->setSound(soundOn);
        scene->addItem(player->getCurrentFire());
        addObjectToList(player->getCurrentFire());
    }
    if(event->button() == Qt::RightButton)
    {
        // change weapon fire
        player->changeWeaponType();
        weaponItem->setPixmap(QPixmap::fromImage(player->getWeaponImage()));
    }
}

