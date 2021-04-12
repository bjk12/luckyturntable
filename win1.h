#ifndef WIN1_H
#define WIN1_H

#include <QWidget>

namespace Ui {
class win1;
}

class win1 : public QWidget
{
    Q_OBJECT

public:
    explicit win1(QWidget *parent = 0);
    ~win1();

private:
    Ui::win1 *ui;
};

#endif // WIN1_H
