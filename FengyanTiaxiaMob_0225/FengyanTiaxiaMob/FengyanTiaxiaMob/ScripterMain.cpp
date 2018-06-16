#include "ScripterMain.h"
#include "DMSoft.h"
#include "ControllerFrameEx.h"


ScripterMain::ScripterMain(QWidget *parent)
	: QMainWindow(parent)
{
	CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);
	qDebug() << "Test";
	ui.setupUi(this);

	ui.modeComboBox->addItem(QString::fromLocal8Bit("��ѡ��汾"));
	ui.modeComboBox->addItem(QString::fromLocal8Bit("15��"));
	ui.modeComboBox->addItem(QString::fromLocal8Bit("���޿�"));

	QObject::connect(ui.unBindBtn, SIGNAL(clicked()), this, SLOT(unBindBtnClicked()));
	QObject::connect(ui.chongzhiBtn, SIGNAL(clicked()), this, SLOT(chongzhiBtnClicked()));
	
	QSettings configIniRead("config/code.ini", QSettings::IniFormat);
	QString value = configIniRead.value("/code_value/value").toString();
	int mode = configIniRead.value("/code_value/mode").toInt();
	ui.modeComboBox->setCurrentIndex(mode);
	ui.lineEdit->setText(value);

	Ifire* DM = DMSoft::getInstance()->newDMObject();
	string machineCode = DM->GetMachineCode();
	qDebug() << DM->PskVer();
	qDebug() << DM->PskGetID();
	qDebug() << machineCode.c_str();
	/*DM->Release();*/

	/*int result = 0;

	result = DM->Reg("pskfire007e595753bc4ecfb25f28447871e625568", "vdvXFZ");
	if (result != 1) {
		qDebug() << "reg error";
		
	}

	result = DM->PskGuard(1, "np");
	if (result != 1) {
		qDebug() << "DmGuard np error";
	}

	result = DM->PskGuard(1, "memory");
	if (result != 1) {
		qDebug() << "DmGuard memory error";
	}

	result = DM->PskGuard(1, "block");
	if (result != 1) {
		qDebug() << "DmGuard block error";
	}

	result = DM->PskGuard(1, "b2");
	if (result != 1) {
		qDebug() << "DmGuard b2 error ";
	}

	result = DM->PskGuard(1, "f1");
	if (result != 1) {
		qDebug() << "DmGuard f1 error";
	}*/

	this->setFixedSize(this->size());
	
}

void ScripterMain::unBindBtnClicked() {

	qDebug() << "unBindBtnClicked";

	if (tokenVerify() == 0) {
		this->close();
		return;
	}
	QString value = ui.lineEdit->text();
	wstring g_csRegCode = value.toStdWString();
	LPCWSTR code = g_csRegCode.c_str();
	LPCWSTR pwd = L"";
	// ��������

	if (UbindW(code, pwd))
	{
		QMessageBox::information(NULL, "Success", QString::fromLocal8Bit("���ɹ���"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
	}
	else
	{
		TCHAR buffer[1024] = { 0 };
		GetLastErrorInfoW(buffer, 1024);
		QString msg = QString::fromWCharArray(buffer);
		/*::AfxMessageBox(_T("��¼ʧ��,ԭ��") + CString(buffer));*/
		QMessageBox::information(NULL, QString::fromLocal8Bit("���ʧ�ܣ�ԭ���ǣ�"), msg, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		return;
	}
	
}

void ScripterMain::chongzhiBtnClicked() {

	qDebug() << "chongzhiBtnClicked";

	if (tokenVerify() == 0) {
		this->close();
		return;
	}
	QString value = ui.lineEdit->text();
	wstring g_csRegCode = value.toStdWString();
	LPCWSTR code = g_csRegCode.c_str();
	LPCWSTR pwd = L"";
	// ��������
	QString newValue = ui.chongzhiLine->text();
	wstring newRegCode = newValue.toStdWString();
	LPCWSTR newCode = newRegCode.c_str();
	QApplication::setQuitOnLastWindowClosed(false);
	if (ChargeW(newCode, code))
	{
		//QMessageBox::information(NULL, "Title", QString::fromLocal8Bit("��ֵ�ɹ���"), QMessageBox::Yes);
		QMessageBox msgBox;
		msgBox.setText(QString::fromLocal8Bit("��ֵ�ɹ���"));
		msgBox.exec();
	}
	else
	{
		TCHAR buffer[1024] = { 0 };
		GetLastErrorInfoW(buffer, 1024);
		QString msg = QString::fromWCharArray(buffer);
		 
		QMessageBox box(QMessageBox::Warning, QString::fromLocal8Bit("��ֵʧ�ܣ�"),
			msg);
		box.setStandardButtons(QMessageBox::Ok);
		box.exec();
		
	}
	QApplication::setQuitOnLastWindowClosed(true);
}

int ScripterMain::tokenVerify() {
	LPCSTR g_csBbyToken = "e1fca05a1aa8186d1407ce653e51a0f9 ";

//#if MAX_ALLOWED == 15
//	LPCSTR g_csProjName = "for15"; 
//#else
//	LPCSTR g_csProjName = "test";
//#endif
	LPCSTR g_csProjName = "";
	if (ui.modeComboBox->currentIndex() == 0) {
		MessageBox(NULL, L"��ѡ��汾",L"ERROR",MB_OK);
		return 0;
	}
	if (ui.modeComboBox->currentIndex() == 1) {
		g_csProjName = "for15";
	}
	if (ui.modeComboBox->currentIndex() == 2) {
		g_csProjName = "test";
	}
	if (InitDll(g_csBbyToken, g_csProjName) == 0)
	{
		TCHAR buffer[1024] = { 0 };
		GetLastErrorInfoW(buffer, 1024);
		QMessageBox::information(NULL, "Error", QString::fromLocal8Bit("Token����"), QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		return 0;
	}
	else {
		return 1;
	}


	return 0;
}

int ScripterMain::regCodeVerify() {
	
	QString value = ui.lineEdit->text();
	wstring g_csRegCode = value.toStdWString();
	LPCWSTR code = g_csRegCode.c_str();

	if (LoginRegCodeW(code))
	{
		QString file = "config/code.ini";
		QSettings settings(file, QSettings::IniFormat);
		settings.beginGroup("code_value");
		settings.setValue("value", value);
		settings.setValue("mode", ui.modeComboBox->currentIndex());
		settings.endGroup();

		TianxiaSingleton* tianxia = TianxiaSingleton::getInstance();
		tianxia->MAX_ALLOWED = ui.modeComboBox->currentIndex();

		return 1;
	}
	else
	{
		TCHAR buffer[1024] = { 0 };
		GetLastErrorInfoW(buffer, 1024);
		QString msg = QString::fromWCharArray(buffer);
		/*::AfxMessageBox(_T("��¼ʧ��,ԭ��") + CString(buffer));*/
		QMessageBox::information(NULL, "Error", msg, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
		return 0;
	}

	return 0;
}

void ScripterMain::enterBtnClicked() {
	
	if (tokenVerify() == 0) {
		this->close();
		return;
	}

	if (regCodeVerify() == 0) {
		this->close();
		return;
	}

	QMessageBox box(QMessageBox::Warning, QString::fromLocal8Bit("���棡"),
		QString::fromLocal8Bit("<font size='6' color='red'>һ.�������ȫ���ڸ�����Ȥ���ã��ɱ�����ҵ��ʱ�俪������һ�ȫ����ɫ���ɿ��������Ʒ.<br>��.�������ּ���ڽ��˫�֣�������Ϸ���ԣ������񫡣<br>��.�Ͻ�������������κ�Ĳ������Ϊ�����д���Ϊ�����˽�����׷���������Լ��������ε�Ȩ����<br>��.��ʹ�ñ���������µ��κ����⡢�������Լ�ٻ����̰�����Ȩ��֪ʶ��Ȩ�ַ���������ɵ��κ���ʧ�����˸Ų�������Ų��е��κ����»����·������Ρ�<br>��.�����һ�ο�ʼʹ�ñ������ṩ���κ��������Դ����һ����ͽ�����Ϊ�Ա�����ȫ�����ݵ��Ͽɡ�ͬʱ�������Ͽ����������������ʹ�ñ��������Դ�������κ����飬��������ɾ�����������Դ����ֹͣʹ��.<br>��.�������ݣ����˱������ս���Ȩ</font>"));
	box.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
	box.setButtonText(QMessageBox::Ok, QString::fromLocal8Bit("ͬ��"));
	box.setButtonText(QMessageBox::Cancel, QString::fromLocal8Bit("��ͬ��"));
	//box.exec();

	int ret = box.exec();
	switch (ret) {
	case QMessageBox::Ok: {
		ControllerFrameEx* ex = new ControllerFrameEx(this);
		ex->show();
		this->hide();
		break;
	}
		
	case QMessageBox::Cancel:
		this->close();
		break;
	default:
		break;
	}


}