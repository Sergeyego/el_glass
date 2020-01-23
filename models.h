#ifndef MODELS_H
#define MODELS_H
#include "db/dbtablemodel.h"
#include "rels.h"
#include "modelro.h"

class ModelSumpLoad : public DbTableModel
{
public:
    ModelSumpLoad(QObject *parent);
    void refresh(QDate begDate, QDate endDate);
};

class ModelSumpLoadPar : public DbTableModel
{
public:
    ModelSumpLoadPar(QObject *parent);
    void refresh(int id_sump);
};

class ModelSumpStat : public ModelRo
{
public:
    ModelSumpStat(QObject *parent);
    void refresh(QDate date);
};

class ModelKorrLoad : public DbTableModel
{
public:
    ModelKorrLoad(QObject *parent);
    void refresh(QDate begDate, QDate endDate);
};

class ModelKorrLoadData : public DbTableModel
{
public:
    ModelKorrLoadData(QObject *parent);
    void refresh(int id_korr);
};

class ModelKorrLoadPar : public DbTableModel
{
public:
    ModelKorrLoadPar(QObject *parent);
    void refresh(int id_korr);
};

class ModelKorrStat : public ModelRo
{
public:
    ModelKorrStat(QObject *parent);
    void refresh(QDate date);
};

class ModelKorrStatData : public ModelRo
{
public:
    ModelKorrStatData(QObject *parent);
    void refresh(int id_load);
    QVariant data(const QModelIndex &item, int role) const;
private:
    QMultiMap <int,QString> inPar;
};

#endif // MODELS_H
