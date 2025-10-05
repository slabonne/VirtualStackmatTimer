#include "mainwindow.h"
#include "threadchrono.h"

ThreadChrono::ThreadChrono(MainWindow * parent)
 {
    _mainWindow = parent;
}

void ThreadChrono::run()
{
    QElapsedTimer _TimeStart;
    _TimeStart.start();
    _mainWindow->switchVoyants(1);

    while (true)
    {
        msleep(20);
       _mainWindow->updateChrono();
    }
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////

ThreadWait::ThreadWait(MainWindow * parent)
{
    _mainWindow = parent;
}

void ThreadWait::run()
{
   QElapsedTimer _TimeStart;
    _TimeStart.start();
    while (_TimeStart.elapsed() < 1000)
    {
    }
    _mainWindow->setReadyState();
}
