#ifndef CELL_H
#define CELL_H

#include <QWidget>
#include<QDebug>
#include<QPair>
#include<QPushButton>
#include<QMouseEvent>
namespace Ui {
class Cell;
}

class Cell : public QWidget
{
    Q_OBJECT

public:
    explicit Cell(int x,int y,QWidget *parent = nullptr);
    ~Cell();
    void show2();
    QPair<int,int>getCoord();

    void setButtonText(int i);
    void mousePressEvent(QMouseEvent *event);

private slots:
    void on_pushButton_clicked();

private:
    Ui::Cell *ui;
    int x,y;
    QPair<int,int>coord;
    bool flag=false;
    bool checked=false;

signals:
    void sendCoord(QPair<int,int>coord);
    void changeFlagsCount(bool change);
    void minusLife();
};

#endif // CELL_H
