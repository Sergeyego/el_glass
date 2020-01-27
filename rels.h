#ifndef RELS_H
#define RELS_H

#include <QObject>
#include "db/dbtablemodel.h"

class Rels : public QObject
{
    Q_OBJECT
public:
    static Rels *instance();
    DbRelation *relSump;
    DbRelation *relKorr;
    DbRelation *relCons;
    DbRelation *relMatr;
    DbRelation *relGlass;
    DbRelation *relPar;
    DbRelation *relSumpLoad;
    DbRelation *relKorrLoad;

    void setSumpLoadFilter(QDate d);
    void setKorrLoadFilter(QDate d);

protected:
    explicit Rels(QObject *parent = 0);

private:
    static Rels *rels_instance;

signals:
    void sigRefresh();

public slots:
    void refresh();

};

#endif // RELS_H
