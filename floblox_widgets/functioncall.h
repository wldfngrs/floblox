#ifndef FUNCTIONCALL_H
#define FUNCTIONCALL_H

#include <QWidget>
#include <QtWidgets/QLabel>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QToolButton>

class FunctionCall : public QWidget
{
    QLabel *label;
    QFont font;
    QComboBox *defined_functions;
    QToolButton *function_arguments;
    QPoint drag_start_pos;
    QPoint click_offset;
    bool emit_drag_start = false;

    Q_OBJECT
public:
    bool dragging = false;
    explicit FunctionCall(QWidget *parent, uint x, uint y);
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    //QSize sizeHint() const;

signals:
    void dragFinished(QWidget* widget, QPoint release_pos);
    void dragStarted(QWidget* widget, QPoint start_pos);
};
#endif // FUNCTIONCALL_H
