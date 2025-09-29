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

    Q_OBJECT
public:
    explicit FunctionCall(QWidget *parent, uint y);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    //QSize sizeHint() const;

signals:
};
#endif // FUNCTIONCALL_H
