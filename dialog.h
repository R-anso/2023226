#ifndef DIALOG_H
#define DIALOG_H
#include <vector>
#include <QDialog>
#include "note.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
Q_OBJECT

public:
    std::vector<Note*> note_vector;
    std::vector<Note*> note_vector_time;
    static bool isSmaller(Note* a,Note* b);
    Dialog(QWidget *parent = nullptr);
    ~Dialog();
    void onRefresh();
    void onRefresh1();
    void onRefresh_for_time();
public slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_toggled(bool checked);

    void on_pushButton_4_clicked();

public:
    Ui::Dialog *ui;
private slots:
    void on_pushButton_5_toggled(bool checked);
};
#endif // DIALOG_H
