#ifndef SC1VBOORANGEOPTIONSFORM_H
#define SC1VBOORANGEOPTIONSFORM_H

#include <QWidget>

namespace Ui {
class Sc1VBOOrangeOptionsForm;
}

class Sc1VBOOrangeOptionsForm : public QWidget
{
    Q_OBJECT

public:
    explicit Sc1VBOOrangeOptionsForm(QWidget *parent = nullptr);
    ~Sc1VBOOrangeOptionsForm();

private:
    Ui::Sc1VBOOrangeOptionsForm *ui;
};

#endif // SC1VBOORANGEOPTIONSFORM_H
