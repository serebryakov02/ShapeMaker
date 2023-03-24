#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "shapecanvas.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_shapeCombo_activated(int index);
    void on_penWidthSpinBox_valueChanged(int arg1);
    void on_penStyleCombo_activated(int index);
    void on_penCapCombo_activated(int index);
    void on_penJoinCombo_activated(int index);
    void on_brushStyleCombo_activated(int index);
    void on_antialiasingCheckBox_toggled(bool checked);
    void on_transformsCheckBox_toggled(bool checked);

    void penChanged();
    void brushChanged();

private:
    Ui::Widget *ui;
    ShapeCanvas* m_ptrCanvas;
};
#endif // WIDGET_H
