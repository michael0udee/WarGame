#ifndef PLAYERINFO_H
#define PLAYERINFO_H

#include <QDialog>
#include <QFile>
#include <QTextStream>
#include <QMap>

namespace Ui {
class playerInfo;
}

class playerInfo : public QDialog
{
    Q_OBJECT

public:
    explicit playerInfo(QWidget *parent = 0);
    ~playerInfo();
    QString getPlayerName();
    void setPlayerName(QString name);
    void setPlayerScore(int score);
    void saveResults();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::playerInfo *ui;
    QString name;
    int score;
};

#endif // PLAYERINFO_H
