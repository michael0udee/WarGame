#include "settings.h"
#include "ui_settings.h"
#include <QDebug>
#include <QMovie>


settings::settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::settings)
{
    ui->setupUi(this);
    setWindowTitle("Settings");

    // default settings
    ui->speedCtrlSlider->setValue(5);
    ui->perseveranceCtrlSlider->setValue(2);

    // sound settings
    QImage music_on(":/images/images/music_on.png");
    QImage music_off(":/images/images/music_off.png");
    ui->musicOnLabel->setPixmap(QPixmap::fromImage(music_on));
    ui->musicOffLabel->setPixmap(QPixmap::fromImage(music_off));
    ui->musicOnLabel->setVisible(true);
    ui->musicOffLabel->setVisible(false);

    // effects settings
    ui->effectsOnLabel->setPixmap(QPixmap::fromImage(music_on));
    ui->effectsOffLabel->setPixmap(QPixmap::fromImage(music_off));
    ui->effectsOnLabel->setVisible(true);
    ui->effectsOffLabel->setVisible(false);

    // tank settings image
    QImage tank(":/images/images/nazi_tank.png");
    tank = tank.scaled(100,100, Qt::KeepAspectRatio);
    ui->tankLabel->setPixmap(QPixmap::fromImage(tank));

    // player settings image
    QImage player(":/images/images/player.png");
    player = player.scaled(50,50,Qt::KeepAspectRatio);
    ui->playerLabel->setPixmap(QPixmap::fromImage(player));

    // soldier settings image
    QMovie *movie = new QMovie(":/images/images/soldier.gif");
    movie->setScaledSize(QSize(50,50));
    ui->soldierLabel->setMovie(movie);
    movie->start();

    // junkers settings image
    QImage junkers(":/images/images/junkers.png");
    junkers = junkers.scaled(67, 90, Qt::KeepAspectRatio);
    QTransform rotating;
    rotating.rotate(-90);
    ui->junkersLabel->setPixmap(QPixmap::fromImage(junkers.transformed(rotating)));
}

settings::~settings()
{
    delete ui;
}

void settings::setParameters()
{
    paramList.push_back(ui->speedCtrlSlider->value());
    paramList.push_back(ui->perseveranceCtrlSlider->value());
    paramList.push_back(ui->musicOnLabel->isVisible());
    paramList.push_back(ui->effectsOnLabel->isVisible());
}

std::vector<int> settings::getParameters()
{
    return paramList;
}

void settings::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        if(ui->musicOnLabel->underMouse() == true || ui->musicOffLabel->underMouse() == true)
        {
            if(ui->musicOnLabel->isVisible())
            {
                ui->musicOffLabel->setVisible(true);
                ui->musicOnLabel->setVisible(false);
            }
            else
            {
                ui->musicOffLabel->setVisible(false);
                ui->musicOnLabel->setVisible(true);
            }
        }
        if(ui->effectsOnLabel->underMouse() == true || ui->effectsOffLabel->underMouse() == true)
        {
            if(ui->effectsOnLabel->isVisible())
            {
                ui->effectsOffLabel->setVisible(true);
                ui->effectsOnLabel->setVisible(false);
            }
            else
            {
                ui->effectsOffLabel->setVisible(false);
                ui->effectsOnLabel->setVisible(true);
            }
        }
    }
}

void settings::on_submitBtn_clicked()
{
    setParameters();
    accept();
    close();
}

void settings::on_cancelBtn_clicked()
{
    reject();
    close();
}

void settings::on_speedCtrlSlider_valueChanged(int value)
{
    ui->speedValueLabel->setText(QString::number(value));
}

void settings::on_perseveranceCtrlSlider_valueChanged(int value)
{
    ui->perseverValueLabel->setText(QString::number(value));
}

void settings::on_rankingBtn_clicked()
{
    rankDialog = new Ranking;
    rankDialog->setModal(true);
    rankDialog->exec();

}
