#include "Sc4UniformInputOptionsForm.h"
#include "ui_Sc4UniformInputOptionsForm.h"

Sc4UniformInputOptionsForm::Sc4UniformInputOptionsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sc4UniformInputOptionsForm)
{
    ui->setupUi(this);
}

Sc4UniformInputOptionsForm::~Sc4UniformInputOptionsForm()
{
    delete ui;
}
