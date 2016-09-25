#include "mylcd.h"
#include <QLCDNumber>
#include <QHBoxLayout>
#include <QFont>
#include <QPalette>
#include <QTime>

MyLCD::MyLCD(QWidget *parent, Qt::WindowFlags f)
    :QLabel(parent,f),times(4)
{
    //this->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    lcd_1 = new QLCDNumber(this);
    lcd_2 = new QLCDNumber(this);
    lcd_3 = new QLCDNumber(this);
    lcd_4 = new QLCDNumber(this);

    lcd_1->setFrameShape(QFrame::NoFrame);
    lcd_2->setFrameShape(QFrame::NoFrame);
    lcd_3->setFrameShape(QFrame::NoFrame);
    lcd_4->setFrameShape(QFrame::NoFrame);

    QPalette lcd_palette;
    lcd_palette = lcd_1->palette();
    lcd_palette.setColor(QPalette::Normal, QPalette::WindowText, Qt::yellow);
    lcd_1->setPalette(lcd_palette);
    lcd_palette = lcd_2->palette();
    lcd_palette.setColor(QPalette::Normal, QPalette::WindowText, Qt::yellow);
    lcd_2->setPalette(lcd_palette);
    lcd_palette = lcd_3->palette();
    lcd_palette.setColor(QPalette::Normal, QPalette::WindowText, Qt::yellow);
    lcd_3->setPalette(lcd_palette);
    lcd_palette = lcd_4->palette();
    lcd_palette.setColor(QPalette::Normal, QPalette::WindowText, Qt::yellow);
    lcd_4->setPalette(lcd_palette);

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addWidget(lcd_1);
    mainLayout->addWidget(lcd_2);
    mainLayout->addWidget(lcd_3);
    mainLayout->addWidget(lcd_4);
    this->setLayout(mainLayout);
}

void MyLCD::run()
{
    QString n1,n2,n3,n4,tmp;

    if(times != -1)
    {
        tmp = createRand();
        n1 = tmp.at(0);n2 = tmp.at(1);
        n3 = tmp.at(2);n4 = tmp.at(3);
        if(times == 4)
        {
            lcd_1->display(n1);
        }
        else if(!luckyNumber.isEmpty())
        {
            lcd_1->display(luckyNumber.at(0));
        }

        if(times >= 3)
        {
            lcd_2->display(n2);
        }
        else if(!luckyNumber.isEmpty())
        {
            lcd_2->display(luckyNumber.at(1));
        }

        if(times >= 2)
        {
            lcd_3->display(n3);
        }
        else if(!luckyNumber.isEmpty())
        {
            lcd_3->display(luckyNumber.at(2));
        }

        if(times >= 1)
        {
            lcd_4->display(n4);
        }
        else if(!luckyNumber.isEmpty())
        {
            times = -1;
            lcd_4->display(luckyNumber.at(3));
            //emit finished();
            luckyNumber = "";
            //luckynums.append(tmp);
        }
    }

}

void MyLCD::stop()
{
    if(times != 0) --times;
}

void MyLCD::reset()
{
    times = 4;
    luckyNumber = "";
    //run();
}

void MyLCD::setLuckyNumber(QString num)
{
    luckyNumber = num;
}

QString MyLCD::createRand()
{
    QTime time = QTime::currentTime();
    uint seed = time.msecsSinceStartOfDay();
    QString num;
    qsrand(seed<<5);
    num = QString("%1").arg((qrand()%5001), 4, 10, QChar('0'));
//    QList<QString>::const_iterator i;
//    bool flag = false;
//    do
//    {
//        num = QString("%1").arg(qrand()%5001, 4, 10, QChar('0'));
//        for(i = luckynums.cbegin();i != luckynums.cend(); ++i)
//        {
//            if(*i == num){ flag = false;break;}
//        }
//        if(i == luckynums.cend()) {flag = true;}
//    }while(!flag);

    return num;
}
