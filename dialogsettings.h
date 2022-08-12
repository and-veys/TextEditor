#ifndef DIALOGSETTINGS_H
#define DIALOGSETTINGS_H

#include <QDialog>
#include <QMap>
#include <QRadioButton>


class RadioProperty {
public:
    RadioProperty(QRadioButton * rd, const QString & act = "");
    ~RadioProperty();
    bool isChecked();
    void setCheck();
    void getCheck();
    QString getAction();
private:
    QString action;
    bool checked;
    QRadioButton * radio;

};


namespace Ui {
class DialogSettings;
}

class DialogSettings : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSettings(QWidget *parent = nullptr);
    ~DialogSettings();
    void retranslateUi();
    QString getLanguage();
    QString getAction(int key);

private:
    Ui::DialogSettings *ui;
    QList<RadioProperty *> languages;
    QMap<int, RadioProperty *> hot_keys;

public slots:
    void cancel();
    void OK();

};

#endif // DIALOGSETTINGS_H
