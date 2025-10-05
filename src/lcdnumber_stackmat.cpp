#include "lcdnumber_stackmat.h"

LCDNumber_Stackmat::LCDNumber_Stackmat(QWidget * parent)
    : QLCDNumber(parent)
{

}

void LCDNumber_Stackmat::saveTime()
{
    _finalTime = _timer;
}

QElapsedTimer LCDNumber_Stackmat::getTime()
{
    return _finalTime;
}
