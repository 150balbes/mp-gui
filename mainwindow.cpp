#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QProcess>
#include <QString>
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    myform = new Form();
    connect(ui->pushButton_RunCreate, SIGNAL(clicked()), myform, SLOT(show()));
    connect(ui->pushButton_RunCreate, SIGNAL(clicked()), this, SLOT(onButtonSend()));
    connect(this, SIGNAL(sendData(QString)), myform, SLOT(recieveData(QString)));

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
    str_make = "make DEBUG=1 ARCH=" + ui->cb_arch->currentText() + " -C " + ui->DirProfiles->text() + " " + ui->comboBox_ListDistro->currentText();
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

void MainWindow::on_pushButton_ListInit_clicked()
{
    str_cmd = ui->DirProfiles->text();
    str_cmd = str_cmd + "/distro.txt";
    QFile file(str_cmd);
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        QString str;
        while (!stream.atEnd())
            {
                str = stream.readLine();
                ui->comboBox_ListDistro->addItem(str);
            }
            if(stream.status()!= QTextStream::Ok)
            {
//                qDebug() << "Ошибка чтения файла";
//                   ui->label_7->setText("Ошибка чтения файла");
            }
            file.close();

    }

//    str_cmd = ui->mp_distro->text() +
//    str_cmd = ui->DirProfiles->text();
//            + ui->mp_distro_flag->text();

//    ui->label_6->setText(str_cmd);

//    QString program = "make help >/tmp/ttt";
//            -C " + QString(ui->DirProfiles->text());
//            "/home/ovp/mp/mp-distro.sh";
//    QStringList arguments;
//    arguments <<  ui->mp_distro_flag->text();
//               << "help/distro" << ">/tmp/dist.txt";

//    arguments << ">/tmp/ddd";

//    QProcess *mp_distr = new QProcess();
//    mp_distr->start(QString(str_cmd));
//    mp_distr->start(program);
//    mp_distr->start("/home/ovp/mp/mp-distro.sh", ui->DirProfiles->text());
//    QString cmd_s = QString::fromStdString(str_cmd);
//    system(cmd_s);

}
