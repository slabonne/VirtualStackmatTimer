#ifndef TABWIDGETSCORES_H
#define TABWIDGETSCORES_H

#include <QString>
#include <QStandardItemModel>
#include <map>

#include <QtWidgets/qtabwidget.h>

class QTreeView;

class TabWidgetScores : public QTabWidget
{
public:
    TabWidgetScores(QWidget * parent = NULL);

    std::map<QString, QTreeView * > _mapOnglets;
    std::map<QString, QStandardItemModel * > _mapModels;
};

#endif // TABWIDGETSCORES_H
