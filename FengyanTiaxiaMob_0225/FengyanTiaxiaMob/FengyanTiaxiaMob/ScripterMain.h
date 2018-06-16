#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ScripterMain.h"
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QScrollBar>
#include <QtCore/QDebug>
#include <QTextCodec>
#include <QMessageBox>

#include "baibao\QFLicense.h"

class ScripterMain : public QMainWindow
{
	Q_OBJECT

public:
	ScripterMain(QWidget *parent = Q_NULLPTR);

private:
	Ui::ScripterMainClass ui;
	int ScripterMain::tokenVerify();
	int ScripterMain::regCodeVerify();

public slots:

	void enterBtnClicked();
	void unBindBtnClicked();
	void chongzhiBtnClicked();
};
