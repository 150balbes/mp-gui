#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QProcess>
#include <QString>
#include <QStringList>
#include <QFile>
#include <QTextStream>
#include <QCheckBox>
#include <QMessageBox>
#include <QDir>

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

//    connect(ui->pushButton_git, SIGNAL(clicked()), myform, SLOT(show()));
//    connect(ui->pushButton_git, SIGNAL(clicked()), this, SLOT(onButtonSend_git()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onButtonSend()
{
    QDir dir_out(QDir::homePath()+"/out");
    if (!QDir(dir_out).exists())
    {
        QDir dir;
        dir.mkdir(QDir::homePath()+"/out");
    }

    QString str_check;
    if (ui->checkBox_Check->checkState())
    {
        str_check = " CHECK=1";
    }
    else
    {
        str_check = "";
    }

    QString str_builddir;
    if (ui->BuildDir->text() != "")
    {
        str_builddir = " BUILDDIR=" + ui->BuildDir->text();
    }
    else
    {
        str_builddir = "";
    }

    QString str_aptconf;
    if (ui->AptConf->text() != "")
    {
        str_aptconf = " APTCONF=" + ui->AptConf->text();
    }
    else
    {
        str_aptconf = "";
    }

    str_make = "make ARCH=" + ui->cb_arch->currentText() + str_check + str_aptconf + str_builddir + " -C " + ui->DirProfiles->text() + " " + ui->comboBox_ListDistro->currentText();
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

void MainWindow::on_pushButton_AptConf_clicked()
{
    QString str = QFileDialog::getOpenFileName(0, "Open Dialog", "~/");
    ui->AptConf->setText(str);
}

void MainWindow::on_pushButton_BuildDir_clicked()
{
    QString str = QFileDialog::getExistingDirectory(0, "Directory Dialog", "~/");
    ui->BuildDir->setText(str);
}

//void MainWindow::onButtonSend_git()
//{
//    str_make = "git clone git://git.altlinux.org/people/mike/packages/mkimage-profiles.git";
//    emit sendData(str_make);
//}


void MainWindow::on_pushButton_git_clicked()
{
    QDir dir_mp(QDir::homePath()+"/mkimage-profiles");
    if (!QDir(dir_mp).exists())
       {
            char *str_cmd = "git clone git://git.altlinux.org/people/mike/packages/mkimage-profiles.git ~/mkimage-profiles";
            system(str_cmd);
            ui->DirProfiles->setText("~/mkimage-profiles");
        }
    else
        {
            QMessageBox msgBox;
            msgBox.setText("Каталог mkimage-profiles уже существует.");
            msgBox.exec();
    }
}
