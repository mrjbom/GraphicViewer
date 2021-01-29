#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "ui_mainwindowform.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QMainWindow *parent = nullptr);
    ~MainWindow();
private:
    QMainWindow* mainWindow = nullptr;
    Ui::MainWindowForm* mainWindowFormUI = nullptr;
};
#endif // MAINWINDOW_H
