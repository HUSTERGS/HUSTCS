#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dpll.h"
#include "sudoku.h"
#include <QList>
#include <qvalidator.h>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    int board[SUDOKU_LENGTH][SUDOKU_LENGTH];
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initSudoku();
    void submitSudoku();
    void SolveSudoku();
    void CheckSudoku();
    void ClearBoard();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
