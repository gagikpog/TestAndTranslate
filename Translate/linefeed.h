#ifndef LINEFEED_H
#define LINEFEED_H

#include <QWidget>
#include "word.h"
#include <QPoint>
#include <QRect>

class LineFeed : public Word
{
public:
    LineFeed();
    explicit LineFeed(QWidget *parent = nullptr);
    void setText(QString t);
    QPoint posEnd()const;
    QPoint posBegin()const;
protected:
    void paintEvent(QPaintEvent* );
    void mousePressEvent(QMouseEvent *eventPress);
    void mouseReleaseEvent(QMouseEvent *releaseEvent);
    void mouseMoveEvent(QMouseEvent *eventMove);
    QPoint headPos;
    QPoint headSize;
    QPoint tailPos;
    QPoint tailSize;
private:
    void Init();

};

#endif // LINEFEED_H
