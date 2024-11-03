#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include <QMutex>
#include "variables.h"


class ThreadChrono;
class ThreadWait;
class QLabelStackmat;
class QPushButton;
class QLabel;
class QComboBox;
class QLineEdit;
class QFile;
class QTextStream;
class QLCDNumber;
class LCDNumber_Stackmat;
class TabWidgetScores;
class QNetworkReply;

enum {_ON_, _OFF_};

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void checkLatestVersion();
    void manifestDownloaded(QNetworkReply *reply);

    QLCDNumber              * _LCDNumber;
    LCDNumber_Stackmat      * _LCDNumber_Stackmat;

    unsigned short int _VOYANTS_STATE_;

    void keyPressEvent ( QKeyEvent * event );
    void keyReleaseEvent ( QKeyEvent * event );




    void getSavedScores(QString filename);
    void saveScores(QString filename);

    void fillPseudosCombobBox();
    void fillPuzzlesCombobBox();
    void saveScore();
    void addEssai(Essai & iEssai);

    void updateStatistiques(QString iPseudo, QString iPuzzle);
    QString convertChronoToString(int iTime);
    int convertChronoToInt(QTime iTime);

    void setStoppedState();
    void setReadyState();
    void setRunningState();
    void setWaitingState();


    void selectOnglet(QString iOnglet);
    bool confirmationSuppression(QString text);
    int getRang(Essai iEssai);
    void selectScore(int iRang, QString & aPuzzle);

    void getLastRecord();
	void switchVoyants(int OnOFF);



    int _STATE;

    QTextStream * out_;
    QFile * file;



signals:
     void needsRepaint();



public slots:
    void updateScores(int i = 0);
    void eraseContextMenu(const QPoint & pos);

    void cleanAllScores();
    void cleanScoresSelectedPuzzle();
    void cleanScoresSelectedPlayer();
    void eraseSelectedScore();
    void changeCurrentOnglet(int iIndex);
    void displayHelp();
    void resetChrono();
        void displayChrono();
        void updateChrono();

private:

    int _n_CTRL;
    bool _isReady;
    int _index;

    QPushButton             * _CTRL1;
    QPushButton             * _CTRL2;
    QLCDNumber              * _LCDNumber_Stackmat_Ecart;

    QPixmap * _LeftHand0;
    QPixmap * _LeftHand1;
    QPixmap * _RightHand0;
    QPixmap * _RightHand1;
    QPixmap * _Voyant_Vert0;
    QPixmap * _Voyant_Vert1;
    QPixmap * _Voyant_Rouge0;
    QPixmap * _Voyant_Rouge1;
    QPixmap * _Reset_Pixmap;

    QLabel * _LeftHand_Timer_Image;
    QLabel * _RightHand_Timer_Image;
    QLabel * _Voyant_Vert_Image;
    QLabel * _Voyant_Rouge_Image;

    QLineEdit * _bestTime;
    QLineEdit * _moyenne;

    QComboBox   * _pseudoComboBox;
    QComboBox   * _puzzleComboBox;
    TabWidgetScores  * _onglets;

    QPushButton * _help;
    QLabelStackmat * _reset;

    ThreadChrono * _threadChrono;
    ThreadWait * _threadWait;

    std::map<QString, std::list<Essai> >  _mapRecords;

    int _currentTime;
    int _bestScoreRef;

    QMutex _chronoRefreshMutex;

};

#endif // MAINWINDOW_H
