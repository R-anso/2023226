#include "appremind.h"
#include "ui_appremind.h"
#include "QPainter"
#include <QPoint>
AppRemind::AppRemind(Note *note):
    ui(new Ui::AppRemind)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    this->setAttribute(Qt::WA_TranslucentBackground,true);
    ui->label_2->setText(note->Thing);
    ui->label->setText(note->Date+" "+note->Time);
}

AppRemind::~AppRemind()
{
    delete ui;
}
void AppRemind::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    for(int i=0;i<=60;i++)
    {
        p.setPen(QPen(QColor(0,120,255,4*i),2));
        p.drawLine(QPointF(i,i),QPointF(i,i));
    }
    p.drawLine(QPoint(60,60),QPoint(60,90));
    p.drawLine(QPoint(60,60),QPoint(90,60));
    p.drawLine(QPoint(30,30),QPoint(90,30));
}
