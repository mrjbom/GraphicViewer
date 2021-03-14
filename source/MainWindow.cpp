#include "MainWindow.h"
#include "globalvars.h"
#include <QWidget>

MainWindow::MainWindow(QMainWindow* parent)
{
    (void)parent;
    qDebug("[INFO] Main window object created successfully");
    mainWindowFormUI = new Ui::MainWindowForm;
    globalMainWindowFormUI = mainWindowFormUI;
    mainWindowFormUI->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete mainWindowFormUI;
    qDebug("[INFO] Main window object destroyed successfully");
}
