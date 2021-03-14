#ifndef SC4UNIFORMINPUTOPTIONSFORM_H
#define SC4UNIFORMINPUTOPTIONSFORM_H

#include <QWidget>

namespace Ui {
class Sc4UniformInputOptionsForm;
}

class Sc4UniformInputOptionsForm : public QWidget
{
    Q_OBJECT

public:
    explicit Sc4UniformInputOptionsForm(QWidget *parent = nullptr);
    ~Sc4UniformInputOptionsForm();

private:
    Ui::Sc4UniformInputOptionsForm *ui;
};

#endif // SC4UNIFORMINPUTOPTIONSFORM_H
