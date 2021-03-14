#ifndef SC6BOX3DPERSPECTIVEOPTIONSFORM_H
#define SC6BOX3DPERSPECTIVEOPTIONSFORM_H

#include <QWidget>

namespace Ui {
class Sc6Box3DPerspectiveOptionsForm;
}

class Sc6Box3DPerspectiveOptionsForm : public QWidget
{
    Q_OBJECT

public:
    explicit Sc6Box3DPerspectiveOptionsForm(QWidget *parent = nullptr);
    ~Sc6Box3DPerspectiveOptionsForm();

private:
    Ui::Sc6Box3DPerspectiveOptionsForm *ui;
};

#endif // SC6BOX3DPERSPECTIVEOPTIONSFORM_H
