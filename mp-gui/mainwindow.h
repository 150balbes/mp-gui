#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "form.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_DirProfiles_clicked();

    void on_pushButton_Exit_clicked();

    void on_pushButton_ListInit_clicked();

    void onButtonSend();

//    void onButtonSend_git();

    void on_pushButton_AptConf_clicked();

    void on_pushButton_BuildDir_clicked();

    void on_pushButton_git_clicked();

public slots:
    void slotDataOnStdoutList();

private:
    Ui::MainWindow *ui;
    QString str_cmd;
    QString str_make;
    QString program_make;
    QProcess*  make_process;

    Form *myform;

signals:
    void sendData(QString str);

};


#endif // MAINWINDOW_H
