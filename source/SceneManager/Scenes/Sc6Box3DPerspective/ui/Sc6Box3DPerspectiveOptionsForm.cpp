#include "Sc6Box3DPerspectiveOptionsForm.h"
#include "ui_Sc6Box3DPerspectiveOptionsForm.h"

Sc6Box3DPerspectiveOptionsForm::Sc6Box3DPerspectiveOptionsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sc6Box3DPerspectiveOptionsForm)
{
    ui->setupUi(this);
}

Sc6Box3DPerspectiveOptionsForm::~Sc6Box3DPerspectiveOptionsForm()
{
    delete ui;
}
