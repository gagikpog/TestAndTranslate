#ifndef CONSTRUCTORFORM_H
#define CONSTRUCTORFORM_H

#include <QDialog>

namespace Ui {
class ConstructorForm;
}

class ConstructorForm : public QDialog
{
    Q_OBJECT

public:
    explicit ConstructorForm(QWidget *parent = 0);
    ~ConstructorForm();

private:
    Ui::ConstructorForm *ui;
};

#endif // CONSTRUCTORFORM_H
