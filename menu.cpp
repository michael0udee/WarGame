#include "menu.h"
#include "ui_menu.h"
#include "scenegui.h"
#include <QDebug>

Menu::Menu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    setWindowTitle("Stalingrad Defence");
    setFixedSize(615,160);
    QImage image(":/images/images/title2.PNG");
    QGraphicsScene* scene = new QGraphicsScene();
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(image));
    scene->addItem(item);
    ui->graphicsTitle->setScene(scene);
    ui->graphicsTitle->setAlignment(Qt::AlignCenter);
    ui->graphicsTitle->setStyleSheet("background: transparent; border-style: none;");
    ui->graphicsTitle->show();

    game = new Game;
}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_startBtn_clicked()
{
    game->startGame();
}

void Menu::on_settingsBtn_clicked()
{
    setDialog = new settings;
    setDialog->setModal(true);
    setDialog->exec();
    if(setDialog->result() == QDialog::Accepted)
    {
        game->setParameters(setDialog->getParameters());
        qDebug() << "Accepted!";
    }
    else
    {
        // set default parameters
        qDebug() << "Rejected!";
    }
}

void Menu::on_exitBtn_clicked()
{
    close();
    //exit(0);
}
