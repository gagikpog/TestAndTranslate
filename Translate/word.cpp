#include "word.h"
#include "constructorform.h"
#include <QColor>


int Word::currentID = 0;

Word::Word(QWidget *parent) : QWidget(parent)
{
    //счетчик объектов типа Word (статическая переменная)
    currentID++;
    //нумеруем объекты
    id = currentID;
}

void Word::setText(QString t)
{
    //присвоить текст
    txt = t;
    //создается font для определения ширины и высоты шрифта чтоб соответственно задать размеры объекта
    font = QFont("ubuntu",11);
    QFontMetrics fm(font);
    int pixelsWide = fm.width(txt);
    int pixelsHigh = fm.height();
    //задается размер объекта
    setGeometry(pos().x(),pos().y(),pixelsWide+50,pixelsHigh+20);
}

void Word::rmBack()
{
    //из цепочки убрать следующий объект
    //если объект существует
    if(next)
    {
        //берется указатель на нее
        Word* ptr = next;
        //убираю объект
        next = NULL;
        //для него освобождаю перед
        ptr->rmFront();
    }
}

void Word::rmFront()
{
    //из цепочки убрать предыдущий объект
    //если объект существует
    if(prev)
    {
        //берется указатель на нее
        Word* ptr = prev;
        //убираю объект
        prev = NULL;
        //для него освобождаю зад
        ptr->rmBack();
    }
}

void Word::setBack(Word *word)
{
    //привязать объект сзади
    //если объект существует
    if(word)
    {
        //и я не пытаюсь повторно его добавить
        if(next != word)
        {
            //если сзади уже прикреплен объект то его нужно сместить
            if(next)
            {
                //берется указатель на нее
                Word* ptr = next;
                //убираю объект
                rmBack();
                //задаю новую позицию
                ptr->setPos(QPoint(posEnd().x(),posEnd().y()+height()*1.5));
            }
            //добавляю сзади
            next = word;
            next->setFront(this);
            //сместить объект в цепочку
            next->setPos(posEnd());
        }
    }
}

void Word::setFront(Word *word)
{
    //привязать объект спереди
    //если объект существует
    if(word)
    {
        //и я не пытаюсь повторно его добавить
        if(prev != word)
        {
            //если спереди уже прикреплен объект то его нужно открепить
            if(prev)
                rmFront();
            //добавляю спереди
            prev = word;
            prev->setBack(this);
        }
    }
}

void Word::setPos(QPoint position)
{
    //задается позиция
    setGeometry(position.x(),position.y(),width(),height());
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

QPoint Word::posEnd()const
{
    //возвращает позицию правой стороны объекта
    return QPoint(pos().x()+width(),pos().y());
}

QPoint Word::posBegin() const
{
    return pos();
}

QPoint Word::randomPos()
{
    //задается рандомная позиция в пределах родительского контейнера
    setPos(QPoint(rand()%(((ConstructorForm*) parent())->width()-100),rand()%(((ConstructorForm*) parent())->height()-100)+25));
    return pos();
}

void Word::paintEvent(QPaintEvent *event)
{
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

    //получаем размеры объекта
    QRect rect = event->rect();
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
    polygonMain << QPoint(l, 0) << QPoint(width(),0);

    //рисуем зад (полукруг)
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

    //если сзади есть объект полукруг заливаем
    if(next)
    {
        //убираю контур
        painter.setPen(brushCol);
        //рисую
        painter.drawPolygon(polygonE);
        //возвращаю контур
        painter.setPen(penCol);
    }

    //нижняя сторона
    polygonMain << QPoint(width(),height()) << QPoint(l, height());

    //передняя сторона (полукруг)
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

    //рисую текст
    painter.setFont(font);
    painter.drawText(rect, Qt::AlignCenter,txt);
}

void Word::mousePressEvent(QMouseEvent *eventPress)
{
    //событие при нажатии мыши
    //сохраняю позицию мыши на объекте
    w = eventPress->pos().x();
    h = eventPress->pos().y();

    //поднимаю объект на передний план
    show();
    activateWindow();
    raise();

    //нахожу общую ширину цепочки
    const Word* ptr = this;
    for(;ptr->Next();ptr = ptr->Next());
    allBlocsWidth = ptr->posEnd().x() - pos().x();
}

void Word::mouseReleaseEvent(QMouseEvent *)
{
    //событие при отжатии мыши
    //перерисовать все объекты
    ((ConstructorForm*)(parent()->parent()))->ListConnect(id);
}

void Word::mouseMoveEvent(QMouseEvent *)
{
    //событие при движении мыши
    //позиция курсора
    QPoint cousorPos = QCursor::pos();
    //позиция родительского контейнера
    QGroupBox* prnt = ((QGroupBox*)parent());
    QPoint parentPos = parentWidget()->mapToGlobal(QPoint(0,0));
    //сдвигаю на позицию при нажатии
    cousorPos.rx() -= w;
    cousorPos.ry() -= h;

    //проверка чтоб не выходила за левый край
    if(cousorPos.x() < parentPos.x())
        cousorPos.rx() = parentPos.x();
    //проверка чтоб не выходила за верхний край
    if(cousorPos.y() < parentPos.y()+25)
        cousorPos.ry() = parentPos.y()+25;
    //проверка чтоб не выходила за правый край
    if(cousorPos.x() + allBlocsWidth > prnt->width() + parentPos.x())
        cousorPos.rx() = parentPos.x() + prnt->width() - allBlocsWidth;
    //проверка чтоб не выходила за нижний край
    if(cousorPos.y() + height() > prnt->height() + parentPos.y())
        cousorPos.ry() = parentPos.y() + prnt->height() - height();

    //переместить объект
    move(parentWidget()->mapFromGlobal(cousorPos));

    //если спереди есть объект то отсоединить его
    if(prev)
        prev->rmBack();
    //если сзади есть объект то его тоже сместить
    if(next)
        next->setPos(QPoint(pos().x()+width(),pos().y()));
    else ListUpdate();
}

void Word::ListUpdate()
{
    //обновить все
    ((ConstructorForm*)(parent()->parent()))->ListUpdate(id);
}
