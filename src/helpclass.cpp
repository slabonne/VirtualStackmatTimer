#include "helpclass.h"
#include "constants.h"

#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/qboxlayout.h>

HelpClass::HelpClass()
{
    setFixedSize(500,280);
    setWindowTitle("A propos...");

    QVBoxLayout * vert_layout1 = new QVBoxLayout;
    QLabel * aLabel = new QLabel("<strong style=""color:red"">Virtual StackMat Timer</strong>");
    aLabel->setAlignment(Qt::AlignHCenter);
    QFont aFont;
    aFont.setBold(true);
    aFont.setPixelSize(18);
    aLabel->setFont(aFont);
    vert_layout1->addWidget(aLabel);

    QLabel * aLabel3 = new QLabel("v1.2");
    aLabel3->setAlignment(Qt::AlignHCenter);
    vert_layout1->addWidget(aLabel3);

    QLabel * aLabel2 = new QLabel(QString("<em>par %1</em>").arg(___AUTHOR___));
    aLabel2->setAlignment(Qt::AlignHCenter);
    vert_layout1->addWidget(aLabel2);

    QLabel * aLabel4 = new QLabel(QString("<a href=""%1"">%1</a>").arg(___WEBPAGE_URL___));
    aLabel4->setAlignment(Qt::AlignHCenter);
    aLabel4->setOpenExternalLinks ( true );
    vert_layout1->addWidget(aLabel4);

    QPlainTextEdit * _help = new QPlainTextEdit(this);
    _help->setReadOnly(true);
    vert_layout1->addWidget(_help);

     setLayout(vert_layout1);

     setModal(true);

     _help->appendHtml("<p>Appuyer simultanément sur les touches <strong style=""color:blue"">Alt</strong> et <strong style=""color:blue"">Ctrl</strong> du clavier : le voyant rouge du Stackmat s'allume.</p><p>Maintenir les touches appuyées pendant une seconde, le voyant vert s'allume à son tour.</p><p>Lorsqu'une des touches est alors relâchée, le chrono démarre.</p><p>Appuyer sur <strong style=""color:blue"">Espace</strong> pour arrêter le chrono et enregistrer le temps.</p><p>Les scores sont automatiquement sauvegardés.</p><br /><p><strong>Reset</strong> : Remise à zéro du chronomètre</p><p><strong>Clic droit</strong> sur les scores : fait apparaître un menu contextuel pour supprimer un score, un joueur, un puzzle ou tous les scores</p>");
}
