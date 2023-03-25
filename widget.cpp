#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    // Shape
    ui->shapeCombo->addItem(tr("Polygon"), ShapeCanvas::Polygon);
    ui->shapeCombo->addItem(tr("Rect"), ShapeCanvas::Rect);
    ui->shapeCombo->addItem(tr("RoundedRect"), ShapeCanvas::RoundedRect);
    ui->shapeCombo->addItem(tr("Ellipse"), ShapeCanvas::Ellipse);
    ui->shapeCombo->addItem(tr("Pie"), ShapeCanvas::Pie);
    ui->shapeCombo->addItem(tr("Chord"), ShapeCanvas::Chord);
    ui->shapeCombo->addItem(tr("Text"), ShapeCanvas::Text);
    ui->shapeCombo->addItem(tr("Pixmap"), ShapeCanvas::Pixmap);

    // Pen style
    ui->penStyleCombo->addItem(tr("SolidLine"), static_cast<int>(Qt::SolidLine));
    ui->penStyleCombo->addItem(tr("DashLine"), static_cast<int>(Qt::DashLine));
    ui->penStyleCombo->addItem(tr("DotLine"), static_cast<int>(Qt::DotLine));
    ui->penStyleCombo->addItem(tr("DashDotLine"), static_cast<int>(Qt::DashDotLine));
    ui->penStyleCombo->addItem(tr("DashDotDotLine"), static_cast<int>(Qt::DashDotDotLine));
    ui->penStyleCombo->addItem(tr("None"), static_cast<int>(Qt::NoPen));

    // Pen Cap
    ui->penCapCombo->addItem(tr("SquareCap"), Qt::SquareCap);
    ui->penCapCombo->addItem(tr("FlatCap"), Qt::FlatCap);
    ui->penCapCombo->addItem(tr("RoundCap"), Qt::RoundCap);

    // Pen Join
    ui->penJoinCombo->addItem(tr("BevelJoin"), Qt::BevelJoin);
    ui->penJoinCombo->addItem(tr("MiterJoin"), Qt::MiterJoin);
    ui->penJoinCombo->addItem(tr("RoundJoin"), Qt::RoundJoin);

    // Brush
    ui->brushStyleCombo->addItem(tr("SolidPattern"), static_cast<int>(Qt::SolidPattern));
    ui->brushStyleCombo->addItem(tr("Dense1Pattern"), static_cast<int>(Qt::Dense1Pattern));
    ui->brushStyleCombo->addItem(tr("Dense2Pattern"), static_cast<int>(Qt::Dense2Pattern));
    ui->brushStyleCombo->addItem(tr("Dense3Pattern"), static_cast<int>(Qt::Dense3Pattern));
    ui->brushStyleCombo->addItem(tr("Dense4Pattern"), static_cast<int>(Qt::Dense4Pattern));
    ui->brushStyleCombo->addItem(tr("Dense5Pattern"), static_cast<int>(Qt::Dense5Pattern));
    ui->brushStyleCombo->addItem(tr("Dense6Pattern"), static_cast<int>(Qt::Dense6Pattern));
    ui->brushStyleCombo->addItem(tr("Dense7Pattern"), static_cast<int>(Qt::Dense7Pattern));
    ui->brushStyleCombo->addItem(tr("None"), static_cast<int>(Qt::NoBrush));
    ui->brushStyleCombo->addItem(tr("HorPattern"), static_cast<int>(Qt::HorPattern));
    ui->brushStyleCombo->addItem(tr("VerPattern"), static_cast<int>(Qt::VerPattern));
    ui->brushStyleCombo->addItem(tr("CrossPattern"), static_cast<int>(Qt::CrossPattern));
    ui->brushStyleCombo->addItem(tr("BDiagPattern"), static_cast<int>(Qt::BDiagPattern));
    ui->brushStyleCombo->addItem(tr("FDiagPattern"), static_cast<int>(Qt::FDiagPattern));
    ui->brushStyleCombo->addItem(tr("DiagCrossPattern"), static_cast<int>(Qt::DiagCrossPattern));
    ui->brushStyleCombo->addItem(tr("LinearGradientPattern"), static_cast<int>(Qt::LinearGradientPattern));
    ui->brushStyleCombo->addItem(tr("RadialGradientPattern"), static_cast<int>(Qt::RadialGradientPattern));
    ui->brushStyleCombo->addItem(tr("ConicalGradientPattern"), static_cast<int>(Qt::ConicalGradientPattern));
    ui->brushStyleCombo->addItem(tr("TexturePattern"), static_cast<int>(Qt::TexturePattern));

    m_ptrCanvas = new ShapeCanvas(this);
    ui->canvasLayout->addWidget(m_ptrCanvas);

    penChanged();
    brushChanged();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_shapeCombo_activated(int index)
{
    ShapeCanvas::Shape shape = ShapeCanvas::Shape(index);
    m_ptrCanvas->setShape(shape);
}

void Widget::on_penWidthSpinBox_valueChanged(int arg1)
{
    Q_UNUSED(arg1);
    penChanged();
}

void Widget::on_penStyleCombo_activated(int index)
{
    Q_UNUSED(index);
    penChanged();
}

void Widget::on_penCapCombo_activated(int index)
{
    penChanged();
}

void Widget::on_penJoinCombo_activated(int index)
{
    Q_UNUSED(index);
    penChanged();
}

void Widget::on_brushStyleCombo_activated(int index)
{
    Q_UNUSED(index);
    brushChanged();
}

void Widget::on_antialiasingCheckBox_toggled(bool checked)
{
    m_ptrCanvas->setAntialiased(checked);
}

void Widget::on_transformsCheckBox_toggled(bool checked)
{
    m_ptrCanvas->setTransfored(checked);
}

void Widget::penChanged()
{
    int penWidth = ui->penWidthSpinBox->value();
    Qt::PenStyle penStyle = Qt::PenStyle(ui->penStyleCombo->itemData(
                                             ui->penStyleCombo->currentIndex()).toInt());
    Qt::PenCapStyle penCapStyle = Qt::PenCapStyle(ui->penCapCombo->itemData(
                                                      ui->penCapCombo->currentIndex()).toInt());
    Qt::PenJoinStyle penJoinStyle = Qt::PenJoinStyle(ui->penJoinCombo->itemData(
                                                         ui->penJoinCombo->currentIndex()).toInt());

    QPen pen;
    pen.setWidth(penWidth);
    pen.setStyle(penStyle);
    pen.setCapStyle(penCapStyle);
    pen.setJoinStyle(penJoinStyle);

    m_ptrCanvas->setPen(pen);
}

void Widget::brushChanged()
{
    Qt::BrushStyle brushStyle = Qt::BrushStyle(ui->brushStyleCombo->itemData(
                                                   ui->brushStyleCombo->currentIndex()).toInt());

    if (brushStyle == Qt::LinearGradientPattern)
    {
        QLinearGradient linearGradient(0, 0, 100, 100);
        linearGradient.setColorAt(0.0, Qt::red);
        linearGradient.setColorAt(0.2, Qt::green);
        linearGradient.setColorAt(1.0, Qt::blue);
        m_ptrCanvas->setBrush(linearGradient);
    }
    else if (brushStyle == Qt::RadialGradientPattern)
    {
        QRadialGradient radialGradient(50, 50, 50, 70, 70);
        radialGradient.setColorAt(0.0, Qt::red);
        radialGradient.setColorAt(0.2, Qt::green);
        radialGradient.setColorAt(1.0, Qt::blue);
        m_ptrCanvas->setBrush(radialGradient);
    }
    else if (brushStyle == Qt::ConicalGradientPattern)
    {
        QConicalGradient conicalGradient(50, 50, 150);
        conicalGradient.setColorAt(0.0, Qt::red);
        conicalGradient.setColorAt(0.2, Qt::green);
        conicalGradient.setColorAt(1.0, Qt::blue);
        m_ptrCanvas->setBrush(conicalGradient);
    }
    else if (brushStyle == Qt::TexturePattern)
    {
        m_ptrCanvas->setBrush(QBrush(QPixmap(":/images/LearnQt.png")));
    }
    else
    {
        m_ptrCanvas->setBrush(QBrush(Qt::blue, brushStyle));
    }
}
