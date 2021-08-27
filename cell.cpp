#include "cell.h"
#include "ui_cell.h"

Cell::Cell(int x, int y, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Cell)
{
    ui->setupUi(this);
    this->x=x;
    this->y=y;
    this->coord={x,y};
    ui->pushButton->setStyleSheet("background-color: rgba(150, 224, 108, 0.8);");
}

Cell::~Cell()
{
    delete ui;
}

void Cell::show2()
{
    qDebug()<<"Hello"<<endl;
}

QPair<int, int> Cell::getCoord()
{
    return this->coord;
}


void Cell::setButtonText(int i)
{
    //this->ui->pushButton->setText(QString::number(i));
    //this->ui->pushButton->setEnabled(false);
    this->checked=true;
    if(i==-1){
        QPixmap *pixmap=new QPixmap(":/images/bomb.png");
        QIcon icon(*pixmap);
        this->ui->pushButton->setIcon(icon);
        this->ui->pushButton->setIconSize(QSize(this->ui->pushButton->width(),this->ui->pushButton->height()));
        this->ui->pushButton->setStyleSheet("QPushButton{background:red;}");
        emit this->minusLife();
    }
    else
    {
        if(i==0)
            this->ui->pushButton->setStyleSheet("background-color: rgba(226, 232, 137, 1);}");
        else{
            QPixmap *pixmap=new QPixmap(":/images/"+QString::number(i)+".png");
            QIcon icon(*pixmap);
            this->ui->pushButton->setIcon(icon);
            this->ui->pushButton->setIconSize(QSize(this->ui->pushButton->width(),this->ui->pushButton->height()));
        }

    }
}

void Cell::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton)
        {
            if(flag==false&&checked==false){
                QPixmap *pixmap=new QPixmap(":/images/flag.png");
                QIcon icon(*pixmap);
                this->ui->pushButton->setIcon(icon);
                this->ui->pushButton->setIconSize(QSize(this->ui->pushButton->width(),this->ui->pushButton->height()));
                flag=true;
                checked=true;
                emit changeFlagsCount(0);
            }
            else if(flag&&checked){
                QPixmap *pixmap=new QPixmap("");
                QIcon icon(*pixmap);
                this->ui->pushButton->setIcon(icon);
                this->ui->pushButton->setIconSize(QSize(this->ui->pushButton->width(),this->ui->pushButton->height()));
                flag=false;
                checked=false;
                emit changeFlagsCount(1);

            }
        }
}

void Cell::on_pushButton_clicked()
{
    emit sendCoord(this->coord);
}
