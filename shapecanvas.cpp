#include "shapecanvas.h"
#include <QPainter>

ShapeCanvas::ShapeCanvas(QWidget *parent)
    : QWidget{parent}
{
    m_shape = Polygon;
    m_antialiased = false;
    m_transfored = false;
    m_pixmap.load(":/images/LearnQt.png");
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

    // Polygon
    static const QPoint points[4] =
    {
        QPoint(10, 80),
        QPoint(20, 10),
        QPoint(80, 30),
        QPoint(90, 70)
    };

    // Rectangle and things that can use a rectangle
    QRect rect(10, 20, 80, 60);

    // Arcs, pies
    int startAngle = 20 * 16;
    int arcLength = 120 * 26;

    painter.setPen(m_pen);
    painter.setBrush(m_brush);
    painter.setFont(QFont("Consolas", 8, QFont::Bold));

    if (m_antialiased)
        painter.setRenderHint(QPainter::Antialiasing, true);

    // Loop around to draw in all the available space
    for (int x = 0; x < width(); x += 100)
    {
        for (int y = 0; y < height(); y += 100)
        {
            // Save the painter
            painter.save();

            painter.translate(x, y);

            if (m_transfored)
            {
                painter.translate(50, 50);
                painter.rotate(60.0);
                painter.scale(0.6, 0.9);
                painter.translate(-50, -50);
            }

            switch (m_shape)
            {
            case Polygon:
                painter.drawPolygon(points, 4);
                break;

            case Rect:
                painter.drawRect(rect);
                break;

            case RoundedRect:
                painter.drawRoundedRect(rect, 25, 25, Qt::RelativeSize);
                break;

            case Ellipse:
                painter.drawEllipse(rect);
                break;

            case Chord:
                painter.drawChord(rect, startAngle, arcLength);
                break;

            case Pie:
                painter.drawPie(rect, startAngle, arcLength);
                break;

            case Text:
                painter.drawText(rect, Qt::AlignCenter, tr("Qt GUI"));
                break;

            case Pixmap:
                painter.drawPixmap(10, 10, m_pixmap);
            }

            painter.restore();
        }
    }

    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setBrush(Qt::NoBrush);
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
