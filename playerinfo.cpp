#include "playerinfo.h"
#include "ui_playerinfodialog.h"
#include <QDebug>

playerInfo::playerInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::playerInfo)
{
    ui->setupUi(this);
}

playerInfo::~playerInfo()
{
    delete ui;
}

QString playerInfo::getPlayerName()
{
    return name;
}

void playerInfo::setPlayerName(QString name)
{
    this->name = name;
}

void playerInfo::setPlayerScore(int score)
{
    this->score = score;
}

void playerInfo::saveResults()
{
    // Save new player data
    QFile file("ranking.txt");
    file.open(QFile::Append | QFile::WriteOnly | QFile::Text);
    QTextStream out(&file);
    QString strScore = QString::number(score);
    out << name << "\t " << strScore << endl;
    file.flush();
    file.close();

    // Read data from file
    QMap<int, QString> map;
    QMap<int, QString>::iterator it;

    if(!file.open(QFile::ReadOnly |
                  QFile::Text))
    {
        qDebug() << " Could not open the file for reading";
        return;
    }

    QTextStream in(&file);

    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList list = line.split("\t");
        QString v = list.last();
        int val = v.toInt();
        map.insert(val,list.first());
    }

    file.close();

    while(map.size() > 10)
        map.erase(map.begin());

    it = --map.end();

    // Save map to file
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        qDebug() << " Could not open the file for writing";
        return;
    }

    QTextStream out2(&file);
    it = --map.end();
    while(it != map.begin()-1)
    {
        out2 << it.value() << "\t" << it.key() << endl;
        it--;
    }

    file.close();
}

void playerInfo::on_buttonBox_accepted()
{
    name = ui->lineEdit->text();
}
