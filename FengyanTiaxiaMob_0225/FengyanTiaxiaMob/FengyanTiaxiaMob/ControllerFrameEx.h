#pragma once

#include <QMainWindow>
#include "ui_ControllerFrameEx.h"
#include <QtCore/QDebug>
#include <QtWidgets/QFileDialog>
#include <QtCore/QProcess>
#include <QtCore/QSettings>
#include "CommonUtil.h"
#include "TheData.h"
#include "TianxiaSingleton.h"
#include "TianxiaScript.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QHash>
#include "OpenWindowThread.h"
#include "IDGenerator.h"
#include "EnginedWindowThread.h"
#include "TimeCheckThread.h"

class ControllerFrameEx : public QMainWindow
{
	Q_OBJECT

public:
	ControllerFrameEx(QWidget *parent = Q_NULLPTR);
	~ControllerFrameEx();

	

private:
	Ui::ControllerFrameEx ui;

	//int windowCount;
	long engineHWND;
	Ifire *clicker;

	void setUpTableView();
	void ControllerFrameEx::generalConfiguration(QString file);
	void ControllerFrameEx::generalLoadConfig(QString file);
	void ControllerFrameEx::loadBaseConfig();
	void ControllerFrameEx::createGameThread();
	void ControllerFrameEx::getWindowInfo(long HWND);

	QString ControllerFrameEx::loadScriptConfig();
	//BOOL ControllerFrameEx::KillProcess(DWORD ProcessId);
	
	
	void ControllerFrameEx::createGameThreadSingle(int row);
	void ControllerFrameEx::getMachineCode();
	void ControllerFrameEx::openTheEngine();
	void ControllerFrameEx::initEngineClicker();

public slots:
	void onCellClicked(int a, int b);
	void onRightClicked(QPoint point);

	void pathBtnClicked();
	void startBtnClicked();

	void readBtn1Clicked();
	void readBtn2Clicked();
	void readBtn3Clicked();
	void readBtn4Clicked();
	void readBtn5Clicked();
	void readBtn6Clicked();

	void writeBtn1Clicked();
	void writeBtn2Clicked();
	void writeBtn3Clicked();
	void writeBtn4Clicked();
	void writeBtn5Clicked();
	void writeBtn6Clicked();

	void baseConfigBtnClicked();
	

	void guaitiBtnClicked();
	void xiangshiBtnClicked();
	void mitanBtnClicked();
	void shimenBtnClicked();
	void wuxingBtnClicked();
	void chumoBtnClicked();
	void zhufuBtnClicked();
	void shiliBtnClicked();
	void wuwaBtnClicked();
	void kuaimaBtnClicked();
	void mijingBtnBtnClicked();
	void tianlaoBtnClicked();
	void biwuBtnClicked();
	void xiaoyaoBtnClicked();
	void yanwuBtnClicked();
	void tianweiBtnClicked();
	void jingjiBtnClicked();
	void huoyaoBtnClicked();
	void huoHQBtnClicked();
	void huoyueLingjiangBtnClicked();

	void xiuliBtnClicked();
	void shengjiJinengBtnClicked();
	void renwuJiadianBtnClicked();
	void lingYoujianBtnClicked();
	void shengjiZuojiBtnClicked();
	void tongjiBtnClicked();
	void lingquFuliBtnClicked();

	void scriptUpBtnClicked();
	void scriptDownBtnClicked();
	void scriptDeleteBtnBtnClicked();
	void scriptClearBtnClicked();

	void scriptUpBtn2Clicked();
	void scriptDownBtn2Clicked();
	void scriptDeleteBtn2Clicked();
	void scriptClearBtn2Clicked();

	void jinhuanJunBtnClicked();
	void cuncangBtnClicked();

	void onTableCellClicked(int a, int b);

	void qingbaoBtnClicked();

	void test();

	void saohuoBtnClicked();
	void terminateWnd();
	void newSingleWnd();
	void allPause();
	void singlePause();
	void singleRestart();

	void goldCalculateClicked();
	void chongwuSmBtnClicked();

	void shangjiaBtnClicked();
	void xiajiaBtnClicked();

	void singleStop();
	void singleStart();
	void allStop();
	void allStart();

	void huoliCanglangBtnClicked();
	void huoliHudieBtnClicked();
	void huoWeiBtnClicked();

	void juediBtnClicked();
	void wanshengBtnClicked();
	void guaguaBtnClicked();
	void yunshiBtnClicked();

	void engineBtnClicked();
	void shengdanBtnClicked();
	void zuduiBtnClicked();
	void jiaoyouBtnClicked();
	void joinForceBtnClicked();
	void jiaoxueqiuBtnClicked();
	void embededScriptBtn();
	void alineBtnClicked();
	void standarlizeWnd();
	void teamMitanbtnClicked();
	void teamPatabtnClicked();
	void kaibaoBtnClicked();
	void huoliJingjiiBtnClicked();
	void huoliWuxingBtnClicked();
};
