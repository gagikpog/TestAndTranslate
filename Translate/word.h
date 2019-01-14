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
    virtual QPoint posEnd()const;
    virtual QPoint posBegin()const;
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
    Word* next = NULL;
    Word* prev = NULL;
    int allBlocsWidth = height();
    void ListUpdate();
private:
    QString txt;
    int X,Y;
    int w = 0,h = 0;
    int id;
    QFont font;
    static int currentID;
};

#endif // WORD_H
