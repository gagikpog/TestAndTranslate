#ifndef READERFORM_H
#define READERFORM_H

#include <QDialog>

namespace Ui {
class ReaderForm;
}

class ReaderForm : public QDialog
{
    Q_OBJECT

public:
    explicit ReaderForm(QWidget *parent = 0);
    void setInterfaceLanguage(QString lang);
    void setText(QString txt);
    bool isChanged() const;
    QString Text() const;
    ~ReaderForm();

private slots:
    void on_btmOk_clicked();

private:
    Ui::ReaderForm *ui;
    bool changed = false;
};

#endif // READERFORM_H
