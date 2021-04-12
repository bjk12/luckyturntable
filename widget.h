#ifndef WIDGET_H
#define WIDGET_H
#include <QPainter>
#include <QRadialGradient>
#include <QPainterPath>
#include <QMouseEvent>
#include <QPushButton>
#include <QTime>
#include <QMap>
#include <QMapIterator>
#define MAX_CIRCLE  1800
namespace Ui {
class Widget;
}
class Widget : public QWidget
{
    Q_OBJECT
public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void gradientArc(QPainter *painter,int radius,int startAngle,
                     int angleLength,int arcHeight,QRgb color);
public slots:
    void updatePaint();
    void btnClicked();
    void reResult(int re);
    void stopRotate();
signals:
    void sigResult(int re);
private:
    Ui::Widget *ui;
    int m_nRotationAngle;
    int m_nRo;
    quint32 m_T;
    QString m_Re;
    QTimer *m_timer;
    QTimer *timer;
    int m_i;
    int init=0,rec=0,change=1;
    QPushButton *m_btn;
    QPushButton *m_about;
    QPushButton *m_rec;
    bool isDefault;
    QLabel *m_labTr;
    QLabel *m_labRe;
    QLineEdit *m_ldeRe;
    QMap<int,QString> m_map;
    QMap<int, QString> returnResult(int re);
    void stopInit();
    int getRand();
    QString thing1="事件一";
    QString thing2="事件二";
    QString thing3="事件三";
    QString thing4="事件四";
    QString thing5="事件五";
    QString thing6="事件六";
    QString thing7="事件七";
    QString thing8="事件八";
    QString thingshow[8]={"事件一:的权重为1\n","事件二:的权重为1\n",
                          "事件三:的权重为1\n","事件四:的权重为1\n",
                          "事件五:的权重为1\n","事件六:的权重为1\n",
                          "事件七:的权重为1\n","事件八:的权重为1\n"};
    int listbox[8]={0,0,0,0,0,0,0,0};
    float listnum[8]={1,1,1,1,1,1,1,1};
protected:
    void paintEvent(QPaintEvent *);
private slots:
    void on_ok_but_clicked();
    void on_det_but_clicked();
    void btnaboutClicked();
    void btnrecClicked();
};
#endif // WIDGET_H
