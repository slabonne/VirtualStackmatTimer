#include "mainwindow.h"
#include "qlabelstackmat.h"

QLabelStackmat::QLabelStackmat(QWidget * parent, MainWindow * frame)
    : QLabel(parent)
{
    _frame = frame;
}

void QLabelStackmat::mousePressEvent(QMouseEvent *e)
{
    _frame->resetChrono();
}
