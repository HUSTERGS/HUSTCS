#include "mainwindow.h"
#include <QApplication>
#include <QPushButton>
#include <QLineEdit>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Sudoku Game @ GS");
    w.show();

    return a.exec();
}
