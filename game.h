#ifndef GAME_H
#define GAME_H
#include "scenegui.h"
#include "playerinfo.h"
#include <QObject>

class Game : public QObject
{
    Q_OBJECT
public:
    Game();

    enum Parameters
    {
        EnemySpeedValue,
        EnemyPersevereValue,
        Music,
        SoundEffects,
        COUNT
    };
    void setParameters(std::vector<int> list);
    void setDefaultParameters();
    void startGame();

private:
    std::vector<int> parametersList;
    sceneGUI *sGUI;
    playerInfo *playerDialog;
};


#endif // GAME_H
