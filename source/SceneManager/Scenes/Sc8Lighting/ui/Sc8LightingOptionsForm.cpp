#include "Sc8LightingOptionsForm.h"
#include "ui_Sc8LightingOptionsForm.h"

Sc8LightingOptionsForm::Sc8LightingOptionsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sc8LightingOptionsForm)
{
    ui->setupUi(this);
}

Sc8LightingOptionsForm::~Sc8LightingOptionsForm()
{
    delete ui;
}
