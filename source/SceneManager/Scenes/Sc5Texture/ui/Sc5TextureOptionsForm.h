#ifndef SC5TEXTUREOPTIONSFORM_H
#define SC5TEXTUREOPTIONSFORM_H

#include <QWidget>

namespace Ui {
class Sc5TextureOptionsForm;
}

class Sc5TextureOptionsForm : public QWidget
{
    Q_OBJECT

public:
    explicit Sc5TextureOptionsForm(QWidget *parent = nullptr);
    ~Sc5TextureOptionsForm();

private:
    Ui::Sc5TextureOptionsForm *ui;
};

#endif // SC5TEXTUREOPTIONSFORM_H
