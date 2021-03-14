#include "Sc0TestOptionsForm.h"
#include "ui_Sc0TestOptionsForm.h"

Sc0TestOptionsForm::Sc0TestOptionsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sc0TestOptionsForm)
{
    ui->setupUi(this);
}

Sc0TestOptionsForm::~Sc0TestOptionsForm()
{
    delete ui;
}
