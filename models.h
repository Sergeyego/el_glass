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

#endif // MODELS_H
