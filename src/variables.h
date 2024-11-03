#ifndef VARIABLES_H
#define VARIABLES_H

#include <QString>
#include <QTime>

enum {_STOPPED_, _WAITING_, _READY_, _RUNNING_};

class Variables
{
public:
    Variables();
};


struct Essai
{
    QString     _pseudo;
    int         _temps;
    QString     _date;
    QString     _puzzle;
    bool        _isMoyenne;
};



#endif // VARIABLES_H
