#ifndef SHAPECANVAS_H
#define SHAPECANVAS_H

#include <QWidget>
#include <QPen>
#include <QBrush>

class ShapeCanvas : public QWidget
{
    Q_OBJECT
public:
    enum Shape { Polygon, Rect, RoundedRect,
               Ellipse, Pie, Chord, Text, Pixmap };
    explicit ShapeCanvas(QWidget *parent = nullptr);

    QSize minimumSizeHint() const override;
    QSize sizeHint() const override;

    Shape shape() const;
    void setShape(Shape newShape);

    QPen pen() const;
    void setPen(const QPen &newPen);

    QBrush brush() const;
    void setBrush(const QBrush &newBrush);

    bool antialiased() const;
    void setAntialiased(bool newAntialiased);

    bool transfored() const;
    void setTransfored(bool newTransfored);

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;

private:
    Shape m_shape;
    QPen m_pen;
    QBrush m_brush;
    bool m_antialiased;
    bool m_transfored;
    QPixmap m_pixmap;
};

#endif // SHAPECANVAS_H
