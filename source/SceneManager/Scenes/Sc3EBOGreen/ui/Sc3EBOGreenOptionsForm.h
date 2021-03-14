#ifndef SC3EBOGREENOPTIONSFORM_H
#define SC3EBOGREENOPTIONSFORM_H

#include <QWidget>

namespace Ui {
class Sc3EBOGreenOptionsForm;
}

class Sc3EBOGreenOptionsForm : public QWidget
{
    Q_OBJECT

public:
    explicit Sc3EBOGreenOptionsForm(QWidget *parent = nullptr);
    ~Sc3EBOGreenOptionsForm();

private:
    Ui::Sc3EBOGreenOptionsForm *ui;
};

#endif // SC3EBOGREENOPTIONSFORM_H
