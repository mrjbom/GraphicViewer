#ifndef SC8LIGHTINGOPTIONSFORM_H
#define SC8LIGHTINGOPTIONSFORM_H

#include <QWidget>

namespace Ui {
class Sc8LightingOptionsForm;
}

class Sc8LightingOptionsForm : public QWidget
{
    Q_OBJECT

public:
    explicit Sc8LightingOptionsForm(QWidget *parent = nullptr);
    ~Sc8LightingOptionsForm();

private:
    Ui::Sc8LightingOptionsForm *ui;
};

#endif // SC8LIGHTINGOPTIONSFORM_H
