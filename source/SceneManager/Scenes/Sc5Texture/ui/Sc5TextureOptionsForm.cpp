#include "Sc5TextureOptionsForm.h"
#include "ui_Sc5TextureOptionsForm.h"

Sc5TextureOptionsForm::Sc5TextureOptionsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sc5TextureOptionsForm)
{
    ui->setupUi(this);
}

Sc5TextureOptionsForm::~Sc5TextureOptionsForm()
{
    delete ui;
}
