#ifndef LCDNUMBER_STACKMAT_H
#define LCDNUMBER_STACKMAT_H


#include <QtWidgets/QLCDNumber>
#include <QElapsedTimer>

class LCDNumber_Stackmat : public QLCDNumber
{
public:
    LCDNumber_Stackmat(QWidget * parent = 0);

    void saveTime();
    QElapsedTimer getTime();

    QElapsedTimer    _timer;

private :
    QElapsedTimer     _finalTime;
};

#endif // LCDNUMBER_STACKMAT_H
