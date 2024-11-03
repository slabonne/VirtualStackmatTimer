#ifndef QLABELSTACKMAT_H
#define QLABELSTACKMAT_H

#include <QtWidgets/QLabel>

class MainWindow;

class QLabelStackmat : public QLabel
{
    Q_OBJECT

    private:
        MainWindow * _frame;

    public:
        QLabelStackmat(QWidget * parent, MainWindow * _frame);

    protected:
        void mousePressEvent(QMouseEvent *e);
};

#endif // QLABELSTACKMAT_H
