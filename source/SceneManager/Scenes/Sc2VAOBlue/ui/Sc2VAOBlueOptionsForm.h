#ifndef SC2VAOBLUEOPTIONSFORM_H
#define SC2VAOBLUEOPTIONSFORM_H

#include <QWidget>

namespace Ui {
class Sc2VAOBlueOptionsForm;
}

class Sc2VAOBlueOptionsForm : public QWidget
{
    Q_OBJECT

public:
    explicit Sc2VAOBlueOptionsForm(QWidget *parent = nullptr);
    ~Sc2VAOBlueOptionsForm();

private:
    Ui::Sc2VAOBlueOptionsForm *ui;
};

#endif // SC2VAOBLUEOPTIONSFORM_H
