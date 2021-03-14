#ifndef SC0TESTOPTIONSFORM_H
#define SC0TESTOPTIONSFORM_H

#include <QWidget>

namespace Ui {
class Sc0TestOptionsForm;
}

class Sc0TestOptionsForm : public QWidget
{
    Q_OBJECT

public:
    explicit Sc0TestOptionsForm(QWidget *parent = nullptr);
    ~Sc0TestOptionsForm();

private:
    Ui::Sc0TestOptionsForm *ui;
};

#endif // SC0TESTOPTIONSFORM_H
