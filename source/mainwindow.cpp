#include "mainwindow.h"
#include "globalvars.h"

MainWindow::MainWindow(QMainWindow* parent)
{
    mainWindow = new QMainWindow(parent);
    if(!mainWindow) { qDebug("[ERROR] Main window object create failed!"); }
    qDebug("[INFO] Main window object created successfully");
    mainWindowFormUI = new Ui::MainWindowForm;
    globalMainWindowFormUI = mainWindowFormUI;
    mainWindowFormUI->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete mainWindowFormUI;
    delete mainWindow;
    qDebug("[INFO] Main window object destroyed successfully");
}
