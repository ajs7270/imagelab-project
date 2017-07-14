#include "clickablelabel.h"

ClickableLabel::ClickableLabel(QWidget* parent, Qt::WindowFlags f)
    : QLabel(parent) {

}

ClickableLabel::~ClickableLabel() {}


//for lable mouse event
void ClickableLabel::mousePressEvent(QMouseEvent* event) {
    emit clicked(event);
}

