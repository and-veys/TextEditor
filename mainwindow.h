#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dialogsettings.h"

#include <QMainWindow>
#include <QTranslator>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QString name_file;
    QTranslator translator;
    DialogSettings * dlg_settings;
    QMap<QString, QObject *> action;

private:
    bool readFile(const QString & nm, QString & res);
    bool writeFile(const QString & nm);
    void changeLanguage(const QString & nm);
    bool isSave();
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void save();
    void saveAs();
    void open();
    void openFile(bool ro);
    void openReadOnly();
    void help();
    void closeWindow();
    void newDocument();
    void settings();

};
#endif // MAINWINDOW_H
