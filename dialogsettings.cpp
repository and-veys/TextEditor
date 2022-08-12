#include "dialogsettings.h"
#include "ui_dialogsettings.h"
#include <QList>

DialogSettings::DialogSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogSettings)
{
    ui->setupUi(this);
    connect(ui->pushButtonCancel, &QPushButton::clicked, this, &DialogSettings::cancel);
    connect(ui->pushButtonOk, &QPushButton::clicked, this, &DialogSettings::OK);

    languages.append(new RadioProperty(ui->langRus, "rus"));
    languages.append(new RadioProperty(ui->langEng, "eng"));

    hot_keys[Qt::Key_F2] = new RadioProperty(ui->radioButtonF2, "save");
    hot_keys[Qt::Key_S | Qt::ControlModifier] = new RadioProperty(ui->radioButtonCTRLS, "save");

    hot_keys[Qt::Key_F3] = new RadioProperty(ui->radioButtonF3, "open");
    hot_keys[Qt::Key_O | Qt::ControlModifier] = new RadioProperty(ui->radioButtonCTRLO, "open");

    hot_keys[Qt::Key_F12] = new RadioProperty(ui->radioButtonF12, "new");
    hot_keys[Qt::Key_N | Qt::ControlModifier] = new RadioProperty(ui->radioButtonCTRLN, "new");

    hot_keys[Qt::Key_F1] = new RadioProperty(ui->radioButtonF1, "help");
    hot_keys[Qt::Key_H | Qt::ControlModifier] = new RadioProperty(ui->radioButtonCTRLH, "help");

    hot_keys[Qt::Key_F4] = new RadioProperty(ui->radioButtonF4, "saveAs");
    hot_keys[Qt::Key_W | Qt::ControlModifier] = new RadioProperty(ui->radioButtonCTRLW, "saveAs");

    hot_keys[Qt::Key_F5] = new RadioProperty(ui->radioButtonF5, "openRO");
    hot_keys[Qt::Key_R | Qt::ControlModifier] = new RadioProperty(ui->radioButtonCTRLR, "openRO");

    hot_keys[Qt::Key_F6] = new RadioProperty(ui->radioButtonF6, "settings");
    hot_keys[Qt::Key_P | Qt::ControlModifier] = new RadioProperty(ui->radioButtonCTRLP, "settings");

    hot_keys[Qt::Key_F11] = new RadioProperty(ui->radioButtonF11, "close");
    hot_keys[Qt::Key_C | Qt::ControlModifier] = new RadioProperty(ui->radioButtonCTRLC, "close");
}

DialogSettings::~DialogSettings()
{
    for(auto el=languages.begin(); el != languages.end(); ++el)
        delete(*el);
    for(auto el=hot_keys.begin(); el != hot_keys.end(); ++el)
        delete(*el);
    delete ui;
}

void DialogSettings::retranslateUi()
{
    ui->retranslateUi(this);
}

QString DialogSettings::getLanguage()
{
    for(auto el=languages.begin(); el != languages.end(); ++el) {
        if((*el)->isChecked())
            return (*el)->getAction();
    }
    return "";
}

QString DialogSettings::getAction(int key)
{
    auto el = hot_keys.find(key);
    if(el != hot_keys.end() && (*el)->isChecked())
        return (*el)->getAction();
    return "";
}

void DialogSettings::cancel()
{
    for(auto el=languages.begin(); el != languages.end(); ++el)
        (*el)->getCheck();
    for(auto el=hot_keys.begin(); el != hot_keys.end(); ++el)
        (*el)->getCheck();
    reject();

}

void DialogSettings::OK()
{
    for(auto el=languages.begin(); el != languages.end(); ++el)
        (*el)->setCheck();
    for(auto el=hot_keys.begin(); el != hot_keys.end(); ++el)
        (*el)->setCheck();
    accept();
}

RadioProperty::RadioProperty(QRadioButton *rd, const QString &act): action(act), radio(rd)
{
    setCheck();
}



RadioProperty::~RadioProperty()
{

}

bool RadioProperty::isChecked()
{
    return checked;
}

void RadioProperty::setCheck()
{
    checked = radio->isChecked();

}

void RadioProperty::getCheck()
{
    radio->setChecked(checked);

}

QString RadioProperty::getAction()
{
    return action;
}
