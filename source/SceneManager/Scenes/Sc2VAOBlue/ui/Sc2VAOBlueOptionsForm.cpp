#include "Sc2VAOBlueOptionsForm.h"
#include "ui_Sc2VAOBlueOptionsForm.h"

Sc2VAOBlueOptionsForm::Sc2VAOBlueOptionsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sc2VAOBlueOptionsForm)
{
    ui->setupUi(this);
}

Sc2VAOBlueOptionsForm::~Sc2VAOBlueOptionsForm()
{
    delete ui;
}
