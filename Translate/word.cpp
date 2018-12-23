#include "word.h"

Word::Word(QWidget *parent) : QWidget(parent)
{
    txt = "text";
}

void Word::setText(QString t)
{
    txt = t;
    font = QFont("ubuntu",11);
    QFontMetrics fm(font);
    int pixelsWide = fm.width(txt);
    int pixelsHigh = fm.height();
    setGeometry(pos().x(),pos().y(),pixelsWide+50,pixelsHigh+20);
}

void Word::paintEvent(QPaintEvent *event)
{
    QRect rect = event->rect();
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(Qt::black);
    painter.setFont(font);
    painter.drawText(rect, Qt::AlignCenter,txt);
    painter.drawRect(rect);
}

void Word::mousePressEvent(QMouseEvent *eventPress)
{
    QPoint p = eventPress->pos();
    w = p.x();
    h = p.y();
}

void Word::mouseReleaseEvent(QMouseEvent *releaseEvent)
{

}

void Word::mouseMoveEvent(QMouseEvent *eventMove)
{
    QPoint cousorPos = QCursor::pos();
    QGroupBox* prnt = ((QGroupBox*)parent());
    QPoint parentPos = parentWidget()->mapToGlobal(QPoint(0,0));
    cousorPos.rx() -= w;
    cousorPos.ry() -= h;

    if(cousorPos.x() < parentPos.x())
        cousorPos.rx() = parentPos.x();
    if(cousorPos.y() < parentPos.y())
        cousorPos.ry() = parentPos.y();
    if(cousorPos.x() + width() > prnt->width() + parentPos.x())
        cousorPos.rx() = parentPos.x() + prnt->width() - width();
    if(cousorPos.y() + height() > prnt->height() + parentPos.y())
        cousorPos.ry() = parentPos.y() + prnt->height() - height();

    move(parentWidget()->mapFromGlobal(cousorPos));
    //txt = QString::number(w)+"|"+QString::number(h)+ "||" + QString::number(parentPos.x())+"|"+QString::number(parentPos.y());
    repaint();
    update();
}
