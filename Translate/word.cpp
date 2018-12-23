#include "word.h"

Word::Word(QWidget *parent) : QWidget(parent)
{
    txt = "text";
}

void Word::paintEvent(QPaintEvent *event)
{
    QRect rect = event->rect();
       QPainter painter(this);
       painter.setRenderHint(QPainter::Antialiasing);
       painter.setPen(Qt::black);
       painter.drawText(rect, Qt::AlignCenter,txt);
       painter.drawRect(rect);
       return;

    //QPainter painter(this);
    //QRectF size = QRectF(0,0,width(),height());
   // painter.setBrush(Qt::red);
       //painter.drawPie(size,0,90*16);
}

void Word::mousePressEvent(QMouseEvent *eventPress)
{
    QPoint p = eventPress->pos();
    w = p.x();
    h = p.y();
    //Y = ((QGroupBox*)(parent()))->pos().y();

    //txt = QString::number(w)+"|"+QString::number(h)+ "||" + QString::number(pos().x())+"|"+QString::number(pos().y());
    //repaint();
    //update();
}

void Word::mouseReleaseEvent(QMouseEvent *releaseEvent)
{
}

void Word::mouseMoveEvent(QMouseEvent *eventMove)
{
    QPoint point = QCursor::pos();
    QGroupBox* prnt = ((QGroupBox*)parent());
    QPoint parentPos = QWidget::mapToGlobal(prnt->pos());
    point.rx() -= w;
    point.ry() -= h;

    if(point.x() < parentPos.x())
        point.rx() = parentPos.x();
    if(point.y() < parentPos.y())
        point.ry() = parentPos.y();
    //if(point.x()+width() > prnt->width()+prnt->pos().x())
        //point.rx() = prnt->pos().x() + prnt->width() - width();

    move(parentWidget()->mapFromGlobal(point));
    //setGeometry(eventMove->pos().x(),eventMove->pos().y(),size().width(),size().height());
    txt = QString::number(w)+"|"+QString::number(h)+ "||" + QString::number(eventMove->pos().x())+"|"+QString::number(eventMove->pos().y());
    repaint();
}
