#ifndef LINEFEED_H
#define LINEFEED_H

#include <QWidget>
#include "word.h"
#include <QPoint>
#include <QRect>

enum moveStatus{
    None,Begin,End
};

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
    void setPosG(QPoint position,int w,int h);
    void Init();
    moveStatus move = moveStatus::None;
    QPoint cursorPos;
};

#endif // LINEFEED_H
