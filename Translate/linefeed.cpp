#include "linefeed.h"
#include "constructorform.h"

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
    return headPos;
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
        painter.drawLine(QPoint(0,3),QPoint(0,height()-3));
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
    //painter2.drawRect(paint->rect());
}

void LineFeed::mousePressEvent(QMouseEvent *eventPress)
{

}

void LineFeed::mouseReleaseEvent(QMouseEvent *releaseEvent)
{
    //событие при отжатии мыши
    //перерисовать все объекты
    ((ConstructorForm*)(parent()->parent()))->ListConnect(ID());
}

void LineFeed::mouseMoveEvent(QMouseEvent *eventMove)
{

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
