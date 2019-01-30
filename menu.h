#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include <QImage>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsPixmapItem>
#include "game.h"
#include "settings.h"

namespace Ui {
class Menu;
}

class Menu : public QMainWindow
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = 0);
    ~Menu();

private slots:
    void on_startBtn_clicked();
    void on_settingsBtn_clicked();
    void on_exitBtn_clicked();

private:
    Ui::Menu *ui;
    settings *setDialog;
    Game *game;
};

#endif // MENU_H
