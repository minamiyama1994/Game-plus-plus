#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<memory>
#include <QMainWindow>

namespace Ui {

    class MainWindow : public QMainWindow
    {
        Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);

    private:
        std::shared_ptr < Ui::MainWindow > ui;
    };
}

#endif // MAINWINDOW_H
