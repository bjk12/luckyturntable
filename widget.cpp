#include "widget.h"
#include "win1.h"
#include "ui_widget.h"
int speed=20,bias=22.75;
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    resize(800,500);
    setMouseTracking(true);
    setStyleSheet("QWidget{font-size:16px;}");
    m_nRotationAngle = 0;
    m_i = 0;
    m_T = 0;
    isDefault = false;
    m_btn = new QPushButton(this);
    m_about= new QPushButton(this);
    m_rec= new QPushButton(this);
    m_about->setStyleSheet("width: 100px;");
    m_about->setText(tr("关于本软件"));
    m_about->move(610,420);
    m_rec->setStyleSheet("width: 100px;");
    m_rec->setText(tr("开始并保存"));
    m_rec->move(390,420);
    m_btn->move(510,420);
    m_labTr = new QLabel(tr("结果:"),this);
    m_labTr->move(420,60);
    m_ldeRe = new QLineEdit(tr("等待中……"),this);
    m_ldeRe->move(470,55);
    m_ldeRe->setEnabled(false);
    m_ldeRe->setAlignment(Qt::AlignCenter);
    m_btn->setText(tr("点击开始"));
    m_timer = new QTimer(this);
    connect(m_rec,SIGNAL(clicked(bool)),this,SLOT(btnrecClicked()));
    connect(m_timer,SIGNAL(timeout()),this,SLOT(updatePaint()));
    connect(m_about,SIGNAL(clicked(bool)),this,SLOT(btnaboutClicked()));
    connect(m_btn,SIGNAL(clicked(bool)),this,SLOT(btnClicked()));
    connect(this,SIGNAL(sigResult(int)),this,SLOT(reResult(int)));
    QString qstr1="";
    for(int i=0;i<8;i++)
    {
        qstr1=qstr1+thingshow[i];
    }
    ui->TextEdit->setPlainText(qstr1);
    ui->lineEdit->setPlaceholderText("新手请点击“关于本软件”按钮");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::gradientArc(QPainter *painter, int radius, int startAngle,
                         int angleLength, int arcHeight, QRgb color)
{
    QRadialGradient gradient(0,0,radius);
    gradient.setColorAt(0,Qt::black);
    gradient.setColorAt(1.0,color);
    painter->setBrush(gradient);

    // << 1（左移1位）相当于radius*2 即：150*2=300
    //QRectF(-150, -150, 300, 300)
    QRectF rectf(-radius,-radius,radius << 1,radius << 1);
    QPainterPath path;
    path.arcTo(rectf,startAngle,angleLength);

    QPainterPath subPath;
    subPath.addEllipse(rectf.adjusted(arcHeight, arcHeight, -arcHeight, -arcHeight));
    //subPath.addEllipse(rect.adjusted(arcHeight,arcHeight,-arcHeight,-arcHeight));
    //path为扇形 subPath为椭圆
    path -= subPath;//

    //        QFont font;
    //        font.setFamily("Microsoft YaHei");
    //        font.setPointSize(14);
    //        painter->setPen(Qt::NoPen);
    //        path.addText(path.pointAtPercent(0.5), font, QStringLiteral("举例"));
    painter->setPen(Qt::NoPen);
    painter->drawPath(path);
}
int flag1=0;
void Widget::updatePaint()
{
    if(flag1<20){
    m_nRotationAngle = m_nRotationAngle+30;
    flag1++;
        if(flag1 >=12)
        {
            m_nRotationAngle=0;
            flag1 = 0;
            m_T++;
            if(m_T == 2)
            {
                 flag1=21;
            }
        }
    }
    else
    {
        stopInit();
    }
    update();
}

void Widget::btnClicked()
{
    if(!m_timer->isActive())
    {
        //start中的数字调整转速，数值越大越慢
        m_timer->start(30);
        int iRangd = getRand();
        emit sigResult(iRangd);
        m_T = 0;
        m_ldeRe->setStyleSheet("color:darkGray;");
        m_ldeRe->setText(tr("正在生成..."));
    }
    else
    {
        stopInit();
    }
}

void Widget::reResult(int re)
{
    isDefault = true;
    m_map =  returnResult(re);
    QMapIterator<int,QString> ii(m_map);
    if(m_map.isEmpty())
        return;
    while(ii.hasNext())
    {
        ii.next();
        m_Re = ii.value();
        m_nRo = ii.key()-bias;
    }
}

void Widget::stopRotate()
{
    m_timer->stop();
}

QMap<int,QString> Widget::returnResult(int re)
{

    int ire = 0;
    QMap<int,QString> map;
    switch(re)
    {
    case 0:
        //（rand（）%（b-a））+ a，-->[a,b)的随机数
        ire = (qrand() % (40 - 5) + 5);
        map.insert(ire,thing1);
        break;
    case 1:
        ire = (qrand() % (85 - 50) + 50);
        map.insert(ire,thing2);
        break;
    case 2:
        ire = (qrand() % (130 - 95) + 95);
        map.insert(ire,thing3);
        break;
    case 3:
        ire = (qrand() % (175 - 140) + 140);
        map.insert(ire,thing4);
        break;
    case 4:
        ire = (qrand() % (220 - 185) + 185);
        map.insert(ire,thing5);
        break;
    case 5:
        ire = (qrand() % (265 - 230) + 230);
        map.insert(ire,thing6);
        break;
    case 6:
        ire = (qrand() % (310 - 275) + 275);
        map.insert(ire,thing7);
        break;
    case 7:
        ire = (qrand() % (355 - 320) + 320);
        map.insert(ire,thing8);
        break;
    default:
        break;
    }
    return map;
}
int i1=0;

void Widget::stopInit()
{
    m_T = 0;
    int ip =  m_nRo+720;
    if(ip > m_nRotationAngle)
    {
        m_nRotationAngle = m_nRotationAngle+30-5*(i1/5);
        if(i1<25)
        {
          i1++;
        }
    }
    else
    {
        flag1=0;
        i1=0;
        m_timer->stop();
        m_nRotationAngle = m_nRo;
        m_ldeRe->setStyleSheet("color:black;");
        m_ldeRe->setText(m_Re);
        if(rec==1)
        {
            QString m_strDate,m_strTime,str1;
            QDateTime curDateTime=QDateTime::currentDateTime();
            m_strDate=curDateTime.toString("yyyy-MM-dd");         //格式化日期
            m_strTime=curDateTime.toString("hh时mm分ss秒");         //格式化时间
            m_strTime="\\rand_table.txt";
            //保存到桌面
            QString location = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
            QFile file1(location+m_strTime);
            file1.open(QIODevice::Append | QIODevice::Text);
            QTextStream txtOutput(&file1);
            if(change==1)
            {
                str1="\n"+ui->TextEdit->toPlainText()+"\n"+m_Re;
                change=0;
            }
            else
            {
                str1=m_Re;
            }
            txtOutput <<str1<< endl;
            file1.close();
            rec=0;
        }
    }
    update();
}

//设置奖项权重
int Widget::getRand()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    if(init==0)
    {
        int re = qrand()%80;
        re=re/10;
        return re;
    }
    else
    {
        float temp[8];
        temp[0]=listnum[0]*10;
        for(int i=1;i<8;i++)
        {
            temp[i]=temp[i-1]+listnum[i]*10;
        }
        for(int i=0;i<8;i++)
        {
            temp[i]=temp[i]/temp[7];
        }
        int re = qrand()%int(temp[7]*100);
        int tempnum=0;
        for(int i=0;i<8;i++)
        {
            if(re<temp[i]*100)
            {
                tempnum=i;
                break;
            }
        }
        return tempnum;
    }
}

void Widget::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing,true);
    int radius = 150;
    int arcHeight = 120;

    //>>1 右移一位，相当于width() / 2
    painter.translate(width()*7/10,height() >> 1);

    painter.rotate(m_nRotationAngle);
    QFont font1("Microsoft YaHei",15,QFont::Bold,false);
    /*
         * 参数二：半径
         * 参数三：开始的角度
         * 参数四：指扫取的角度-顺时针（360度 / 8 = 45度）
         * 参数五：圆环的高度
         * 参数六：填充色
        **/
    painter.setFont(font1);
    painter.setPen(QPen(QColor(Qt::white),2));
    gradientArc(&painter,radius,0+bias,44,arcHeight,qRgb(200,200,0));
    gradientArc(&painter,radius,45+bias,44,arcHeight,qRgb(200,0,200));
    gradientArc(&painter,radius,90+bias,44,arcHeight,qRgb(0,200,200));
    gradientArc(&painter,radius,135+bias,44,arcHeight,qRgb(200,0,0));
    gradientArc(&painter,radius,225+bias,44,arcHeight,qRgb(0,200,0));
    gradientArc(&painter,radius,180+bias,44,arcHeight,qRgb(0,0,200));
    gradientArc(&painter,radius,270+bias,44,arcHeight,qRgb(0,0,0));
    gradientArc(&painter,radius,315+bias,44,arcHeight,qRgb(150,150,150));

    painter.setPen(QPen(QColor(Qt::yellow),2));
    painter.rotate(0);
    painter.drawText(80,10,thing1);

    painter.rotate(-45);
    painter.drawText(80,10,thing2);

    painter.rotate(-45);
    painter.drawText(80,10,thing3);

    painter.rotate(-45);
    painter.drawText(80,10,thing4);

    painter.rotate(-45);
    painter.drawText(80,10,thing5);

    painter.rotate(-45);
    painter.drawText(80,10,thing6);

    painter.rotate(-45);
    painter.drawText(80,10,thing7);

    painter.rotate(-45);
    painter.drawText(80,10,thing8);
    QPainter painter2(this);
    painter2.setRenderHint(QPainter::Antialiasing,true);
    painter2.translate(width()*7/10,height() >> 1);
    painter2.rotate(-90);
    static const QPoint poit[4] = {QPoint(0,-18),QPoint(10,0),QPoint(0,70),QPoint(-10,0)};
    painter2.setBrush(QColor(Qt::red));
    painter2.setPen(Qt::NoPen);
    painter2.drawPolygon(poit,4);

    painter2.setBrush(QColor(Qt::darkGray));
    painter2.drawEllipse(-7,-7,14,14);
}

void Widget::on_ok_but_clicked()
{
        QString qstr1=ui->lineEdit->text();
        QString qstr2=ui->lineEdit_2->text();
        if(qstr2.isEmpty())
        {
            ui->lineEdit_2->setText("请输入正整数。");
            return;
        }
        int nCount = qstr2.count();
        for(int i = 0 ; i < nCount ; i++)
        {
            QChar cha = qstr2.at(i);
            ushort uni = cha.unicode();
            if(uni >= 0x4E00 && uni <= 0x9FA5)
            {
                //这个字符是中文
                ui->lineEdit_2->setText("汉字无效！");
                return;
            }
        }
        for(int i = 0 ; i < nCount ; i++)
        {
            QChar cha = qstr2.at(i);
            ushort uni = cha.unicode();
            if(uni >= 65 && uni <= 90)
            {
                //这个字符是字母
                ui->lineEdit_2->setText("大写字母无效！");
                return;
            }
            if(uni >= 97 && uni <= 122)
            {
                //这个字符是字母
                ui->lineEdit_2->setText("小写字母无效！");
                return;
            }
        }
        float datatemp=0;
        int ind=ui->comboBox->currentIndex();
        if(listbox[ind]==0)
        {
            listbox[ind]=1;
            datatemp=listnum[ind];
            listnum[ind]=qstr2.toFloat();
        }
        else
            return;
        float temp=0;
        for(int i=0;i<8;i++)
        {
            temp=temp+listnum[i];
        }
        if(temp==0)
        {
            QMessageBox::about(NULL, "温馨提示", "要求至少有一个事件的权值不为零");
            listnum[ind]=datatemp;
            qstr2=QString("%1").arg(QString::number(datatemp, 'f',4));
        }
        init=1;
        change=1;
    switch(ind)
    {
        case 0:
            thing1=qstr1;
            thingshow[0]="事件一:"+thing1+"的权重为"+qstr2+"\n";
            break;
        case 1:
            thing2=qstr1;
            thingshow[1]="事件二:"+thing2+"的权重为"+qstr2+"\n";
            break;
        case 2:
            thing3=qstr1;
            thingshow[2]="事件三:"+thing3+"的权重为"+qstr2+"\n";
            break;
        case 3:
            thing4=qstr1;
            thingshow[3]="事件四:"+thing4+"的权重为"+qstr2+"\n";
            break;
        case 4:
            thing5=qstr1;
            thingshow[4]="事件五:"+thing5+"的权重为"+qstr2+"\n";
            break;
        case 5:
            thing6=qstr1;
            thingshow[5]="事件六:"+thing6+"的权重为"+qstr2+"\n";
            break;
        case 6:
            thing7=qstr1;
            thingshow[6]="事件七:"+thing7+"的权重为"+qstr2+"\n";
            break;
        case 7:
            thing8=qstr1;
            thingshow[7]="事件八:"+thing8+"的权重为"+qstr2+"\n";
            break;
        default:
            break;
    }
    qstr1="";
    qstr2="";
    for(int i=0;i<8;i++)
    {
        qstr1=qstr1+thingshow[i];
    }
    ui->TextEdit->setPlainText(qstr1);
}

void Widget::on_det_but_clicked()
{
    ui->lineEdit->clear();
    int ind=ui->comboBox->currentIndex();
    if(listbox[ind]>0)
    {
        listbox[ind]=0;
    }
    else
        return;
    thingshow[ind]="\n";
    QString qstr1="";
    for(int i=0;i<8;i++)
    {
        qstr1=qstr1+thingshow[i];
    }
    ui->TextEdit->setPlainText(qstr1);
}

void Widget::btnaboutClicked()
{
    win1* dlg=new win1();
    dlg->show();
}

void Widget::btnrecClicked()
{
    btnClicked();
    rec=1;
}
