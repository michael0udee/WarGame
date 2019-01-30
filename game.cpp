#include "game.h"
#include <QDebug>
#include <QTime>

Game::Game()
{
    setDefaultParameters();
}

void Game::setParameters(std::vector<int> list)
{
    parametersList = list;
}

void Game::setDefaultParameters()
{
    parametersList.resize(Game::COUNT);
    parametersList[Game::EnemySpeedValue] = 5;
    parametersList[Game::EnemyPersevereValue] = 2;
    parametersList[Game::Music] = 1;
    parametersList[Game::SoundEffects] = 1;
}

void Game::startGame()
{
    playerDialog = new playerInfo;
    playerDialog->setModal(true);
    playerDialog->exec();

    if(playerDialog->result() == QDialog::Accepted)
    {
        qDebug() << "Accepted player!";
        playerDialog->setModal(false);
        playerDialog->hide();

        sGUI = new sceneGUI;
        sGUI->setPlayerInfoPointer(playerDialog);
        sGUI->setWindowModality(Qt::ApplicationModal);
        sGUI->setMusic(parametersList[Game::Music]);
        sGUI->setSoundEffect(parametersList[Game::SoundEffects]);
        sGUI->setEnemyTimer(parametersList[Game::EnemySpeedValue]);
        sGUI->setEnemyLive(parametersList[Game::EnemyPersevereValue]);
        sGUI->show();

        sGUI->startGameTimer();
    }
    else
    {
        qDebug() << "Rejected player!";
    }
}
