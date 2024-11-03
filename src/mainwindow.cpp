#include "constants.h"
#include "helpclass.h"
#include "mainwindow.h"
#include "qlabelstackmat.h"
#include "tabwidgetscores.h"
#include "threadchrono.h"
#include <set>

#include <math.h>
#include <QDir>
#include <QCoreApplication>
#include <QTextStream>
#include <qevent.h>
#include <QBitmap>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDomDocument>
#include <QDesktopServices>

#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTreeView>
#include <QtWidgets/qboxlayout.h>
#include <QtWidgets/qlineedit.h>
#include <QtWidgets/qmenu.h>

#include <QtWidgets/QMessageBox>


using namespace std;





bool bestScore(Essai & e1, Essai & e2)
{
    return(e1._temps < e2._temps);
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Virtual StackMat Timer");

    QWidget *zoneCentrale = new QWidget;
    setCentralWidget(zoneCentrale);

    setFixedSize(819,607);

    // IMAGES
    QPixmap * _Stackmat_Timer = new QPixmap;
    _Stackmat_Timer->load(QString(":/Images/res/background.jpg"));
    _Stackmat_Timer->setMask(_Stackmat_Timer->createHeuristicMask());

    _LeftHand0 = new QPixmap;
    _LeftHand0->load(QString(":/Images/res/hand-left-off.png"));
    _LeftHand0->setMask(_LeftHand0->createHeuristicMask());

    _RightHand0 = new QPixmap;
    _RightHand0->load(QString(":/Images/res/hand-right-off.png"));
    _RightHand0->setMask(_RightHand0->createHeuristicMask());

    _LeftHand1 = new QPixmap;
    _LeftHand1->load(QString(":/Images/res/hand-left.png"));
    _LeftHand1->setMask(_LeftHand1->createHeuristicMask());

    _RightHand1 = new QPixmap;
    _RightHand1->load(QString(":/Images/res/hand-right.png"));
    _RightHand1->setMask(_RightHand1->createHeuristicMask());

    _Voyant_Vert0 = new QPixmap;
    _Voyant_Vert0->load(QString(":/Images/res/voyant_vert_off.png"));
    _Voyant_Vert0->setMask(_Voyant_Vert0->createHeuristicMask());

    _Voyant_Vert1 = new QPixmap;
    _Voyant_Vert1->load(QString(":/Images/res/voyant_vert_on.png"));
    _Voyant_Vert1->setMask(_Voyant_Vert1->createHeuristicMask());

    _Voyant_Rouge0 = new QPixmap;
    _Voyant_Rouge0->load(QString(":/Images/res/voyant_rouge_off.png"));
    _Voyant_Rouge0->setMask(_Voyant_Rouge0->createHeuristicMask());

    _Voyant_Rouge1 = new QPixmap;
    _Voyant_Rouge1->load(QString(":/Images/res/voyant_rouge_on.png"));
    _Voyant_Rouge1->setMask(_Voyant_Rouge1->createHeuristicMask());

    _Reset_Pixmap = new QPixmap;
    _Reset_Pixmap->load(QString(":/Images/res/reset.png"));
    _Reset_Pixmap->setMask(_Reset_Pixmap->createHeuristicMask());


    QVBoxLayout *vert_layout1 = new QVBoxLayout;

        QLabel * Stackmat_Timer_Image = new QLabel;
        Stackmat_Timer_Image->setScaledContents(true);
        Stackmat_Timer_Image->setPixmap(_Stackmat_Timer->scaled(Stackmat_Timer_Image->size(),Qt::KeepAspectRatioByExpanding,Qt::SmoothTransformation));

        _LeftHand_Timer_Image = new QLabel(Stackmat_Timer_Image);
        _LeftHand_Timer_Image->setScaledContents(true);
        _LeftHand_Timer_Image->setGeometry(66,452,60,60);
        _LeftHand_Timer_Image->setPixmap(_LeftHand0->scaled(_LeftHand_Timer_Image->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));

        _RightHand_Timer_Image = new QLabel(Stackmat_Timer_Image);
        _RightHand_Timer_Image->setScaledContents(true);
        _RightHand_Timer_Image->setGeometry(505,451,60,60);
        _RightHand_Timer_Image->setPixmap(_RightHand0->scaled(_RightHand_Timer_Image->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));

        _Voyant_Vert_Image = new QLabel(Stackmat_Timer_Image);
        _Voyant_Vert_Image->setScaledContents(true);
        _Voyant_Vert_Image->setGeometry(357,472,14,14);

        _Voyant_Rouge_Image = new QLabel(Stackmat_Timer_Image);
        _Voyant_Rouge_Image->setScaledContents(true);
        _Voyant_Rouge_Image->setGeometry(357,456,14,14);




         _LCDNumber_Stackmat = new LCDNumber_Stackmat(Stackmat_Timer_Image);
         _LCDNumber_Stackmat->setGeometry(580,38,174,35);
         _LCDNumber_Stackmat->setSegmentStyle(QLCDNumber::Flat);
         _LCDNumber_Stackmat->setStyleSheet(tr("QLCDNumber {\ncolor : rgb(255,0,0);\n background-color : rgb(0, 0, 0);\n border: 0px;   ""}"));
         _LCDNumber_Stackmat->setDigitCount(9);

         _LCDNumber = new QLCDNumber(Stackmat_Timer_Image);
         _LCDNumber->setGeometry(225,467,80,24);
         _LCDNumber->setSegmentStyle(QLCDNumber::Flat);             // (136, 131, 101)
         _LCDNumber->setStyleSheet(tr("QLCDNumber {\ncolor : rgb(0,0,0);\n background-color : rgb(136, 131, 101);\n border: 0px;   ""}"));
         _LCDNumber->setDigitCount(9);

         _help = new QPushButton(Stackmat_Timer_Image);
         _help->setGeometry(726,525,50,50);

         _reset = new QLabelStackmat(Stackmat_Timer_Image, this);
         _reset->setScaledContents(true);
         _reset->setGeometry(378,464,30,30);
         _reset->setPixmap(_Reset_Pixmap->scaled(_reset->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));



         QPixmap * myPixmap14 = new QPixmap(QString(":/Images/res/interrogation.png"));
         myPixmap14->setMask(myPixmap14->createHeuristicMask());
         _help->setIcon(QIcon(*myPixmap14));
         _help->setFixedSize(50,50);
         _help->setIconSize(QSize(40,40));


        QFrame * aFrame = new QFrame(Stackmat_Timer_Image);

        QHBoxLayout *hori_layout4 = new QHBoxLayout;
             QGroupBox *groupBox1 = new QGroupBox("Joueur", Stackmat_Timer_Image);
                QVBoxLayout *vert_layout2 = new QVBoxLayout;
                    QHBoxLayout *hori_layout2 = new QHBoxLayout;
                    hori_layout2->addWidget(new QLabel("Pseudo :          "));
                        _pseudoComboBox = new QComboBox();
                        _pseudoComboBox->setEditable(true);
                        _pseudoComboBox->setFixedWidth(150);
                    hori_layout2->addWidget(_pseudoComboBox);
                vert_layout2->addLayout(hori_layout2);

                    QHBoxLayout *hori_layout3 = new QHBoxLayout;
                    hori_layout3->addWidget(new QLabel("Puzzle :         "));
                        _puzzleComboBox = new QComboBox();
                        _puzzleComboBox->setEditable(true);
                        _puzzleComboBox->setFixedWidth(150);
                        _puzzleComboBox->setCurrentIndex(1);
                    hori_layout3->addWidget(_puzzleComboBox);
                vert_layout2->addLayout(hori_layout3);
            groupBox1->setLayout(vert_layout2);
        hori_layout4->addWidget(groupBox1);


            QGroupBox *groupBox2 = new QGroupBox("Statistiques", Stackmat_Timer_Image);

                QVBoxLayout *vert_layout3 = new QVBoxLayout;

                    QHBoxLayout *hori_layout5 = new QHBoxLayout;

                    hori_layout5->addWidget(new QLabel("Meilleur temps : "));

                        _bestTime = new QLineEdit;
                        _bestTime->setFixedWidth(100);
                        _bestTime->setReadOnly(true);
                        _bestTime->setFont(QFont("Verdana", 10, QFont::Bold));
                        _bestTime->setAlignment(Qt::AlignHCenter);
                        _bestTime->setStyleSheet(tr("QLineEdit {\ncolor : rgb(255,0,0);\n background-color : rgb(255, 255, 0);\n border: 0px; \nborder-radius: 6px; \n border: 2px solid red""}"));
                    hori_layout5->addWidget(_bestTime);

                vert_layout3->addLayout(hori_layout5);

                    QHBoxLayout *hori_layout6 = new QHBoxLayout;
                    hori_layout6->addWidget(new QLabel("Moyenne :         "));

                        _moyenne = new QLineEdit;
                        _moyenne->setFixedWidth(100);
                        _moyenne->setReadOnly(true);
                        _moyenne->setFont(QFont("Verdana", 10, QFont::Bold));
                        _moyenne->setAlignment(Qt::AlignHCenter);
                        _moyenne->setStyleSheet(tr("QLineEdit {\ncolor : rgb(0,0,255);\n background-color : rgb(255, 255, 0);\n border: 0px; \nborder-radius: 6px; \n border: 2px solid blue""}"));
                    hori_layout6->addWidget(_moyenne);

                vert_layout3->addLayout(hori_layout6);

            groupBox2->setLayout(vert_layout3);

        hori_layout4->addWidget(groupBox2);

        aFrame->setLayout(hori_layout4);
        aFrame->move(10,10);

        _onglets = new TabWidgetScores(Stackmat_Timer_Image);
        _onglets->setGeometry(20,120,600,300);

    vert_layout1->addWidget(Stackmat_Timer_Image);

    zoneCentrale->setLayout(vert_layout1);


    _n_CTRL = 0;

    resetChrono();
    getSavedScores("scores.txt");
    fillPseudosCombobBox();
    fillPuzzlesCombobBox();
    updateScores();

    _threadWait = new ThreadWait(this);
    _threadChrono = new ThreadChrono(this);
    setStoppedState();


    connect(_pseudoComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateScores(int)));
    connect(_puzzleComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateScores(int)));
    connect(_onglets, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(eraseContextMenu(QPoint)));
    connect(_onglets, SIGNAL(currentChanged(int)), this, SLOT(changeCurrentOnglet(int)));
    connect(_help, SIGNAL(clicked()), this, SLOT(displayHelp()));
    connect(this, SIGNAL(needsRepaint()), this, SLOT(displayChrono()));

    _bestTime->setFocusPolicy(Qt::NoFocus);
    _moyenne->setFocusPolicy(Qt::NoFocus);

    getLastRecord();


    try
    {
        checkLatestVersion();
    }
    catch (...)
    {

    }
}


/******************************
 * CHECK LATEST VERSION
 * ***************************/
void MainWindow::checkLatestVersion()
{
    QNetworkAccessManager * manager = new QNetworkAccessManager(this);
    manager->clearAccessCache();
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(manifestDownloaded(QNetworkReply*)) );
    manager->get(QNetworkRequest(QUrl(___MANIFEST_FILE___)));
}

void MainWindow::manifestDownloaded(QNetworkReply *reply)
{
    char* data = new char[1000];
    reply->readLine(data, 1000);

    reply->deleteLater();

     QDomDocument dom("mon_xml");
     QString s = data;
     if (!dom.setContent(s)) {
         return;
     }

       QDomElement dom_element = dom.documentElement();
       QDomNode noeud = dom_element.firstChild();
       QString version, url;
       while(!noeud.isNull())
       {
           if (noeud.toElement().tagName() == "version")
           {
               version = noeud.firstChild().nodeValue();
           }
           else if (noeud.toElement().tagName() == "url")
           {
               url = noeud.firstChild().nodeValue();
           }
           noeud = noeud.nextSibling();
       }

       if (!version.isEmpty())
       {
           if (version != ___VERSION___)
           {
               QMessageBox::StandardButton reply = QMessageBox::question(this, ___APP_NAME___+" "+___VERSION___,
                    QString(tr("Une nouvelle version est disponible : %1\nVoulez-vous la télécharger?")).arg(version), QMessageBox::Yes|QMessageBox::No);
               if (reply == QMessageBox::Yes)
               {
                   QDesktopServices::openUrl(url);
               }
           }
       }
}









MainWindow::~MainWindow()
{
}



void MainWindow::updateScores(int i)
{
    QObject::disconnect(_onglets, SIGNAL(currentChanged(int)), this, SLOT(changeCurrentOnglet(int)));
    QObject::disconnect(_puzzleComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateScores(int)));

    QString aCurrentOnglet = _puzzleComboBox->currentText();
    _onglets->clear();
     _onglets->_mapOnglets.clear();
    for (std::map<QString, std::list<Essai> >::iterator it = _mapRecords.begin(); it != _mapRecords.end(); it++)
    {
        QTreeView * aTreeView = new QTreeView;
        aTreeView->setRootIsDecorated(false);
        aTreeView->setAlternatingRowColors(true);

        _onglets->_mapModels[it->first] = new QStandardItemModel(0, 5);
        QStandardItemModel * model = _onglets->_mapModels[it->first];
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Rang"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Pseudo"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Chrono"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Ecart"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date"));
        aTreeView->setModel(model);
        aTreeView->setContextMenuPolicy( Qt::CustomContextMenu  );

        aTreeView->setColumnWidth(0, 50);

        aTreeView->setColumnWidth(1, 120);
        aTreeView->setColumnWidth(2, 100);
        aTreeView->setColumnWidth(3, 100);
        aTreeView->setColumnWidth(4, 120);

        QFont aDefaultFont;
        aDefaultFont.setPixelSize(12);
        aTreeView->setFont(aDefaultFont);

        _onglets->_mapOnglets[it->first] = aTreeView;
        _onglets->addTab(aTreeView, it->first);

         QObject::connect(aTreeView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(eraseContextMenu(QPoint)));


        it->second.sort(bestScore);
        _index = 0;

        std::list<Essai>::const_iterator itEssai = it->second.begin();
        _bestScoreRef = itEssai->_temps;

        for (; itEssai != it->second.end(); itEssai++)
        {
            QFont qFont1;
            QFont qFont2;
            qFont2.setPixelSize(12);

            if (_pseudoComboBox->currentText() == itEssai->_pseudo)
            {
                qFont1.setBold(true);
            }

            QStandardItem * aRang = new QStandardItem(QString::number(_index+1));
            aRang->setTextAlignment(Qt::AlignHCenter);
            aRang->setFont(qFont1);
            model->setItem(_index, 0, aRang);

            QStandardItem * aPseudo = new QStandardItem(itEssai->_pseudo);
            aPseudo->setFont(qFont1);
            model->setItem(_index, 1, aPseudo);

            QStandardItem * aChrono = new QStandardItem(convertChronoToString(itEssai->_temps));
            aChrono->setFont(qFont1);
            aChrono->setTextAlignment(Qt::AlignHCenter);
            model->setItem(_index, 2, aChrono);

            QStandardItem * aEcart = new QStandardItem(QString("+ ")+convertChronoToString(itEssai->_temps - _bestScoreRef));
            aEcart->setFont(qFont2);
            aEcart->setTextAlignment(Qt::AlignHCenter);
            if (itEssai->_temps - _bestScoreRef != 0)
                model->setItem(_index, 3, aEcart);

            QStandardItem * aDate = new QStandardItem(itEssai->_date);
            aDate->setFont(qFont2);
            aDate->setTextAlignment(Qt::AlignHCenter);
            model->setItem(_index, 4, aDate);

            _index++;
        }
    }

    QObject::disconnect(_onglets, SIGNAL(currentChanged(int)), this, SLOT(changeCurrentOnglet(int)));
    selectOnglet(aCurrentOnglet);
    QObject::connect(_onglets, SIGNAL(currentChanged(int)), this, SLOT(changeCurrentOnglet(int)));

    updateStatistiques(_pseudoComboBox->currentText(), _puzzleComboBox->currentText());

    QObject::connect(_puzzleComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateScores(int)));
    QObject::connect(_onglets, SIGNAL(currentChanged(int)), this, SLOT(changeCurrentOnglet(int)));

    saveScores("scores.txt");
}


// Get last record saved to get pseudo & puzzle of last trial
// Update pseudo & puzzle combobox & tab
void MainWindow::getLastRecord()
{
    QString aPseudo = "";
    QString aPuzzle = "";
    QDateTime aDateTime, aLastDateTime;


    if (!_mapRecords.empty())
    {
        aLastDateTime = QDateTime::fromString(_mapRecords.begin()->second.front()._date, "dd/MM/yyyy  hh:mm");
        for (std::map<QString, std::list<Essai> >::iterator it = _mapRecords.begin(); it != _mapRecords.end(); it++)
        {
            for (std::list<Essai>::const_iterator itEssai = it->second.begin(); itEssai != it->second.end(); itEssai++)
            {
                aDateTime = QDateTime::fromString(itEssai->_date, "dd/MM/yyyy  hh:mm");
                if (aDateTime >= aLastDateTime)
                {
                    aPseudo = itEssai->_pseudo;
                    aPuzzle = itEssai->_puzzle;
                    aLastDateTime = aDateTime;
                }
            }
        }

        QObject::disconnect(_onglets, SIGNAL(currentChanged(int)), this, SLOT(changeCurrentOnglet(int)));
        _pseudoComboBox->setCurrentIndex( _pseudoComboBox->findText(aPseudo));
        _puzzleComboBox->setCurrentIndex( _puzzleComboBox->findText(aPuzzle));
        QObject::connect(_onglets, SIGNAL(currentChanged(int)), this, SLOT(changeCurrentOnglet(int)));
    }
}








void MainWindow::saveScores(QString filename)
{
    QString MyAppDirPath =  QCoreApplication::applicationDirPath();
    QDir::setCurrent(MyAppDirPath);

    QString aSaveFolder = "scores";
    QDir().mkdir(aSaveFolder);
    QDir::setCurrent(MyAppDirPath+"//"+aSaveFolder);

    QFile file(filename);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
         return;

     QTextStream out(&file);

     for (std::map<QString, std::list<Essai> >::const_iterator it = _mapRecords.begin(); it != _mapRecords.end(); it++)
     {
        for (std::list<Essai>::const_iterator itEssai = it->second.begin(); itEssai != it->second.end(); itEssai++)
        {
            out << it->first << endl;
            out << itEssai->_pseudo << endl;
            out << QString::number(itEssai->_temps) << endl;
            out << itEssai->_date << endl;
        }
     }

     file.close();
}

void MainWindow::getSavedScores(QString filename)
{
    QString aSaveFolder = "scores";
    QString MyAppDirPath =  QCoreApplication::applicationDirPath();
    QDir::setCurrent(MyAppDirPath+"//"+aSaveFolder);

     QFile file(filename);
     if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
         return;

     QTextStream in(&file);
     while (!in.atEnd())
     {
         Essai aEssai;
         aEssai._puzzle = in.readLine();
         aEssai._pseudo = in.readLine();
         aEssai._temps = (in.readLine()).toInt();
         aEssai._date = in.readLine();
         _mapRecords[aEssai._puzzle].push_back(aEssai);
     }

     file.close();
}


void MainWindow::fillPseudosCombobBox()
{
    std::set<QString> _listPseudos;
    for (std::map<QString, std::list<Essai> >::const_iterator it = _mapRecords.begin(); it != _mapRecords.end(); it++)
    {
        for (std::list<Essai>::const_iterator itEssai = it->second.begin(); itEssai != it->second.end(); itEssai++)
        {
            _listPseudos.insert(itEssai->_pseudo);
        }
    }

    _pseudoComboBox->clear();
    for (std::set<QString>::const_iterator it = _listPseudos.begin(); it != _listPseudos.end(); it++)
    {
        _pseudoComboBox->addItem(*it);
    }
}

bool foundInList(const std::list<QString> & iList, const QString & iString)
{
    for (std::list<QString>::const_iterator it = iList.begin(); it != iList.end(); it++)
    {
        if (*it == iString)
            return true;
    }
    return false;
}

void MainWindow::fillPuzzlesCombobBox()
{
    std::list<QString> _listPuzzles;
    _listPuzzles.push_back("Rubik's Cube");


    for (std::map<QString, std::list<Essai> >::const_iterator it = _mapRecords.begin(); it != _mapRecords.end(); it++)
    {
        if (!foundInList(_listPuzzles, it->first))
            _listPuzzles.push_back(it->first);
    }

    _puzzleComboBox->clear();
    for (std::list<QString>::const_iterator it = _listPuzzles.begin(); it != _listPuzzles.end(); it++)
    {
        _puzzleComboBox->addItem(*it);
    }
    _puzzleComboBox->setCurrentIndex(1);
}

void MainWindow::saveScore()
{
    displayChrono();
    releaseKeyboard();

    if (_mapRecords.find(_puzzleComboBox->currentText()) != _mapRecords.end())
        _bestScoreRef = _mapRecords[_puzzleComboBox->currentText()].front()._temps;
    else
        _bestScoreRef = _currentTime;

    Essai aEssai;
    aEssai._pseudo = _pseudoComboBox->currentText();
    aEssai._temps = _currentTime;
    aEssai._date = (QDateTime::currentDateTime()).toString("dd/MM/yyyy  hh:mm");
    aEssai._puzzle = _puzzleComboBox->currentText();

    QString aTemps = convertChronoToString(_currentTime);
    QString aEcart = "+ ";
    int aEcartInt = _currentTime - _bestScoreRef;
    aEcart = (aEcartInt > 0) ? "+ " : "- ";
    aEcart += convertChronoToString(abs(_currentTime - _bestScoreRef));

    QString aRang = QString::number(getRang(aEssai));

    QMessageBox msgBox;
    msgBox.setText("Conserver ce score ?");
    QString aText = "Puzzle : "+aEssai._puzzle+"\n"+aEssai._pseudo+" :  "+aTemps+"\nEcart : "+aEcart+"\nRang : "+aRang;
    msgBox.setInformativeText(aText);
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);

    switch (msgBox.exec())
    {
       case QMessageBox::Ok:
            addEssai(aEssai);
            selectScore(aRang.toInt(), aEssai._puzzle);
            break;

       default:
           break;
    }
    _n_CTRL = 0;
}



void MainWindow::selectScore(int iRang, QString & aPuzzle)
{
    selectOnglet(aPuzzle);
    QItemSelectionModel * _selectionModel = _onglets->_mapOnglets[aPuzzle]->selectionModel();
     int i = iRang-1;

    QStandardItemModel * model = _onglets->_mapModels[aPuzzle];
    QModelIndex qmodelindex0 = model->index(i,0);
    QModelIndex qmodelindex1 = model->index(i,1);
    QModelIndex qmodelindex2 = model->index(i,2);
    QModelIndex qmodelindex3 = model->index(i,3);
    QModelIndex qmodelindex4 = model->index(i,4);

    _onglets->_mapOnglets[aPuzzle]->setCurrentIndex(qmodelindex0);

    _selectionModel->select(qmodelindex0, QItemSelectionModel::ClearAndSelect);
    _selectionModel->select(qmodelindex1, QItemSelectionModel::Select);
    _selectionModel->select(qmodelindex2, QItemSelectionModel::Select);
    _selectionModel->select(qmodelindex3, QItemSelectionModel::Select);
    _selectionModel->select(qmodelindex4, QItemSelectionModel::Select);

    _onglets->_mapOnglets[aPuzzle]->setFocus();
}

int MainWindow::getRang(Essai iEssai)
{
    std::list<Essai> aListEssais = _mapRecords[iEssai._puzzle];

    aListEssais.push_back(iEssai);
    aListEssais.sort(bestScore);

    int n = 1;
    for (std::list<Essai>::const_iterator it = aListEssais.begin(); it != aListEssais.end(); it++)
    {
        if (it->_temps == iEssai._temps && it->_date == iEssai._date)
            return n;
        n++;
    }
    return -1;
}


void MainWindow::addEssai(Essai & iEssai)
{
    _mapRecords[iEssai._puzzle].push_back(iEssai);
    updateScores();
}






void MainWindow::updateStatistiques(QString iPseudo, QString iPuzzle)
{
    QString aStringBestTime, aStringMoyenne;

    iPseudo = _pseudoComboBox->currentText();
    iPuzzle = _puzzleComboBox->currentText();

    if (_mapRecords.find(iPuzzle) != _mapRecords.end())
    {
        std::list<Essai> aVectorEssais = _mapRecords[iPuzzle];
        for (std::list<Essai>::iterator itEssai = aVectorEssais.begin(); itEssai != aVectorEssais.end();)
        {
            if (itEssai->_pseudo != iPseudo)
                aVectorEssais.erase(itEssai++);
            else
                itEssai++;
        }

        if (!aVectorEssais.empty())
        {
            aStringBestTime = convertChronoToString(aVectorEssais.front()._temps);
        }

        int aMoyenne = 0;
        int n = 0;
        for (std::list<Essai>::const_iterator itEssai = aVectorEssais.begin(); itEssai != aVectorEssais.end(); itEssai++)
        {
            aMoyenne += itEssai->_temps;
            n++;
        }
        if (n>0)
        {
            aMoyenne /= n;
            aStringMoyenne = convertChronoToString(aMoyenne);
        }
    }

    _bestTime->setText(aStringBestTime);
    _moyenne->setText(aStringMoyenne);

}

void MainWindow::resetChrono()
{
    QString aTime = convertChronoToString(0);
    _LCDNumber->display(aTime);
    _LCDNumber_Stackmat->display(aTime);
}

QString MainWindow::convertChronoToString(int iTime)
{
    int zzz = iTime % 1000;
    iTime = (iTime- zzz)/1000;
    int ss = iTime % 60;
    iTime = (iTime- ss)/60;
    int mm = iTime;

    QTime aTime(0,mm,ss,zzz);
    return (aTime.toString("mm:ss.zzz"));
}

int MainWindow::convertChronoToInt(QTime iTime)
{
    return (iTime.msec() + 1000 * iTime.second() + 60 * 1000 * iTime.minute());
}


void MainWindow::setStoppedState()
{
    _STATE = _STOPPED_;
    _threadChrono->terminate();
    _LCDNumber_Stackmat->saveTime();
    _threadWait->terminate();
    _Voyant_Vert_Image->setPixmap(_Voyant_Vert0->scaled(_Voyant_Vert_Image->size(),Qt::KeepAspectRatio));
    _Voyant_Rouge_Image->setPixmap(_Voyant_Rouge0->scaled(_Voyant_Rouge_Image->size(),Qt::KeepAspectRatio));
    _LeftHand_Timer_Image->setPixmap(_LeftHand0->scaled(_LeftHand_Timer_Image->size(),Qt::KeepAspectRatio));
    _RightHand_Timer_Image->setPixmap(_RightHand0->scaled(_RightHand_Timer_Image->size(),Qt::KeepAspectRatio));
    _n_CTRL = 0;
    releaseKeyboard();
}

void MainWindow::setWaitingState()
{
    _STATE = _WAITING_;
    _Voyant_Vert_Image->setPixmap(_Voyant_Vert0->scaled(_Voyant_Vert_Image->size(),Qt::KeepAspectRatio));
    _Voyant_Rouge_Image->setPixmap(_Voyant_Rouge1->scaled(_Voyant_Rouge_Image->size(),Qt::KeepAspectRatio));
    _threadWait->start();
}

void MainWindow::setReadyState()
{
    _STATE = _READY_;
    switchVoyants(1);
    resetChrono();
}

void MainWindow::setRunningState()
{
    _STATE = _RUNNING_;

    _LCDNumber_Stackmat->_timer.setHMS(0,0,0);
    _LCDNumber_Stackmat->_timer.start();

    grabKeyboard();
    _threadChrono->start();
}


void MainWindow::switchVoyants(int OnOFF)
{
	if (OnOFF)
	{
            _Voyant_Vert_Image->setPixmap(_Voyant_Vert1->scaled(_Voyant_Vert_Image->size(),Qt::KeepAspectRatio));
            _Voyant_Rouge_Image->setPixmap(_Voyant_Rouge1->scaled(_Voyant_Rouge_Image->size(),Qt::KeepAspectRatio));
            _VOYANTS_STATE_ = _ON_;
	} else {
            _Voyant_Vert_Image->setPixmap(_Voyant_Vert0->scaled(_Voyant_Vert_Image->size(),Qt::KeepAspectRatio));
            _Voyant_Rouge_Image->setPixmap(_Voyant_Rouge0->scaled(_Voyant_Rouge_Image->size(),Qt::KeepAspectRatio));
            _VOYANTS_STATE_ = _OFF_;
	}
}



void MainWindow::updateChrono()
{
    emit needsRepaint();
}


void MainWindow::displayChrono()
{
    _chronoRefreshMutex.lock();

    _currentTime = _LCDNumber_Stackmat->_timer.elapsed();

    unsigned int aTimeSlice = (_currentTime % 200);

    if (_VOYANTS_STATE_ == _ON_ && aTimeSlice >= 100)
    {
        switchVoyants(0);
    }
    else if (_VOYANTS_STATE_ == _OFF_ && aTimeSlice >= 0 && aTimeSlice<100 )
    {
         switchVoyants(1);
    }

    QString aTime = convertChronoToString(_currentTime);


    _LCDNumber->display(aTime);
    _LCDNumber->repaint();

    _LCDNumber_Stackmat->display(aTime);
    _LCDNumber_Stackmat->repaint();

    _chronoRefreshMutex.unlock();
}

void MainWindow::keyPressEvent ( QKeyEvent * event )
{
   if (event->key() == Qt::Key_Alt)
   {
        _LeftHand_Timer_Image->setPixmap(_LeftHand1->scaled(_LeftHand_Timer_Image->size(),Qt::KeepAspectRatio));
        _n_CTRL++;
    }
   else if (event->key() == Qt::Key_Control)
   {
       _RightHand_Timer_Image->setPixmap(_RightHand1->scaled(_LeftHand_Timer_Image->size(),Qt::KeepAspectRatio));
        _n_CTRL++;
   }
   else if (event->key() == Qt::Key_Space && _STATE == _RUNNING_)
   {
       _n_CTRL = 0;
       setStoppedState();
        saveScore();
   }
   else if (event->key() == Qt::Key_R && _STATE == _STOPPED_)
   {
       resetChrono();
   }
   else if (event->key() == Qt::Key_Delete)
   {
       eraseSelectedScore();
   }


    if (_n_CTRL == 2 && _STATE != _RUNNING_)
    {
        setWaitingState();
    }
}


void MainWindow::keyReleaseEvent ( QKeyEvent * event )
{
   if (event->key() == Qt::Key_Alt)
   {
        _LeftHand_Timer_Image->setPixmap(_LeftHand0->scaled(_LeftHand_Timer_Image->size(),Qt::KeepAspectRatio));
        _n_CTRL =  (_n_CTRL > 0) ? --_n_CTRL : 0;
    }
   else if (event->key() == Qt::Key_Control)
   {
       _RightHand_Timer_Image->setPixmap(_RightHand0->scaled(_LeftHand_Timer_Image->size(),Qt::KeepAspectRatio));
        _n_CTRL =  (_n_CTRL > 0) ? --_n_CTRL : 0;
   }

   if (_n_CTRL==1)
   {
       if (_STATE == _READY_)
       {
           setRunningState();
       }
       else if (_STATE == _WAITING_)
       {
           setStoppedState();
       }
   }
}


void MainWindow::cleanAllScores()
{
    if (confirmationSuppression("Etes-vous sur de vouloir supprimer TOUS les scores ?"))
    {
        _mapRecords.clear();
        updateScores();
    }
}

void MainWindow::cleanScoresSelectedPuzzle()
{
    QString aString = "Etes-vous sur de vouloir supprimer les scores du Puzzle ";
    aString += _puzzleComboBox->currentText();
    aString += " ?";
    if (confirmationSuppression(aString))
    {
        _mapRecords.erase(_puzzleComboBox->currentText());
        updateScores();
    }
}

void MainWindow::cleanScoresSelectedPlayer()
{
    QString aString = "Etes-vous sur de vouloir supprimer les scores du Joueur ";
    aString += _pseudoComboBox->currentText();
    aString += " ?";
    if (confirmationSuppression(aString))
    {
        std::map<QString, std::list<Essai> > aNewMap;
        for (std::map<QString, std::list<Essai> >::iterator it = _mapRecords.begin(); it != _mapRecords.end(); it++)
        {
            for (std::list<Essai>::iterator itEssai = it->second.begin(); itEssai != it->second.end(); )
            {
                if (_pseudoComboBox->currentText() == itEssai->_pseudo)
                    it->second.erase(itEssai++);
                else
                    itEssai++;
            }
        }
        updateScores();
    }
}

void MainWindow::eraseSelectedScore()
{
    QItemSelectionModel * _selectionModel = (_onglets->_mapOnglets[_puzzleComboBox->currentText()])->selectionModel();
    int aIndex = (_selectionModel->currentIndex()).row();
    std::list<Essai>::iterator itEssai = _mapRecords[_puzzleComboBox->currentText()].begin();
    for (int i=0; i<aIndex; i++)
        itEssai++;
    _mapRecords[_puzzleComboBox->currentText()].erase(itEssai);
    updateScores();
}


void MainWindow::selectOnglet(QString iOnglet)
{
    for (int i = 0; i < _onglets->count(); i++)
    {
        if (_onglets->tabText(i) == iOnglet)
        {
            _onglets->setCurrentIndex(i);
            return;
        }
    }
}


void MainWindow::eraseContextMenu(const QPoint & pos)
{
    QMenu menu( this );
    QIcon icon;
    QString aString;

    QAction * pAction_Test_1 = menu.addAction( icon, "Supprimer sélection" );
    aString = "Supprimer scores Joueur ";
    aString += _pseudoComboBox->currentText();
    QAction * pAction_Test_2 = menu.addAction( icon, aString);
    aString = "Supprimer scores Puzzle ";
    aString += _puzzleComboBox->currentText();
    QAction * pAction_Test_3 = menu.addAction( icon, aString);
    QAction * pAction_Test_4 = menu.addAction( icon, "Supprimer TOUS les scores" );

    connect(pAction_Test_1, SIGNAL(triggered()), this, SLOT(eraseSelectedScore()));
    connect(pAction_Test_2, SIGNAL(triggered()), this, SLOT(cleanScoresSelectedPlayer()));
    connect(pAction_Test_3, SIGNAL(triggered()), this, SLOT(cleanScoresSelectedPuzzle()));
    connect(pAction_Test_4, SIGNAL(triggered()), this, SLOT(cleanAllScores()));

    menu.exec( _onglets->_mapOnglets[_puzzleComboBox->currentText()]->viewport()->mapToGlobal(pos) );
}


bool MainWindow::confirmationSuppression(QString text)
{
    QMessageBox msgBox;
    msgBox.setText(text);
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);

    switch (msgBox.exec())
    {
       case QMessageBox::Ok:
            return true;
            break;

       default:
           return false;
           break;
    }

    return false;
}


void MainWindow::changeCurrentOnglet(int iIndex)
{
    QString aPuzzle = _onglets->tabText(iIndex);
    int aIndex = _puzzleComboBox->findText(aPuzzle); 

    if (aIndex >= 0)
    {
        disconnect(_puzzleComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateScores(int)));
        disconnect(_onglets, SIGNAL(currentChanged(int)), this, SLOT(changeCurrentOnglet(int)));

        _puzzleComboBox->setCurrentIndex(aIndex);
        updateStatistiques(_pseudoComboBox->currentText(), _puzzleComboBox->currentText());

        connect(_onglets, SIGNAL(currentChanged(int)), this, SLOT(changeCurrentOnglet(int)));
        connect(_puzzleComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(updateScores(int)));
    }
}



void MainWindow::displayHelp()
{
    HelpClass().exec();
}

