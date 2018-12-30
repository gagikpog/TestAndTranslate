#include "word.h"
#include "constructorform.h"
#include <QColor>


int Word::currentID = 0;

Word::Word(QWidget *parent) : QWidget(parent)
{
    txt = "text";
    id = currentID;
    currentID++;
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

void Word::rmBack()
{
    if(next)
    {
        Word* ptr = next;
        next = NULL;
        ptr->rmFront();
    }
}

void Word::rmFront()
{
    if(prev)
    {
        Word* ptr = prev;
        prev = NULL;
        ptr->rmBack();
    }
}

void Word::setBack(Word *word)
{
    if(word)
    {
        if(next != word)
        {
            if(next)
            {
                Word* ptr = next;
                rmBack();
                ptr->setPos(QPoint(posEnd().x(),posEnd().y()+height()*1.5));
            }
            next = word;
            next->setFront(this);
            next->setPos(posEnd());
        }
    }
}

void Word::setFront(Word *word)
{
    if(word)
    {
        if(prev != word)
        {
            if(prev)
                rmFront();
            prev = word;
            prev->setBack(this);
        }
    }
}

void Word::setPos(QPoint position)
{
    setGeometry(position.x(),position.y(),width(),height());
    if(next)
    {
        next->setPos(posEnd());
    }  else {
        ListUpdate();
    }
}

QPoint Word::posEnd()const
{
    return QPoint(pos().x()+width(),pos().y());
}

QPoint Word::randomPos()
{
    setPos(QPoint(rand()%(((ConstructorForm*) parent())->width()-100),rand()%(((ConstructorForm*) parent())->height()-100)+25));
    return pos();
}

void Word::paintEvent(QPaintEvent *event)
{
    int l = 16;
    if(prev)
        l = 0;
    QColor penCol(Qt::black);
    QColor brushCol(20,250,250);

    QRect rect = event->rect();
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(penCol);
    painter.setBrush(brushCol);

    QPolygon polygonMain;
    polygonMain << QPoint(l, 0) << QPoint(width(),0);

    QPolygon polygonE;
    polygonE << QPoint(width(),height()*0.35);
    polygonE << QPoint(width()-2,height()*0.35);
    polygonE << QPoint(width()-4,height()*0.3);
    polygonE << QPoint(width()-11,height()*0.25);
    polygonE << QPoint(width()-14,height()*0.30);

    polygonE << QPoint(width()-16,height()/2);

    polygonE << QPoint(width()-14,height()*0.7);
    polygonE << QPoint(width()-11,height()*0.75);
    polygonE << QPoint(width()-4,height()*0.7);
    polygonE << QPoint(width()-2,height()*0.65);
    polygonE << QPoint(width(),height()*0.65);
    polygonMain << polygonE;

    if(next)
    {
        painter.setPen(brushCol);
        painter.drawPolygon(polygonE);
        painter.setPen(penCol);
    }

    polygonMain << QPoint(width(),height()) << QPoint(l, height());

    QPolygon polygonB;
    polygonB << QPoint(16,height()*0.65);
    polygonB << QPoint(14,height()*0.65);
    polygonB << QPoint(12,height()*0.7);
    polygonB << QPoint(5,height()*0.75);
    polygonB << QPoint(2,height()*0.7);

    polygonB << QPoint(0,height()/2);

    polygonB << QPoint(2,height()*0.30);
    polygonB << QPoint(5,height()*0.25);
    polygonB << QPoint(12,height()*0.3);
    polygonB << QPoint(14,height()*0.35);
    polygonB << QPoint(16,height()*0.35);

    if(!prev)
    {
        painter.setPen(brushCol);
        painter.drawPolygon(polygonB);
        painter.setPen(penCol);
        polygonMain << polygonB;
    }

    painter.drawPolygon(polygonMain);

    if(prev)
    {
        painter.setPen(QPen(brushCol,3));
        painter.drawLine(QPoint(0,3),QPoint(0,height()-3));
        painter.setPen(QPen(penCol,1));
    }
    /*
    txt = "";
    if(prev)
        txt = QString::number(prev->ID());
    txt += "|" +QString::number(id)+ "|";
    if(next)
        txt += QString::number(next->ID());
    */
    painter.setFont(font);
    painter.drawText(rect, Qt::AlignCenter,txt);
}

void Word::mousePressEvent(QMouseEvent *eventPress)
{
    QPoint p = eventPress->pos();
    w = p.x();
    h = p.y();

    show();
    activateWindow();
    raise();
    const Word* ptr = this;
    for(;ptr->Next();ptr = ptr->Next());
    allBlocsWidth = ptr->posEnd().x() - pos().x();
}

void Word::mouseReleaseEvent(QMouseEvent *)
{
    ((ConstructorForm*)(parent()->parent()))->ListConnect(id);
}

void Word::mouseMoveEvent(QMouseEvent *)
{
    QPoint cousorPos = QCursor::pos();
    QGroupBox* prnt = ((QGroupBox*)parent());
    QPoint parentPos = parentWidget()->mapToGlobal(QPoint(0,0));
    cousorPos.rx() -= w;
    cousorPos.ry() -= h;

    if(cousorPos.x() < parentPos.x())
        cousorPos.rx() = parentPos.x();
    if(cousorPos.y() < parentPos.y()+25)
        cousorPos.ry() = parentPos.y()+25;
    if(cousorPos.x() + allBlocsWidth > prnt->width() + parentPos.x())
        cousorPos.rx() = parentPos.x() + prnt->width() - allBlocsWidth;
    if(cousorPos.y() + height() > prnt->height() + parentPos.y())
        cousorPos.ry() = parentPos.y() + prnt->height() - height();

    move(parentWidget()->mapFromGlobal(cousorPos));

    if(prev)
        prev->rmBack();
    if(next)
        next->setPos(QPoint(pos().x()+width(),pos().y()));
    ListUpdate();
}

void Word::ListUpdate()
{
    ((ConstructorForm*)(parent()->parent()))->ListUpdate(id);
}
