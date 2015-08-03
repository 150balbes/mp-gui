#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QProcess>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    make_process = new QProcess(this);
    connect(make_process, SIGNAL(readyReadStandardOutput()), SLOT(slotDataOnStdoutList()));

    myform = new Form();
    connect(ui->pushButton_RunCreate, SIGNAL(clicked()), myform, SLOT(show()));
    connect(ui->pushButton_RunCreate, SIGNAL(clicked()), this, SLOT(onButtonSend()));
    connect(this, SIGNAL(sendData(QString)), myform, SLOT(recieveData(QString)));

//    connect(ui->pushButton_ListInit, SIGNAL(clicked()), myform, SLOT(show()));
//    connect(ui->pushButton_ListInit, SIGNAL(clicked()), this, SLOT(onButtonSend_list()));

//    ui->comboBox_repo->addItem("rsync://ftp.altlinux.org/ALTLinux/p7/branch/");
//    ui->comboBox_repo->addItem("rsync://ftp.heanet.ie/mirrors/ftp.altlinux.org/p7/branch/");
//    ui->comboBox_repo->addItem("rsync://pspo.fcior.edu.ru/ALTLinux/p7/branch/");
//    ui->comboBox_repo->addItem("rsync://distrib-coffee.ipsl.jussieu.fr/pub/linux/altlinux/p7/branch/");
//    ui->comboBox_repo->addItem("rsync://ftp.linux.kiev.ua/ALTLinux/p7/branch/");
//    ui->comboBox_repo->addItem("rsync://mirror.yandex.ru/altlinux/p7/branch/");

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onButtonSend()
{
    str_make = "make ARCH=" + ui->cb_arch->currentText() + " -C " + ui->DirProfiles->text() + " " + ui->comboBox_ListDistro->currentText();
    emit sendData(str_make);
}

void MainWindow::on_pushButton_DirProfiles_clicked()
{
    QString str = QFileDialog::getExistingDirectory(0, "Directory Dialog", "~/");
    ui->DirProfiles->setText(str);
}

void MainWindow::on_pushButton_Exit_clicked()
{
    close();
}

void MainWindow::slotDataOnStdoutList()
{
    ui->ListDistro->append(make_process->readAllStandardOutput());
    str_cmd = ui->ListDistro->toPlainText();
    QStringList strList=str_cmd.split('\n');
    strList.removeDuplicates();
    QString str;
    for (int i=0; i<strList.size(); i++)
    {
        str = strList.at(i);
        if (!str.isEmpty())
        {
            if (str.left(5) != "make:" )
                ui->comboBox_ListDistro->addItem(str);
        }
    }
}

void MainWindow::on_pushButton_ListInit_clicked()
{
    str_make = "make -C " + ui->DirProfiles->text() + " help";
    make_process->start(str_make);

}
