#include "ranking.h"
#include "ui_rankingDialog.h"
#include <QDebug>

Ranking::Ranking(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Ranking)
{
    ui->setupUi(this);
	// Top 10 players
    model = new QStandardItemModel(10,2,this); //10 rows and 2 columns
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Player")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Score")));
    ui->tableView->setModel(model);

    // Read data from file

    QMap<int, QString> map;
    QMap<int, QString>::iterator it;

    QFile file("ranking.txt");
    if(!file.open(QFile::ReadOnly |
                  QFile::Text))
    {
        qDebug() << " Could not open the file for reading";
        return;
    }

    QTextStream in(&file);
    QStringList list;

    while (!in.atEnd())
    {
      QString line = in.readLine();
      list = line.split("\t");
      QString v = list.last();
      int val = v.toInt();
      map.insert(val,list.first());
    }

    file.close();

    qDebug() << map;
    it = --map.end();

    // Insert data to table
    for(int row = 0; row < map.size(); row++)
    {
        for(int col = 0; col < 2; col++)
        {
            QModelIndex index = model->index(row, col, QModelIndex());
            model->setData(index, it.value());
            index = model->index(row, ++col, QModelIndex());
            model->setData(index, it.key());
            it--;
        }
    }
}

Ranking::~Ranking()
{
    delete ui;
}

void Ranking::on_okBtn_clicked()
{
    close();
}
