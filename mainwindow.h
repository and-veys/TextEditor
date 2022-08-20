#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dialogsettings.h"

#include <QFileSystemModel>
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
    QFileSystemModel model_file_system;

    QString name_file;
    QTranslator translator;
    DialogSettings * dlg_settings;
    //QMap<QString, QObject *> action;
    QMap<QString, std::function<void()>> action;

private:
    bool readFile(const QString & nm, QString & res);
    bool writeFile(const QString & nm);
    void changeLanguage(const QString & nm);
    void changeView(const QString & nm);
    bool isSave();
    void openFile(bool ro, QString nm="");
    void keyPressEvent(QKeyEvent *event) override;
    void setCaption();


private slots:
    void onClickTree();
    void save();
    void saveAs();
    void open();
    void openReadOnly();
    void help();
    void closeWindow();
    void newDocument();
    void settings();

};
#endif // MAINWINDOW_H
