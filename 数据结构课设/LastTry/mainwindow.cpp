#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPushButton *initialButton = this->findChild<QPushButton *>(QString("pushButton"));
    QPushButton *SubmitButton = this->findChild<QPushButton *>(QString("pushButton_2"));
    QPushButton *SolveButton = this->findChild<QPushButton *>(QString("pushButton_3"));
    QPushButton *ClearButton = this->findChild<QPushButton *>(QString("pushButton_4"));

    connect(initialButton, &QPushButton::clicked, this, &MainWindow::initSudoku);
    connect(SolveButton, &QPushButton::clicked, this, &MainWindow::SolveSudoku);
    connect(SubmitButton, &QPushButton::clicked, this, &MainWindow::submitSudoku);
    connect(ClearButton, &QPushButton::clicked, this, &MainWindow::ClearBoard);

    QRegExp regExp ("[1-9]");
    for (int i = 0; i < 9; i ++){
        for (int j = 0; j < 9; j ++){
            QLineEdit * box = this->findChild<QLineEdit *>(QString("lineEdit%1%2").arg(i).arg(j));
            box->setValidator(new QRegExpValidator(regExp, this));
        }
    }

    this->initSudoku();
}

MainWindow::~MainWindow()
{

    delete ui;
}


void MainWindow::initSudoku(){
    QList<QLineEdit *> singleBoxes = this->findChildren<QLineEdit *>();
    this->ClearBoard();
    //int a[SUDOKU_LENGTH][SUDOKU_LENGTH];
    memset(this->board, 0, SUDOKU_LENGTH * SUDOKU_LENGTH * sizeof(int));
    generate(this->board, 0, 0);
    Dig2(this->board, 40, "lulala.cnf");
    for (int i = 0; i < 9; i ++){
        for (int j = 0; j < 9; j ++){
            QLineEdit * box = this->findChild<QLineEdit *>(QString("lineEdit%1%2").arg(i).arg(j));
            box->setText("");
            if (board[i][j]){
                box->setEnabled(false);
                box->setText(QString::number(board[i][j]));
            }else {
                box->setEnabled(true);
            }

        }
    }

}
void MainWindow::submitSudoku(){
    Reduction(this->board, "hai.cnf");
    CNF * cnf = (CNF *)malloc(sizeof(CNF));
    LoadFile("hai.cnf", cnf);
    DecisionTreeHead * result = DPLL(cnf);
    int * resultArray = TurnToArray(result, cnf);
    int b[SUDOKU_LENGTH][SUDOKU_LENGTH];
    memset(b, 0, SUDOKU_LENGTH * SUDOKU_LENGTH);
    fillIn(resultArray, b);
    for (int i = 0; i < 9; i ++){
        for (int j = 0; j < 9; j ++){
            QLineEdit * box = this->findChild<QLineEdit *>(QString("lineEdit%1%2").arg(i).arg(j));
            if (b[i][j] && box->isEnabled()){
                int temp = box->text().toInt();
                if (b[i][j] == temp)
                    box->setStyleSheet("QLineEdit{border: 1px solid green;}");
                else
                    box->setStyleSheet("QLineEdit{border: 1px solid red;}");
            }else {
                box->setStyleSheet("");
            }
        }
    }
}
void MainWindow::SolveSudoku(){
    Reduction(this->board, "hai.cnf");
    CNF * cnf = (CNF *)malloc(sizeof(CNF));
    LoadFile("hai.cnf", cnf);
    DecisionTreeHead * result = DPLL(cnf);
    int * resultArray = TurnToArray(result, cnf);
    int b[SUDOKU_LENGTH][SUDOKU_LENGTH];
    fillIn(resultArray, b);
    for (int i = 0; i < 9; i ++){
        for (int j = 0; j < 9; j ++){
            QLineEdit * box = this->findChild<QLineEdit *>(QString("lineEdit%1%2").arg(i).arg(j));
            if (b[i][j]){
                box->setText(QString::number(b[i][j]));
            }
        }
    }
}
void CheckSudoku();

void MainWindow::ClearBoard(){
    for (int i = 0; i < 9; i ++){
        for (int j = 0; j < 9; j ++){
            QLineEdit * box = this->findChild<QLineEdit *>(QString("lineEdit%1%2").arg(i).arg(j));
            if (box->isEnabled()){
                box->setText("");
            }
            box->setStyleSheet("");
        }
    }
}
