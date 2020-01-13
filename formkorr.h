#ifndef FORMKORR_H
#define FORMKORR_H

#include <QWidget>
#include "models.h"

namespace Ui {
class FormKorr;
}

class FormKorr : public QWidget
{
    Q_OBJECT

public:
    explicit FormKorr(QWidget *parent = 0);
    ~FormKorr();

private:
    Ui::FormKorr *ui;
    ModelKorrLoad *modelKorrLoad;
    ModelKorrLoadData *modelKorrLoadData;

private slots:
    void updLoad();
    void updLoadData(QModelIndex ind);
};

#endif // FORMKORR_H
