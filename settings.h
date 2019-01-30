#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QMouseEvent>
#include <QGraphicsPixmapItem>
#include "ranking.h"

namespace Ui {
class settings;
}

class settings : public QDialog
{
    Q_OBJECT

public:
    explicit settings(QWidget *parent = 0);
    ~settings();

    void setParameters();
    std::vector<int> getParameters();

protected:
    void mousePressEvent(QMouseEvent *event);

private slots:
    void on_submitBtn_clicked();
    void on_cancelBtn_clicked();
    void on_speedCtrlSlider_valueChanged(int value);
    void on_perseveranceCtrlSlider_valueChanged(int value);

    void on_rankingBtn_clicked();

private:
    Ui::settings *ui;
    std::vector<int> paramList;
    QGraphicsPixmapItem *itemMusicOn, *itemMusicOff, *itemTank, *itemSoldier;
    Ranking *rankDialog;
};

#endif // SETTINGS_H
