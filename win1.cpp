#include "win1.h"
#include "ui_win1.h"

win1::win1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::win1)
{
    ui->setupUi(this);
    setStyleSheet("QWidget{font-size:16px;}");
    this->setWindowFlags(Qt::WindowMinMaxButtonsHint);
    //去掉最大化最小化按钮，保留关闭按钮
    this->setWindowFlags(Qt::WindowCloseButtonHint);
    ui->TextEdit->setReadOnly(true);
    QString str1="    随机事件生成软件用于按照用户预先设定的权重生成各类随机事件。\n\
    权重会被软件归一化为概率，权重越大的事件发生的概率也就越大，\
软件会将这一规则通过轮盘选择的方式直观地展现给用户。此外，\
用户还可以自行修改各个事件（最多八个）的名称及其对应的权重\
（至少有一个不为零，否则报错）。点击“点击开始”按钮生成随机事件，\
转盘随即转动，结果文本框中的文字由“等待中……”变成“正在生成···”。\
轮盘转动数圈后开始减速直至停止，红色指针指向的事件\
即为随机生成的事件，结果文本框中也会显示该事件的名称。\
在修改完各个事件的名称和对应权重后，用户可以通过鼠标点击\
“开始并保存”按钮，随机生成事件并将其记录以文本文档格式\
保存于电脑桌面处便于用户查看、分析和统计。\
\n\n\n\n\
                            by 7M";
    ui->TextEdit->setPlainText(str1);
}

win1::~win1()
{
    delete ui;
}
