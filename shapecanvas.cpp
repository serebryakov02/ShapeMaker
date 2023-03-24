#include "shapecanvas.h"
#include <QPainter>

ShapeCanvas::ShapeCanvas(QWidget *parent)
    : QWidget{parent}
{

}

QSize ShapeCanvas::minimumSizeHint() const
{
    return QSize(400, 200);
}

QSize ShapeCanvas::sizeHint() const
{
    return QSize(500, 300);
}

void ShapeCanvas::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(Qt::red);
    painter.drawRect(0, 0, width() - 1, height() - 1);
}

bool ShapeCanvas::transfored() const
{
    return m_transfored;
}

void ShapeCanvas::setTransfored(bool newTransfored)
{
    m_transfored = newTransfored;
    update();
}

bool ShapeCanvas::antialiased() const
{
    return m_antialiased;
}

void ShapeCanvas::setAntialiased(bool newAntialiased)
{
    m_antialiased = newAntialiased;
    update();
}

QBrush ShapeCanvas::brush() const
{
    return m_brush;
}

void ShapeCanvas::setBrush(const QBrush &newBrush)
{
    m_brush = newBrush;
    update();
}

QPen ShapeCanvas::pen() const
{
    return m_pen;
}

void ShapeCanvas::setPen(const QPen &newPen)
{
    m_pen = newPen;
    update();
}

ShapeCanvas::Shape ShapeCanvas::shape() const
{
    return m_shape;
}

void ShapeCanvas::setShape(Shape newShape)
{
    m_shape = newShape;
    update();
}
