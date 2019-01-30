#ifndef RANKING_H
#define RANKING_H

#include <QDialog>
#include <QStandardItemModel>
#include <QFile>
#include <QTextStream>
#include <QMap>

namespace Ui {
class Ranking;
}

class Ranking : public QDialog
{
    Q_OBJECT

public:
    explicit Ranking(QWidget *parent = 0);
    ~Ranking();

private slots:
    void on_okBtn_clicked();

private:
    Ui::Ranking *ui;
    QStandardItemModel *model;
};

#endif // RANKING_H
