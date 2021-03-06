#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QProcess>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QCheckBox>
#include <QMessageBox>
#include <QDir>
#include <QSettings>
#include <QRect>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);

    make_process = new QProcess(this);
    make_process->setProcessChannelMode(QProcess::MergedChannels);

    connect(make_process, SIGNAL(readyReadStandardOutput()), SLOT(slotDataOnStdoutList()));

    myform = new Form();

    connect(ui->pushButton_RunCreate, SIGNAL(clicked()), myform, SLOT(show()));
    connect(ui->pushButton_RunCreate, SIGNAL(clicked()), this, SLOT(onButtonSend()));
    connect(this, SIGNAL(sendData(QString)), myform, SLOT(recieveData(QString)));

    char *prog = "rm -f /tmp/distro";
    system(prog);
    str_make = "make -C " + ui->DirProfiles->text() + " help>/tmp/distro";
    make_process->start(str_make);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onButtonSend()
{
    QString str_mirror;
    QString str_branch1;
    QString str_branch2;
    if (ui->checkBox_mirror->checkState())
    {
        QMessageBox msgBox;
        msgBox.setText("ВНИМАНИЕ !!!! \n Будет запущено скачивание ВСЕХ пакетов из отмеченных сетевых репозиториев \
 в каталог /var/ftp/ALTLinux/ \n Это может занимать много времени и до 180 Гб места в разделе var !!!! \n Для \
 исключения из процесса копирования части пакетов, можно воспользоваться сервисом \
 \n http://sisyphus.ru/rsync/ \n Cформировать там список ИСКЛЮЧАЕМЫХ пакетов и скопировать его \
 в файл \n /etc/mp-gui.d/sisyphus-mirror/exclude ");
        msgBox.move(400, 300);
        msgBox.exec();
       if (ui->checkBox_sisyphus->checkState())
        {
               str_branch1 = "Sisyphus ";
        }
       if (ui->checkBox_p7->checkState())
        {
               str_branch1 += "p7/branch ";
        }
       if (ui->checkBox_t7->checkState())
        {
               str_branch1 += "t7/branch ";
        }
       if (ui->checkBox_p6->checkState())
        {
               str_branch1 += "p6/branch ";
        }
       if (ui->checkBox_t6->checkState())
        {
               str_branch1 += "t6/branch ";
        }
        str_branch2 = "\"" + str_branch1 + "\"";
        str_mirror = "sisyphus-mirror -i -c /etc/mp-gui.d/sisyphus-mirror/sisyphus-mirror.conf -l " + str_branch2;
        emit sendData(str_mirror);
    }
    else
    {

    QDir dir_out(QDir::homePath()+"/out");
    if (!QDir(dir_out).exists())
    {
        QDir dir;
        dir.mkdir(QDir::homePath()+"/out");
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

    QString str_check;
    if (ui->checkBox_Check->checkState())
    {
        str_check = " CHECK=1";
    }
    else
    {
        str_check = "";
    }

    QString str_bell;
    if (ui->checkBox_BELL_CMD->checkState())
    {
        str_bell = " BELL_CMD=1";
    }
    else
    {
        str_bell = "";
    }


    QString str_clean;
    str_clean = " CLEAN=" + ui->cb_Clean->currentText();

    QString str_arch;
    str_arch = " ARCH=" + ui->cb_arch->currentText();

    QString str_pro;
    QString str_builddir;
    QString str_profiles;
    str_profiles = ui->DirProfiles->text();
    if (ui->BuildDir->text() != "")
    {
        str_builddir = " BUILDDIR_NO_RM=1 BUILDDIR=" + ui->BuildDir->text();
    }
    else
    {
        str_builddir = "";
    }

    if (ui->checkBox_ReMake->checkState())
    {
        str_pro = " -C " + ui->BuildDir->text();
    }
    else
    {
        str_pro = str_arch + str_clean + str_bell + str_builddir + " -C " + str_profiles  + " " + ui->comboBox_ListDistro->currentText();
    }
    str_make = "make " + str_check + str_aptconf + str_pro;
    emit sendData(str_make);
    }
}

void MainWindow::on_pushButton_DirProfiles_clicked()
{
    QString str = QFileDialog::getExistingDirectory(0, "Directory Dialog", "~/");
    ui->DirProfiles->setText(str);
    char *prog = "rm -f /tmp/distro";
    system(prog);
    str_make = "make -C " + ui->DirProfiles->text() + " help>/tmp/distro";
    make_process->start(str_make);
}

void MainWindow::slotDataOnStdoutList()
{
    ui->comboBox_ListDistro->clear();
    str_cmd = "/tmp/distro";
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
//        if(stream.status()!= QTextStream::Ok)
//            {
//                qDebug() << "Ошибка чтения файла";
//                   ui->label_7->setText("Ошибка чтения файла");
//            }
        file.close();

    }
}

void MainWindow::on_pushButton_AptConf_clicked()
{
    QString str = QFileDialog::getOpenFileName(0, "Open Dialog", "/etc/mp-gui.d/apt/apt-conf/");
    ui->AptConf->setText(str);
}

void MainWindow::on_pushButton_BuildDir_clicked()
{
    QString str = QFileDialog::getExistingDirectory(0, "Directory Dialog", "~/");
    ui->BuildDir->setText(str);
}

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
            msgBox.move(200, 200);
            msgBox.exec();
    }
}

void MainWindow::on_pushButton_Exit_clicked()
{
    close();
}

void MainWindow::on_pushButton_Settings_clicked()
{
    QSettings settings("mp-gui","mp-gui");
//    settings.setValue("geometry", geometry());
    settings.setValue("dir_profiles", ui->DirProfiles->text());
    settings.setValue("apt_conf", ui->AptConf->text());
    settings.setValue("dir_build", ui->BuildDir->text());
}

void MainWindow::on_pushButton_RedSet_clicked()
{
    QSettings settings("mp-gui","mp-gui");
//    QRect rect = settings.value("geometry", QRect(0, 0, 740, 480)).toRect();
//    move(rect.topLeft());
//    resize(rect.size());
    QString profil_set = settings.value("dir_profiles").toString();
    ui->DirProfiles->setText(profil_set);
    QString apt_set = settings.value("apt_conf").toString();
    ui->AptConf->setText(apt_set);
    QString build_set = settings.value("dir_build").toString();
    ui->BuildDir->setText(build_set);

    char *prog = "rm -f /tmp/distro";
    system(prog);
    str_make = "make -C " + ui->DirProfiles->text() + " help>/tmp/distro";
    make_process->start(str_make);

}

