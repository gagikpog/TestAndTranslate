#ifndef TRAININGFORM_H
#define TRAININGFORM_H

#include <QDialog>

namespace Ui {
class TrainingForm;
}

class TrainingForm : public QDialog
{
    Q_OBJECT

public:
    explicit TrainingForm(QWidget *parent = 0);
    ~TrainingForm();
    void setInterfaceLanguage();

private:
    Ui::TrainingForm *ui;
};

#endif // TRAININGFORM_H
