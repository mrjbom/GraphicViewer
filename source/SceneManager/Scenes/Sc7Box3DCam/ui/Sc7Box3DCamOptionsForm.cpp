#include "Sc7Box3DCamOptionsForm.h"
#include "ui_Sc7Box3DCamOptionsForm.h"

Sc7Box3DCamOptionsForm::Sc7Box3DCamOptionsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sc7Box3DCamOptionsForm)
{
    ui->setupUi(this);
}

Sc7Box3DCamOptionsForm::~Sc7Box3DCamOptionsForm()
{
    delete ui;
}
