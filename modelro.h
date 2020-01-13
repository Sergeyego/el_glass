#ifndef MODELRO_H
#define MODELRO_H

#include <QSqlQueryModel>
#include <QLocale>
#include <QDate>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

class ModelRo : public QSqlQueryModel
{
public:
    ModelRo(QObject *parent);
    QVariant data(const QModelIndex &item, int role) const;
    bool execQuery(QSqlQuery &query);
protected:
    int dec;
};

#endif // MODELRO_H
