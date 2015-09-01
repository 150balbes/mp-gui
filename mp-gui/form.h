#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QProcess>

namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();

private:
    Ui::Form *ui;
    QProcess* m_process;

public slots:
    void slotDataOnStdout();

    void slotReturnPressed();

    void recieveData(QString str);

private slots:
    void on_pushButton_clicked();
};

#endif // FORM_H
