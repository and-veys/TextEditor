#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFile>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    name_file = "";
    ui->setupUi(this);
    setWindowTitle("Текстовый редактор");

    connect(ui->buttonSave, &QPushButton::clicked, this, &MainWindow::save);
    connect(ui->buttonSaveAs, &QPushButton::clicked, this, &MainWindow::saveAs);
    connect(ui->buttonOpen, &QPushButton::clicked, this, &MainWindow::open);
    connect(ui->buttonHelp, &QPushButton::clicked, this, &MainWindow::help);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::readFile(QString & nm, QString & res)
{
    QFile file(nm);
    if(file.open(QIODevice::ReadOnly)) {
        QByteArray arr = file.readAll();
        file.close();
        res = arr;
        return true;
    }
    return false;
}

bool MainWindow::writeFile(QString &nm)
{
    QFile file(nm);
    if(file.open(QIODevice::WriteOnly)) {
        file.write(ui->textEdit->toPlainText().toUtf8());
        file.flush();
        file.close();
        return true;
    }
    return false;

}

void MainWindow::save()
{
    if(name_file != "") {
        if(! writeFile(name_file))
            QMessageBox::critical(this, "Ошибка", "Ошибка записи в файл...");
    }
    else
        saveAs();
}

void MainWindow::saveAs()
{
     QString nm = QFileDialog::getSaveFileName(this, "Сохранить в новый файл", QDir::currentPath(), "Text files (*.txt)");
     if(nm == "")
         return;
     if(writeFile(nm)) {
         name_file = nm;
         this->setWindowTitle(nm);
     }
     else
         QMessageBox::critical(this, "Ошибка", "Ошибка записи в файл...");
}

void MainWindow::open()
{
    QString nm = QFileDialog::getOpenFileName(this, "Открыть текстовый файл", QDir::currentPath(), "Text files (*.txt)");
    if(nm == "")
        return;
    QString str;
    if(readFile(nm, str)) {
        name_file = nm;
        this->setWindowTitle(nm);
        ui->textEdit->setText(str);
    }
    else
        QMessageBox::critical(this, "Ошибка", "Ошибка чтения файла...");

}

void MainWindow::help()
{
    QString nm = ":/src/help.txt";
    QString str;
    if(readFile(nm, str))
        QMessageBox::about(this, "Справка", str);
    else
        QMessageBox::critical(this, "Ошибка", "Ошибка чтения ресурса...");
}

