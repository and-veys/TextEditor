#include "dialoghelp.h"
#include "ui_dialoghelp.h"

DialogHelp::DialogHelp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogHelp)
{
    ui->setupUi(this);
    ui->textEdit->setReadOnly(true);
    connect(ui->Close, &QPushButton::clicked, this, &DialogHelp::close);
}

DialogHelp::~DialogHelp()
{
    delete ui;
}

void DialogHelp::setHelp(const QString & str)
{
    ui->textEdit->setText(str);
}

void DialogHelp::close()
{
    accept();
}
