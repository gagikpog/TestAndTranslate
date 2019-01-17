#include "linefeed.h"
#include "constructorform.h"
#include <QVector>
#include <QDebug>

LineFeed::LineFeed()
{
    Init();
}

LineFeed::LineFeed(QWidget *parent): Word(parent)
{
    Init();
}

void LineFeed::setText(QString)
{

}

QPoint LineFeed::posEnd() const
{
    return QPoint(pos().x() + tailPos.x() + tailSize.x(),pos().y() + tailPos.y());
}

QPoint LineFeed::posBegin() const
{
    return QPoint(headPos.x()+pos().x(),headPos.y()+pos().y());
}


void LineFeed::paintEvent(QPaintEvent* paint)
{
    //head
    //рисуется объект
    //передний отступ
    int l = 16;
    //если спереди есть объект убирается отступ
    if(prev)
        l = 0;
    //цвет обводки и текста
    QColor penCol(Qt::black);
    //цвет заливки
    QColor brushCol(20,250,250);
    //создаются объект для рисования
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    //задается цвета отрисовки
    painter.setPen(penCol);
    painter.drawRect(paint->rect());
    painter.setBrush(brushCol);

    //объект с помощью которого рисуем полигонами
    QPolygon polygonMain;
    //начинаем рисовать

    //рисуем верх
    polygonMain << QPoint(headPos.x() + l, headPos.y())
                << QPoint(headPos.x() + headSize.x(),headPos.y());
    //нижняя сторона
    polygonMain << QPoint(headPos.x() + headSize.x(),headPos.y() + headSize.y())
                << QPoint(headPos.x() + l,headPos.y() + headSize.y());

    //передняя сторона (полукруг)
    QPolygon polygonB;
    polygonB<< QPoint(headPos.x() + 16,headPos.y() + headSize.y()*0.65)
            << QPoint(headPos.x() + 14,headPos.y() + headSize.y()*0.65)
            << QPoint(headPos.x() + 12,headPos.y() + headSize.y()*0.70)
            << QPoint(headPos.x() + 5, headPos.y() + headSize.y()*0.75)
            << QPoint(headPos.x() + 2, headPos.y() + headSize.y()*0.70)

            << QPoint(headPos.x() + 0, headPos.y() + headSize.y()*0.50)

            << QPoint(headPos.x() + 2, headPos.y() + headSize.y()*0.30)
            << QPoint(headPos.x() + 5, headPos.y() + headSize.y()*0.25)
            << QPoint(headPos.x() + 12,headPos.y() + headSize.y()*0.30)
            << QPoint(headPos.x() + 14,headPos.y() + headSize.y()*0.35)
            << QPoint(headPos.x() + 16,headPos.y() + headSize.y()*0.35);

    //если спереди нет объекта то рисуем полукруг
    if(!prev)
    {
        //убираю контур
        painter.setPen(brushCol);
        //рисую полигони
        painter.drawPolygon(polygonB);
        //возвращаю контур
        painter.setPen(penCol);
        polygonMain << polygonB;
    }

    painter.drawPolygon(polygonMain);

    if(prev)
    {
        //задаю толщину линий 3px
        painter.setPen(QPen(brushCol,3));
        //рисую линию
        painter.drawLine(QPoint(headPos.x(),headPos.y() + 3),QPoint(headPos.x(),headPos.y() + headSize.y() - 3));
        //задаю толщину линий 1px
        painter.setPen(QPen(penCol,1));
    }

    //////////////////////
    //tail
    QPainter painter2(this);
    painter2.setRenderHint(QPainter::Antialiasing);
    //задается цвета отрисовки
    painter2.setPen(penCol);
    painter2.setBrush(brushCol);
    QPolygon polygonMain2;

    polygonMain2 << QPoint(tailPos.x(),tailPos.y())
                 << QPoint(tailPos.x()+tailSize.x(),tailPos.y());

    //рисуем зад (полукруг)
    QPolygon polygonE;
    polygonE<< QPoint(tailPos.x() + tailSize.x()   ,tailPos.y() + tailSize.y()*0.35)
            << QPoint(tailPos.x() + tailSize.x()-2 ,tailPos.y() + tailSize.y()*0.35)
            << QPoint(tailPos.x() + tailSize.x()-4 ,tailPos.y() + tailSize.y()*0.30)
            << QPoint(tailPos.x() + tailSize.x()-11,tailPos.y() + tailSize.y()*0.25)
            << QPoint(tailPos.x() + tailSize.x()-14,tailPos.y() + tailSize.y()*0.30)

            << QPoint(tailPos.x() + tailSize.x()-16,tailPos.y() + tailSize.y()*0.50)

            << QPoint(tailPos.x() + tailSize.x()-14,tailPos.y() + tailSize.y()*0.70)
            << QPoint(tailPos.x() + tailSize.x()-11,tailPos.y() + tailSize.y()*0.75)
            << QPoint(tailPos.x() + tailSize.x()-4 ,tailPos.y() + tailSize.y()*0.70)
            << QPoint(tailPos.x() + tailSize.x()-2 ,tailPos.y() + tailSize.y()*0.65)
            << QPoint(tailPos.x() + tailSize.x()   ,tailPos.y() + tailSize.y()*0.65);

    polygonMain2 << polygonE;

    polygonMain2 << QPoint(tailPos.x()+tailSize.x(),tailPos.y()+tailSize.y())
                 << QPoint(tailPos.x(),tailPos.y()+tailSize.y());

    //если сзади есть объект полукруг заливаем
    if(next)
    {
        //убираю контур
        painter2.setPen(brushCol);
        //рисую
        painter2.drawPolygon(polygonE);
        //возвращаю контур
        painter2.setPen(penCol);
    }
    painter2.drawPolygon(polygonMain2);
    //line
    QPainter painterLine(this);
    painterLine.setPen(Qt::black);
    QVector<QPoint> points;
    points.append(QPoint(headPos.x()+headSize.x(),headPos.y()+headSize.y()*0.5));
    points.append(QPoint(headPos.x()+headSize.x()+50,headPos.y()+headSize.y()*0.5));

    points.append(QPoint(headPos.x()+headSize.x()+50,headPos.y()+headSize.y()*0.5));
    points.append(QPoint(headPos.x()+headSize.x()+50,(headPos.y()+tailPos.y()+headSize.y())*0.5));

    points.append(QPoint(headPos.x()+headSize.x()+50,(headPos.y()+tailPos.y()+headSize.y())*0.5));
    points.append(QPoint(tailPos.x()-50,(headPos.y()+tailPos.y()+headSize.y())*0.5));

    points.append(QPoint(tailPos.x()-50,(headPos.y()+tailPos.y()+headSize.y())*0.5));
    points.append(QPoint(tailPos.x()-50,tailPos.y()+tailSize.y()*0.5));

    points.append(QPoint(tailPos.x()-50,tailPos.y()+tailSize.y()*0.5));
    points.append(QPoint(tailPos.x(),tailPos.y()+tailSize.y()*0.5));
    painterLine.drawLines(points);
    for(int i = 0;i<points.length();i++)
        points[i] = QPoint(points[i].x()+1,points[i].y()+1);
    painterLine.setPen(Qt::white);
    painterLine.drawLines(points);
}

void LineFeed::mousePressEvent(QMouseEvent *eventPress)
{
    QPoint p = eventPress->pos();

    const Word* ptr = this;
    for(;ptr->Next();ptr = ptr->Next());
    allBlocsWidth = ptr->posEnd().x() - pos().x();

    if(p.x()>headPos.x() && p.x()<headPos.x()+headSize.x() && p.y()>headPos.y()&&p.y()<headPos.y()+headSize.y())
    {
        cursorPos = eventPress->pos();
        move = moveStatus::Begin;
        return;
    }
    if(p.x()>tailPos.x() && p.x()<tailPos.x()+tailSize.x() && p.y()>tailPos.y()&&p.y()<tailPos.y()+tailSize.y())
    {
        cursorPos = eventPress->pos()-tailPos;
        move = moveStatus::End;
        return;
    }
    move = moveStatus::None;
}

void LineFeed::mouseReleaseEvent(QMouseEvent *)
{
    //событие при отжатии мыши
    //перерисовать все объекты
    ((ConstructorForm*)(parent()->parent()))->ListConnect(ID());
}

void LineFeed::mouseMoveEvent(QMouseEvent *eventMove)
{
    if(move == moveStatus::Begin)
    {
        //позиция курсора
        QPoint point = QCursor::pos();
        //позиция родительского контейнера
        QGroupBox* prnt = ((QGroupBox*)parent());
        QPoint parentPos = parentWidget()->mapToGlobal(QPoint(0,0));
        //сдвигаю на позицию при нажатии
        point.rx() -= cursorPos.x();
        point.ry() -= cursorPos.y();

        allBlocsWidth = 0;

        //проверка чтоб не выходила за левый край
        if(point.x() < parentPos.x())
            point.rx() = parentPos.x();
        //проверка чтоб не выходила за верхний край
        if(point.y() < parentPos.y()+25)
            point.ry() = parentPos.y()+25;
        //проверка чтоб не выходила за правый край
        if(point.x() + allBlocsWidth > prnt->width() + parentPos.x())
            point.rx() = parentPos.x() + prnt->width() - allBlocsWidth;
        //проверка чтоб не выходила за нижний край
        if(point.y() + height() > prnt->height() + parentPos.y())
            point.ry() = parentPos.y() + prnt->height() - height();

        //переместить объект
        //move(parentWidget()->mapFromGlobal(point));
        QPoint p = parentWidget()->mapFromGlobal(point);
        int dx = p.x()-pos().x();
        int dy = p.y()-pos().y();
        tailPos.rx() -= dx;
        tailPos.ry() -= dy;
        setPosG(p,width()-dx,height()-dy);
        //setPos(p);
        //setGeometry();
        //если спереди есть объект то отсоединить его
        if(prev)
            prev->rmBack();
    }
    if(move == moveStatus::End)
    {
        QPoint point = QCursor::pos();
        //позиция родительского контейнера
        QGroupBox* prnt = ((QGroupBox*)parent());
        QPoint parentPos = parentWidget()->mapToGlobal(QPoint(0,0));
        //сдвигаю на позицию при нажатии
        point.rx() -= cursorPos.x();
        point.ry() -= cursorPos.y();

        //проверка чтоб не выходила за левый край
        if(point.x() < parentPos.x())
            point.rx() = parentPos.x();
        //проверка чтоб не выходила за верхний край
        if(point.y() < parentPos.y()+25)
            point.ry() = parentPos.y()+25;
        //проверка чтоб не выходила за правый край
        if(point.x() + allBlocsWidth > prnt->width() + parentPos.x())
            point.rx() = parentPos.x() + prnt->width() - allBlocsWidth;
        //проверка чтоб не выходила за нижний край
        if(point.y() + tailSize.y() > prnt->height() + parentPos.y())
            point.ry() = parentPos.y() + prnt->height() - tailSize.y();

        //переместить объект
        //move(parentWidget()->mapFromGlobal(point));
        //QPoint p = parentWidget()->mapFromGlobal(point);
        //int dx = p.x()-pos().x();
        //int dy = p.y()-pos().y();
        //tailPos.rx() -= dx;
        //tailPos.ry() -= dy;
        //qDebug()<< point.x()<<" "<<point.y();
        tailPos = point-parentPos-pos();
        //setPosG(p,width()-dx,height()-dy);
        setPos(pos());
        repaint();
    }
}

void LineFeed::setPosG(QPoint position,int w,int h)
{
    //задается позиция
    setGeometry(position.x(),position.y(),w,h);
    //если сзади есть объект то он смещается вместе с ним
    if(next)
    {
        //задать позицию
        QPoint  p = posEnd();
        next->setPos(p);
    }  else {
        //иначе этот объект последний в цепочке и нужно перерисовать все объекты
        ListUpdate();
    }
}

void LineFeed::Init()
{
    int pixelsHigh = (QFontMetrics(QFont("ubuntu",11))).height()+20;
    headPos = QPoint(0,0);
    headSize = QPoint(80,pixelsHigh);
    tailPos = QPoint(60,pixelsHigh+20);
    tailSize = headSize;
    setGeometry(pos().x(),pos().y(),140,pixelsHigh*2+20);
}

