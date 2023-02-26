#ifndef APPREMIND_H
#define APPREMIND_H

#include <QDialog>
#include "note.h"
namespace Ui {
class AppRemind;
}

class AppRemind : public QDialog
{
    Q_OBJECT

public:
    explicit AppRemind(Note *note = nullptr);
    ~AppRemind();

private:
    Ui::AppRemind *ui;

protected:
    void paintEvent(QPaintEvent *);
};

#endif // APPREMIND_H
