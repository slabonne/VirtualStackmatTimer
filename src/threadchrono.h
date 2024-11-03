#ifndef THREADCHRONO_H
#define THREADCHRONO_H

#include <QThread>
#include <QTime>
#include "lcdnumber_stackmat.h"

class MainWindow;

class ThreadChrono : public QThread
{
public:
    ThreadChrono(MainWindow * parent);

    MainWindow * _mainWindow;

    void run();
};



class ThreadWait : public QThread
{
public:
    ThreadWait(MainWindow * parent);

    MainWindow * _mainWindow;

    void run();
};


#endif // THREADCHRONO_H
