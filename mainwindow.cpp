#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    for(int i=0;i<size;++i){

        for(int j=0;j<size;++j){
            Cell *cell=new Cell(i,j);
            connect(cell,&Cell::sendCoord,this,&MainWindow::getCoord);
            connect(cell,&Cell::changeFlagsCount,this,&MainWindow::changeFlagCounts);
            connect(cell,&Cell::minusLife,this,&MainWindow::minusLife);
            this->ui->gridLayout->addWidget(cell,i,j);

        }

    }
    ((Cell*)this->ui->gridLayout->itemAtPosition(2,2)->widget())->show2();
    field.resize(size);
    for(auto &el:field){

        el.resize(size);
    }
    checked_cell.resize(size);
    for(auto &el:checked_cell){

        el.resize(size);
    }
    this->ui->label->setText(QString::number(mines));
    this->ui->label_2->setText(QString::number(lifes));

    setMines2(field, mines);
    showField(field);

}

MainWindow::~MainWindow()
{
    delete ui;


}

void MainWindow::my_shuffle(QVector<int> &vec)
{
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(vec.begin(), vec.end(),g);
}

void MainWindow::setMines2(QVector<QVector<int> > &field, int mines)
{
    int rest=mines%field.size();
    if(!rest)
    for (int j = 0; j < field.size(); ++j) {
            QVector<int>temp(field.size());
            /*good shuffle*/

            for (int i = field.size()- mines/field.size(); i < field.size(); ++i) {
                temp[i] = -1;

            }
            my_shuffle(temp);
            field[j] = temp;
        }
    else{
        for (int j = 0; j <rest; ++j) {
                QVector<int>temp(field.size());
                /*good shuffle*/

                for (int i = field.size()- mines/field.size()-1; i < field.size(); ++i) {
                    temp[i] = -1;

                }
                my_shuffle(temp);
                field[j] = temp;
            }
        for (int j = rest; j < field.size(); ++j) {
                QVector<int>temp(field.size());
                /*good shuffle*/

                for (int i = field.size()- mines/field.size(); i < field.size(); ++i) {
                    temp[i] = -1;

                }
                my_shuffle(temp);
                field[j] = temp;
            }

    }


        for (int i = 0; i < field.size(); ++i) {
            QVector<int> temp;
            for (int j = 0; j < field.size(); ++j) {

                temp.push_back(field[j][i]);

            }
            my_shuffle(temp);
            for (int k = 0; k < temp.size(); ++k) {

                field[k][i] = temp[k];

            }

        }
        for (int i = 0; i < field.size(); ++i) {

            for (int j = 0; j < field.size(); ++j) {

                if (field[i][j] == 0) {
                    int count_mines = 0;
                    if (i - 1 >= 0 && field[i-1][j] == -1) {
                        ++count_mines;

                    }
                    if (i + 1 < field.size() && field[i + 1][j] == -1)
                        ++count_mines;

                    if (j - 1 >= 0 && field[i][j-1] == -1) {
                        ++count_mines;

                    }
                    if (j + 1 < field.size() && field[i][j+1] == -1)
                        ++count_mines;

                    if (j + 1 < field.size() &&i+1<field.size()&& field[i+1][j + 1] == -1)
                        ++count_mines;

                    if (j - 1 >= 0 && i + 1 < field.size() && field[i + 1][j - 1] == -1)
                        ++count_mines;

                    if (j + 1 < field.size() && i - 1 >= 0 && field[i - 1][j + 1] == -1)
                        ++count_mines;

                    if (j - 1 >= 0 && i - 1 >=0 && field[i - 1][j - 1] == -1)
                        ++count_mines;

                    field[i][j] = count_mines;

                }

            }

        }

}

void MainWindow::showField(QVector<QVector<int> > &field)
{
    qDebug() << "Field" << endl;
        for (auto el : field) {

            for (auto elem : el) {
                qDebug() << elem << "\t";
            }
            qDebug() << endl;
        }
}

void MainWindow::openCells(QVector<QVector<int> > &field, int i, int j)
{
    int count_mines = 0;
    if (i - 1 >= 0 && field[i-1][j]!= -1) {
        ++count_mines;

    }
    if (i + 1 < field.size() && field[i + 1][j] != -1)
        ++count_mines;

    if (j - 1 >= 0 && field[i][j-1] != -1) {
        ++count_mines;

    }
    if (j + 1 < field.size() && field[i][j+1] != -1)
        ++count_mines;

    if (j + 1 < field.size() &&i+1<field.size()&& field[i+1][j + 1] != -1)
        ++count_mines;

    if (j - 1 >= 0 && i + 1 < field.size() && field[i + 1][j - 1] != -1)
        ++count_mines;

    if (j + 1 < field.size() && i - 1 >= 0 && field[i - 1][j + 1] != -1)
        ++count_mines;

    if (j - 1 >= 0 && i - 1 >=0 && field[i - 1][j - 1] != -1)
        ++count_mines;

    //field[i][j] = count_mines;
    bool first = (i-1<0 ||i+1>field.size()-1)&&count_mines==5;
    bool second = (j-1<0 ||j+1>field.size()-1)&&count_mines==5;
    bool third = (i-1<0 &&j-1<0)&&count_mines==3;
    bool fourth = (i+1>=field.size() &&j+1>=field.size())&&count_mines==3;
    bool left_bot=(i+1>=field.size() &&j-1<0)&&count_mines==3;
    bool right_top=(i-1<0 &&j+1>=field.size())&&count_mines==3;
    bool left=(j-1<0&&count_mines==5);
    bool top=(i-1<0&&count_mines==5);
    bool right=(j+1>=field.size()&&count_mines==5);
    bool bottom=(i+1>=field.size()&&count_mines==5);

    if(bottom){
        if(checked_cell[i-1][j]==false){
            ((Cell*)this->ui->gridLayout->itemAtPosition(i -1,j)->widget())->setButtonText(field[i-1][j]);
            //((Cell*)this->ui->gridLayout->itemAtPosition(i -1,j)->widget())->set;
            checked_cell[i-1][j]=true;
            openCells(field,i-1,j);
        }
        if(checked_cell[i][j-1]==false){
            ((Cell*)this->ui->gridLayout->itemAtPosition(i,j-1)->widget())->setButtonText(field[i][j-1]);
            checked_cell[i][j-1]=true;
            openCells(field,i,j-1);
        }
        if(checked_cell[i][j+1]==false){
            ((Cell*)this->ui->gridLayout->itemAtPosition(i,j+1)->widget())->setButtonText(field[i][j+1]);
            checked_cell[i][j+1]=true;
            openCells(field,i,j+1);
        }
        if(checked_cell[i-1][j-1]==false){
            ((Cell*)this->ui->gridLayout->itemAtPosition(i-1,j-1)->widget())->setButtonText(field[i-1][j-1]);
            checked_cell[i-1][j-1]=true;
            openCells(field,i-1,j-1);
        }
        if(checked_cell[i-1][j+1]==false){
            ((Cell*)this->ui->gridLayout->itemAtPosition(i-1,j+1)->widget())->setButtonText(field[i-1][j+1]);
            checked_cell[i-1][j+1]=true;
            openCells(field,i-1,j+1);
        }

    }


    if(right){
        if(checked_cell[i-1][j]==false){
            ((Cell*)this->ui->gridLayout->itemAtPosition(i -1,j)->widget())->setButtonText(field[i-1][j]);
            checked_cell[i-1][j]=true;
            openCells(field,i-1,j);
        }
        if(checked_cell[i+1][j]==false){
            ((Cell*)this->ui->gridLayout->itemAtPosition(i +1,j)->widget())->setButtonText(field[i+1][j]);
            checked_cell[i+1][j]=true;
            openCells(field,i+1,j);
        }
        if(checked_cell[i][j-1]==false){
            ((Cell*)this->ui->gridLayout->itemAtPosition(i,j-1)->widget())->setButtonText(field[i][j-1]);
            checked_cell[i][j-1]=true;
            openCells(field,i,j-1);
        }
        if(checked_cell[i+1][j-1]==false){
            ((Cell*)this->ui->gridLayout->itemAtPosition(i+1,j-1)->widget())->setButtonText(field[i+1][j-1]);
            checked_cell[i+1][j-1]=true;
            openCells(field,i+1,j-1);
        }
        if(checked_cell[i-1][j-1]==false){
            ((Cell*)this->ui->gridLayout->itemAtPosition(i-1,j-1)->widget())->setButtonText(field[i-1][j-1]);
            checked_cell[i-1][j-1]=true;
            openCells(field,i-1,j-1);
        }

    }

    if(top){
        if(checked_cell[i+1][j]==false){
            ((Cell*)this->ui->gridLayout->itemAtPosition(i +1,j)->widget())->setButtonText(field[i+1][j]);
            checked_cell[i+1][j]=true;
            openCells(field,i+1,j);
        }
        if(checked_cell[i][j-1]==false){
            ((Cell*)this->ui->gridLayout->itemAtPosition(i,j-1)->widget())->setButtonText(field[i][j-1]);
            checked_cell[i][j-1]=true;
            openCells(field,i,j-1);
        }
        if(checked_cell[i][j+1]==false){
            ((Cell*)this->ui->gridLayout->itemAtPosition(i,j+1)->widget())->setButtonText(field[i][j+1]);
            checked_cell[i][j+1]=true;
            openCells(field,i,j+1);
        }
        if(checked_cell[i+1][j+1]==false){
            ((Cell*)this->ui->gridLayout->itemAtPosition(i+1,j+1)->widget())->setButtonText(field[i+1][j+1]);
            checked_cell[i+1][j+1]=true;
            openCells(field,i+1,j+1);
        }
        if(checked_cell[i+1][j-1]==false){
            ((Cell*)this->ui->gridLayout->itemAtPosition(i+1,j-1)->widget())->setButtonText(field[i+1][j-1]);
            checked_cell[i+1][j-1]=true;
            openCells(field,i+1,j-1);
        }

    }


    if(left){
        if(checked_cell[i-1][j]==false){
            ((Cell*)this->ui->gridLayout->itemAtPosition(i -1,j)->widget())->setButtonText(field[i-1][j]);
            checked_cell[i-1][j]=true;
            openCells(field,i-1,j);
        }
        if(checked_cell[i+1][j]==false){
            ((Cell*)this->ui->gridLayout->itemAtPosition(i +1,j)->widget())->setButtonText(field[i+1][j]);
            checked_cell[i+1][j]=true;
            openCells(field,i+1,j);
        }
        if(checked_cell[i][j+1]==false){
            ((Cell*)this->ui->gridLayout->itemAtPosition(i,j+1)->widget())->setButtonText(field[i][j+1]);
            checked_cell[i][j+1]=true;
            openCells(field,i,j+1);
        }
        if(checked_cell[i+1][j+1]==false){
            ((Cell*)this->ui->gridLayout->itemAtPosition(i+1,j+1)->widget())->setButtonText(field[i+1][j+1]);
            checked_cell[i+1][j+1]=true;
            openCells(field,i+1,j+1);
        }
        if(checked_cell[i-1][j+1]==false){
            ((Cell*)this->ui->gridLayout->itemAtPosition(i-1,j+1)->widget())->setButtonText(field[i-1][j+1]);
            checked_cell[i-1][j+1]=true;
            openCells(field,i-1,j+1);
        }

    }

    if(right_top){

        if(checked_cell[i+1][j-1]==false){
            ((Cell*)this->ui->gridLayout->itemAtPosition(i +1,j-1)->widget())->setButtonText(field[i+1][j-1]);
            checked_cell[i+1][j-1]=true;
            openCells(field,i+1,j-1);
        }

        if(checked_cell[i+1][j]==false){
            ((Cell*)this->ui->gridLayout->itemAtPosition(i +1,j)->widget())->setButtonText(field[i+1][j]);
            checked_cell[i+1][j]=true;
            openCells(field,i+1,j);
        }

        if(checked_cell[i][j-1]==false){
            ((Cell*)this->ui->gridLayout->itemAtPosition(i,j-1)->widget())->setButtonText(field[i][j-1]);
            checked_cell[i][j-1]=true;
            openCells(field,i,j-1);
        }


    }


    if(left_bot){

        if(checked_cell[i-1][j+1]==false){
            ((Cell*)this->ui->gridLayout->itemAtPosition(i -1,j+1)->widget())->setButtonText(field[i-1][j+1]);
            checked_cell[i-1][j+1]=true;
            openCells(field,i-1,j+1);
        }

        if(checked_cell[i-1][j]==false){
            ((Cell*)this->ui->gridLayout->itemAtPosition(i -1,j)->widget())->setButtonText(field[i-1][j]);
            checked_cell[i-1][j]=true;
            openCells(field,i-1,j);
        }

        if(checked_cell[i][j+1]==false){
            ((Cell*)this->ui->gridLayout->itemAtPosition(i,j+1)->widget())->setButtonText(field[i][j+1]);
            checked_cell[i][j+1]=true;
            openCells(field,i,j+1);
        }


    }

    if(fourth){
        if(checked_cell[i-1][j-1]==false){
            ((Cell*)this->ui->gridLayout->itemAtPosition(i -1,j-1)->widget())->setButtonText(field[i-1][j-1]);
            checked_cell[i-1][j-1]=true;
            openCells(field,i-1,j-1);
        }

        if(checked_cell[i-1][j]==false){
            ((Cell*)this->ui->gridLayout->itemAtPosition(i -1,j)->widget())->setButtonText(field[i-1][j]);
            checked_cell[i-1][j]=true;
            openCells(field,i-1,j);
        }

        if(checked_cell[i][j-1]==false){
            ((Cell*)this->ui->gridLayout->itemAtPosition(i,j-1)->widget())->setButtonText(field[i][j-1]);
            checked_cell[i][j-1]=true;
            openCells(field,i,j-1);
        }
    }

    if(third){
        if(checked_cell[i+1][j+1]==false){
            ((Cell*)this->ui->gridLayout->itemAtPosition(i +1,j+1)->widget())->setButtonText(field[i+1][j+1]);
            checked_cell[i+1][j+1]=true;
            openCells(field,i+1,j+1);
        }

        if(checked_cell[i+1][j]==false){
            ((Cell*)this->ui->gridLayout->itemAtPosition(i + 1,j)->widget())->setButtonText(field[i+1][j]);
            checked_cell[i+1][j]=true;
            openCells(field,i+1,j);
        }

        if(checked_cell[i][j+1]==false){
            ((Cell*)this->ui->gridLayout->itemAtPosition(i,j+1)->widget())->setButtonText(field[i][j+1]);
            checked_cell[i][j+1]=true;
            openCells(field,i,j+1);
        }
    }

    if(count_mines==8){
            if(checked_cell[i-1][j]==false){
                ((Cell*)this->ui->gridLayout->itemAtPosition(i - 1,j)->widget())->setButtonText(field[i-1][j]);
                checked_cell[i-1][j]=true;
                openCells(field,i-1,j);
            }
            if(checked_cell[i+1][j]==false){
                ((Cell*)this->ui->gridLayout->itemAtPosition(i + 1,j)->widget())->setButtonText(field[i+1][j]);
                checked_cell[i+1][j]=true;
                openCells(field,i+1,j);
            }
            if(checked_cell[i][j-1]==false){
                ((Cell*)this->ui->gridLayout->itemAtPosition(i,j-1)->widget())->setButtonText(field[i][j-1]);
                checked_cell[i][j-1]=true;
                openCells(field,i,j-1);
            }
            if(checked_cell[i][j+1]==false){
                ((Cell*)this->ui->gridLayout->itemAtPosition(i,j+1)->widget())->setButtonText(field[i][j+1]);
                checked_cell[i][j+1]=true;
                openCells(field,i,j+1);
            }
            if(checked_cell[i-1][j-1]==false){
                ((Cell*)this->ui->gridLayout->itemAtPosition(i - 1,j-1)->widget())->setButtonText(field[i-1][j-1]);
                checked_cell[i-1][j-1]=true;
                openCells(field,i-1,j-1);
            }
            if(checked_cell[i+1][j+1]==false){
                ((Cell*)this->ui->gridLayout->itemAtPosition(i +1,j+1)->widget())->setButtonText(field[i+1][j+1]);
                checked_cell[i+1][j+1]=true;
                openCells(field,i+1,j+1);
            }
            if(checked_cell[i-1][j+1]==false){
                ((Cell*)this->ui->gridLayout->itemAtPosition(i - 1,j+1)->widget())->setButtonText(field[i-1][j+1]);
                checked_cell[i-1][j+1]=true;
                openCells(field,i-1,j+1);
            }
            if(checked_cell[i+1][j-1]==false){
                ((Cell*)this->ui->gridLayout->itemAtPosition(i +1,j-1)->widget())->setButtonText(field[i+1][j-1]);
                checked_cell[i+1][j-1]=true;
                openCells(field,i+1,j-1);
            }


    }

}



void MainWindow::getCoord(QPair<int, int> coord)
{

    if(checked_cell[coord.first][coord.second]==false){
        qDebug()<<coord<<endl;
        ((Cell*)QObject::sender())->setButtonText((this->field[coord.first][coord.second]));

        int i=coord.first,j=coord.second;
        if(field[i][j]>=0){
            openCells(field,i,j);
        }
        checked_cell[coord.first][coord.second]=true;
    }
}

void MainWindow::changeFlagCounts(bool change)
{
    if(change)
        this->ui->label->setText(QString::number(++mines));
    else
        this->ui->label->setText(QString::number(--mines));
}

void MainWindow::minusLife()
{
    this->lifes--;
    this->ui->label_2->setText(QString::number(lifes));
}

