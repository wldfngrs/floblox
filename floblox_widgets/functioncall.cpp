#include "functioncall.h"

FunctionCall::FunctionCall(QWidget *parent, uint y)
    : QWidget{parent}
{
    this->setObjectName("FlobloxFunctionCall");
    this->setGeometry(QRect(10, y, 601, 71));
    this->setStyleSheet(QString::fromUtf8("background-color: lightblue;\n"
"border: 2px solid #444;\n"
"border-radius: 5px;"));

    this->label = new QLabel(this);
    this->label->setObjectName("FlobloxFunctionCallLabel");
    this->label->setGeometry(QRect(220, 10, 161, 20));

    this->font.setFamilies({QString::fromUtf8("Courier New")});
    this->font.setPointSize(12);
    this->font.setBold(true);
    this->font.setItalic(false);
    this->font.setUnderline(false);
    this->font.setKerning(true);

    this->label->setFont(this->font);
    this->label->setStyleSheet(QString::fromUtf8("border: none"));
    this->label->setAlignment(Qt::AlignmentFlag::AlignCenter);
    this->label->setText("Function Call");

    this->defined_functions = new QComboBox(this);
    // add defined functions to the combo box
    this->defined_functions->addItem(QString("Line Output"));
    this->defined_functions->addItem(QString("Line Input"));
    this->defined_functions->setObjectName("DefinedFunctions");
    this->defined_functions->setGeometry(QRect(10, 40, 431, 21));
    this->defined_functions->setFont(this->font);

    this->function_arguments = new QToolButton(this);
    this->function_arguments->setObjectName("FunctionArguments");
    this->function_arguments->setGeometry(QRect(450, 40, 131, 21));
    this->function_arguments->setFont(this->font);
    this->function_arguments->setText("Arguments");

    this->setAttribute(Qt::WA_StyledBackground, true);
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    this->show();
}

//QSize FunctionCall::sizeHint() const {
    // Tell Qt the widget's preferred size
    //return QSize(601, 71);  // width, height
//}

void FunctionCall::mousePressEvent(QMouseEvent *event)
{

}
void FunctionCall::mouseMoveEvent(QMouseEvent *event)
{

}
