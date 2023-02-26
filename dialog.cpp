#include "dialog.h"
#include "ui_dialog.h"
#include "addnew.h"
#include "about.h"
#include "history.h"
#include "windows.h"
#include <QGridLayout>
#include <QDebug>
#include "note.h"
#include <QFile>
#include <QTextCodec>
#include <QDateTime>
#include <algorithm>
//主界面窗口设置
Dialog::Dialog(QWidget *parent)
        : QDialog(parent), ui(new Ui::Dialog) {
    ui->setupUi(this);

}

Dialog::~Dialog() {
    delete ui;
}  //析构函数


void Dialog::on_pushButton_clicked() {
    Addnew *add = new Addnew(&note_vector);
    add->exec();
    onRefresh() ; //刷新
}   //打开新增面板

void Dialog::on_pushButton_2_clicked() {
    About *about = new About;
    about->show();

}  //打开关于面板

void Dialog::on_pushButton_3_toggled(bool checked) {

    if (checked) {
        ui->pushButton_3->setText(tr("显示"));
        ui->frame->hide();
    } else {
        ui->pushButton_3->setText(tr("最小化"));
        ui->frame->show();
    }
}  //叶zc应该换掉的


void Dialog::on_pushButton_4_clicked() {
    history *a = new history(this, &note_vector);
    a->show();
}   //历史事项对应窗口


void Dialog::onRefresh() {        //用于初始化和添加的刷新函数
//
    if (ui->frame_2->widget()->layout() != nullptr) {   //删除原有布局
        QLayoutItem *item;
        while ((item = ui->frame_2->widget()->layout()->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete ui->frame_2->widget()->layout();
    }
    QGridLayout *gridLayout = new QGridLayout();                     //网格布局
    gridLayout->setVerticalSpacing(20);
    //---------------------------------------------------------------//
    QFile file;
    file.setFileName("log.txt");                                     //保存到本地地址
    QString str_read[9];
    QString strline;
    int num;
    if (file.open(QIODevice::ReadOnly))                              //只读
    {
        QTextCodec *codec = QTextCodec::codecForName("GBK");         //指定读码方式为GBK
        note_vector.clear();                                         //清空vector
        while (!file.atEnd())                                        //当没有读到文件末尾时
        {
            strline = codec->toUnicode(file.readLine());             //以GBK的编码方式读取一行
            QChar c = strline[0];                                    //判断第一个字符是否是回车符（空文件只有一个回车符）
            char c0 = c.toLatin1();
            if (c0 > 57 || c0 < 48)
            { return; }
            //
            QStringList list = strline.split(" ");                   //以一个空格为分隔符
            for (int i = 0; i < 9; i++)    {str_read[i] = list[i];}
            num = str_read[0].toInt();                 //将第一个数据转化为int类
            Note *n1 = new Note(&note_vector,num,str_read[1],str_read[2],str_read[3],str_read[4],str_read[5],str_read[6],str_read[7]);
            //
            QObject::connect(n1,&Note::refresh,this,&Dialog::onRefresh1);  //关联信号和槽
            note_vector.push_back(n1);                //放到vector最后一个位置
            if (n1->finish == 0) {
                gridLayout->addWidget(n1);
            }
        }
        ui->frame_2->widget()->setLayout(gridLayout);
        repaint();                                //顺序输出vector所有的东西
    }
}

void Dialog::onRefresh1() {     //专门用于编辑的刷新函数
   //
    if (ui->frame_2->widget()->layout() != nullptr) {//删除原有布局
        QLayoutItem *item;
        while ((item = ui->frame_2->widget()->layout()->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete ui->frame_2->widget()->layout();
    }
    QGridLayout *gridLayout = new QGridLayout();                   //网格布局

    //

    QFile file;
    file.setFileName("log.txt");                                    //保存到本地地址
    QString str_read[9];
    QString strline;
    int num;
    if (file.open(QIODevice::ReadOnly))                              //只读
    {
        QTextCodec *codec = QTextCodec::codecForName("GBK");         //指定读码方式为GBK
        note_vector.clear();                                         //清空当前vector，避免重复
        while (!file.atEnd())                                        //当没有读到文件末尾时
        {
            strline = codec->toUnicode(file.readLine());             //以GBK的编码方式读取一行
            QChar c = strline[0];                                    //判断第一个字符是否是回车符（空文件只有一个回车符）
            char c0 = c.toLatin1();
            if (c0 > 57 || c0 < 48)
            { return; }

            //
            QStringList list = strline.split(" ");                   //以一个空格为分隔符
            for (int i = 0; i < 9; i++) {
                str_read[i] = list[i];
            }
            num = str_read[0].toInt();         //将第一个数据转化为int类
            Note *n1 = new Note(&note_vector, num, str_read[1], str_read[2], str_read[3], str_read[4], str_read[5],str_read[6],str_read[7]);
            QObject::connect(n1,&Note::refresh,this,&Dialog::onRefresh1);   //关联信号和槽
            note_vector.push_back(n1);         //放到vector最后一个位置
            if (n1->finish == 0) {gridLayout->addWidget(n1);}
        }
        ui->frame_2->widget()->setLayout(gridLayout);
        repaint();                             //顺序输出vector所有的东西
    }
}

void Dialog::onRefresh_for_time(){        //用于时间顺序的刷新函数

    if (ui->frame_2->widget()->layout() != nullptr) {   //删除原有布局
        QLayoutItem *item;
        while ((item = ui->frame_2->widget()->layout()->takeAt(0)) != nullptr) {
            delete item->widget();
            delete item;
        }
        delete ui->frame_2->widget()->layout();
    }
    QGridLayout *gridLayout = new QGridLayout();                     //网格布局
    gridLayout->setVerticalSpacing(20);
    //---------------------------------------------------------------//
    QFile file;
    file.setFileName("log.txt");                                     //保存到本地地址
    QString str_read[9];
    QString strline;
    int num;
    if (file.open(QIODevice::ReadOnly))                              //只读
    {
        QTextCodec *codec = QTextCodec::codecForName("GBK");         //指定读码方式为GBK
        note_vector.clear();                                         //清空vector
        while (!file.atEnd())                                        //当没有读到文件末尾时
        {
            strline = codec->toUnicode(file.readLine());             //以GBK的编码方式读取一行
            QChar c = strline[0];                                    //判断第一个字符是否是回车符（空文件只有一个回车符）
            char c0 = c.toLatin1();
            if (c0 > 57 || c0 < 48) { return; }
            //
            QStringList list = strline.split(" ");                   //以一个空格为分隔符
            for (int i = 0; i < 9; i++) { str_read[i] = list[i]; }
            num = str_read[0].toInt();                 //将第一个数据转化为int类
            Note *n1 = new Note(&note_vector, num, str_read[1], str_read[2], str_read[3], str_read[4], str_read[5],
                                str_read[6], str_read[7]);
            //
            QObject::connect(n1, &Note::refresh, this, &Dialog::onRefresh1);  //关联信号和槽
            note_vector.push_back(n1);                //放到vector最后一个位置

        }
    }//删除布局之后再从文件中读一遍
    note_vector_time.clear();
    //
    QString date_time_str[note_vector.size()][2];   //储存时间和日期
    QDateTime date_time[note_vector.size()];        //日时
    uint time[note_vector.size()];
    for(int i = 0; i < note_vector.size(); i++ )
    {
        date_time_str[i][0] = note_vector.at(i)->Date;
        date_time_str[i][1] = note_vector.at(i)->Time;
        QString s=date_time_str[i][0];
        QDate d = QDate::fromString(s,"yyyy/MM/dd");
        QTime t = QTime::fromString(date_time_str[i][1],"hh:mm");
        date_time[i] = QDateTime(d,t);
        time[i] = date_time[i].toTime_t();
        note_vector.at(i)->time_int=time[i];
    }//以上步骤提取了note_vector内的时间和日期并且合成了QDateTime 类，转换为时间截time
    for(int i=0;i<note_vector.size();i++){
        note_vector_time.push_back(note_vector.at(i));
    }
    std::sort(note_vector_time.begin(),note_vector_time.end(),isSmaller);
    for(int i=0;i<note_vector_time.size();i++){

        if(note_vector_time.at(i)->finish==0)
            gridLayout->addWidget(note_vector_time.at(i));
    }
    ui->frame_2->widget()->setLayout(gridLayout);
    repaint();
}

void Dialog::on_pushButton_5_toggled(bool checked)
{
    if (checked) {
        ui->pushButton_5->setText(tr("按创建先后顺序显示"));
        qDebug()<<"0"<<endl;
        this->onRefresh_for_time();
    }
    else {
        ui->pushButton_5->setText(tr("按时间先后顺序显示"));
        qDebug()<<"0"<<endl;
        this->onRefresh();
    }
}
bool Dialog::isSmaller(Note *a, Note *b){
    return a->time_int < b->time_int;
}
