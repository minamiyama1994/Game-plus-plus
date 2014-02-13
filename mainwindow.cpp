#include "mainwindow.h"
#include "ui_mainwindow.h"
namespace Ui
{
    MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(std::make_shared < Ui::MainWindow > ( ))
    {
        ui->setupUi(this);
    }
}
