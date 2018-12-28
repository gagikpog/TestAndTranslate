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
    int ID()const{return id;}
    void rmBack();
    void rmFront();
    void setBack(Word* word);
    void setFront(Word* word);
    void setPos(QPoint position);
    QPoint posEnd()const;
    const Word* Next()const{return next;}
    const Word* Prev()const{return prev;}
    QPoint randomPos();

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
    int id;
    int allBlocsWidth = height();
    QFont font;
    void ListUpdate();
    static int currentID;
    Word* next = NULL;
    Word* prev = NULL;
};

#endif // WORD_H
