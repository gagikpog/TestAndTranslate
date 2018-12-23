#ifndef WORD_H
#define WORD_H

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QGroupBox>

class Word : public QWidget
{
    Q_OBJECT
public:
    explicit Word(QWidget *parent = nullptr);
    void setText(QString t);
    QString text()const{return txt;}
signals:

public slots:

protected:
    void paintEvent(QPaintEvent* );
    void mousePressEvent(QMouseEvent *eventPress);
    void mouseReleaseEvent(QMouseEvent *releaseEvent);
    void mouseMoveEvent(QMouseEvent *eventMove);
private:
    QString txt;
    int X,Y;
    int w = 0,h = 0;
    QFont font;
};

#endif // WORD_H
