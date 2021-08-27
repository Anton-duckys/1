#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "cell.h"
#include<QVector>
#include<algorithm>
#include<random>
#include<QPushButton>
#include<QString>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void my_shuffle(QVector<int>&vec);
    void setMines2(QVector<QVector<int>>&field,int mines);
    void showField(QVector<QVector<int>>& field);
    void openCells(QVector<QVector<int>>&field,int i,int j);

public slots:
    void getCoord(QPair<int,int>coord);
    void changeFlagCounts(bool change);
    void minusLife();

private:
    Ui::MainWindow *ui;
    int size=20;
    int mines=80;
    int lifes=3;
    QVector<QVector<int>>field;
    QVector<QVector<bool>>checked_cell;
};
#endif // MAINWINDOW_H
