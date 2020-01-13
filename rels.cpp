#include "rels.h"

Rels* Rels::rels_instance=0;

Rels *Rels::instance()
{
    if (rels_instance==0)
        rels_instance = new Rels();
    return rels_instance;
}

Rels::Rels(QObject *parent) : QObject(parent)
{
    relSump = new DbRelation(QString("select id, num from glass_sump order by num"),0,1,this);
    relKorr = new DbRelation(QString("select id, num from glass_korr order by num"),0,1,this);
    relCons = new DbRelation(QString("select id, num from glass_cons order by num"),0,1,this);
    relMatr = new DbRelation(QString("select id, nam from matr where cod='g' order by nam"),0,1,this);
    relPar = new DbRelation(QString("select id, nam from glass_par order by nam"),0,1,this);
}

void Rels::refresh()
{
    relSump->refreshModel();
    relKorr->refreshModel();
    relCons->refreshModel();
    relMatr->refreshModel();
    emit sigRefresh();
}
