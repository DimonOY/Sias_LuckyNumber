#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStack>
class QResizeEvent;
class QPushButton;
class QRadioButton;
class MyLCD;

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

protected:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);

public slots:
    void reset();
    void setLucky_one(bool status);
    void setLucky_two(bool status);
    void setLucky_three(bool status);

signals:
    void luckyNumber(QString num);

private:
    QTimer *timer;
    MyLCD *mylcd;

    QPushButton *start_btn;
    QPushButton *stop_btn;
    QPushButton *quit_btn;
    QPushButton *reset_btn;

    QRadioButton *one_rbtn;
    QRadioButton *two_rbtn;
    QRadioButton *three_rbtn;

    QStack<QString> one_list,two_list,three_list,total_list;

    int which;
    //inline void setLuckyNumber(QString num);


};

#endif // WIDGET_H
