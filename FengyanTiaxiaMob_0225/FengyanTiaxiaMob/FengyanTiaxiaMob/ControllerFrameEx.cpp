#include "ControllerFrameEx.h"
#include<stdio.h>
#include<windows.h>
#include <atlbase.h>


ControllerFrameEx::ControllerFrameEx(QWidget *parent)
	: QMainWindow(parent)
{
	TianxiaSingleton* tianxia = TianxiaSingleton::getInstance();
	ui.setupUi(this);
	this->setUpTableView();
	this->getMachineCode();
	tianxia->windowCount = 0;
	this->setWindowTitle(CommonUtil::getRandomPhoneNumebr().c_str());
	this->engineHWND = 0;

	//this->openTheEngine();

	TianxiaSingleton* tx = TianxiaSingleton::getInstance();
	tx->table = ui.tableWidget;

	TimeCheckThread* thread = new TimeCheckThread(ui.timeLabel);
	thread->start();
	

	QButtonGroup* zoneGroup = new QButtonGroup(this);
	zoneGroup->addButton(ui.zoneRadio1);
	zoneGroup->addButton(ui.zoneRadio2);

	ui.saoComboBox->addItem(QWidget::tr("------"));
	ui.saoComboBox->addItem(QWidget::tr("JDFD"));
	ui.saoComboBox->addItem(QWidget::tr("MYZL"));
	ui.saoComboBox->addItem(QWidget::tr("7C"));
	ui.saoComboBox->addItem(QWidget::tr("JN"));
	ui.saoComboBox->addItem(QWidget::tr("CYHY"));

	ui.charaComboBox->addItem(QWidget::tr("RANDOM"));
	ui.charaComboBox->addItem(QWidget::tr("BX"));
	ui.charaComboBox->addItem(QWidget::tr("TJ"));
	ui.charaComboBox->addItem(QWidget::tr("YJ"));
	ui.charaComboBox->addItem(QWidget::tr("YL"));
	ui.charaComboBox->addItem(QWidget::tr("TX"));
	ui.charaComboBox->addItem(QWidget::tr("WL"));
	ui.charaComboBox->addItem(QWidget::tr("TEAMED"));

	loadBaseConfig();
	
	ui.autoCRole->setChecked(true);
	ui.autoCRole->setDisabled(true);

	QObject::connect(ui.onePunch, SIGNAL(clicked()), this, SLOT(startBtnClicked()));

	QObject::connect(ui.engineBtn, SIGNAL(clicked()), this, SLOT(engineBtnClicked()));

	QObject::connect(ui.readBtn1, SIGNAL(clicked()), this, SLOT(readBtn1Clicked()));
	QObject::connect(ui.readBtn2, SIGNAL(clicked()), this, SLOT(readBtn2Clicked()));
	QObject::connect(ui.readBtn3, SIGNAL(clicked()), this, SLOT(readBtn3Clicked()));
	QObject::connect(ui.readBtn4, SIGNAL(clicked()), this, SLOT(readBtn4Clicked()));
	QObject::connect(ui.readBtn5, SIGNAL(clicked()), this, SLOT(readBtn5Clicked()));
	QObject::connect(ui.readBtn6, SIGNAL(clicked()), this, SLOT(readBtn6Clicked()));
	
	QObject::connect(ui.writeBtn1, SIGNAL(clicked()), this, SLOT(writeBtn1Clicked()));
	QObject::connect(ui.writeBtn2, SIGNAL(clicked()), this, SLOT(writeBtn2Clicked()));
	QObject::connect(ui.writeBtn3, SIGNAL(clicked()), this, SLOT(writeBtn3Clicked()));
	QObject::connect(ui.writeBtn4, SIGNAL(clicked()), this, SLOT(writeBtn4Clicked()));
	QObject::connect(ui.writeBtn5, SIGNAL(clicked()), this, SLOT(writeBtn5Clicked()));
	QObject::connect(ui.writeBtn6, SIGNAL(clicked()), this, SLOT(writeBtn6Clicked()));
	
	QObject::connect(ui.goldCalculate, SIGNAL(clicked()), this, SLOT(goldCalculateClicked()));

	QObject::connect(ui.baseConfigBtn, SIGNAL(clicked()), this, SLOT(baseConfigBtnClicked()));


	QObject::connect(ui.guaitiBtn, SIGNAL(clicked()), this, SLOT(guaitiBtnClicked()));
	QObject::connect(ui.xiangshiBtn, SIGNAL(clicked()), this, SLOT(xiangshiBtnClicked()));
	QObject::connect(ui.mitanBtn, SIGNAL(clicked()), this, SLOT(mitanBtnClicked()));
	QObject::connect(ui.shimenBtn, SIGNAL(clicked()), this, SLOT(shimenBtnClicked()));
	QObject::connect(ui.wuxingBtn, SIGNAL(clicked()), this, SLOT(wuxingBtnClicked()));
	QObject::connect(ui.chumoBtn, SIGNAL(clicked()), this, SLOT(chumoBtnClicked()));
	QObject::connect(ui.zhufuBtn, SIGNAL(clicked()), this, SLOT(zhufuBtnClicked()));
	QObject::connect(ui.shiliBtn, SIGNAL(clicked()), this, SLOT(shiliBtnClicked()));
	QObject::connect(ui.wuwaBtn, SIGNAL(clicked()), this, SLOT(wuwaBtnClicked()));
	QObject::connect(ui.kuaimaBtn, SIGNAL(clicked()), this, SLOT(kuaimaBtnClicked()));
	QObject::connect(ui.mijingBtn, SIGNAL(clicked()), this, SLOT(mijingBtnBtnClicked()));
	QObject::connect(ui.tianlaoBtn, SIGNAL(clicked()), this, SLOT(tianlaoBtnClicked()));
	QObject::connect(ui.biwuBtn, SIGNAL(clicked()), this, SLOT(biwuBtnClicked()));
	QObject::connect(ui.xiaoyaoBtn, SIGNAL(clicked()), this, SLOT(xiaoyaoBtnClicked()));
	QObject::connect(ui.yanwuBtn, SIGNAL(clicked()), this, SLOT(yanwuBtnClicked()));
	QObject::connect(ui.tianweiBtn, SIGNAL(clicked()), this, SLOT(tianweiBtnClicked()));
	QObject::connect(ui.jingjiBtn, SIGNAL(clicked()), this, SLOT(jingjiBtnClicked()));
	QObject::connect(ui.huoliXiangyaoBtn, SIGNAL(clicked()), this, SLOT(huoyaoBtnClicked()));
	QObject::connect(ui.huoliHuangquanBtn, SIGNAL(clicked()), this, SLOT(huoHQBtnClicked()));
	QObject::connect(ui.huoliWeijiBtn, SIGNAL(clicked()), this, SLOT(huoWeiBtnClicked()));

	QObject::connect(ui.jiaoxueqiuBtn, SIGNAL(clicked()), this, SLOT(jiaoxueqiuBtnClicked()));

	QObject::connect(ui.huoyueLingJiangBtn, SIGNAL(clicked()), this, SLOT(huoyueLingjiangBtnClicked()));
	QObject::connect(ui.sahuoBtn, SIGNAL(clicked()), this, SLOT(saohuoBtnClicked()));
	QObject::connect(ui.cuncangBtn, SIGNAL(clicked()), this, SLOT(cuncangBtnClicked()));
	QObject::connect(ui.chongwuShoumingBtn, SIGNAL(clicked()), this, SLOT(chongwuSmBtnClicked()));

	QObject::connect(ui.shangjiaBtn, SIGNAL(clicked()), this, SLOT(shangjiaBtnClicked()));
	QObject::connect(ui.xiajiaBtn, SIGNAL(clicked()), this, SLOT(xiajiaBtnClicked()));


	QObject::connect(ui.qingbaoBtn, SIGNAL(clicked()), this, SLOT(qingbaoBtnClicked()));
	QObject::connect(ui.xiuliBtn, SIGNAL(clicked()), this, SLOT(xiuliBtnClicked()));
	QObject::connect(ui.shengjiBtn, SIGNAL(clicked()), this, SLOT(shengjiJinengBtnClicked()));
	QObject::connect(ui.jiadianBtn, SIGNAL(clicked()), this, SLOT(renwuJiadianBtnClicked()));
	QObject::connect(ui.lingyouBtn, SIGNAL(clicked()), this, SLOT(lingYoujianBtnClicked()));
	QObject::connect(ui.shengmaBtn, SIGNAL(clicked()), this, SLOT(shengjiZuojiBtnClicked()));
	QObject::connect(ui.tongjiCailiaoBtn, SIGNAL(clicked()), this, SLOT(huoyueLingjiangBtnClicked()));
	QObject::connect(ui.lingFuliBtn, SIGNAL(clicked()), this, SLOT(lingquFuliBtnClicked()));
	QObject::connect(ui.jinHJunBtn, SIGNAL(clicked()), this, SLOT(jinhuanJunBtnClicked()));
	QObject::connect(ui.wanshengBtn, SIGNAL(clicked()), this, SLOT(wanshengBtnClicked()));
	QObject::connect(ui.guaguaBtn, SIGNAL(clicked()), this, SLOT(guaguaBtnClicked()));
	QObject::connect(ui.juediBtn, SIGNAL(clicked()), this, SLOT(juediBtnClicked()));
	QObject::connect(ui.yunshiBtn, SIGNAL(clicked()), this, SLOT(yunshiBtnClicked()));
	QObject::connect(ui.joinForceBtn, SIGNAL(clicked()), this, SLOT(joinForceBtnClicked()));
	QObject::connect(ui.kaibaoBtn, SIGNAL(clicked()), this, SLOT(kaibaoBtnClicked()));
	QObject::connect(ui.huoliJingjiiBtn, SIGNAL(clicked()), this, SLOT(huoliJingjiiBtnClicked()));
	QObject::connect(ui.huoliWuxingBtn, SIGNAL(clicked()), this, SLOT(huoliWuxingBtnClicked()));

	QObject::connect(ui.embededScriptBtn, SIGNAL(clicked()), this, SLOT(embededScriptBtn()));

	QObject::connect(ui.huoliCanglangBtn, SIGNAL(clicked()), this, SLOT(huoliCanglangBtnClicked()));
	QObject::connect(ui.huoliHudieBtn, SIGNAL(clicked()), this, SLOT(huoliHudieBtnClicked()));

	QObject::connect(ui.scriptUp, SIGNAL(clicked()), this, SLOT(scriptUpBtnClicked()));
	QObject::connect(ui.scriptDown, SIGNAL(clicked()), this, SLOT(scriptDownBtnClicked()));
	QObject::connect(ui.scriptDelete, SIGNAL(clicked()), this, SLOT(scriptDeleteBtnBtnClicked()));
	QObject::connect(ui.scriptClear, SIGNAL(clicked()), this, SLOT(scriptClearBtnClicked()));

	QObject::connect(ui.scriptUp_2, SIGNAL(clicked()), this, SLOT(scriptUpBtn2Clicked()));
	QObject::connect(ui.scriptDown_2, SIGNAL(clicked()), this, SLOT(scriptDownBtn2Clicked()));
	QObject::connect(ui.scriptDelete_2, SIGNAL(clicked()), this, SLOT(scriptDeleteBtn2Clicked()));
	QObject::connect(ui.scriptClear_2, SIGNAL(clicked()), this, SLOT(scriptClearBtn2Clicked()));
	
	
	QObject::connect(ui.shengdanBtn, SIGNAL(clicked()), this, SLOT(shengdanBtnClicked()));

	QObject::connect(ui.zuduiBtn, SIGNAL(clicked()), this, SLOT(zuduiBtnClicked()));
	QObject::connect(ui.jiaoyouBtn, SIGNAL(clicked()), this, SLOT(jiaoyouBtnClicked()));
	QObject::connect(ui.alineBtn, SIGNAL(clicked()), this, SLOT(alineBtnClicked()));
	QObject::connect(ui.teamMitanbtn, SIGNAL(clicked()), this, SLOT(teamMitanbtnClicked()));
	QObject::connect(ui.teamPatabtn, SIGNAL(clicked()), this, SLOT(teamPatabtnClicked()));

	QObject::connect(ui.tableWidget, SIGNAL(cellClicked(int,int)), this, SLOT(onTableCellClicked(int,int)));



}

ControllerFrameEx::~ControllerFrameEx()
{
}

void ControllerFrameEx::getMachineCode() {
	Ifire* DM = DMSoft::getInstance()->newDMObject();
	qDebug() << DM->PskVer();


	int result = 0;

	DM->PskSetShowErrorMsg(0);

	string code = DM->GetMachineCode();
	
	ui.test->setText(QString::fromStdString(code));

	DM->Release();
}

/* a row, b column*/
void ControllerFrameEx::onTableCellClicked(int a, int b) {
	qDebug() << "onTableCellClicked";
	qDebug() << QString::number(a);
	qDebug() << QString::number(b);

	QTableWidgetItem* item = ui.tableWidget->item(a, 1);
	if (item == NULL) {
		return;
	}

	QString tHWND = item->text();
	qDebug() << tHWND;
	
	long lHWND = tHWND.toLong();

	SetWindowPos((HWND)lHWND, HWND_NOTOPMOST, -1, -1, -1, -1, SWP_NOSIZE | SWP_NOMOVE);
}

void ControllerFrameEx::scriptUpBtnClicked() {
	qDebug() << "scriptUpBtnClicked";

	QListWidgetItem* item = ui.scriptSortList->currentItem();
	if (item == NULL) {
		return;
	}
	qDebug() << item->text();

	QListWidgetItem* upperItem = ui.scriptSortList->item(ui.scriptSortList->currentRow() - 1);
	if (upperItem == NULL) {
		return;
	}
	qDebug() << upperItem->text();
	QString tempText = item->text();
	item->setText(upperItem->text());
	upperItem->setText(tempText);

	ui.scriptSortList->setCurrentRow(ui.scriptSortList->currentRow() - 1);
}

void ControllerFrameEx::scriptDownBtnClicked() {
	qDebug() << "scriptDownBtnClicked";
	QListWidgetItem* item = ui.scriptSortList->currentItem();
	if (item == NULL) {
		return;
	}
	qDebug() << item->text();

	QListWidgetItem* lowerItem  = ui.scriptSortList->item(ui.scriptSortList->currentRow() + 1);
	if (lowerItem == NULL) {
		return;
	}
	qDebug() << lowerItem->text();
	QString tempText = item->text();
	item->setText(lowerItem->text());
	lowerItem->setText(tempText);

	ui.scriptSortList->setCurrentRow(ui.scriptSortList->currentRow() + 1);
}

void ControllerFrameEx::scriptDeleteBtnBtnClicked() {
	qDebug() << "scriptDeleteBtnBtnClicked";
	/*QListWidgetItem* item = ui.scriptSortList->currentItem();
	ui.scriptSortList->removeItemWidget(item);
*/
	int row = ui.scriptSortList->currentRow();
	ui.scriptSortList->takeItem(row);
}

void ControllerFrameEx::scriptClearBtnClicked() {
	qDebug() << "scriptClearBtnClicked";
	int row = ui.scriptSortList->count();

	while (row != 0) {
		ui.scriptSortList->takeItem(row - 1);
		//row = ui.scriptSortList->currentRow();
		row = ui.scriptSortList->count();
	}
}

void ControllerFrameEx::scriptUpBtn2Clicked() {
	qDebug() << "scriptUpBtn2Clicked";

	QListWidgetItem* item = ui.subScriptSortList->currentItem();
	if (item == NULL) {
		return;
	}
	qDebug() << item->text();

	QListWidgetItem* upperItem = ui.subScriptSortList->item(ui.subScriptSortList->currentRow() - 1);
	if (upperItem == NULL) {
		return;
	}
	qDebug() << upperItem->text();
	QString tempText = item->text();
	item->setText(upperItem->text());
	upperItem->setText(tempText);

	ui.subScriptSortList->setCurrentRow(ui.subScriptSortList->currentRow() - 1);
}

void ControllerFrameEx::scriptDownBtn2Clicked() {
	qDebug() << "scriptDownBtn2Clicked";
	QListWidgetItem* item = ui.subScriptSortList->currentItem();
	if (item == NULL) {
		return;
	}
	qDebug() << item->text();

	QListWidgetItem* lowerItem = ui.subScriptSortList->item(ui.subScriptSortList->currentRow() + 1);
	if (lowerItem == NULL) {
		return;
	}
	qDebug() << lowerItem->text();
	QString tempText = item->text();
	item->setText(lowerItem->text());
	lowerItem->setText(tempText);

	ui.subScriptSortList->setCurrentRow(ui.subScriptSortList->currentRow() + 1);
}

void ControllerFrameEx::scriptDeleteBtn2Clicked() {
	qDebug() << "scriptDeleteBtn2Clicked";
	/*QListWidgetItem* item = ui.scriptSortList->currentItem();
	ui.scriptSortList->removeItemWidget(item);
	*/
	int row = ui.subScriptSortList->currentRow();
	ui.subScriptSortList->takeItem(row);
}

void ControllerFrameEx::scriptClearBtn2Clicked() {
	qDebug() << "scriptClearBtn2Clicked";
	int row = ui.subScriptSortList->count();

	while (row != 0) {
		ui.subScriptSortList->takeItem(row - 1);
		//row = ui.scriptSortList->currentRow();
		row = ui.subScriptSortList->count();
	}
}

void ControllerFrameEx::zuduiBtnClicked() {
	qDebug() << "zuduiBtnClicked";
	ui.subScriptSortList->addItem(QString::fromLocal8Bit("TEAM"));
	ui.subScriptSortList->setCurrentRow(ui.subScriptSortList->count() - 1);
}
//jiaoyouBtnClicked
void ControllerFrameEx::jiaoyouBtnClicked() {
	qDebug() << "jiaoyouBtnClicked";
	ui.subScriptSortList->addItem(QString::fromLocal8Bit("JYOU"));
	ui.subScriptSortList->setCurrentRow(ui.subScriptSortList->count() - 1);
}
//alineBtn
void ControllerFrameEx::alineBtnClicked() {
	qDebug() << "alineBtnClicked";
	ui.subScriptSortList->addItem(QString::fromLocal8Bit("DUIQ"));
	ui.subScriptSortList->setCurrentRow(ui.subScriptSortList->count() - 1);
}

void ControllerFrameEx::teamMitanbtnClicked() {
	qDebug() << "teamMitanbtnClicked";
	ui.subScriptSortList->addItem(QString::fromLocal8Bit("TMMT"));
	ui.subScriptSortList->setCurrentRow(ui.subScriptSortList->count() - 1);
}

void ControllerFrameEx::teamPatabtnClicked() {
	qDebug() << "teamPatabtnClicked";
	ui.subScriptSortList->addItem(QString::fromLocal8Bit("TMPT"));
	ui.subScriptSortList->setCurrentRow(ui.subScriptSortList->count() - 1);
}

void ControllerFrameEx::shengdanBtnClicked() {
	qDebug() << "shengdanBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("XUEQ"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}

void ControllerFrameEx::guaitiBtnClicked() {
	qDebug() << "guaitiBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("DHGT"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}

void ControllerFrameEx::xiangshiBtnClicked() {
	qDebug() << "xiangshiBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("MXXS"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}

void ControllerFrameEx::mitanBtnClicked() {
	qDebug() << "mitanBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("WCMT"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}

void ControllerFrameEx::shimenBtnClicked() {
	qDebug() << "shimenBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("SMRW"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}

void ControllerFrameEx::wuxingBtnClicked() {
	qDebug() << "wuxingBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("WXP"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}

void ControllerFrameEx::chumoBtnClicked() {
	qDebug() << "chumoBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("CMFB"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}

void ControllerFrameEx::zhufuBtnClicked() {
	qDebug() << "zhufuBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("ZF"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}

void ControllerFrameEx::shiliBtnClicked() {
	qDebug() << "shiliBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("SLRW"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}

void ControllerFrameEx::wuwaBtnClicked() {
	qDebug() << "wuwaBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("WWXP"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}

void ControllerFrameEx::kuaimaBtnClicked() {
	qDebug() << "kuaimaBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("KMJB"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}

void ControllerFrameEx::mijingBtnBtnClicked() {
	qDebug() << "mijingBtnBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("MJXX"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}

void ControllerFrameEx::tianlaoBtnClicked() {
	qDebug() << "tianlaoBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("TLZY"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}

void ControllerFrameEx::biwuBtnClicked() {
	qDebug() << "biwuBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("MPBW"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}

void ControllerFrameEx::xiaoyaoBtnClicked() {
	qDebug() << "xiaoyaoBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("HLXY"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}

void ControllerFrameEx::yanwuBtnClicked() {
	qDebug() << "yanwuBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("YWT"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}

void ControllerFrameEx::tianweiBtnClicked() {
	qDebug() << "tianweiBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("TLWJ"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}

void ControllerFrameEx::jingjiBtnClicked() {
	qDebug() << "jingjiBtnCLicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("JJZD"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}

void ControllerFrameEx::huoyaoBtnClicked() {
	qDebug() << "huoyaoBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("HLCY"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}

void ControllerFrameEx::huoHQBtnClicked() {
	qDebug() << "huoHQBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("HLHQ"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}

void ControllerFrameEx::huoWeiBtnClicked() {
	qDebug() << "huoWeiBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("HLWJ"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}
//jiaoxueqiuBtnClicked
void ControllerFrameEx::jiaoxueqiuBtnClicked() {
	qDebug() << "jiaoxueqiuBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("JIXQ"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}

void ControllerFrameEx::huoyueLingjiangBtnClicked() {
	qDebug() << "huoyueLingjiangBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("HYLJ"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}

void ControllerFrameEx::saohuoBtnClicked() {
	qDebug() << "saohuoBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("SAOH"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}

void ControllerFrameEx::chongwuSmBtnClicked() {
	qDebug() << "chongwuSmBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("CWSM"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}

void ControllerFrameEx::cuncangBtnClicked() {
	qDebug() << "cuncangBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("CUNC"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}

void ControllerFrameEx::shangjiaBtnClicked() {
	qDebug() << "shangjiaBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("SHAJ"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}

void ControllerFrameEx::xiajiaBtnClicked() {
	qDebug() << "xiajiaBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("XIAJ"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}

void ControllerFrameEx::lingquFuliBtnClicked() {
	qDebug() << "lingquFuliBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("LQFL"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}

void ControllerFrameEx::huoliCanglangBtnClicked() {
	qDebug() << "huoliCanglangBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("HLCL"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}

void ControllerFrameEx::huoliHudieBtnClicked() {
	qDebug() << "huoliHudieBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("HLHD"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}

void ControllerFrameEx::jinhuanJunBtnClicked() {
	qDebug() << "jinhuanJunBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("JHJ"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}

void ControllerFrameEx::juediBtnClicked() {
	qDebug() << "juediBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("JDQS"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}

void ControllerFrameEx::yunshiBtnClicked() {
	qDebug() << "yunshiBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("YUNS"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}

void ControllerFrameEx::joinForceBtnClicked() {
	qDebug() << "joinForceBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("JOIS"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}
//kaibaoBtnClicked
void ControllerFrameEx::kaibaoBtnClicked() {
	qDebug() << "kaibaoBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("KAIB"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}
//huoliJingjiiBtnClicked
void ControllerFrameEx::huoliJingjiiBtnClicked() {
	qDebug() << "huoliJingjiiBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("HLJJ"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}
//huoliWuxingBtnClicked
void ControllerFrameEx::huoliWuxingBtnClicked() {
	qDebug() << "huoliWuxingBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("HLWX"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}

void ControllerFrameEx::embededScriptBtn() {
	qDebug() << "embededScriptBtn";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("EMBS"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}

void ControllerFrameEx::wanshengBtnClicked() {
	qDebug() << "wanshengBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("WSJ"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}

void ControllerFrameEx::guaguaBtnClicked() {
	qDebug() << "guaguaBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("GG"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}

void ControllerFrameEx::xiuliBtnClicked() {
	qDebug() << "xiuliBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("ZBXL"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}

void ControllerFrameEx::shengjiJinengBtnClicked() {
	qDebug() << "shengjiJinengBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("SJJL"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}

void ControllerFrameEx::renwuJiadianBtnClicked() {
	qDebug() << "renwuJiadianBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("RWJD"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}

void ControllerFrameEx::lingYoujianBtnClicked() {
	qDebug() << "renwuJiadianBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("LQYJ"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}

void ControllerFrameEx::shengjiZuojiBtnClicked() {
	qDebug() << "shengjiZuojiBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("SJZJ"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}

void ControllerFrameEx::tongjiBtnClicked() {
	qDebug() << "tongjiBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("TJCL"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}

void ControllerFrameEx::qingbaoBtnClicked() {
	qDebug() << "qingbaoBtnClicked";
	ui.scriptSortList->addItem(QString::fromLocal8Bit("QLBG"));
	ui.scriptSortList->setCurrentRow(ui.scriptSortList->count() - 1);
}

void ControllerFrameEx::loadBaseConfig() {
	qDebug() << "loadBaseConfig";

	generalLoadConfig("config/base.ini");
}

void ControllerFrameEx::generalLoadConfig(QString file) {
	QSettings configIniRead(file, QSettings::IniFormat);

	QString daqu = configIniRead.value("/zone_config/daqu").toString();

	qDebug() << daqu;
	if (daqu == "") {
		return;
	}

	if (daqu == "yitong") {
		ui.zoneRadio1->setChecked(true);
	}
	if (daqu == "huaxia") {
		ui.zoneRadio2->setChecked(true);
	}

	QString mengyan = configIniRead.value("/combat_config/mengyan").toString();

	qDebug() << mengyan;
	if (mengyan == "") {
		//return;
	}

	if (mengyan == "1") {
		ui.mengyanRadio1->setChecked(true);
	}
	if (mengyan == "0") {
		ui.mengyanRadio2->setChecked(true);
	}

	QString jianding = configIniRead.value("/combat_config/jianding").toString();

	qDebug() << jianding;
	if (jianding == "") {
		//return;
	}

	if (jianding == "1") {
		ui.jiandingRadio1->setChecked(true);
	}
	if (jianding == "0") {
		ui.jiandingRadio2->setChecked(true);
	}

	QString qicai = configIniRead.value("/combat_config/qicai").toString();

	qDebug() << qicai;
	if (qicai == "") {
		//return;
	}

	if (qicai == "1") {
		ui.qicaiRadio1->setChecked(true);
	}
	if (qicai == "0") {
		ui.qicaiRadio2->setChecked(true);
	}

	ui.zoneNumberSetter->setValue(configIniRead.value("/zone_config/zone_num").toInt());

	int team_param = configIniRead.value("/script_config/team_param").toInt();
	if (team_param != 0) {
		ui.teamSpinBox->setValue(team_param);
	}
	//timeLimitSpinBox
	int time_limit = configIniRead.value("/script_config/time_limit").toInt();
	if (time_limit != 0) {
		ui.timeLimitSpinBox->setValue(time_limit);
	}

	int mitan_counter = configIniRead.value("/script_config/mitan_counter").toInt();
	if (mitan_counter != 0) {
		ui.mitanCounterSpinBox->setValue(mitan_counter);
	}
	//shimenCounterSpinBox
	int shimen_counter = configIniRead.value("/script_config/shimen_counter").toInt();
	if (shimen_counter != 0) {
		ui.shimenCounterSpinBox->setValue(shimen_counter);
	}

	int zhuxian_level = configIniRead.value("/script_config/zhuxian_level").toInt();
	if (zhuxian_level != 0) {
		ui.levelSpinBox->setValue(zhuxian_level);
	}

	int chara_size = configIniRead.value("/character_config/character_size").toInt();
	if (chara_size != 0) {
		ui.charaNumberSetter->setValue(configIniRead.value("/character_config/character_size").toInt());
	}
	//settings.setValue("charaComboBox", ui.charaComboBox->currentIndex());
	int charaComboBox = configIniRead.value("/character_config/charaComboBox").toInt();
	if (chara_size != 0) {
		ui.charaComboBox->setCurrentIndex(configIniRead.value("/character_config/charaComboBox").toInt());
	}

	QString isAutoChangeRole = configIniRead.value("/character_config/isAutoChangeRole").toString();
	if (isAutoChangeRole == "0") {
		ui.autoCRole->setChecked(false);
	}
	else {
		ui.autoCRole->setChecked(true);
	}

	QString isAutoLogin = configIniRead.value("/character_config/isAutoLogin").toString();
	if (isAutoLogin == "0") {
		ui.autoLogin->setChecked(false);
	}
	else {
		ui.autoLogin->setChecked(true);
	}

	/*QString character1 = configIniRead.value("/character_config/character1").toString();
	if (character1 == "0") {
		ui.charaBox1->setChecked(false);
	}
	else {
		ui.charaBox1->setChecked(true);
	}

	QString character2 = configIniRead.value("/character_config/character2").toString();
	if (character2 == "0") {
		ui.charaBox2->setChecked(false);
	}
	else {
		ui.charaBox2->setChecked(true);
	}

	QString character3 = configIniRead.value("/character_config/character3").toString();
	if (character3 == "0") {
		ui.charaBox3->setChecked(false);
	}
	else {
		ui.charaBox3->setChecked(true);
	}

	QString character4 = configIniRead.value("/character_config/character4").toString();
	if (character4 == "0") {
		ui.charaBox4->setChecked(false);
	}
	else {
		ui.charaBox4->setChecked(true);
	}

	QString character5 = configIniRead.value("/character_config/character5").toString();
	if (character5 == "0") {
		ui.charaBox5->setChecked(false);
	}
	else {
		ui.charaBox5->setChecked(true);
	}



	QString character6 = configIniRead.value("/character_config/character6").toString();
	if (character6 == "0") {
		ui.charaBox6->setChecked(false);
	}
	else {
		ui.charaBox6->setChecked(true);
	}

	QString character7 = configIniRead.value("/character_config/character7").toString();
	if (character7 == "0") {
		ui.charaBox7->setChecked(false);
	}
	else {
		ui.charaBox7->setChecked(true);
	}

	QString character8 = configIniRead.value("/character_config/character8").toString();
	if (character8 == "0") {
		ui.charaBox8->setChecked(false);
	}
	else {
		ui.charaBox8->setChecked(true);
	}

	QString character9 = configIniRead.value("/character_config/character9").toString();
	if (character9 == "0") {
		ui.charaBox9->setChecked(false);
	}
	else {
		ui.charaBox9->setChecked(true);
	}

	QString character10 = configIniRead.value("/character_config/character10").toString();
	if (character10 == "0") {
		ui.charaBox10->setChecked(false);
	}
	else {
		ui.charaBox10->setChecked(true);
	}*/

	QString isZhuxianEnabled = configIniRead.value("/general_config/isZhuxianEnabled").toString();

	if (isZhuxianEnabled == "0") {
		ui.isZhuxianEnableBox->setChecked(false);
	}
	else {
		ui.isZhuxianEnableBox->setChecked(true);
	}

	QString huoyueCheckBox = configIniRead.value("/general_config/huoyueCheckBox").toString();

	if (huoyueCheckBox == "0") {
		ui.huoyueCheckBox->setChecked(false);
	}
	else {
		ui.huoyueCheckBox->setChecked(true);
	}

	QString generalDZCheckBox = configIniRead.value("/general_config/generalDZCheckBox").toString();
	if (generalDZCheckBox == "0") {
		ui.generalDZCheckBox->setChecked(false);
	}
	else {
		ui.generalDZCheckBox->setChecked(true);
	}

	QString EnginedBox = configIniRead.value("/general_config/EnginedBox").toString();

	if (EnginedBox == "0") {
		ui.EnginedBox->setChecked(false);
	}
	else {
		ui.EnginedBox->setChecked(true);
	}

	ui.duimoSpinBox->setValue(configIniRead.value("/general_config/team_mode").toInt());

	int huoliParameter = configIniRead.value("/general_config/huoli_param").toInt();
	if (huoliParameter != 0) {
		ui.manhuoSpinBox->setValue(configIniRead.value("/general_config/huoli_param").toInt());
	}

	QString isCaptained = configIniRead.value("/general_config/isCaptained").toString();

	if (isCaptained == "0") {
		ui.captainBox->setChecked(false);
	}
	else {
		ui.captainBox->setChecked(true);
	}

	QString isShimenJun = configIniRead.value("/general_config/isShimenJun").toString();

	if (isShimenJun == "0") {
		ui.shimenYongjunBox->setChecked(false);
	}
	else {
		ui.shimenYongjunBox->setChecked(true);
	}

	QString isHuoliProtected = configIniRead.value("/general_config/isHuoliProtected").toString();

	if (isHuoliProtected == "0") {
		ui.huoliProtectBox->setChecked(false);
	}
	else {
		ui.huoliProtectBox->setChecked(true);
	}

	ui.windowCounter->setValue(configIniRead.value("/start_config/window_count").toInt());
	ui.open_lag->setValue(configIniRead.value("/start_config/open_lag").toInt());
	ui.gamePathEditor->setText(configIniRead.value("/character_config/exePath").toString());

	int scriptCount = configIniRead.value("/script_config/count").toInt();

	scriptClearBtnClicked();
	for (int i = 0; i < scriptCount; i++) {
		QString path = "/script_config/";
		path.append(QString::number(i));

		QString temp = configIniRead.value(path).toString();
		ui.scriptSortList->addItem(temp);
	}

	int subscriptCount = configIniRead.value("/subscript_config/count").toInt();

	scriptClearBtn2Clicked();
	for (int i = 0; i < subscriptCount; i++) {
		QString path = "/subscript_config/";
		path.append(QString::number(i));

		QString temp = configIniRead.value(path).toString();
		ui.subScriptSortList->addItem(temp);
	}

	ui.junziShiyongBox->setChecked(configIniRead.value("/general_config/isYongjun").toInt());

	ui.rizuanBox->setChecked(configIniRead.value("/advanced_config/rizuanBox").toInt());
	ui.yuezuanBox->setChecked(configIniRead.value("/advanced_config/yuezuanBox").toInt());
	ui.liuyaoBox->setChecked(configIniRead.value("/advanced_config/liuyaoBox").toInt());
	/*settings.beginGroup("advanced_config");

	settings.setValue("rizuanBox", ui.rizuanBox->isChecked());
	settings.setValue("yuezuanBox", ui.yuezuanBox->isChecked());
	settings.setValue("liuyaoBox", ui.liuyaoBox->isChecked());

	settings.endGroup();*/
}

void ControllerFrameEx::baseConfigBtnClicked() {
	qDebug() << "baseConfigBtnClicked";

	generalConfiguration("config/base.ini");
}

void ControllerFrameEx::goldCalculateClicked() {
	qDebug() << "goldCalculateClicked";
	QString file = "logs/theAll.ini";
	QSettings settings(file, QSettings::IniFormat);
	settings.beginGroup("divided");

	int total = 0;

	for (int i = 0; i < 30; i++) {
		int gold = CommonUtil::calculateSingleWindow(i + 1);
		ui.tableWidget->setItem(i, 6, new QTableWidgetItem(QString::number(gold)));

		QString single = "window";
		single.append(QString::number(i + 1));

		settings.setValue(single, gold);
		total += gold;
	}

	settings.endGroup();

	settings.beginGroup("all");
	settings.setValue("total", total);
	settings.endGroup();
}

QString ControllerFrameEx::loadScriptConfig() {
	TianxiaSingleton* tx = TianxiaSingleton::getInstance();

	QJsonObject json;
	if (ui.zoneRadio1->isChecked()) {
		json.insert("daqu", "yitong");
	}
	if (ui.zoneRadio2->isChecked()) {
		json.insert("daqu", "huaxia");
	}

	if (ui.mengyanRadio1->isChecked()) {
		json.insert("mengyan", "1");
	}
	if (ui.mengyanRadio2->isChecked()) {
		json.insert("mengyan", "0");
	}

	if (ui.jiandingRadio1->isChecked()) {
		json.insert("jianding", "1");
	}
	if (ui.jiandingRadio2->isChecked()) {
		json.insert("jianding", "0");
	}

	if (ui.qicaiRadio1->isChecked()) {
		json.insert("qicai", "1");
	}
	if (ui.qicaiRadio2->isChecked()) {
		json.insert("qicai", "0");
	}

	json.insert("team_param", ui.teamSpinBox->text());
	json.insert("time_limit", ui.timeLimitSpinBox->text());
	json.insert("mitan_counter", ui.mitanCounterSpinBox->text());
	json.insert("shimen_counter", ui.shimenCounterSpinBox->text());
	json.insert("zhuxian_level", ui.levelSpinBox->text());
	//team_param
	json.insert("idField", ui.idField->text());
	json.insert("charaChoose", QString::number(ui.charaComboBox->currentIndex()));
	json.insert("sao", ui.saoComboBox->currentText());
	json.insert("goldController", ui.goldController->text());
	json.insert("safeJunzi", ui.safeJunzi->text());
	json.insert("saoPointer", ui.saoPointer->text());

	json.insert("zone_num", QString::number(ui.zoneNumberSetter->value()));
	json.insert("team_mode", QString::number(ui.duimoSpinBox->value()));
	json.insert("huoli_param", QString::number(ui.manhuoSpinBox->value()));

	json.insert("rizuanBox", QString::number(ui.rizuanBox->isChecked()));
	json.insert("yuezuanBox", QString::number(ui.yuezuanBox->isChecked()));
	json.insert("liuyaoBox", QString::number(ui.liuyaoBox->isChecked()));



	json.insert("character_size", ui.charaNumberSetter->text());
	if (ui.autoCRole->isChecked()) {
		json.insert("isAutoChangeRole", "1");
	}
	else {
		json.insert("isAutoChangeRole", "0");
	}

	if (ui.autoLogin->isChecked()) {
		json.insert("isAutoLogin", "1");
		tx->isAutoRestart = true;
	}
	else {
		json.insert("isAutoLogin", "0");
		tx->isAutoRestart = false;
	}

	/*if (ui.charaBox1->isChecked()) {
		json.insert("character1", "1");
	}
	else {
		json.insert("character1", "0");
	}
	if (ui.charaBox2->isChecked()) {
		json.insert("character2", "1");
	}
	else {
		json.insert("character2", "0");
	}
	if (ui.charaBox3->isChecked()) {
		json.insert("character3", "1");
	}
	else {
		json.insert("character3", "0");
	}
	if (ui.charaBox4->isChecked()) {
		json.insert("character4", "1");
	}
	else {
		json.insert("character4", "0");
	}
	if (ui.charaBox5->isChecked()) {
		json.insert("character5", "1");
	}
	else {
		json.insert("character5", "0");
	}
	if (ui.charaBox6->isChecked()) {
		json.insert("character6", "1");
	}
	else {
		json.insert("character6", "0");
	}
	if (ui.charaBox7->isChecked()) {
		json.insert("character7", "1");
	}
	else {
		json.insert("character7", "0");
	}
	if (ui.charaBox8->isChecked()) {
		json.insert("character8", "1");
	}
	else {
		json.insert("character8", "0");
	}
	if (ui.charaBox9->isChecked()) {
		json.insert("character9", "1");
	}
	else {
		json.insert("character9", "0");
	}
	if (ui.charaBox10->isChecked()) {
		json.insert("character10", "1");
	}
	else {
		json.insert("character10", "0");
	}*/

	if (ui.isZhuxianEnableBox->isChecked()) {
		json.insert("isZhuxianEnabled", "1");
	}
	else {
		json.insert("isZhuxianEnabled", "0");
	}
	//generalDZCheckBox
	if (ui.generalDZCheckBox->isChecked()) {
		json.insert("generalDZCheckBox", "1");
	}
	else {
		json.insert("generalDZCheckBox", "0");
	}
	//huoyueCheckBox
	if (ui.huoyueCheckBox->isChecked()) {
		json.insert("huoyueCheckBox", "1");
	}
	else {
		json.insert("huoyueCheckBox", "0");
	}

	if (ui.buqianBox->isChecked()) {
		json.insert("isBuqian", "1");
	}
	else {
		json.insert("isBuqian", "0");
	}

	if (ui.junziShiyongBox->isChecked()) {
		json.insert("isYongjun", "1");
	}
	else {
		json.insert("isYongjun", "0");
	}

	if (ui.captainBox->isChecked()) {
		json.insert("isCaptained", "1");
	}
	else {
		json.insert("isCaptained", "0");
	}

	if (ui.shimenYongjunBox->isChecked()) {
		json.insert("isShimenJun", "1");
	}
	else {
		json.insert("isShimenJun", "0");
	}

	if (ui.huoliProtectBox->isChecked()) {
		json.insert("isHuoliProtected", "1");
	}
	else {
		json.insert("isHuoliProtected", "0");
	}

	QJsonArray scriptArray;
	for (int i = 0; i < ui.scriptSortList->count(); i++) {
		QListWidgetItem* item = ui.scriptSortList->item(i);
		QString itemString = item->text();
		qDebug() << "item = " << itemString;
		
		scriptArray.append(itemString);
	}

	json.insert("scriptArray", QJsonValue(scriptArray));

	QJsonArray subscriptArray;
	for (int i = 0; i < ui.subScriptSortList->count(); i++) {
		QListWidgetItem* item = ui.subScriptSortList->item(i);
		QString itemString = item->text();
		qDebug() << "item = " << itemString;

		subscriptArray.append(itemString);
	}

	json.insert("subscriptArray", QJsonValue(subscriptArray));

	QJsonDocument document;
	document.setObject(json);
	QByteArray byteArray = document.toJson(QJsonDocument::Compact);
	QString strJson(byteArray);
	qDebug() << strJson;

	
	tx->config = strJson;

	return strJson;
}




void ControllerFrameEx::generalConfiguration(QString file) {

	QSettings settings(file, QSettings::IniFormat); // 当前目录的INI文件

	/* 区服设置 */
	settings.beginGroup("zone_config");

	if (ui.zoneRadio1->isChecked()) {
		settings.setValue("daqu", "yitong");
	}
	if (ui.zoneRadio2->isChecked()) {
		settings.setValue("daqu", "huaxia");
	}

	settings.setValue("zone_num", ui.zoneNumberSetter->value());
	settings.endGroup();

	/* 上下架设置 */
	settings.beginGroup("combat_config");

	if (ui.mengyanRadio1->isChecked()) {
		settings.setValue("mengyan", "1");
	}
	if (ui.mengyanRadio2->isChecked()) {
		settings.setValue("mengyan", "0");
	}

	if (ui.jiandingRadio1->isChecked()) {
		settings.setValue("jianding", "1");
	}
	if (ui.jiandingRadio2->isChecked()) {
		settings.setValue("jianding", "0");
	}

	if (ui.qicaiRadio1->isChecked()) {
		settings.setValue("qicai", "1");
	}
	if (ui.qicaiRadio2->isChecked()) {
		settings.setValue("qicai", "0");
	}

	settings.endGroup();

	settings.beginGroup("advanced_config");

	if (ui.rizuanBox->isChecked()) {
		settings.setValue("rizuanBox", "1");
	}
	else {
		settings.setValue("rizuanBox", "0");
	}
	
	if (ui.yuezuanBox->isChecked()) {
		settings.setValue("yuezuanBox", "1");
	}
	else {
		settings.setValue("yuezuanBox", "0");
	}

	if (ui.liuyaoBox->isChecked()) {
		settings.setValue("liuyaoBox", "1");
	}
	else {
		settings.setValue("liuyaoBox", "0");
	}
	//settings.setValue("rizuanBox", ui.rizuanBox->isChecked());
	//settings.setValue("yuezuanBox", ui.yuezuanBox->isChecked());
	//settings.setValue("liuyaoBox", ui.liuyaoBox->isChecked());

	settings.endGroup();

	/* 角色设置 */
	settings.beginGroup("character_config");

	settings.setValue("character_size", ui.charaNumberSetter->value());
	settings.setValue("charaComboBox", ui.charaComboBox->currentIndex());

	


	if (ui.autoCRole->isChecked()) {
		settings.setValue("isAutoChangeRole", "1");
	}
	else {
		settings.setValue("isAutoChangeRole", "0");
	}
	if (ui.autoLogin->isChecked()) {
		settings.setValue("isAutoLogin", "1");
	}
	else {
		settings.setValue("isAutoLogin", "0");
	}

	/*if (ui.charaBox1->isChecked()) {
		settings.setValue("character1", "1");
	}
	else {
		settings.setValue("character1", "0");
	}
	if (ui.charaBox2->isChecked()) {
		settings.setValue("character2", "1");
	}
	else {
		settings.setValue("character2", "0");
	}
	if (ui.charaBox3->isChecked()) {
		settings.setValue("character3", "1");
	}
	else {
		settings.setValue("character3", "0");
	}
	if (ui.charaBox4->isChecked()) {
		settings.setValue("character4", "1");
	}
	else {
		settings.setValue("character4", "0");
	}
	if (ui.charaBox5->isChecked()) {
		settings.setValue("character5", "1");
	}
	else {
		settings.setValue("character5", "0");
	}
	if (ui.charaBox6->isChecked()) {
		settings.setValue("character6", "1");
	}
	else {
		settings.setValue("character6", "0");
	}
	if (ui.charaBox7->isChecked()) {
		settings.setValue("character7", "1");
	}
	else {
		settings.setValue("character7", "0");
	}
	if (ui.charaBox8->isChecked()) {
		settings.setValue("character8", "1");
	}
	else {
		settings.setValue("character8", "0");
	}
	if (ui.charaBox9->isChecked()) {
		settings.setValue("character9", "1");
	}
	else {
		settings.setValue("character9", "0");
	}
	if (ui.charaBox10->isChecked()) {
		settings.setValue("character10", "1");
	}
	else {
		settings.setValue("character10", "0");
	}*/

	settings.setValue("exePath", ui.gamePathEditor->text());

	settings.endGroup();

	/* 开始结束配置 */
	settings.beginGroup("start_config");

	settings.setValue("window_count", ui.windowCounter->value());
	settings.setValue("open_lag", ui.open_lag->value());

	settings.endGroup();

	settings.beginGroup("script_config");

	settings.setValue("team_param", ui.teamSpinBox->value());
	settings.setValue("time_limit", ui.timeLimitSpinBox->value());
	settings.setValue("mitan_counter", ui.mitanCounterSpinBox->value());
	settings.setValue("shimen_counter", ui.shimenCounterSpinBox->value());
	settings.setValue("zhuxian_level", ui.levelSpinBox->value());

	settings.setValue("count", QString::number(ui.scriptSortList->count(), 10));
	for (int i = 0; i < ui.scriptSortList->count(); i++) {
		QListWidgetItem* item = ui.scriptSortList->item(i);
		qDebug() << "item = " << item->text();
		settings.setValue(QString::number(i,10), item->text().toLatin1());
	}

	settings.endGroup();

	settings.beginGroup("subscript_config");

	settings.setValue("count", QString::number(ui.subScriptSortList->count(), 10));
	for (int i = 0; i < ui.subScriptSortList->count(); i++) {
		QListWidgetItem* item = ui.subScriptSortList->item(i);
		qDebug() << "item = " << item->text();
		settings.setValue(QString::number(i, 10), item->text().toLatin1());
	}

	settings.endGroup();

	/* 基本配置 */
	settings.beginGroup("general_config");

	if (ui.shimenYongjunBox->isChecked()) {
		settings.setValue("isShimenJun", "1"); 
	}
	else {
		settings.setValue("isShimenJun", "0");
	}

	if (ui.isZhuxianEnableBox->isChecked()) {
		settings.setValue("isZhuxianEnabled", "1");
	}
	else {
		settings.setValue("isZhuxianEnabled", "0");
	}
	//generalDZCheckBox
	if (ui.generalDZCheckBox->isChecked()) {
		settings.setValue("generalDZCheckBox", "1");
	}
	else {
		settings.setValue("generalDZCheckBox", "0");
	}
	//huoyueCheckBox
	if (ui.huoyueCheckBox->isChecked()) {
		settings.setValue("huoyueCheckBox", "1");
	}
	else {
		settings.setValue("huoyueCheckBox", "0");
	}

	if (ui.EnginedBox->isChecked()) {
		settings.setValue("EnginedBox", "1");
	}
	else {
		settings.setValue("EnginedBox", "0");
	}
	

	if (ui.captainBox->isChecked()) {
		settings.setValue("isCaptained", "1");
	}
	else {
		settings.setValue("isCaptained", "0");
	}

	if (ui.junziShiyongBox->isChecked()) {
		settings.setValue("isYongjun", "1");
	}
	else {
		settings.setValue("isYongjun", "0");
	}

	settings.setValue("team_mode", ui.duimoSpinBox->value());
	settings.setValue("huoli_param", ui.manhuoSpinBox->value());

	if (ui.huoliProtectBox->isChecked()) {
		settings.setValue("isHuoliProtected", "1");
	}
	else {
		settings.setValue("isHuoliProtected", "0");
	}

	settings.endGroup();
}

	

void ControllerFrameEx::readBtn1Clicked() {

	qDebug() << "readBtn1Clicked";
	generalLoadConfig("config/config1.ini");
}

void ControllerFrameEx::readBtn2Clicked() {

	qDebug() << "readBtn2Clicked";
	generalLoadConfig("config/config2.ini");
}

void ControllerFrameEx::readBtn3Clicked() {

	qDebug() << "readBtn3Clicked";
	generalLoadConfig("config/config3.ini");
}

void ControllerFrameEx::readBtn4Clicked() {

	qDebug() << "readBtn4Clicked";
	generalLoadConfig("config/config4.ini");
}

void ControllerFrameEx::readBtn5Clicked() {

	qDebug() << "readBtn5Clicked";
	generalLoadConfig("config/config5.ini");
}

void ControllerFrameEx::readBtn6Clicked() {

	qDebug() << "readBtn6Clicked";
	generalLoadConfig("config/config6.ini");
}



void ControllerFrameEx::writeBtn1Clicked() {

	qDebug() << "writeBtn1Clicked";
	generalConfiguration("config/config1.ini");
}

void ControllerFrameEx::writeBtn2Clicked() {

	qDebug() << "writeBtn2Clicked";
	generalConfiguration("config/config2.ini");
}

void ControllerFrameEx::writeBtn3Clicked() {

	qDebug() << "writeBtn3Clicked";
	generalConfiguration("config/config3.ini");
}

void ControllerFrameEx::writeBtn4Clicked() {

	qDebug() << "writeBtn4Clicked";
	generalConfiguration("config/config4.ini");
}

void ControllerFrameEx::writeBtn5Clicked() {

	qDebug() << "writeBtn5Clicked";
	generalConfiguration("config/config5.ini");
}

void ControllerFrameEx::writeBtn6Clicked() {

	qDebug() << "writeBtn6Clicked";
	generalConfiguration("config/config6.ini");
}

void ControllerFrameEx::engineBtnClicked() {

	qDebug() << "engineBtnClicked";
	this->openTheEngine();
}

void ControllerFrameEx::setUpTableView()
{
	TianxiaSingleton *tianxia = TianxiaSingleton::getInstance();
	tianxia->windowCount = 0;
//#if MAX_ALLOWED == 15
//	ui.tableWidget->setRowCount(15);
//#else
//	ui.tableWidget->setRowCount(50);
//#endif

	if (tianxia->MAX_ALLOWED == 1) {
		ui.tableWidget->setRowCount(15);
		for (int i = 0; i < 15; i++) {
			ui.tableWidget->setRowHeight(i, 20);
		}
	}
	else {
		ui.tableWidget->setRowCount(50);
		for (int i = 0; i < 50; i++) {
			ui.tableWidget->setRowHeight(i, 20);
		}
	}
	
	ui.tableWidget->setColumnCount(12);

//#if MAX_ALLOWED == 15
//	for (int i = 0; i < 15; i++) {
//		ui.tableWidget->setRowHeight(i, 20);
//	}
//#else
//	for (int i = 0; i < 50; i++) {
//		ui.tableWidget->setRowHeight(i, 20);
//	}
//#endif

	

	QStringList header;
	header << QString::fromLocal8Bit("  状态  ") << QString::fromLocal8Bit("窗口句柄") 
		<< QString::fromLocal8Bit("当前任务") << QString::fromLocal8Bit("备注")
		<< QString::fromLocal8Bit("角色编号") << QString::fromLocal8Bit("存货")
		<< QString::fromLocal8Bit("总") << QString::fromLocal8Bit("时") << QString::fromLocal8Bit("及")
		<< QString::fromLocal8Bit("活乐") << QString::fromLocal8Bit("ID") << QString::fromLocal8Bit("金币");
	ui.tableWidget->setHorizontalHeaderLabels(header);
	ui.tableWidget->horizontalHeader()->setStretchLastSection(true);
	ui.tableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	ui.tableWidget->setColumnWidth(0, 100);
	ui.tableWidget->setColumnWidth(1, 60);
	ui.tableWidget->setColumnWidth(2, 65);
	ui.tableWidget->setColumnWidth(3, 50);
	ui.tableWidget->setColumnWidth(4, 60);
	ui.tableWidget->setColumnWidth(5, 65);
	ui.tableWidget->setColumnWidth(6, 35);
	ui.tableWidget->setColumnWidth(7, 35);
	ui.tableWidget->setColumnWidth(8, 35);
	ui.tableWidget->setColumnWidth(9, 35);
	ui.tableWidget->setColumnWidth(10, 35);
	ui.tableWidget->setColumnWidth(11, 80);
	ui.tableWidget->setColumnWidth(12, 80);
}

void ControllerFrameEx::onCellClicked(int a, int b)
{
	int test = a + b;

}

void ControllerFrameEx::onRightClicked(QPoint point) {
	qDebug() << "onRightClicked";
	int a = ui.tableWidget->currentColumn();
	int b = ui.tableWidget->currentRow();

	QMenu menu;
	menu.addAction(QString::fromLocal8Bit("刷新列表"), this, SLOT(test()));
	menu.addSeparator();
	menu.addAction(QString::fromLocal8Bit("全部暂停"), this, SLOT(allPause()));
	menu.addAction(QString::fromLocal8Bit("单个暂停"), this, SLOT(singlePause()));
	menu.addAction(QString::fromLocal8Bit("暂停恢复"), this, SLOT(singleRestart()));
	menu.addSeparator();
	menu.addAction(QString::fromLocal8Bit("全部停止"), this, SLOT(allStop()));
	menu.addAction(QString::fromLocal8Bit("单个停止"), this, SLOT(singleStop()));
	menu.addAction(QString::fromLocal8Bit("单个开始"), this, SLOT(singleStart()));
	menu.addAction(QString::fromLocal8Bit("全部开始"), this, SLOT(allStart()));
	menu.addSeparator();
	menu.addAction(QString::fromLocal8Bit("单个结束"), this, SLOT(terminateWnd()));
	menu.addAction(QString::fromLocal8Bit("单个启动"), this, SLOT(newSingleWnd()));
	menu.addSeparator();
	menu.addAction(QString::fromLocal8Bit("窗口缩小"), this, SLOT(standarlizeWnd()));

	menu.exec(QCursor::pos());

}

void ControllerFrameEx::test() {

	qDebug() << "test";
	
}

void ControllerFrameEx::allPause() {
	TianxiaSingleton* tianxia = TianxiaSingleton::getInstance();
	qDebug() << "allPause";
	for (int i = 0; i < tianxia->windowCount; i++) {
		
		QTableWidgetItem* item = ui.tableWidget->item(i, 0);
		if (item == NULL) {
			return;
		}

		QString tHWND = item->text();
		qDebug() << tHWND;

		if ("222222" == tHWND || "222220" == tHWND) {
			continue;
		}

		ui.tableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromLocal8Bit("已暂停")));
		ui.tableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromLocal8Bit("111111")));
	}

}

void ControllerFrameEx::allStop() {
	TianxiaSingleton* tianxia = TianxiaSingleton::getInstance();
	qDebug() << "allStop";
	for (int i = 0; i < tianxia->windowCount; i++) {

		QTableWidgetItem* item = ui.tableWidget->item(i, 0);
		QString tHWND = item->text();
		qDebug() << tHWND;

		if ("222222" == tHWND || "222220" == tHWND) {
			continue;
		}

		ui.tableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromLocal8Bit("停止中")));
		ui.tableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromLocal8Bit("222220")));
	}

	

}

void ControllerFrameEx::singlePause() {
	qDebug() << "singlePause";
	int a = ui.tableWidget->currentColumn();
	int b = ui.tableWidget->currentRow();

	qDebug() << "column =" << a;
	qDebug() << "row =" << b;
	TianxiaSingleton* tianxia = TianxiaSingleton::getInstance();
	QTableWidgetItem* item = ui.tableWidget->item(b, 0);
	if (item == NULL) {
		return;
	}

	QString tHWND = item->text();
	qDebug() << tHWND;

	if ("222222" == tHWND || "222220" == tHWND) {
		return;
	}
	
	ui.tableWidget->setItem(b, 2, new QTableWidgetItem(QString::fromLocal8Bit("已暂停")));
	ui.tableWidget->setItem(b, 0, new QTableWidgetItem(QString::fromLocal8Bit("111111")));

}

void ControllerFrameEx::singleStop() {
	qDebug() << "singleStop";
	int a = ui.tableWidget->currentColumn();
	int b = ui.tableWidget->currentRow();

	qDebug() << "column =" << a;
	qDebug() << "row =" << b;
	TianxiaSingleton* tianxia = TianxiaSingleton::getInstance();
	QTableWidgetItem* item = ui.tableWidget->item(b, 0);
	if (item == NULL) {
		return;
	}

	QString tHWND = item->text();
	qDebug() << tHWND;

	if ("222222" == tHWND || "222220" == tHWND) {
		return;
	}


	ui.tableWidget->setItem(b, 2, new QTableWidgetItem(QString::fromLocal8Bit("停止中")));
	ui.tableWidget->setItem(b, 0, new QTableWidgetItem(QString::fromLocal8Bit("222220")));

}

void ControllerFrameEx::allStart() {
	TianxiaSingleton* tianxia = TianxiaSingleton::getInstance();
	qDebug() << "allStart";
	
	for (int i = 0; i < tianxia->windowCount; i++) {

		QTableWidgetItem* item = ui.tableWidget->item(i, 0);
		if (item == NULL) {
			return;
		}

		QString tHWND = item->text();
		qDebug() << tHWND;

		if ("222222" != tHWND || "000000" == tHWND) {
			continue;
		}

		QString config = loadScriptConfig();


		QString file = ui.gamePathEditor->text();
		OpenWindowThread* thread = new OpenWindowThread(512, file.toStdString(), config, i);

		ui.tableWidget->setItem(i, 2, new QTableWidgetItem(QString::fromLocal8Bit("开始中")));
		ui.tableWidget->setItem(i, 0, new QTableWidgetItem(QString::fromLocal8Bit("RUNNING")));
		thread->start();

		Sleep(1000);
	}
}

void ControllerFrameEx::singleStart() {
	qDebug() << "singleStart";
	int a = ui.tableWidget->currentColumn();
	int b = ui.tableWidget->currentRow();

	qDebug() << "column =" << a;
	qDebug() << "row =" << b;

	QTableWidgetItem* item = ui.tableWidget->item(b, 0);
	if (item == NULL) {
		return;
	}

	QString tHWND = item->text();
	qDebug() << tHWND;

	if ("222222" != tHWND || "000000" == tHWND) {
		return;
	}

	//createGameThreadSingle(b);
	//createGameThread();
	QString config = loadScriptConfig();

	/*int count = ui.windowCounter->value();
	for (int i = 0; i < count; i++) {
	createGameThread();
	Sleep(8000);
	}*/
	//ui.tableWidget->setItem(b, 1, new QTableWidgetItem(QString::fromLocal8Bit("000001")));

	//if (this->ui.EnginedBox->isChecked() == false) {
	//	QString file = ui.gamePathEditor->text();
	//	OpenWindowThread* thread = new OpenWindowThread(512, file.toStdString(), config, b);

	//	ui.tableWidget->setItem(b, 2, new QTableWidgetItem(QString::fromLocal8Bit("开始中")));
	//	ui.tableWidget->setItem(b, 0, new QTableWidgetItem(QString::fromLocal8Bit("RUNNING")));
	//	thread->start();
	//}
	//else {
	//	QString file = ui.gamePathEditor->text();
	//	//EnginedWindowThread* thread = new EnginedWindowThread(512, file.toStdString(), config, b);
	//	EnginedWindowThread* thread = new EnginedWindowThread(512, config, engineHWND, clicker);
	//	ui.tableWidget->setItem(b, 2, new QTableWidgetItem(QString::fromLocal8Bit("开始中")));
	//	ui.tableWidget->setItem(b, 0, new QTableWidgetItem(QString::fromLocal8Bit("RUNNING")));
	//	thread->start();
	//}

	QString file = ui.gamePathEditor->text();
	OpenWindowThread* thread = new OpenWindowThread(512, file.toStdString(), config, b);

	ui.tableWidget->setItem(b, 2, new QTableWidgetItem(QString::fromLocal8Bit("开始中")));
	ui.tableWidget->setItem(b, 0, new QTableWidgetItem(QString::fromLocal8Bit("RUNNING")));
	thread->start();
}


void ControllerFrameEx::singleRestart() {
	qDebug() << "singleRestart";
	int a = ui.tableWidget->currentColumn();
	int b = ui.tableWidget->currentRow();

	qDebug() << "column =" << a;
	qDebug() << "row =" << b;
	TianxiaSingleton* tianxia = TianxiaSingleton::getInstance();


	ui.tableWidget->setItem(b, 2, new QTableWidgetItem(QString::fromLocal8Bit("暂停恢复")));
	ui.tableWidget->setItem(b, 0, new QTableWidgetItem(QString::fromLocal8Bit("RUNNING")));

}

void ControllerFrameEx::newSingleWnd() {
	qDebug() << "terminateWnd";
	int a = ui.tableWidget->currentColumn();
	int b = ui.tableWidget->currentRow();

	qDebug() << "column =" << a;
	qDebug() << "row =" << b;

	QTableWidgetItem* item = ui.tableWidget->item(b, 1);
	if (item == NULL) {
		return;
	}

	QString tHWND = item->text();
	qDebug() << tHWND;

	if ("000000" != tHWND) {
		return;
	}

	//createGameThreadSingle(b);
	//createGameThread();
	QString config = loadScriptConfig();

	/*int count = ui.windowCounter->value();
	for (int i = 0; i < count; i++) {
	createGameThread();
	Sleep(8000);
	}*/

	if (this->ui.EnginedBox->isChecked() == false) {
		
		ui.tableWidget->setItem(b, 1, new QTableWidgetItem(QString::fromLocal8Bit("000001")));
		QString file = ui.gamePathEditor->text();
		OpenWindowThread* thread = new OpenWindowThread(1024, file.toStdString(), config, b);
		thread->start();
	}
	else {
		
		//EnginedWindowThread* thread = new EnginedWindowThread(512, file.toStdString(), config, b);
		ui.tableWidget->setItem(b, 1, new QTableWidgetItem(QString::fromLocal8Bit("000001")));
		EnginedWindowThread* thread = new EnginedWindowThread(1024, config, engineHWND, clicker, b);
		//ui.tableWidget->setItem(b, 2, new QTableWidgetItem(QString::fromLocal8Bit("开始中")));
		//ui.tableWidget->setItem(b, 0, new QTableWidgetItem(QString::fromLocal8Bit("RUNNING")));
		thread->start();
	}

}

void ControllerFrameEx::standarlizeWnd() {
	qDebug() << "standarlizeWnd";
	int a = ui.tableWidget->currentColumn();
	int b = ui.tableWidget->currentRow();

	qDebug() << "column =" << a;
	qDebug() << "row =" << b;

	QTableWidgetItem* item = ui.tableWidget->item(b, 1);
	if (item == NULL) {
		return;
	}

	QString tHWND = item->text();
	qDebug() << tHWND;

	if ("000000" == tHWND) {
		return;
	}
	DEVMODE NewDevMode;
	EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &NewDevMode);

	SetWindowPos((HWND)tHWND.toInt(), 0, NewDevMode.dmPelsWidth - 600, 0, 600, 400, SWP_SHOWWINDOW | SWP_NOZORDER);
}

void ControllerFrameEx::terminateWnd() {
	TianxiaSingleton* tianxia = TianxiaSingleton::getInstance();
	qDebug() << "terminateWnd";
	int a = ui.tableWidget->currentColumn();
	int b = ui.tableWidget->currentRow();

	qDebug() << "a =" << a;
	qDebug() << "b =" << b;

	QTableWidgetItem* item = ui.tableWidget->item(b, 1);
	if (item == NULL) {
		return;
	}

	QString tHWND = item->text();
	qDebug() << tHWND;

	if ("000008" == tHWND || "000000" == tHWND) {
		return;
	}

	item = ui.tableWidget->item(b, 0);
	if (item == NULL) {
		return;
	}

	tHWND = item->text();
	qDebug() << tHWND;

	if ("222222" == tHWND || "222220" == tHWND) {
		MessageBoxA(NULL,"停止状态下无法结束！","警告",ERROR);
		return;
	}

	long lHWND = tHWND.toLong();


	qDebug() << lHWND;

	QHash<int, DWORD>::iterator iter = tianxia->threadMap.find(b);

	DWORD pid = iter.value();
	tianxia->threadMap.remove(b);

	CommonUtil::KillProcess(pid);

	ui.tableWidget->setItem(b, 2, new QTableWidgetItem(QString::fromLocal8Bit("结束中")));
	ui.tableWidget->setItem(b, 1, new QTableWidgetItem(QString::fromLocal8Bit("000008")));
	/*TerminateProcess(0);*/
}

void ControllerFrameEx::pathBtnClicked() {

	QString file = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("天下手游exe"),QString(), QString::fromLocal8Bit("天下手游exe(*.exe);;All files(*.*)"));

	if (file.isEmpty()) {
		return;
	}

	qDebug() << file;

	ui.gamePathEditor->setText(file);
}

void ControllerFrameEx::startBtnClicked() {

	QString config = loadScriptConfig();
	TianxiaSingleton *tx = TianxiaSingleton::getInstance();
//#if MAX_ALLOWED == 15
//	if (tx->windowCount >= 15) {
//		MessageBoxA(NULL,"您已经到达开启限制！","已经15个了",ERROR);
//		return ;
//	}
//#endif

	if (tx->MAX_ALLOWED == 1) {
		if (tx->windowCount >= 15) {
			MessageBoxA(NULL, "您已经到达开启限制！", "已经15个了", ERROR);
			return;
		}
	}

	if (ui.EnginedBox->isChecked() == false) {
		QString file = ui.gamePathEditor->text();
		OpenWindowThread* thread = new OpenWindowThread(ui.windowCounter->value(), file.toStdString(), config);
		thread->start();
	}
	else {
		if (this->engineHWND == 0) {
			return;
		}

		EnginedWindowThread* thread = new EnginedWindowThread(ui.windowCounter->value(), config, engineHWND, clicker);
		thread->start();
	}

	
}



void ControllerFrameEx::createGameThread() {
	QString file = ui.gamePathEditor->text();
	TianxiaSingleton* tianxia = TianxiaSingleton::getInstance();

	STARTUPINFOA si;
	memset(&si, 0, sizeof(STARTUPINFO));//初始化si在内存块中的值（详见memset函数）
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_SHOW;
	PROCESS_INFORMATION pi;//必备参数设置结束
	if (!CreateProcessA(file.toStdString().c_str(),
		NULL,
		NULL,
		NULL,
		FALSE,
		0,
		NULL,
		NULL,
		&si,
		&pi
	)) {
		qDebug() << "CreateFail!" << endl;
		exit(1);
	}
	else {
		qDebug() << "Success!" << endl;
		Sleep(10000);
		HWND hwnd = CommonUtil::GetHwndFromPID(pi.dwProcessId);
		//HKL layout = GetKeyboardLayout(pi.dwThreadId);.
	/*	HKL layout = GetKeyboardLayout(0);
		TCHAR uChar[1025] = { 0 };


		int ret = ImmGetDescription(layout, uChar, 1024);

		bool isOpen = ImmIsIME(GetKeyboardLayout(pi.dwThreadId));
		LPWSTR pwszKLID;
		GetKeyboardLayoutName(pwszKLID);
		if (isOpen) {
			ActivateKeyboardLayout((HKL)HKL_NEXT, 0);
		}

		isOpen = ImmIsIME(GetKeyboardLayout(pi.dwThreadId));

		HKL *hkl;
		GetKeyboardLayoutList(4096, hkl);
		GetKeyboardLayoutName(pwszKLID);
*/
		//GetKeyboardLayout
		long lHWND = (long)hwnd;
		qDebug() << pi.hProcess;

		//THE_DATA *data = new THE_DATA;
		//int rowCount = ui.tableWidget->rowCount();
		
		getWindowInfo(lHWND);
		
		/*for (int i = 0; i < 200; i++) {
			CommonUtil::getRandomCNChar();
		}*/
		
		tianxia->threadMap.insert(tianxia->windowCount, pi.dwProcessId);
		//string test = CommonUtil::getIDNumber();

		SetWindowPos(hwnd, 0, 0, 0, 600, 400, SWP_SHOWWINDOW| SWP_NOZORDER);
		//不使用的句柄最好关掉
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);

		QString config = loadScriptConfig();
		tianxia->windowCount++;

		TianxiaScript* tianxiaScript = new TianxiaScript(lHWND, config, tianxia->windowCount, pi.dwThreadId);
		tianxiaScript->startScript();
		

	}

	
}

void ControllerFrameEx::initEngineClicker() {
	this->clicker = DMSoft::getInstance()->newDMObject();
	qDebug() << clicker->PskVer();

#if 0

	qDebug() << DM->GetID();
	qDebug() << DM->GetMachineCode();
	DM->Release();

	return 0;
#endif


	int result = 0;

	clicker->PskSetShowErrorMsg(0);
	string code = clicker->GetMachineCode();


	result = clicker->PskReg("pskfire20928db6b002f54b0b0f1d5dcc665316", "ambition");
	qDebug() << "machineCode=";
	qDebug() << code.c_str();
	if (result != 1) {
		qDebug() << "reg error";

	}

	result = clicker->PskGuard(1, "np");
	if (result != 1) {
		qDebug() << "DmGuard np error";
	}

	result = clicker->PskGuard(1, "memory");
	if (result != 1) {
		qDebug() << "DmGuard memory error";
	}

	result = clicker->PskGuard(1, "block");
	if (result != 1) {
		qDebug() << "DmGuard block error";
	}

	result = clicker->PskGuard(1, "b2");
	if (result != 1) {
		qDebug() << "DmGuard b2 error ";
	}

	result = clicker->PskGuard(1, "f1");
	if (result != 1) {
		qDebug() << "DmGuard f1 error";
	}

	
}

void ControllerFrameEx::openTheEngine() {
	
	this->initEngineClicker();

	STARTUPINFOA si;
	memset(&si, 0, sizeof(STARTUPINFO));//初始化si在内存块中的值（详见memset函数）
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_SHOW;
	PROCESS_INFORMATION pi;//必备参数设置结束
	if (!CreateProcessA("engine.exe",
		NULL,
		NULL,
		NULL,
		FALSE,
		0,
		NULL,
		NULL,
		&si,
		&pi
	)) {
		qDebug() << "CreateFail!" << endl;
		exit(1);
	}
	else {
		qDebug() << "Success!" << endl;

	}

	Sleep(8000);

	HWND hwnd = CommonUtil::GetHwndFromPID(pi.dwProcessId);
	//engineHWND = (long)hwnd;
	engineHWND = clicker->PskFindWndByProcId(pi.dwProcessId, "", "");
	//engineHWND = clicker->FindWindowByProcess("engine.exe","","");
	
	int bindRet = clicker->PskBindWndEx(engineHWND, "normal", "windows", "windows", "", 0);
	if (bindRet == 1) {
		qDebug() << "EngineBindSuccess!" << endl;
		string title = clicker->PskGetWndTitle(engineHWND);
		MessageBoxA(NULL, "绑定成功!", title.c_str(), MB_OK);
	}
	else {
		qDebug() << "EngineBindFail!" << endl;
		MessageBoxA(NULL, "绑定失败!", "", MB_OK);
		
	}
	clicker->PskCapture(0,0,300,300,"123.bmp");

	qDebug() << engineHWND << endl;
}

void ControllerFrameEx::createGameThreadSingle(int row) {
	QString file = ui.gamePathEditor->text();
	TianxiaSingleton* tianxia = TianxiaSingleton::getInstance();

	STARTUPINFOA si;
	memset(&si, 0, sizeof(STARTUPINFO));//初始化si在内存块中的值（详见memset函数）
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_SHOW;
	PROCESS_INFORMATION pi;//必备参数设置结束
	if (!CreateProcessA(file.toStdString().c_str(),
		NULL,
		NULL,
		NULL,
		FALSE,
		0,
		NULL,
		NULL,
		&si,
		&pi
	)) {
		qDebug() << "CreateFail!" << endl;
		exit(1);
	}
	else {
		qDebug() << "Success!" << endl;
		Sleep(10000);
		HWND hwnd = CommonUtil::GetHwndFromPID(pi.dwProcessId);
	
		long lHWND = (long)hwnd;
		qDebug() << pi.hProcess;
		
		ui.tableWidget->setItem(row, 0, new QTableWidgetItem(QString::fromLocal8Bit("RUNNING")));
		ui.tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(lHWND)));

		//threadMap.remove(row);
		tianxia->threadMap.insert(row, pi.dwProcessId);
		//string test = CommonUtil::getIDNumber();

		SetWindowPos(hwnd, 0, 0, 0, 600, 400, SWP_SHOWWINDOW | SWP_NOZORDER);
		//不使用的句柄最好关掉
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);

		QString config = loadScriptConfig();


		TianxiaScript* tianxia = new TianxiaScript(lHWND, config, row + 1, pi.dwThreadId);
		tianxia->startScript();


	}


}


//BOOL ControllerFrameEx::KillProcess(DWORD ProcessId)
//{
//	HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, FALSE, ProcessId);
//	if (hProcess == NULL)
//		return FALSE;
//	if (!TerminateProcess(hProcess, 0))
//		return FALSE;
//	return TRUE;
//}

void ControllerFrameEx::getWindowInfo(long lHWND) {

	//LPWSTR wText = T2W(text);

	/*QString q = QString::fromUtf8(text);
	qDebug() << q;*/
	TianxiaSingleton* tianxia = TianxiaSingleton::getInstance();

	ui.tableWidget->setItem(tianxia->windowCount, 0, new QTableWidgetItem(QString::fromLocal8Bit("RUNNING")));
	ui.tableWidget->setItem(tianxia->windowCount, 1, new QTableWidgetItem(QString::number(lHWND)));
	
}