#ifndef LCDNUMBER_STACKMAT_H
#define LCDNUMBER_STACKMAT_H

#include <QTime>

#include <QtWidgets/QLCDNumber>

class LCDNumber_Stackmat : public QLCDNumber
{
public:
    LCDNumber_Stackmat(QWidget * parent = 0);

    void saveTime();
    QTime getTime();

    QTime    _timer;

private :
    QTime     _finalTime;
};

#endif // LCDNUMBER_STACKMAT_H
