#include "Sc3EBOGreenOptionsForm.h"
#include "ui_Sc3EBOGreenOptionsForm.h"

Sc3EBOGreenOptionsForm::Sc3EBOGreenOptionsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sc3EBOGreenOptionsForm)
{
    ui->setupUi(this);
}

Sc3EBOGreenOptionsForm::~Sc3EBOGreenOptionsForm()
{
    delete ui;
}
