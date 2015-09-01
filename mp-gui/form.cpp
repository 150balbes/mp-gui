#include "form.h"
#include "ui_form.h"

Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);

    m_process = new QProcess(this);

    connect(m_process, SIGNAL(readyReadStandardOutput()), SLOT(slotDataOnStdout()));
    connect(ui->m_ptxtCommand, SIGNAL(returnPressed()), SLOT(slotReturnPressed()));
    connect(ui->pcmd, SIGNAL(clicked()), SLOT(slotReturnPressed()));

}

Form::~Form()
{
    delete ui;
}

void Form::recieveData(QString str)
{
    ui->m_ptxtCommand->setText(str);
}

void Form::slotDataOnStdout()
{
    ui->m_ptxtDisplay->append(m_process->readAllStandardOutput());
}

void Form::slotReturnPressed()
{
    QString strCommand = "";
    strCommand += ui->m_ptxtCommand->text();
    m_process->start(strCommand);
}

void Form::on_pushButton_clicked()
{
    close();
}
