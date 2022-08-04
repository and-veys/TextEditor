#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    bool readFile(QString & nm, QString & res);
    bool writeFile(QString & nm);

private slots:
    void save();
    void saveAs();
    void open();
    void help();
};
#endif // MAINWINDOW_H
