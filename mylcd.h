#ifndef MYLCD_H
#define MYLCD_H

#include <QLabel>
//#include <QList>
class QLCDNumber;

class MyLCD : public QLabel
{
    Q_OBJECT
public:
    MyLCD(QWidget *parent = Q_NULLPTR, Qt::WindowFlags f = Qt::WindowFlags());

public slots:
    void run();
    void stop();
    void reset();
    void setLuckyNumber(QString num);

signals:
    void finished();

private:
    QLCDNumber *lcd_1;
    QLCDNumber *lcd_2;
    QLCDNumber *lcd_3;
    QLCDNumber *lcd_4;

    QString luckyNumber;

    int times;
    //QList<QString> luckynums;
    QString createRand();
};

#endif // MYLCD_H
