#include "Sc1VBOOrangeOptionsForm.h"
#include "ui_Sc1VBOOrangeOptionsForm.h"

Sc1VBOOrangeOptionsForm::Sc1VBOOrangeOptionsForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Sc1VBOOrangeOptionsForm)
{
    ui->setupUi(this);
}

Sc1VBOOrangeOptionsForm::~Sc1VBOOrangeOptionsForm()
{
    delete ui;
}
