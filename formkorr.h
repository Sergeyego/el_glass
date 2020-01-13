#ifndef FORMKORR_H
#define FORMKORR_H

#include <QWidget>

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
};

#endif // FORMKORR_H
