#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include "ui_MainWindowForm.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    Ui::MainWindowForm* mainWindowFormUI = nullptr;
public:
    MainWindow(QMainWindow *parent = nullptr);
    ~MainWindow();
};
#endif // MAINWINDOW_H
