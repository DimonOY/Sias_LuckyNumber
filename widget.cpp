#include "widget.h"
#include "mylcd.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QPushButton>
#include <QRadioButton>
#include <QPainter>
#include <QPixmap>
#include <QBrush>
#include <QTimer>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowTitle(tr("电院迎新晚会抽奖系统"));
    //this->showFullScreen();
    QRect screen = QApplication::desktop()->screenGeometry(); //屏幕分辨率
    int s_width = screen.size().width();
    int s_height = screen.size().height();
    this->resize(s_width,s_height);

    mylcd = new MyLCD(this);

    start_btn = new QPushButton(tr("开始"), this);
    QPalette btn_palette = start_btn->palette();
    btn_palette.setColor(QPalette::Button,Qt::red);
    start_btn->setPalette(btn_palette);
    start_btn->setGeometry(s_width/8*4, s_height/5*4,80,50);

    quit_btn = new QPushButton(tr("退出"), this);
    quit_btn->setPalette(btn_palette);
    quit_btn->setGeometry(s_width/8*5, s_height/5*4,80,50);

    stop_btn = new QPushButton(tr("停止"), this);
    stop_btn->setPalette(btn_palette);
    stop_btn->setGeometry(s_width/8*6, s_height/5*4,80,50);

    reset_btn = new QPushButton(tr("重置"), this);
    reset_btn->setPalette(btn_palette);
    reset_btn->setGeometry(s_width/8*7, s_height/5*4,80,50);

    /*radioButtons*/

    one_rbtn = new QRadioButton(tr("一等奖"), this);
    two_rbtn = new QRadioButton(tr("二等奖"), this);
    three_rbtn = new QRadioButton(tr("三等奖"), this);
    QPalette rbtn_palette;
    rbtn_palette = one_rbtn->palette();
    rbtn_palette.setColor(QPalette::Normal, QPalette::WindowText, Qt::yellow);
    one_rbtn->setPalette(rbtn_palette);
    two_rbtn->setPalette(rbtn_palette);
    three_rbtn->setPalette(rbtn_palette);




    timer = new QTimer(this);
    connect(quit_btn, &QPushButton::clicked, &QApplication::quit);
    connect(start_btn, &QPushButton::clicked, [=](){
        timer->start(30);
        mylcd->reset();
        //set lucknumber
        QString num("");
        switch(which)
        {
        case 1:
            num = one_list.isEmpty() ? "":one_list.pop();
            break;
        case 2:
            num = two_list.isEmpty() ? "":two_list.pop();
            break;
        case 3:
            num = three_list.isEmpty() ? "":three_list.pop();
            break;
        default:
            break;
        }
        emit luckyNumber(num);

    });
    connect(timer, &QTimer::timeout, mylcd, &MyLCD::run);
    connect(stop_btn, &QPushButton::clicked, mylcd, &MyLCD::stop);
    connect(reset_btn, &QPushButton::clicked, this, &Widget::reset);
    connect(one_rbtn, &QRadioButton::toggled, this, &Widget::setLucky_one);
    connect(two_rbtn, &QRadioButton::toggled, this, &Widget::setLucky_two);
    connect(three_rbtn, &QRadioButton::toggled, this, &Widget::setLucky_three);
    connect(this, &Widget::luckyNumber, mylcd, &MyLCD::setLuckyNumber);
    connect(mylcd, &MyLCD::finished, timer, &QTimer::stop);

    reset();

}

Widget::~Widget()
{
}

void Widget::paintEvent(QPaintEvent */*event*/)
{
    QPainter painter(this);
    QPixmap bg_pixmap(":/images/images/kuanghuan.png");

    painter.drawPixmap(this->rect(), bg_pixmap);
}

void Widget::resizeEvent(QResizeEvent */*event*/)
{
    //qDebug()<<size();
    int w = size().width();
    int h = size().height();
    mylcd->setGeometry(w/27, 0, w/5*4, h/5*4);
    start_btn->setGeometry(w/8*4, h/5*4, 80, 50);
    stop_btn->setGeometry(w/8*5, h/5*4, 80, 50);
    reset_btn->setGeometry(w/8*6, h/5*4, 80 ,50);
    quit_btn->setGeometry(w/8*7, h/5*4, 80, 50);

    one_rbtn->setGeometry(w/30, h/10*4, 100,50);
    two_rbtn->setGeometry(w/30, h/10*5, 100,50);
    three_rbtn->setGeometry(w/30, h/10*6, 100,50);
    QFont font = one_rbtn->font();
    font.setPixelSize(one_rbtn->size().height()/2);
    one_rbtn->setFont(font);
    two_rbtn->setFont(font);
    three_rbtn->setFont(font);

}

void Widget::reset()
{
    one_list.clear();
    two_list.clear();
    three_list.clear();
    total_list.clear();

    one_list.append("1017");
    three_list.append("3709");
}

void Widget::setLucky_one(bool status)
{
    if(!status) return ;
    which = 1;
}

void Widget::setLucky_two(bool status)
{
    if(!status) return ;
    which = 2;
}

void Widget::setLucky_three(bool status)
{
    if(!status) return ;
    which = 3;
}

//void Widget::setLuckyNumber(QString num)
//{
//    emit luckyNumber(num);
//}

