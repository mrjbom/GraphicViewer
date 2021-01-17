#include "mainwindow.h"

MainWindow::MainWindow(QMainWindow* parent)
{
    mainWindow = new QMainWindow(parent);
    if(!mainWindow) { qDebug("[ERROR] Main window object create failed!"); }
    qDebug("[INFO] Main window object created successfully");

    Ui::MainWindowForm mainWindowFormUI;
    mainWindowFormUI.setupUi(this);


}

MainWindow::~MainWindow()
{
    delete mainWindow;
    qDebug("[INFO] Main window object destroyed successfully");
}
