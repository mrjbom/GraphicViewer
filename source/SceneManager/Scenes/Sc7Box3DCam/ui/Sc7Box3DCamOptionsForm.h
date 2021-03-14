#ifndef SC7BOX3DCAMOPTIONSFORM_H
#define SC7BOX3DCAMOPTIONSFORM_H

#include <QWidget>

namespace Ui {
class Sc7Box3DCamOptionsForm;
}

class Sc7Box3DCamOptionsForm : public QWidget
{
    Q_OBJECT

public:
    explicit Sc7Box3DCamOptionsForm(QWidget *parent = nullptr);
    ~Sc7Box3DCamOptionsForm();

private:
    Ui::Sc7Box3DCamOptionsForm *ui;
};

#endif // SC7BOX3DCAMOPTIONSFORM_H
