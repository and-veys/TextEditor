#include "mainwindow.h"
#include "dialoghelp.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QKeyEvent>
#include <QDebug>

//MessageBox - одноязычные ((. Можно потом переделать.

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    name_file = "";
    ui->setupUi(this);

    connect(ui->buttonSave, &QPushButton::clicked, this, &MainWindow::save);
    connect(ui->buttonSaveAs, &QPushButton::clicked, this, &MainWindow::saveAs);
    connect(ui->buttonOpen, &QPushButton::clicked, this, &MainWindow::open);
    connect(ui->buttonHelp, &QPushButton::clicked, this, &MainWindow::help);
    connect(ui->buttonOpenRO, &QPushButton::clicked, this, &MainWindow::openReadOnly);
    connect(ui->buttonClose, &QPushButton::clicked, this, &MainWindow::closeWindow);
    connect(ui->buttonNew, &QPushButton::clicked, this, &MainWindow::newDocument);
    connect(ui->buttonSettings, &QPushButton::clicked, this, &MainWindow::settings);

    dlg_settings = new DialogSettings(this);
    changeLanguage(dlg_settings->getLanguage());

    action["open"] = ui->buttonOpen;
    action["new"] = ui->buttonNew;
    action["save"] = ui->buttonSave;
    action["openRO"] = ui->buttonOpenRO;
    action["help"] = ui->buttonHelp;
    action["close"] = ui->buttonClose;
    action["saveAs"] = ui->buttonSaveAs;
    action["settings"] = ui->buttonSettings;

}

MainWindow::~MainWindow()
{
    delete ui;
    delete(dlg_settings);
}



bool MainWindow::readFile(const QString & nm, QString & res)
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

bool MainWindow::writeFile(const QString &nm)
{
    QFile file(nm);
    if(file.open(QIODevice::WriteOnly)) {
        file.write(ui->textEdit->toPlainText().toUtf8());
        file.close();
        return true;
    }
    return false;

}

void MainWindow::changeLanguage(const QString &nm)
{
    translator.load(":/src/lang_" + nm);
    qApp->installTranslator(&translator);
    ui->retranslateUi(this);
    dlg_settings->retranslateUi();
}

bool MainWindow::isSave()
{
    int res = QMessageBox::question(this, "Сохранить файл?", "Сохранить в файл текущий текст?", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
    if(res == QMessageBox::Cancel)
        return false;
    if(res == QMessageBox::Yes)
        save();
    return true;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    QString act = dlg_settings->getAction(event->modifiers() | event->key());
    auto obj = action.find(act);
    if(obj != action.end()) {
        qApp->postEvent(*obj, new QMouseEvent(QEvent::MouseButtonPress, QPoint(1, 1), Qt::LeftButton, Qt::LeftButton, Qt::NoModifier));
        qApp->postEvent(*obj, new QMouseEvent(QEvent::MouseButtonRelease, QPoint(1, 1), Qt::LeftButton, Qt::NoButton, Qt::NoModifier));
    }
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
    openFile(false);
}

void MainWindow::openFile(bool ro)
{
    if(! isSave()) return;
    QString nm = QFileDialog::getOpenFileName(this, "Открыть текстовый файл", QDir::currentPath(), "Text files (*.txt)");
    if(nm == "")
        return;
    QString str;
    if(readFile(nm, str)) {
        name_file = nm;
        this->setWindowTitle(nm.split("/").last());
        ui->textEdit->setText(str);
        ui->textEdit->setReadOnly(ro);
    }
    else
        QMessageBox::critical(this, "Ошибка", "Ошибка чтения файла...");

}

void MainWindow::openReadOnly()
{
    openFile(true);
}

void MainWindow::help()
{
    QString nm = ":/src/help_" + dlg_settings->getLanguage()+ ".txt";
    QString str;
    if(readFile(nm, str)) {
        DialogHelp dlg(this);
        dlg.setHelp(str);
        dlg.exec();
    }
    else
        QMessageBox::critical(this, "Ошибка", "Ошибка чтения ресурса...");
}

void MainWindow::closeWindow()
{
    close();
}

void MainWindow::newDocument()
{
    if(! isSave()) return;
    this->setWindowTitle(tr("Text Editor"));
    ui->textEdit->setText("");
    ui->textEdit->setReadOnly(false);
}

void MainWindow::settings()
{
    if(dlg_settings->exec() == QDialog::Accepted)
        changeLanguage(dlg_settings->getLanguage());

}


