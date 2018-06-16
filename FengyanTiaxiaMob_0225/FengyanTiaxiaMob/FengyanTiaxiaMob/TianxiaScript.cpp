#include "TianxiaScript.h"



TianxiaScript::TianxiaScript()
{
}


TianxiaScript::~TianxiaScript()
{
}

TianxiaScript::TianxiaScript(long HWNDLong) {
	stepIndex = 0;
	this->lHWND = HWNDLong;
}

TianxiaScript::TianxiaScript(long HWNDLong, QString config) {
	stepIndex = 0;
	this->lHWND = HWNDLong;
	this->jsonConfig = config;
}

TianxiaScript::TianxiaScript(long HWNDLong, QString config, int windowCount) {
	stepIndex = 0;
	this->lHWND = HWNDLong;
	this->jsonConfig = config;
	this->index = windowCount;
}

TianxiaScript::TianxiaScript(long HWNDLong, QString config, int windowCount, DWORD threadId) {
	stepIndex = 0;
	this->lHWND = HWNDLong;
	this->jsonConfig = config;
	this->index = windowCount;
	this->threadId = threadId;
}

int TianxiaScript::waitForScanFunction(Ifire* DM) {
	TianxiaSingleton* tx = TianxiaSingleton::getInstance();
	QTableWidget* table = tx->table;

	while (findScanPic(DM) == 1 /**|| findLoginScreen(DM) == 0*/ && getIsEnded() == false) {
		Sleep(10000);
		table->setItem(this->index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("等待扫码")));

	}

	return 0;
}

int TianxiaScript::authIDCard(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;
	bstr = DM->PskFindPicE(300, 150, 450, 300, "无法登陆.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "wufaDengLux=" << result[1].c_str();
	qDebug() << "wufaDengLuy=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 50, 20, 20);
		DM->PskLClick();
		Sleep(3000);

		authIDCardName(DM);
		authIDCardNumber(DM);
		Sleep(1000);
		authPhoneNumber(DM);
		Sleep(1000);
		authQuerenBTN(DM);
		DM->PskMToEx(300, 290, 10, 10);
		DM->PskLClick();
		Sleep(3000);

		return 1;
	}

	return 0;
}

//HKL TianxiaScript::InitHklRPC()
//{
//	// Find RPC hkl  
//	UINT nMaxHklCnt = GetKeyboardLayoutList(0, NULL);
//	HKL g_hklRPC;
//
//	HKL* p_hklList = (HKL*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, nMaxHklCnt * sizeof(HKL));
//
//	UINT nHklCnt = GetKeyboardLayoutList(nMaxHklCnt, p_hklList);
//
//	for (UINT i = 0; i<nHklCnt; i++) {
//		if (LOWORD(p_hklList[i]) == 0x0804) {
//			g_hklRPC = p_hklList[i];
//			return g_hklRPC;
//			break;
//		}
//	}
//
//	HeapFree(GetProcessHeap(), NULL, p_hklList);
//
//	return g_hklRPC;
//}

int TianxiaScript::sendStr(QString str) {
	HWND hFocusHwnd = (HWND)lHWND;

	const wchar_t * encodedName = reinterpret_cast<const wchar_t *>(str.utf16());
	PostMessageW(hFocusHwnd, WM_CHAR, *encodedName, 1);

	return 0;
}

int TianxiaScript::authIDCardName(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(80, 100, 200, 170, "姓名.bmp|Xingming.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(80, 100, 200, 170, "Xingming.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "xingmingx=" << result[1].c_str();
	qDebug() << "xingmingy=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 100, y + 5, 10, 10);
		DM->PskLClick();
		Sleep(3000);

		srand((unsigned)time(NULL));
		HWND hFocusHwnd = (HWND)lHWND;

		QString test = CommonUtil::getRandomCNChar();
		const wchar_t * encodedName = reinterpret_cast<const wchar_t *>(test.utf16());
		PostMessageW(hFocusHwnd, WM_CHAR, *encodedName, 1);

		test = CommonUtil::getRandomCNChar();
		encodedName = reinterpret_cast<const wchar_t *>(test.utf16());
		PostMessageW(hFocusHwnd, WM_CHAR, *encodedName, 1);

		test = CommonUtil::getRandomCNChar();
		encodedName = reinterpret_cast<const wchar_t *>(test.utf16());
		PostMessageW(hFocusHwnd, WM_CHAR, *encodedName, 1);

		return 1;
	}

	return 0;
}

int TianxiaScript::authIDCardNumber(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(250, 100, 350, 220, "证件号.bmp|Zhengjianhao.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(250, 100, 350, 220, "Zhengjianhao.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "zhengjianhaoX=" << result[1].c_str();
	qDebug() << "zhengjianhaoY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 100, y + 5, 10, 10);
		DM->PskLClick();
		Sleep(3000);

		IDGenerator *gen = new IDGenerator();
		string idNumber = gen->getIDNumber();

		DM->PskKPressStr(idNumber.c_str(), 50);

		return 1;
	}

	return 0;
}

int TianxiaScript::authPhoneNumber(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(250, 200, 350, 250, "手机号.bmp|Shoujihao.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(250, 200, 350, 250, "Shoujihao.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "shoujihaoX=" << result[1].c_str();
	qDebug() << "shoujihaoX=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 100, y + 5, 10, 10);
		DM->PskLClick();
		Sleep(3000);

		string phoneNumber = CommonUtil::getRandomPhoneNumebr();

		DM->PskKPressStr(phoneNumber.c_str(), 50);

		return 1;
	}

	return 0;
}

int TianxiaScript::authQuerenBTN(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(250, 200, 350, 250, "手机号.bmp|Shoujihao.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(250, 200, 350, 250, "Shoujihao.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "shoujihaoX=" << result[1].c_str();
	qDebug() << "shoujihaoX=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x, y + 55, 10, 10);
		DM->PskLClick();
		Sleep(3000);

		return 1;
	}

	return 0;
}

int TianxiaScript::getWindowIsExist(Ifire* DM)
{
	TianxiaSingleton* tx = TianxiaSingleton::getInstance();
	QTableWidget* table = tx->table;

	_bstr_t bstr;
	bstr = DM->PskGetWndClass(this->lHWND);
	string str;
	str = (_bstr_t)bstr;
	if (str != "") {

		return 1;
	}
	else {
		table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("已掉线")));
		table->setItem(index - 1, 1, new QTableWidgetItem(QString::fromLocal8Bit("000008")));
	}

	return 0;
}

int TianxiaScript::findYaogan(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(230, 40, 320, 100, "摇杆.bmp|Yaogan.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(230, 40, 320, 100, "Yaogan.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "yaoganX=" << result[1].c_str();
	qDebug() << "yaoganY=" << result[2].c_str();

	if (x != -1) {
		Sleep(2000);

		return 1;
	}

	return 0;
}

int TianxiaScript::findKaichangPugong(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(300, 50, 400, 150, "开场普攻.bmp|KaichangPugong.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(300, 50, 400, 150, "KaichangPugong.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "kaichangPugongX=" << result[1].c_str();
	qDebug() << "kaichangPugongY=" << result[2].c_str();

	if (x != -1) {
		Sleep(2000);

		return 1;
	}

	return 0;
}

int TianxiaScript::findZhankaiBtn(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(500, 50, 600, 180, "展开按钮.bmp|ZhankaiBtn.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(500, 50, 600, 180, "ZhankaiBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "zhankaiX=" << result[1].c_str();
	qDebug() << "zhankaiY=" << result[2].c_str();
	this->fixNameBug(DM);
	if (authIDCardName(DM) == 1) {
		Sleep(1000);
		authIDCardNumber(DM);
		Sleep(1000);
		authPhoneNumber(DM);
		Sleep(1000);
		authQuerenBTN(DM);
		DM->PskMToEx(300, 290, 10, 10);
		DM->PskLClick();
		Sleep(3000);
	}
	if (x != -1) {
		if (this->stepIndex != TIANXIA_STEPS::CHANGGUI) {
			if (this->isZhuxianEnabled == true) {
				this->stepIndex = TIANXIA_STEPS::ZHUXIAN;
			}
			else {
				this->stepIndex = TIANXIA_STEPS::CHANGGUI;
			}

		}
		Sleep(2000);

		return 1;
	}

	return 0;
}

int TianxiaScript::find12Chongzhifanli(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;
	bstr = DM->PskFindPicE(420, 50, 520, 180, "ChongzhiFanli.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ChongzhiFanliX=" << result[1].c_str();
	qDebug() << "ChongzhiFanliY=" << result[2].c_str();

	if (x != -1) {
		Sleep(1000);

		return 1;
	}

	bstr = DM->PskFindPicE(0, 0, 60, 90, "Shuang.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "Shuang=" << result[1].c_str();
	qDebug() << "Shuang=" << result[2].c_str();

	if (x != -1) {
		Sleep(1000);

		return 1;
	}

	return 0;
}

int TianxiaScript::findBattery(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;
	bstr = DM->PskFindPicE(60, 0, 120, 80, "Battery.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "BatteryX=" << result[1].c_str();
	qDebug() << "BatteryY=" << result[2].c_str();

	if (x != -1) {
		Sleep(1000);

		return 1;
	}
	else {
		DM->PskMToEx(303, 15, 10, 10);
		DM->PskLClick();
	}

	return 0;
}

int TianxiaScript::zouGuangquan(Ifire* DM)
{
	TianxiaSingleton* tx = TianxiaSingleton::getInstance();
	QTableWidget* table = tx->table;


	table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("光圈")));

	DM->PskKDown(87);
	Sleep(1000);
	DM->PskKUp(87);
	Sleep(1000);
	DM->PskKDown(68);
	Sleep(500);
	DM->PskKUp(68);
	Sleep(1000);
	DM->PskKDown(83);
	Sleep(5000);
	DM->PskKUp(83);
	Sleep(1000);
	/*DM->PskKDown(65);
	Sleep(500);
	DM->PskKUp(65);
	Sleep(1000);*/
	DM->PskKDown(87);
	Sleep(1000);
	DM->PskKUp(87);
	Sleep(1000);
	/*DM->PskKDown(65);
	Sleep(500);
	DM->PskKUp(65);
	Sleep(1000);*/
	DM->PskKDown(87);
	Sleep(500);
	DM->PskKUp(87);
	Sleep(1000);
	DM->PskKDown(65);
	Sleep(500);
	DM->PskKUp(65);
	Sleep(1000);
	DM->PskKDown(87);
	Sleep(1000);
	DM->PskKUp(87);
	Sleep(1000);

	/*DM->PskKUp(87);
	DM->PskKUp(65);
	DM->PskKUp(68);
	DM->PskKUp(83);*/
	int tempCount = 0;
	while (findKaichangPugong(DM) == 0 && getIsEnded() == false) {
		DM->PskKPress(49);
		DM->PskKDown(87);
		Sleep(5000);
		if (tempCount > 100) {
			tempCount = 0;
			break;
		}

		if (findZhankaiBtn(DM) == 1) {
			return 0;
		}
	}

	while (findZhankaiBtn(DM) == 0 && getIsEnded() == false) {

		DM->PskKUp(87);
		DM->PskKUp(65);
		DM->PskKUp(68);
		DM->PskKUp(83);
		Sleep(1000);

		DM->PskKPress(49);
		Sleep(500);
		DM->PskKPress(49);
		Sleep(500);
		DM->PskKPress(49);
		Sleep(500);
		DM->PskKPress(49);
		Sleep(500);
		DM->PskKPress(49);
		Sleep(500);
		DM->PskKPress(49);
		Sleep(1000);

		if (tempCount > 100) {
			tempCount = 0;
			break;
		}
	}

	//_bstr_t bstr;
	//string str, size;
	//long x, y, l;

	/*DM->PskKPress(87);
	Sleep(1000);
	reload(DM);*/
	//std::vector<std::string> result;
	//bstr = DM->PskFindPicE(250, 200, 350, 250, "手机号.bmp", "000000", 0.9, 0);
	//str = (_bstr_t)bstr;

	//qDebug() << str.c_str();

	//result = CommonUtil::split(str, "|");

	//l = result.size();
	//size = CommonUtil::Long2STR(l);
	//if (l < 3) {
	//	return 0;
	//}

	//x = atol(result[1].c_str());
	//y = atol(result[2].c_str());

	//qDebug() << "shoujihaoX=" << result[1].c_str();
	//qDebug() << "shoujihaoX=" << result[2].c_str();

	//if (x != -1) {
	//	DM->PskMTo(x, y + 55);
	//	DM->PskLClick();
	//	Sleep(3000);

	//	return 1;
	//}

	return 0;
}

int TianxiaScript::selectCharacter(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;
	bstr = DM->PskFindPicE(500, 200, 600, 350, "放大镜按钮.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "FangdaJx=" << result[1].c_str();
	qDebug() << "FangdaJy=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x - 20, y + 80, 10, 10);
		DM->PskLClick();
		return 1;
	}

	return 0;
}

int TianxiaScript::zhuxianUseBTN(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(400, 200, 550, 350, "使用按钮.bmp|ShiyongBtn.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(400, 200, 550, 350, "ShiyongBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "shiyongJx=" << result[1].c_str();
	qDebug() << "shiyongJy=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		return 1;
	}

	return 0;
}

int TianxiaScript::yuandiFuhuo(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;

	bstr = DM->PskFindPicE(300, 40, 470, 100, "已死亡.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "yisix=" << result[1].c_str();
	qDebug() << "yisiy=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(2000);
	}

	bstr = DM->PskFindPicE(300, 40, 500, 100, "已死亡2.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "yisix=" << result[1].c_str();
	qDebug() << "yisiy=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(2000);
	}
	//else {
	//	return 0;
	//}

	/*bstr = DM->PskFindPicE(300, 40, 500, 100, "已死亡3.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
	return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "yisix=" << result[1].c_str();
	qDebug() << "yisiy=" << result[2].c_str();

	if (x != -1) {
	DM->PskMToEx(x + 2, y + 2, 10, 10);
	DM->PskLClick();
	Sleep(2000);
	}*/

	/*bstr = DM->PskFindPicE(300, 40, 500, 100, "已死亡4.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
	return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "yisix=" << result[1].c_str();
	qDebug() << "yisiy=" << result[2].c_str();

	if (x != -1) {
	DM->PskMToEx(x + 2, y + 2, 10, 10);
	DM->PskLClick();
	Sleep(2000);
	}*/

	bstr = DM->PskFindPicE(100, 100, 400, 300, "复活.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "yuandix=" << result[1].c_str();
	qDebug() << "yuandiy=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		return 1;
	}

	dangqianFuhuo(DM);

	return 0;
}

int TianxiaScript::yuandiFuhuoEx(Ifire* DM)
{
	getIsDead(DM);
	dangqianFuhuo(DM);
	bangdingFuhuo(DM);
	yuandiFuhuoPic(DM);

	return 0;
}

int TianxiaScript::dangqianFuhuo(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;

	bstr = DM->PskFindPicE(220, 200, 350, 300, "当前复活.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "dangqianFuhuoX=" << result[1].c_str();
	qDebug() << "dangqianFuhuoY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(2000);

		return 1;
	}

	return 0;
}



int TianxiaScript::yuandiFuhuoPic(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;

	//bstr = DM->PskFindPicE(220, 200, 350, 300, "YuandiFuhuo.bmp|YuandiFuhuo2.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(220, 200, 350, 300, "YuandiFuhuo2.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "YuandiFuhuoX=" << result[1].c_str();
	qDebug() << "YuandiFuhuoY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(2000);

		return 1;
	}




	return 0;
}

int TianxiaScript::bangdingFuhuo(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;

	//bstr = DM->PskFindPicE(280, 200, 420, 300, "绑定复活.bmp|BangdingFuhuo.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(280, 200, 420, 300, "BangdingFuhuo.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "bangdingFuhuoX=" << result[1].c_str();
	qDebug() << "bangdingFuhuoY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(2000);

		return 1;
	}




	return 0;
}

int TianxiaScript::getIsDead(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;

	bstr = DM->PskFindPicE(300, 10, 500, 120, "已死亡EX.bmp", "000000", 0.8, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "yisiExX=" << result[1].c_str();
	qDebug() << "yisiExY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(2000);

		return 1;
	}

	bstr = DM->PskFindPicE(300, 10, 500, 120, "已死亡EX2.bmp", "000000", 0.8, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "yisiExX=" << result[1].c_str();
	qDebug() << "yisiExY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(2000);

		return 1;
	}

	bstr = DM->PskFindPicE(300, 10, 500, 120, "已死亡.bmp", "000000", 0.8, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "yisix=" << result[1].c_str();
	qDebug() << "yisiy=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(2000);

		return 1;
	}

	bstr = DM->PskFindPicE(300, 10, 500, 120, "已死亡2.bmp|IsDead.bmp", "000000", 0.8, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "yisix=" << result[1].c_str();
	qDebug() << "yisiy=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(2000);

		return 1;
	}

	return 0;
}

int TianxiaScript::duihuaSuojin(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;
	bstr = DM->PskFindPicE(200, 150, 300, 300, "对话缩进.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "duihuasox=" << result[1].c_str();
	qDebug() << "duihuasoy=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		return 1;
	}

	return 0;
}

int TianxiaScript::tongjiClose(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;
	bstr = DM->PskFindPicE(400, 20, 520, 150, "TongjiClose.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "TongjiClose=" << result[1].c_str();
	qDebug() << "TongjiClose=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		return 1;
	}

	return 0;
}

int TianxiaScript::duihuaHuangtiao(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(10, 300, 60, 360, "对话条.bmp", "000000", 0.9, 0);
	//str = (_bstr_t)bstr;

	//qDebug() << str.c_str();

	//result = CommonUtil::split(str, "|");

	//l = result.size();
	//size = CommonUtil::Long2STR(l);
	//if (l < 3) {
	//	return 0;
	//}

	//x = atol(result[1].c_str());
	//y = atol(result[2].c_str());

	//qDebug() << "duihuaTx=" << result[1].c_str();
	//qDebug() << "duihuaTy=" << result[2].c_str();

	//if (x != -1) {
	//	DM->PskMToEx(x + 2, y + 2, 10, 10);
	//	DM->PskLClick();
	//	return 1;
	//}

	if (findZhankaiBtn(DM) == 1) {
		return 0;
	}

	bstr = DM->PskFindPicE(10, 300, 80, 360, "DuiHuaTiao.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "DuiHuaTiaoX=" << result[1].c_str();
	qDebug() << "DuiHuaTiaoY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		return 1;
	}

	/*bstr = DM->PskFindPicE(10, 300, 60, 360, "对话条2.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
	return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "duihuaT2x=" << result[1].c_str();
	qDebug() << "duihuaT2y=" << result[2].c_str();

	if (x != -1) {
	DM->PskMToEx(x + 2, y + 2, 10, 10);
	DM->PskLClick();
	return 1;
	}*/

	bstr = DM->PskFindPicE(400, 300, 550, 360, "DuiHuaTiaoRight.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "DuiHuaTiaoRightX=" << result[1].c_str();
	qDebug() << "DuiHuaTiaoRightY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		return 1;
	}
	return 0;
}

int TianxiaScript::shiliChaqi(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(150, 100, 300, 200, "势力插旗.bmp|ShiliChaqi.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(150, 100, 300, 200, "ShiliChaqi.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "shiliChaqiX=" << result[1].c_str();
	qDebug() << "shiliChaqiXY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(x + 40, y + 85);
		DM->PskLClick();
		return 1;
	}

	return 0;
}

int TianxiaScript::querenQiangzhi(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;
	bstr = DM->PskFindPicE(320, 120, 420, 220, "确认强制.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "querenQiangzhiX=" << result[1].c_str();
	qDebug() << "querenQiangzhiY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(340, 240);
		DM->PskLClick();
		return 1;
	}

	bstr = DM->PskFindPicE(220, 120, 320, 220, "重置副本.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "chongzhiFbX=" << result[1].c_str();
	qDebug() << "chongzhiFbY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(340, 240);
		DM->PskLClick();
		return 1;
	}
	return 0;
}

int TianxiaScript::zhuxianTuibenCancel(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;
	bstr = DM->PskFindPicE(200, 200, 300, 300, "ZhuxianTuibenCancel.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ZhuxianTuibenCancelX=" << result[1].c_str();
	qDebug() << "ZhuxianTuibenCancelY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		return 1;
	}


	return 0;
}

int TianxiaScript::findQiehuanBtn(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;
	bstr = DM->PskFindPicE(500, 300, 600, 400, "切换按钮.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "qiehuanX=" << result[1].c_str();
	qDebug() << "qiehuanY=" << result[2].c_str();

	if (x != -1) {
		Sleep(1000);
		return 1;
	}

	return 0;
}

int TianxiaScript::closeQiehuanBtn(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;
	bstr = DM->PskFindPicE(500, 300, 600, 400, "切换按钮.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "qiehuanX=" << result[1].c_str();
	qDebug() << "qiehuanY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(1000);
		return 1;
	}

	return 0;
}

int TianxiaScript::findYunshiCloseBtn(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;
	bstr = DM->PskFindPicE(500, 0, 600, 100, "YunshiCloseBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "YunshiCloseBtnX=" << result[1].c_str();
	qDebug() << "YunshiCloseBtnY=" << result[2].c_str();

	if (x != -1) {

		return 1;
	}

	return 0;
}

int TianxiaScript::newsClose(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;
	bstr = DM->PskFindPicE(480, 10, 600, 120, "NewsClose.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "NewsCloseX=" << result[1].c_str();
	qDebug() << "NewsCloseY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(1000);
		return 1;
	}

	return 0;
}

int TianxiaScript::clickYunshiCloseBtn(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;
	bstr = DM->PskFindPicE(500, 0, 600, 100, "YunshiCloseBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "YunshiCloseBtnX=" << result[1].c_str();
	qDebug() << "YunshiCloseBtnY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(1000);
		return 1;
	}

	return 0;
}

int TianxiaScript::hideTheOthers(Ifire* DM)
{
	generalClose(DM);
	if (findZhankaiBtn(DM) == 1) {
		DM->PskKPress(120);
		this->isHided = true;
	}

	return 0;
}

int TianxiaScript::taskGoumai(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(400, 200, 550, 350, "购买.bmp|GoumaiBtn.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(400, 200, 550, 350, "GoumaiBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "goumaiX=" << result[1].c_str();
	qDebug() << "goumaiY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		return 1;
	}


	bstr = DM->PskFindPicE(400, 200, 550, 350, "购买2.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "goumaiX=" << result[1].c_str();
	qDebug() << "goumaiY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		return 1;
	}

	return 0;
}

int TianxiaScript::zhuxianTask(Ifire* DM)
{

	TianxiaSingleton* tx = TianxiaSingleton::getInstance();
	QTableWidget* table = tx->table;

	if (isZhuxianEnabled == false) {
		if (findOpenMap(DM) == 1) {
			zhuxianIng = false;
			stepIndex = TIANXIA_STEPS::CHANGGUI;
		}

		return 0;
	}

	if (zhuxianSubScript(DM) == 1) {


		Sleep(1000);
		DM->PskLClick();





		return 1;
	}

	return 0;
}

int TianxiaScript::zhuxianSubScript(Ifire* DM)
{
	TianxiaSingleton* tianxia = TianxiaSingleton::getInstance();


	if (currentLevel == 0) {
		getLevel(DM);
		if (currentLevel > 1 && currentLevel < this->zhuxian_level) {
			tianxia->table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("主线任务")));
			stepIndex = TIANXIA_STEPS::ZHUXIAN;
		}
		/*if (currentLevel >= 43) {
		zhuxianIng = false;
		stepIndex = TIANXIA_STEPS::CHANGGUI;
		}*/
	}

	if (currentLevel >= this->zhuxian_level) {
		zhuxianIng = false;
		stepIndex = TIANXIA_STEPS::CHANGGUI;

		return 0;
	}

	zuduiClose(DM);
	zhuxianConfirmCircle(DM);
	zhuxianTuibenCancel(DM);
	clickYunshiCloseBtn(DM);
	generalClose(DM);
	shangchengClose(DM);

	if (jinruBtn(DM) == 1) {
		return 0;
	}

	if (dianjiTiaoguo(DM) == 1) {
		if (isZhuxianEnabled == false) {
			this->zhuxianIng = false;
			this->stepIndex = TIANXIA_STEPS::CHANGGUI;
			return 0;
		}
		return 0;
	}

	if (this->isInfuben) {
		tuichuDuiwu(DM);
	}

	yuandiFuhuo(DM);
	zhuxianZhanchangClose(DM);
	zhuxianJinben(DM);
	//zhuxianConfirmCircle(DM);
	//zhuxianInFuben(DM);

	zhuxianGuankan(DM);
	zhuxianUseBTN(DM);

	if (findZhuxianIn(DM) == 0) {

		if (findChangguiInZhuxian(DM) == 0) {
			renwuClose(DM);

			Sleep(1000);
			if (duihuaHuangtiao(DM) == 0) {
				DM->PskKPress(76);
				Sleep(3000);


			}

			if (zhuxianQinggong(DM) == 1) {
				return 0;
			}

			if (findChangguiInZhuxian(DM) == 1 && findZhuxianIn(DM) == 0) {
				DM->PskMTo(125, 80);
				DM->PskLClick();
				Sleep(2000);
			}

		}
		else {
			DM->PskMTo(125, 80);
			DM->PskLClick();
			Sleep(2000);

		}

	}

	if (findZhuxianIn(DM) == 1) {
		//tuijianJiadian(DM);
		if (zhuxian3RD(DM) == 1) {
			zhuxianIng = false;
			stepIndex = TIANXIA_STEPS::CHANGGUI;
			return 0;
		}


		zhuxianConfirmCircle(DM);
		int ret = zhuxianShangwuju(DM);
		if (ret == 0) {
			ret = zhuxianTianqiong(DM);
			mapClose(DM);
		}


		if (zhuxianJinxingIn(DM) == 0) {
			DM->PskMTo(540, 165);
			DM->PskLClick();
			Sleep(2000);
			zhuxianJieshouIn(DM);
			Sleep(1000);
			zhuxianGuankan(DM);
		}
		else {
			Sleep(2000);
			zhuxianUseBTN(DM);
			taskGoumai(DM);

			if (ret == 1) {
				DM->PskKDown(87);
				Sleep(1000);
				DM->PskKUp(87);
				DM->PskKPress(9);
				Sleep(1000);
				DM->PskKPress(49);
				Sleep(500);
				DM->PskKPress(49);
				Sleep(500);
				DM->PskKPress(49);
				Sleep(500);
				DM->PskKPress(49);
				Sleep(500);
				DM->PskKPress(49);
				Sleep(500);
				DM->PskKPress(49);
				Sleep(500);
			}

			if (zhuxianInFubenSub(DM) == 1) {
				if (ret == 2) {
					/*	DM->PskKDown(87);
					Sleep(3000);
					DM->PskKUp(87);
					Sleep(1000);
					DM->PskKDown(68);
					Sleep(3000);
					DM->PskKUp(68);
					Sleep(500);*/
					DM->PskMTo(20, 345);
					DM->PskLClick();
					Sleep(1000);
					DM->PskKDown(68);
					Sleep(500);
					DM->PskKPress(32);
					Sleep(500);
					DM->PskKUp(68);
					Sleep(2000);
					DM->PskKPress(9);
					Sleep(1000);
					DM->PskKPress(49);
					Sleep(500);
					DM->PskKPress(49);
					Sleep(500);
					DM->PskKPress(49);
					Sleep(500);
					DM->PskKPress(49);
					Sleep(500);
					DM->PskKPress(49);
					Sleep(500);
					DM->PskKPress(49);
					Sleep(500);
				}
			}


			return 1;
		}
	}

	/*if (findZhuxianIn(DM) == 1) {
	DM->PskKPress(76);
	}*/

	renwuClose(DM);
	duihuaSuojin(DM);
	return 0;
}

int TianxiaScript::zhuxianJinxingIn(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;

	//bstr = DM->PskFindPicE(70, 70, 200, 300, "主线任务IN.bmp|ZhuxianIn.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(70, 70, 200, 300, "ZhuxianIn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "zhuxianINx=" << result[1].c_str();
	qDebug() << "zhuxianINy=" << result[2].c_str();

	if (x != -1) {

		if (zhuxianSuojinIn(DM, x, y) == 2) {
			return 0;
		}
		Sleep(3000);
	}

	if (zhuxianZhang(DM) == 1) {
		if (xieliFuben(DM) == 1 && xieliFubenJindu(DM) == 1) {
			if (findWutongMap(DM) == 0) {
				DM->PskMTo(230, 310);
				DM->PskLClick();
				Sleep(2000);
				DM->PskMTo(340, 240);
				DM->PskLClick();
				Sleep(2000);
			}


		}
	}
	else {
		DM->PskMTo(125, 80);
		DM->PskLClick();
		Sleep(1000);
		if (zhuxianZhang(DM) == 0) {
			Sleep(1000);

			//bstr = DM->PskFindPicE(70, 70, 200, 300, "主线任务IN.bmp|ZhuxianIn.bmp", "000000", 0.9, 0);
			bstr = DM->PskFindPicE(70, 70, 200, 300, "ZhuxianIn.bmp", "000000", 0.9, 0);
			str = (_bstr_t)bstr;

			qDebug() << str.c_str();

			result = CommonUtil::split(str, "|");

			l = result.size();
			size = CommonUtil::Long2STR(l);
			if (l < 3) {
				return 0;
			}

			x = atol(result[1].c_str());
			y = atol(result[2].c_str());
			Sleep(1000);

			if (zhuxianZhiyin(DM, y) == 0) {
				return 0;
			}
		}
	}

	if (zhuxian3RD(DM) == 1) {
		zhuxianIng = false;
		stepIndex = TIANXIA_STEPS::CHANGGUI;
		return 0;
	}

	//bstr = DM->PskFindPicE(400, 250, 550, 350, "进行IN.bmp|JinxingIn.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(400, 250, 550, 350, "JinxingIn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "zhuxianINx=" << result[1].c_str();
	qDebug() << "zhuxianINy=" << result[2].c_str();

	if (x != -1) {
		DM->PskKDown(87);
		Sleep(1000);
		DM->PskKUp(87);
		Sleep(1000);
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(10000);
		return 1;
	}

	return 0;
}

int TianxiaScript::zhuxianHaoyou(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(400, 250, 550, 350, "进行IN.bmp|JinxingIn.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(400, 250, 550, 350, "JinxingIn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "zhuxianINx=" << result[1].c_str();
	qDebug() << "zhuxianINy=" << result[2].c_str();

	if (x != -1) {
		DM->PskKDown(87);
		Sleep(1000);
		DM->PskKUp(87);
		Sleep(1000);
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		return 1;
	}

	return 0;
}

int TianxiaScript::zhuxianZhang(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(30, 100, 220, 360, "主线章.bmp|ZhangChara2.bmp|ZhangChara1.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(30, 100, 220, 360, "ZhangChara2.bmp|ZhangChara1.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "zhuxianZhangX=" << result[1].c_str();
	qDebug() << "zhuxianZhangY=" << result[2].c_str();

	if (x != -1) {

		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		return 1;
	}


	return 0;
}

int TianxiaScript::xieliFuben(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(30, 100, 220, 360, "XieLiFuben.bmp|XieliFuben2.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "XieLiFubenX=" << result[1].c_str();
	qDebug() << "XieLiFubenY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);
		return 1;
	}


	return 0;
}


int TianxiaScript::xieliFubenJindu(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(180, 50, 300, 360, "XieliJindu.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "XieliJinduX=" << result[1].c_str();
	qDebug() << "XieliJinduY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);
		return 1;
	}


	return 0;
}

int TianxiaScript::zhuxianZhiyin(Ifire* DM, long pY)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(30, pY, 220, 360, "主线指引1.bmp|Zhiyin2.bmp|Zhiyin1.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(30, pY, 220, 360, "Zhiyin2.bmp|Zhiyin1.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "zhuxianZhiyinX=" << result[1].c_str();
	qDebug() << "zhuxianZhiyinY=" << result[2].c_str();

	if (x != -1) {

		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		return 1;
	}


	return 0;
}

int TianxiaScript::jinruBtn(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(450, 150, 550, 300, "进入战斗.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "zhuxianINx=" << result[1].c_str();
	qDebug() << "zhuxianINy=" << result[2].c_str();

	if (x != -1) {

		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		return 1;
	}

	return 0;
}

int TianxiaScript::zhuxianQinggong(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(150, 50, 300, 150, "轻功IN.bmp|QinggongIn.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(150, 50, 300, 150, "QinggongIn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "qinggongINx=" << result[1].c_str();
	qDebug() << "qinggongINy=" << result[2].c_str();

	if (x != -1) {

		zhuxianJinxingIn(DM);
		Sleep(1000);


		huidaoMenpai(DM);
		Sleep(10000);

		DM->PskKPress(32);
		Sleep(1000);
		/*DM->PskKPress(32);
		Sleep(1000);
		DM->PskKPress(32);
		Sleep(1000);*/

		return 1;
	}

	return 0;
}


int TianxiaScript::zhuxianShangwuju(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(200, 50, 300, 150, "尚武IN.bmp|ShangwuIn.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(200, 50, 300, 150, "ShangwuIn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "shangwuInx=" << result[1].c_str();
	qDebug() << "shangwuIny=" << result[2].c_str();

	if (x != -1) {

		/*DM->PskKDown(87);
		Sleep(5000);
		DM->PskKUp(87);*/

		//DM->PskLClick();
		return 1;
	}

	return 0;
}

int TianxiaScript::zhuxianTianqiong(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(50, 50, 200, 300, "天穹之上.bmp|TianqiongZhishang.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(50, 50, 200, 300, "TianqiongZhishang.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "tianqiongX=" << result[1].c_str();
	qDebug() << "tianqiongY=" << result[2].c_str();

	if (x != -1) {

		/*DM->PskKDown(87);
		Sleep(5000);
		DM->PskKUp(87);*/

		//DM->PskLClick();
		return 2;
	}

	return 0;
}


int TianxiaScript::zhuxianInFuben(Ifire* DM)
{
	if (zhuxianInFubenSub(DM) == 1) {
		Sleep(10000);

		DM->PskMTo(15, 350);
		Sleep(1000);
		DM->PskLClick();
		Sleep(3000);
		DM->PskKDown(87);
		Sleep(3000);
		DM->PskKUp(87);
		Sleep(3000);
		DM->PskKDown(65);
		Sleep(3000);
		DM->PskKUp(65);
		Sleep(1000);
		DM->PskKPress(9);
		Sleep(1000);
		DM->PskKPress(49);
		Sleep(200);
		DM->PskKPress(49);
		Sleep(200);
		DM->PskKPress(49);
		Sleep(200);
		DM->PskKPress(49);
		Sleep(200);
		DM->PskKPress(49);
		Sleep(1000);
		DM->PskKPress(51);
		Sleep(1000);
		DM->PskKPress(52);
		Sleep(1000);
		DM->PskKPress(53);
		Sleep(1000);
		DM->PskKPress(54);
		Sleep(1000);
		DM->PskKPress(55);
		Sleep(1000);
		DM->PskKPress(56);
		Sleep(1000);
		DM->PskKPress(57);

	}

	return 0;
}

int TianxiaScript::zhuxianInFubenSub(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(300, 20, 550, 90, "退副本.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "tuiFubenx=" << result[1].c_str();
	qDebug() << "tuiFubeny=" << result[2].c_str();

	if (x != -1) {

		/*DM->PskKDown(87);
		Sleep(5000);
		DM->PskKUp(87);*/

		//DM->PskLClick();
		return 1;
	}

	return 0;
}

int TianxiaScript::zhuxianJinben(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(400, 100, 550, 350, "主线进本.bmp|Jinru.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(400, 100, 550, 350, "Jinru.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "zhuxianJinBenx=" << result[1].c_str();
	qDebug() << "zhuxianJinBeny=" << result[2].c_str();

	if (x != -1) {

		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		return 1;
	}

	//bstr = DM->PskFindPicE(0, 150, 150, 300, "主线进本.bmp|Jinru.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(0, 150, 150, 300, "Jinru.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "zhuxianJinBenx=" << result[1].c_str();
	qDebug() << "zhuxianJinBeny=" << result[2].c_str();

	if (x != -1) {

		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		return 1;
	}

	return 0;
}

int TianxiaScript::zhuxianZhanchangClose(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(400, 30, 550, 150, "战场关闭.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "zhanchangClosex=" << result[1].c_str();
	qDebug() << "zhanchangClosey=" << result[2].c_str();

	if (x != -1) {

		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		return 1;
	}

	return 0;
}

int TianxiaScript::renwuClose(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(450, 10, 580, 100, "任务关闭.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "renwuCloseX=" << result[1].c_str();
	qDebug() << "renwuCloseY=" << result[2].c_str();

	if (x != -1) {

		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		return 1;
	}

	return 0;
}

int TianxiaScript::jishouQuhui(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(150, 290, 210, 350, "寄售取回.bmp|JishouQuhui.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(150, 290, 210, 350, "JishouQuhui.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "jishouQuhuiX=" << result[1].c_str();
	qDebug() << "jishouQuhuiY=" << result[2].c_str();

	if (x != -1) {

		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		return 1;
	}

	return 0;
}

int TianxiaScript::sellClose(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(260, 20, 420, 200, "出售关闭按钮.bmp|SellCloseBtn.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(260, 20, 420, 200, "SellCloseBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "sellCloseX=" << result[1].c_str();
	qDebug() << "sellCloseY=" << result[2].c_str();

	if (x != -1) {

		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		return 1;
	}

	return 0;
}

int TianxiaScript::xiajiaClose(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(150, 280, 220, 350, "下架取消.bmp|XiajiaQuxiao.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(150, 280, 220, 350, "XiajiaQuxiao.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "xiajiaQuxiaoX=" << result[1].c_str();
	qDebug() << "xiajiaQuxiaoY=" << result[2].c_str();

	if (x != -1) {

		DM->PskMTo(295, 50);
		DM->PskLClick();
		return 1;
	}

	bstr = DM->PskFindPicE(250, 50, 350, 150, "ShangjiaCancelBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ShangjiaCancelBtnX=" << result[1].c_str();
	qDebug() << "ShangjiaCancelBtnY=" << result[2].c_str();

	if (x != -1) {

		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		return 1;
	}

	return 0;
}




int TianxiaScript::saomaClose(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(250, 50, 350, 150, "扫码支付.bmp|SaomaZhifu.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(250, 50, 350, 150, "SaomaZhifu.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "saomaCloseX=" << result[1].c_str();
	qDebug() << "saomaCloseY=" << result[2].c_str();

	if (x != -1) {

		DM->PskMTo(410, 75);
		DM->PskLClick();
		return 1;
	}

	return 0;
}


int TianxiaScript::zuduiClose(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(450, 10, 580, 100, "组队关闭.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "zuduiCloseX=" << result[1].c_str();
	qDebug() << "zuduiCloseY=" << result[2].c_str();

	if (x != -1) {

		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		return 1;
	}

	return 0;
}

int TianxiaScript::pindaoClose(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(200, 50, 350, 150, "PindaoXuanze.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "PindaoXuanzeX=" << result[1].c_str();
	qDebug() << "PindaoXuanzeY=" << result[2].c_str();

	if (x != -1) {

		DM->PskMTo(295, 240);
		DM->PskLClick();
		return 1;
	}

	return 0;
}

int TianxiaScript::shangchengClose(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(340, 0, 450, 100, "商城框.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "shangchengKX=" << result[1].c_str();
	qDebug() << "shangchengKY=" << result[2].c_str();

	if (x != -1) {

		DM->PskMTo(525, 35);
		DM->PskLClick();
		return 1;
	}

	return 0;
}

int TianxiaScript::richangClose(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(450, 10, 600, 100, "日常关闭按钮.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "richangCloseX=" << result[1].c_str();
	qDebug() << "richangCloseY=" << result[2].c_str();

	if (x != -1) {

		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		return 1;
	}

	//bstr = DM->PskFindPicE(350, 50, 450, 150, "活力完成.bmp|HuoliWanchengBtn.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(350, 50, 450, 150, "HuoliWanchengBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "huoliX=" << result[1].c_str();
	qDebug() << "huoliY=" << result[2].c_str();

	if (x != -1) {

		DM->PskKPress(75);
		Sleep(2000);
		return 1;
	}

	return 0;
}

int TianxiaScript::dazaoClose(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(450, 10, 600, 100, "打造关闭.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "dazaoCloseX=" << result[1].c_str();
	qDebug() << "dazaoCloseY=" << result[2].c_str();

	if (x != -1) {

		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		return 1;
	}



	return 0;
}

int TianxiaScript::jiagaoTishiCancel(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(200, 120, 450, 250, "价高提示.bmp|JiagaoTishi.bmp|JiagaoTishi2.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(280, 120, 450, 250, "JiagaoTishi.bmp|JiagaoTishi2.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "jiagaoX=" << result[1].c_str();
	qDebug() << "jiagaoY=" << result[2].c_str();

	if (x != -1) {

		DM->PskMTo(250, 240);
		DM->PskLClick();
		Sleep(1000);
		return 1;
	}



	return 0;
}

int TianxiaScript::zhenpinCancel(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(200, 120, 300, 250, "ZhenpinZhuangbei.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ZhenpinZhuangbeiX=" << result[1].c_str();
	qDebug() << "ZhenpinZhuangbeiY=" << result[2].c_str();

	if (x != -1) {

		DM->PskMTo(250, 240);
		DM->PskLClick();
		Sleep(1000);
		return 1;
	}



	return 0;
}

int TianxiaScript::zhenpinConfirm(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(200, 120, 300, 250, "ZhenpinZhuangbei.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ZhenpinZhuangbeiX=" << result[1].c_str();
	qDebug() << "ZhenpinZhuangbeiY=" << result[2].c_str();

	if (x != -1) {

		DM->PskMTo(350, 240);
		DM->PskLClick();
		Sleep(1000);
		return 1;
	}
	else {
		DM->PskMTo(250, 240);
		DM->PskLClick();
		Sleep(1000);
	}



	return 0;
}

int TianxiaScript::jiagaoTishiConfirm(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(200, 120, 320, 250, "价高提示.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "jiagaoX=" << result[1].c_str();
	qDebug() << "jiagaoY=" << result[2].c_str();

	if (x != -1) {

		DM->PskMTo(350, 240);
		DM->PskLClick();
		Sleep(1000);
		return 1;
	}



	return 0;
}

int TianxiaScript::goumaiClose(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(200, 180, 260, 280, "GoumaiShuliang.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "GoumaiShuliangX=" << result[1].c_str();
	qDebug() << "GoumaiShuliangY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(375, 45);
		DM->PskLClick();
		return 1;
	}

	return 0;
}

int TianxiaScript::yuyiClose(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(470, 10, 550, 100, "羽翼关闭.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "yuyiGuanbiX=" << result[1].c_str();
	qDebug() << "yuyiGuanbiY=" << result[2].c_str();

	if (x != -1) {

		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		return 1;
	}

	return 0;
}


int TianxiaScript::zhuxianConfirmCircle(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(200, 200, 350, 260, "确认圈.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "querenQuanINx=" << result[1].c_str();
	qDebug() << "querenQuanINy=" << result[2].c_str();

	if (x != -1) {

		DM->PskMTo(x + 25, y + 2);
		DM->PskLClick();

		Sleep(1000);

	}

	passConfirm(DM);
	return 0;
}

int TianxiaScript::passConfirm(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;



	std::vector<std::string> result;
	bstr = DM->PskFindPicE(490, 280, 570, 380, "PassConfirm.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "PassConfirmX=" << result[1].c_str();
	qDebug() << "PassConfirmY=" << result[2].c_str();

	if (x != -1) {

		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();

		Sleep(10000);
		return 1;
	}
	else {
		if (findZhankaiBtn(DM) == 1) {
			return 0;
		}

		DM->PskMTo(525, 300);
		DM->PskLClick();
	}

	return 0;
}

int TianxiaScript::shimenConfirmCircle(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(200, 200, 350, 285, "师门圈.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "SMquerenQuanINx=" << result[1].c_str();
	qDebug() << "SMquerenQuanINy=" << result[2].c_str();

	if (x != -1) {

		DM->PskMTo(x + 25, y + 2);
		DM->PskLClick();

		Sleep(10000);
		return 1;
	}
	else {
		passConfirm(DM);
	}

	return 0;
}

int TianxiaScript::zidongPipei(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	/*bstr = DM->PskFindPicE(430, 250, 520, 360, "密探匹配.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
	return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "mitanPipeiX=" << result[1].c_str();
	qDebug() << "mitanPipeiX=" << result[2].c_str();

	if (x != -1) {


	Sleep(3000);
	if (jingjiPipeiIng(DM) == 0) {
	tuichuDuiwu(DM);
	}

	return 0;
	}*/


	//bstr = DM->PskFindPicE(350, 250, 500, 350, "自动匹配.bmp|ZidongPipei.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(350, 250, 500, 350, "ZidongPipei.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ZiDongPiPeix=" << result[1].c_str();
	qDebug() << "ZiDongPiPeiy=" << result[2].c_str();

	if (x != -1) {

		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(1000);
		DM->PskMTo(485, 125);
		DM->PskLClick();
		Sleep(1000);
		DM->PskMTo(485, 175);
		DM->PskLClick();
		Sleep(1000);
		DM->PskMTo(485, 225);
		DM->PskLClick();
		Sleep(1000);
		DM->PskMTo(485, 275);
		DM->PskLClick();

		Sleep(10000);


		while (dengdaiPipei(DM) == 1 && getIsEnded() == false) {
			DM->PskMTo(125, 230);
			DM->PskLClick();
			Sleep(1000);
			DM->PskMTo(125, 195);
			DM->PskLClick();
			Sleep(1000);
			DM->PskMTo(420, 350);
			DM->PskLClick();
			Sleep(1000);
			DM->PskMTo(485, 125);
			DM->PskLClick();
			Sleep(1000);
			DM->PskMTo(485, 175);
			DM->PskLClick();
			Sleep(1000);
			DM->PskMTo(485, 225);
			DM->PskLClick();
			Sleep(1000);
			DM->PskMTo(485, 275);
			DM->PskLClick();
			mitanCounter++;
			if (mitanCounter > 50) {
				scriptIndex++;
				break;
			}
		}


		return 1;
	}
	else {
		Sleep(1000);
		DM->PskMTo(485, 125);
		DM->PskLClick();
		Sleep(1000);
		DM->PskMTo(485, 175);
		DM->PskLClick();
		Sleep(1000);
		DM->PskMTo(485, 225);
		DM->PskLClick();
		Sleep(1000);
		DM->PskMTo(485, 275);
		DM->PskLClick();

		Sleep(10000);

		while (dengdaiPipei(DM) == 1 && getIsEnded() == false) {
			DM->PskMTo(125, 230);
			DM->PskLClick();
			Sleep(1000);
			DM->PskMTo(125, 195);
			DM->PskLClick();
			Sleep(1000);
			DM->PskMTo(420, 350);
			DM->PskLClick();
			Sleep(1000);
			DM->PskMTo(485, 125);
			DM->PskLClick();
			Sleep(1000);
			DM->PskMTo(485, 175);
			DM->PskLClick();
			Sleep(1000);
			DM->PskMTo(485, 225);
			DM->PskLClick();
			Sleep(1000);
			DM->PskMTo(485, 275);
			DM->PskLClick();
			mitanCounter++;
			if (mitanCounter > 50) {
				scriptIndex++;
				break;
			}
		}
	}

	return 0;
}

int TianxiaScript::jingjiPipeiIng(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(100, 50, 200, 150, "竞技匹配ING.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "jingjiPipeiX=" << result[1].c_str();
	qDebug() << "jingjiPipeiY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);
		return 1;
	}

	return 0;
}

int TianxiaScript::isInMitan(Ifire* DM)
{
	if (isInJiuli(DM) == 1) {
		return 0;
	}

	/*if (findDuiwuWnd(DM) == 0) {
	DM->PskKPress(84);
	}

	if (findDuiwuWnd(DM) == 1) {
	Sleep(1000);
	if (findMitanTarget(DM) == 1) {

	generalClose(DM);

	return 1;
	}

	}

	generalClose(DM);*/

	return 1;
}

int TianxiaScript::findMapShili(Ifire* DM)
{


	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(465, 80, 520, 180, "HuiShiLi.bmp|HuishiliBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "HuiShiLiX=" << result[1].c_str();
	qDebug() << "HuiShiLiY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);
		return 1;
	}

	return 0;
}


int TianxiaScript::isInJiuli(Ifire* DM)
{
	renwuClose(DM);
	mapClose(DM);
	ChuangShiliWnd(DM);
	DM->PskKPress(77);
	Sleep(2000);

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(40, 160, 100, 300, "地图搜索按钮.bmp|DitusousuoBtn.bmp", "000000", 0.9, 0);

	bstr = DM->PskFindPicE(40, 160, 100, 300, "DitusousuoBtn.bmp|DituSousuoBtn2.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ditusousuoX=" << result[1].c_str();
	qDebug() << "ditusousuoY=" << result[2].c_str();

	if (x != -1) {

		if (findMapShili(DM) == 1) {
			return 1;
		}

	}

	mapClose(DM);

	return 0;
}



int TianxiaScript::findMitanTarget(Ifire* DM)
{


	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(100, 50, 200, 150, "MitanTG.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "MitanTGx=" << result[1].c_str();
	qDebug() << "MitanTy=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);
		return 1;
	}

	return 0;
}

int TianxiaScript::findJianmu(Ifire* DM)
{


	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(120, 200, 200, 300, "JianMu.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "JianMuX=" << result[1].c_str();
	qDebug() << "JianMuY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);
		return 1;
	}

	return 0;
}

int TianxiaScript::findDuiwuWnd(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(250, 10, 350, 100, "DuiwuWnd.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "DuiwuWndX=" << result[1].c_str();
	qDebug() << "DuiwuWndY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);
		return 1;
	}

	return 0;
}


int TianxiaScript::dahuangGuaiti(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(240, 90, 350, 150, "大荒怪题.bmp|DahuangGuaiti.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(240, 90, 350, 150, "DahuangGuaiti.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "DaHuangGuaiTiX=" << result[1].c_str();
	qDebug() << "DaHuangGuaiTiY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(x + 60, y + 70);
		DM->PskLClick();
		Sleep(1000);
		DM->PskMTo(435, 115);
		DM->PskLClick();
		Sleep(1000);
		return 1;
	}

	return 0;
}

int TianxiaScript::dengdaiPipei(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(350, 250, 500, 350, "取消匹配.bmp|QuxiaoPipei.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(350, 250, 500, 350, "QuxiaoPipei.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "QuXiaoPiPeiX=" << result[1].c_str();
	qDebug() << "QuXiaoPiPeiY=" << result[2].c_str();

	if (x != -1) {

		Sleep(10000);
		return 1;
	}

	return 0;
}

int TianxiaScript::updateSkill(Ifire* DM)
{
	if (findJinengWnd(DM) == 0) {
		DM->PskKPress(80);
		Sleep(3000);
	}

	if (findJinengWnd(DM) == 1) {
		quanbuShengjiBtn(DM);
		Sleep(1000);
		closeJinengWnd(DM);
		Sleep(1000);
	}

	this->scriptIndex++;
	return 0;
}

int TianxiaScript::updateSkillNormal(Ifire* DM)
{
	if (findJinengWnd(DM) == 0) {
		DM->PskKPress(80);
		Sleep(3000);
	}

	if (findJinengWnd(DM) == 1) {
		quanbuShengjiBtn(DM);
		Sleep(1000);
		closeJinengWnd(DM);
		Sleep(1000);
	}
	return 0;
}

int TianxiaScript::quanbuShengjiBtn(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(440, 280, 520, 360, "全部升级.bmp|QuanbuShengji.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(440, 280, 520, 360, "QuanbuShengji.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "quanbuShengjiX=" << result[1].c_str();
	qDebug() << "quanbuShengjiY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(1000);

		return 1;
	}

	return 0;
}

int TianxiaScript::lingquYoujian(Ifire* DM)
{
	if (findYoujianWnd(DM) == 0) {
		DM->PskKPress(71);
		Sleep(3000);
	}

	if (findYoujianWnd(DM) == 1) {
		youjianLingquBtn(DM);
		Sleep(1000);
		closeYoujianWnd(DM);
		Sleep(1000);
		scriptIndex++;
	}

	if (findXiaoxiWnd(DM) == 1) {
		//youjianLingquBtn(DM);
		Sleep(1000);
		closeXiaoxiWnd(DM);
		Sleep(1000);
		scriptIndex++;
	}
	return 0;
}

int TianxiaScript::jinhuanJun(Ifire* DM)
{
	if (findShangchengWnd(DM) == 0) {
		DM->PskKPress(89);
		Sleep(1000);
		DM->PskMTo(545, 205);
		DM->PskLClick();
		Sleep(3000);
	}

	if (findShangchengWnd(DM) == 1) {
		DM->PskMTo(340, 70);
		DM->PskLClick();
		Sleep(1000);


		if (jhjGaoshu(DM) == 1) {
			shangchengGoumai(DM);
			Sleep(2000);
		}
		if (jhjLeizuan(DM) == 1) {
			shangchengGoumai(DM);
			Sleep(2000);
		}
		/*if (jhjXixinshi(DM) == 1) {
		shangchengGoumai(DM);
		Sleep(2000);
		}*/


		Sleep(1000);
		if (yuanbaoBuzu(DM) == 1) {

		}
		else if (duihuanJunziWnd(DM) == 1) {

		}

		quxiaoClose(DM);

		Sleep(2000);
		shangchengClose(DM);
		//closeShangchengWnd(DM);
		Sleep(1000);
		scriptIndex++;
	}


	return 0;
}

int TianxiaScript::findJishouWnd(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(250, 20, 350, 100, "寄售窗口.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "shangchengWndX=" << result[1].c_str();
	qDebug() << "shangchengWndY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);
		return 1;
	}

	return 0;
}

int TianxiaScript::shangjiaChenggong(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(250, 80, 350, 160, "上架成功.bmp|ShangjiaChenggong.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(250, 80, 350, 160, "ShangjiaChenggong.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "shangjiaChenggongX=" << result[1].c_str();
	qDebug() << "shangjiaChenggongY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(305, 255);
		DM->PskLClick();
		Sleep(1000);
		DM->PskMTo(330, 255);
		DM->PskLClick();
		Sleep(1000);
		return 1;
	}

	return 0;
}

int TianxiaScript::shangjia(Ifire* DM)
{
	if (findJishouWnd(DM) == 0) {
		DM->PskKPress(89);
		Sleep(1000);
		DM->PskMTo(545, 155);
		DM->PskLClick();
		Sleep(3000);
	}

	if (findJishouWnd(DM) == 1) {
		DM->PskMTo(185, 65);
		DM->PskLClick();
		Sleep(2000);

		if (this->mengyan == true) {
			kaweiMY(DM);
		}

		long pX = 410;
		long pY = 120;
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) {

				DM->PskMTo(pX + j * 40, pY + i * 40);
				//DM->PskMTo(pX,pY);
				DM->PskLClick();

				Sleep(3000);

				if (findTanweiFei(DM) == 0) {
					shangchengClose(DM);
					scriptIndex++;
					return 0;
				}

				if (this->jianding == false) {
					if (findJiandingDi(DM) == 1) {
						tanweiClose(DM);
						continue;
					}
				}

				if (this->qicai == false) {
					if (findQiCai(DM) == 1) {
						tanweiClose(DM);
						continue;
					}
				}

				if (findShoujiaItem(DM) == 1) {
					DM->PskMTo(365, 80);
					DM->PskLClick();
					continue;
				}

				if (findTanweiFei(DM) == 1) {
					shangjiaSubScript(DM);
					Sleep(1000);
				}

				sellClose(DM);


				Sleep(1000);
			}
		}
	}

	shangchengClose(DM);
	scriptIndex++;
	return 0;
}

int TianxiaScript::kaweiMY(Ifire* DM) {
	kaweiMYSub(DM);
	Sleep(2000);
	DM->PskMTo(225, 300);
	DM->PskLClick();
	Sleep(2000);
	shangjiaChenggong(DM);

	return 0;
}

int TianxiaScript::findTanweiFei(Ifire* DM) {
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(130, 250, 200, 330, "摊位费.bmp|Tanweifei.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(130, 250, 200, 330, "Tanweifei.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "tanweiX=" << result[1].c_str();
	qDebug() << "tanweiY=" << result[2].c_str();

	if (x != -1) {


		Sleep(1000);
		return 1;
	}

	return 0;
}

int TianxiaScript::tanweiClose(Ifire* DM) {
	if (findTanweiFei(DM) == 1) {
		DM->PskMTo(300, 80);
		DM->PskLClick();
	}

	return 0;
}


int TianxiaScript::kaweiMYSub(Ifire* DM) {
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(380, 80, 530, 320, "卡位梦魇.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "kaweiMengyanX=" << result[1].c_str();
	qDebug() << "kaweiMengyanY=" << result[2].c_str();

	if (x != -1) {

		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(1000);
		return 1;
	}

	return 0;
}

int TianxiaScript::xiajia(Ifire* DM)
{
	if (findJishouWnd(DM) == 0) {
		DM->PskKPress(89);
		Sleep(1000);
		DM->PskMTo(545, 155);
		DM->PskLClick();
		Sleep(3000);
	}

	if (findJishouWnd(DM) == 1) {
		DM->PskMTo(185, 65);
		DM->PskLClick();
		Sleep(2000);

		long pX = 90;
		long pY = 120;
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 2; j++) {
				DM->PskMTo(pX + j * 135, pY + i * 50);
				DM->PskLClick();
				Sleep(1000);
				int jishouRet = jishouQuhui(DM);
				if (jishouRet == 1) {
					j--;
				}

				if (jishouRet == 0 && xiajiaClose(DM) == 0) {
					scriptIndex++;
					return 0;
				}

				if (this->jianding == false) {
					if (findJiandingDi(DM) == 1) {
						xiajiaBtn(DM);
					}
				}

				if (this->qicai == false) {
					if (findQiCai(DM) == 1) {
						xiajiaBtn(DM);
					}
				}
				Sleep(1000);
				xiajiaClose(DM);
			}
		}
	}

	shangchengClose(DM);
	scriptIndex++;
	return 0;
}

int TianxiaScript::shangjiaSubScript(Ifire* DM) {
	int sellPrice = getSellPrice(DM);
	int sellingPrice = getSellingPrice(DM);

	int temp = 0;

	if (sellingPrice <= 300) {
		tanweiClose(DM);
		return 0;
	}

	while (sellPrice > sellingPrice && getIsEnded() == false) {
		DM->PskMTo(220, 240);
		DM->PskLClick();

		Sleep(2000);

		sellPrice = getSellPrice(DM);
		sellingPrice = getSellingPrice(DM);

		temp++;
		if (temp >= 10) {
			temp = 0;
			break;
		}
	}

	temp = 0;
	while (sellPrice < sellingPrice && getIsEnded() == false) {
		DM->PskMTo(285, 240);
		DM->PskLClick();

		Sleep(2000);

		sellPrice = getSellPrice(DM);
		sellingPrice = getSellingPrice(DM);

		temp++;
		if (temp >= 10) {
			temp = 0;
			break;
		}
	}

	Sleep(2000);
	DM->PskMTo(225, 300);
	DM->PskLClick();
	Sleep(2000);
	shangjiaChenggong(DM);

	return 0;
}


int TianxiaScript::saoJishou(Ifire* DM)
{
	if (findJishouWnd(DM) == 0) {
		DM->PskKPress(89);
		Sleep(1000);
		DM->PskMTo(545, 155);
		DM->PskLClick();
		Sleep(3000);
	}

	if (findJishouWnd(DM) == 1) {
		Sleep(2000);
		int temp = 0;
		while (saoSubScript(DM) == 1 && getIsEnded() == false) {
			Sleep(2000);
			temp++;
			if (temp > 5) {
				break;
			}
		}

		xiaofeiQueren(DM);
	}

	scriptIndex++;
	return 0;
}

int TianxiaScript::saoSubScript(Ifire* DM) {
	int money = getSaohuoJunzi(DM);

	if (this->goldController != 0) {
		if (money > this->goldController) {
			return 0;
		}
	}


	Sleep(2000);
	DM->PskMTo(120, 100);
	DM->PskLClick();
	Sleep(1000);
	DM->PskMTo(220, 140);
	DM->PskLClick();
	Sleep(1000);

	if (this->sao == "MYZL") {
		HWND hFocusHwnd = (HWND)lHWND;
		const wchar_t * msgTemp = L"梦";
		PostMessageW(hFocusHwnd, WM_CHAR, *msgTemp, 1);
		Sleep(1000);
		msgTemp = L"魇";
		PostMessageW(hFocusHwnd, WM_CHAR, *msgTemp, 1);

		Sleep(1000);

		DM->PskMTo(420, 140);
		DM->PskLClick();

		Sleep(1000);

		DM->PskMTo(230, 180);
		DM->PskLClick();

		Sleep(1000);
	}

	if (this->sao == "CYHY") {
		HWND hFocusHwnd = (HWND)lHWND;
		const wchar_t * msgTemp = L"赤";
		PostMessageW(hFocusHwnd, WM_CHAR, *msgTemp, 1);
		Sleep(1000);
		msgTemp = L"焰";
		PostMessageW(hFocusHwnd, WM_CHAR, *msgTemp, 1);

		Sleep(1000);

		DM->PskMTo(420, 140);
		DM->PskLClick();

		Sleep(1000);

		DM->PskMTo(230, 180);
		DM->PskLClick();

		Sleep(1000);
	}

	if (this->sao == "7C") {
		HWND hFocusHwnd = (HWND)lHWND;
		const wchar_t * msgTemp = L"七";
		PostMessageW(hFocusHwnd, WM_CHAR, *msgTemp, 1);
		Sleep(1000);
		msgTemp = L"彩";
		PostMessageW(hFocusHwnd, WM_CHAR, *msgTemp, 1);
		Sleep(1000);
		msgTemp = L"果";
		PostMessageW(hFocusHwnd, WM_CHAR, *msgTemp, 1);

		Sleep(1000);

		DM->PskMTo(420, 140);
		DM->PskLClick();

		Sleep(1000);

		DM->PskMTo(230, 180);
		DM->PskLClick();

		Sleep(1000);
	}

	if (this->sao == "JDFD") {
		HWND hFocusHwnd = (HWND)lHWND;
		const wchar_t * msgTemp = L"鉴";
		PostMessageW(hFocusHwnd, WM_CHAR, *msgTemp, 1);
		Sleep(1000);
		msgTemp = L"定";
		PostMessageW(hFocusHwnd, WM_CHAR, *msgTemp, 1);

		Sleep(1000);

		DM->PskMTo(420, 140);
		DM->PskLClick();

		Sleep(1000);

		DM->PskMTo(230, 180);
		DM->PskLClick();

		Sleep(1000);
	}

	if (this->sao == "JN") {
		HWND hFocusHwnd = (HWND)lHWND;
		const wchar_t * msgTemp = L"金";
		PostMessageW(hFocusHwnd, WM_CHAR, *msgTemp, 1);
		Sleep(1000);
		msgTemp = L"牛";
		PostMessageW(hFocusHwnd, WM_CHAR, *msgTemp, 1);

		Sleep(1000);

		DM->PskMTo(420, 140);
		DM->PskLClick();

		Sleep(1000);

		DM->PskMTo(230, 180);
		DM->PskLClick();

		Sleep(1000);
	}

	int price = getSaohuoPrice(DM);
	if (this->safeJunzi != 0) {
		if (price >= this->safeJunzi) {
			return 0;
		}
	}

	int flag = 0;
	if (price == 0) {
		price = getSaohuoPriceEx(DM);
		flag = 1;
	}
	if (price == 0) {
		return 0;
	}

	int pointer = 0;
	pointer = this->saoPointer;
	if (flag != 1) {
		saohuoPointSelector(DM, pointer);
		Sleep(1000);
	}

	int number = money / price;

	if (money > price) {
		DM->PskMTo(450, 310);
		DM->PskLClick();
		Sleep(2000);

		saoJishouSelecter(DM, number);
	}
	else {
		return 0;
	}

	return 1;
}

int TianxiaScript::saoJishouSelecter(Ifire* DM, int number) {
	int hundred = number / 100;
	int ten = (number - 100 * hundred) / 10;
	int one = number - 100 * hundred - 10 * ten;

	DM->PskMTo(315, 230);
	DM->PskLClick();
	Sleep(1000);
	digitClicker(DM, hundred);
	Sleep(1000);
	digitClicker(DM, ten);
	Sleep(1000);
	digitClicker(DM, one);
	Sleep(1000);
	DM->PskMTo(435, 280);
	DM->PskLClick();
	Sleep(1000);
	DM->PskMTo(435, 280);
	DM->PskLClick();
	Sleep(1000);
	DM->PskMTo(335, 300);
	DM->PskLClick();
	Sleep(1000);

	return 0;
}

int TianxiaScript::saohuoPointSelector(Ifire* DM, int pointer) {
	int digit = 0;
	if (pointer == 0) {
		digit = index;
		if (digit > 20)
		{
			digit = digit - 10;
		}
		if (digit > 10)
		{
			digit = digit - 10;
		}
		if (digit > 8) {
			digit = digit - 8;
		}
	}
	else {
		digit = pointer;
	}


	switch (digit) {

	case 1: {
		DM->PskMTo(280, 110);
		DM->PskLClick();
	}
			break;
	case 2: {
		DM->PskMTo(450, 110);
		DM->PskLClick();
	}
			break;
	case 3: {
		DM->PskMTo(280, 165);
		DM->PskLClick();
	}
			break;
	case 4: {
		DM->PskMTo(450, 165);
		DM->PskLClick();
	}
			break;
	case 5: {
		DM->PskMTo(280, 210);
		DM->PskLClick();
	}
			break;
	case 6: {
		DM->PskMTo(450, 210);
		DM->PskLClick();
	}
			break;
	case 7: {
		DM->PskMTo(280, 265);
		DM->PskLClick();
	}
			break;
	case 8: {
		DM->PskMTo(450, 265);
		DM->PskLClick();
	}
			break;
	}

	return 0;
}

int TianxiaScript::digitClicker(Ifire* DM, int digit) {

	switch (digit) {
	case 0: {
		DM->PskMTo(395, 280);
		DM->PskLClick();
	}
			break;
	case 1: {
		DM->PskMTo(350, 180);
		DM->PskLClick();
	}
			break;
	case 2: {
		DM->PskMTo(395, 180);
		DM->PskLClick();
	}
			break;
	case 3: {
		DM->PskMTo(435, 180);
		DM->PskLClick();
	}
			break;
	case 4: {
		DM->PskMTo(350, 215);
		DM->PskLClick();
	}
			break;
	case 5: {
		DM->PskMTo(395, 215);
		DM->PskLClick();
	}
			break;
	case 6: {
		DM->PskMTo(435, 215);
		DM->PskLClick();
	}
			break;
	case 7: {
		DM->PskMTo(350, 250);
		DM->PskLClick();
	}
			break;
	case 8: {
		DM->PskMTo(395, 250);
		DM->PskLClick();
	}
			break;
	case 9: {
		DM->PskMTo(435, 250);
		DM->PskLClick();
	}
			break;
	}
	return 0;
}

int TianxiaScript::shangchengGoumai(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(420, 280, 500, 360, "ShangchengGoumaiBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "shangchengGoumaiX=" << result[1].c_str();
	qDebug() << "shangchengGoumaiY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(1000);
		return 1;
	}

	return 0;
}

int TianxiaScript::xiajiaBtn(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(220, 280, 300, 360, "XJiaBtn.bmp|XiajiaBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "XJiaBtnX=" << result[1].c_str();
	qDebug() << "XJiaBtnY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(1000);
		return 1;
	}

	return 0;
}

int TianxiaScript::findShoujiaItem(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(180, 200, 260, 290, "ShajPrice.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ShajPriceX=" << result[1].c_str();
	qDebug() << "ShajPriceY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);
		return 1;
	}

	return 0;
}

int TianxiaScript::findJiandingDi(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(180, 30, 260, 150, "JDingDi.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "JDingDiX=" << result[1].c_str();
	qDebug() << "JDingDiY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);
		return 1;
	}

	return 0;
}

int TianxiaScript::findQiCai(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(180, 30, 260, 150, "QiCai.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "QiCaiX=" << result[1].c_str();
	qDebug() << "QiCaiY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);
		return 1;
	}

	return 0;
}

int TianxiaScript::xiaofeiQueren(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(250, 90, 330, 160, "消费确认.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "xiaofeiQuerenX=" << result[1].c_str();
	qDebug() << "xiaofeiQuerenY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(375, 45);
		DM->PskLClick();
		Sleep(1000);
		return 1;
	}

	return 0;
}

int TianxiaScript::yuanbaoBuzu(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(200, 130, 305, 220, "YuanbaoBuzu.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "yuanbaoBuzuX=" << result[1].c_str();
	qDebug() << "yuanbaoBuzuY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(250, 240);
		DM->PskLClick();
		Sleep(1000);
		return 1;
	}

	return 0;
}

int TianxiaScript::duihuanJunziWnd(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(200, 130, 305, 220, "DuihuanJunWnd.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "duihuanJunziX=" << result[1].c_str();
	qDebug() << "duihuanJunziY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(310, 285);
		DM->PskLClick();
		Sleep(1000);
		return 1;
	}

	return 0;
}

int TianxiaScript::findZhenbaoJinbi(Ifire* DM, long pX, long pY)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(pX - 30, pY, pX + 50, pY + 40, "JinbiAbled.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "zhenbaoJinbiX=" << result[1].c_str();
	qDebug() << "zhenbaoJinbiY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);
		return 1;
	}

	return 0;
}

int TianxiaScript::jhjGaoshu(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(65, 90, 360, 270, "YuanshenItem.bmp|TaiyinItem.bmp|LeizuanItem.bmp|FanbenhuanyuanItem.bmp|GaoshuItem.bmp|RuanyuItem.bmp|ZizhidanItem.bmp|DouzhuanxingyiItem.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "gaoshuX=" << result[1].c_str();
	qDebug() << "gaoshuY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(1000);

		if (findZhenbaoJinbi(DM, x, y) == 1) {
			return 1;
		}

	}

	return 0;
}

int TianxiaScript::jhjLeizuan(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(65, 90, 360, 270, "商城雷钻.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "leizuanX=" << result[1].c_str();
	qDebug() << "leizuanY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(1000);

		if (findZhenbaoJinbi(DM, x, y) == 1) {
			return 1;
		}

	}

	return 0;
}

int TianxiaScript::jhjXixinshi(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(65, 90, 360, 270, "商城洗心石.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "xixinshiX=" << result[1].c_str();
	qDebug() << "xixinshiY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(1000);

		if (findZhenbaoJinbi(DM, x, y) == 1) {
			return 1;
		}

	}

	return 0;
}

int TianxiaScript::findYoujianWnd(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(250, 20, 350, 100, "邮件窗口.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "youjianWndX=" << result[1].c_str();
	qDebug() << "youjianWndY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);
		return 1;
	}

	return 0;
}

int TianxiaScript::getCaptainIndex(int captainNumber)
{
	TianxiaSingleton* tianxia = TianxiaSingleton::getInstance();
	QTableWidgetItem* item = tianxia->table->item(captainNumber - 1, 4);
	if (item == NULL) {
		return 0;
	}

	QString captainNumberStr = item->text();
	qDebug() << captainNumberStr;

	return captainNumberStr.toInt();
}

int TianxiaScript::findShangchengWnd(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(250, 20, 350, 100, "商城窗口.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "shangchengWndX=" << result[1].c_str();
	qDebug() << "shangchengWndY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);
		return 1;
	}

	return 0;
}

int TianxiaScript::closeShangchengWnd(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(250, 20, 350, 100, "商城窗口.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "shangchengWndX=" << result[1].c_str();
	qDebug() << "shangchengWndY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(525, 35);
		DM->PskLClick();
		Sleep(1000);
		return 1;
	}

	return 0;
}

int TianxiaScript::findXiaoxiWnd(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(250, 20, 350, 100, "消息窗口.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "xiaoxiWndX=" << result[1].c_str();
	qDebug() << "xiaoxiWndY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);
		return 1;
	}

	return 0;
}

int TianxiaScript::findHaoyouWnd(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(250, 20, 350, 100, "HaoyouWnd.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "HaoyouWndX=" << result[1].c_str();
	qDebug() << "HaoyouWndY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);
		return 1;
	}

	return 0;
}


int TianxiaScript::haoyouWndClose(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(250, 60, 350, 180, "HaoyouWnd2.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "HaoyouWnd2X=" << result[1].c_str();
	qDebug() << "HaoyouWnd2Y=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(250, 240);
		DM->PskLClick();
		Sleep(1000);
		return 1;
	}

	bstr = DM->PskFindPicE(250, 60, 350, 180, "HaoyouWnd1.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "HaoyouWnd1X=" << result[1].c_str();
	qDebug() << "HaoyouWnd1Y=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(490, 65);
		DM->PskLClick();
		Sleep(1000);
		return 1;
	}
	return 0;
}


int TianxiaScript::closeXiaoxiWnd(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(250, 20, 350, 100, "消息窗口.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "xiaoxiWndX=" << result[1].c_str();
	qDebug() << "xiaoxiWndY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(520, 40);
		DM->PskLClick();
		Sleep(1000);
		return 1;
	}

	return 0;
}

int TianxiaScript::youjianLingquBtn(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(420, 250, 520, 350, "一键领取按钮.bmp|YijianLingquBtn.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(420, 250, 520, 350, "YijianLingquBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "youjianLingquBtnX=" << result[1].c_str();
	qDebug() << "youjianLingquBtnY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(1000);

		return 1;
	}

	return 0;
}

int TianxiaScript::quxiaoClose(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(200, 220, 300, 350, "Quxiao.bmp|QuxiaoBtn2.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "QuxiaoX=" << result[1].c_str();
	qDebug() << "QuxiaoY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(x + 2, y + 2);
		DM->PskLClick();
		Sleep(1000);

		return 1;
	}

	return 0;
}

int TianxiaScript::findQuxiaoBtn(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(200, 200, 300, 350, "QuxiaoBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "QuxiaoBtnX=" << result[1].c_str();
	qDebug() << "QuxiaoBtnY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(1000);

		return 1;
	}

	return 0;
}

int TianxiaScript::closeYoujianWnd(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(250, 20, 350, 100, "邮件窗口.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "youjianWndX=" << result[1].c_str();
	qDebug() << "youjianWndY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(520, 40);
		DM->PskLClick();
		Sleep(1000);
		return 1;
	}

	return 0;
}

int TianxiaScript::findJinengWnd(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(250, 20, 350, 100, "技能学习窗口.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "jinengXuexiWndX=" << result[1].c_str();
	qDebug() << "jinengXuexiWndY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);
		return 1;
	}

	return 0;
}

int TianxiaScript::closeJinengWnd(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(250, 20, 350, 100, "技能学习窗口.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "jinengXuexiWndX=" << result[1].c_str();
	qDebug() << "jinengXuexiWndY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(520, 40);
		DM->PskLClick();
		Sleep(1000);
		return 1;
	}

	return 0;
}

int TianxiaScript::qiandaoChoujiang(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(250, 20, 350, 100, "签到抽奖窗口.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "qiandaoChoujiangX=" << result[1].c_str();
	qDebug() << "qiandaoChoujiangY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(295, 220);
		DM->PskLClick();
		Sleep(10000);
		DM->PskMTo(520, 40);
		DM->PskLClick();
		Sleep(1000);
		return 1;
	}

	return 0;
}

int TianxiaScript::findLevelLabel(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(300, 50, 350, 125, "DengJi.bmp|Dengji2.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "DengJiX=" << result[1].c_str();
	qDebug() << "DengJiY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);
		return 1;
	}

	return 0;
}

int TianxiaScript::getLevel(Ifire* DM) {

	int ret = 0;
	if (findLevelLabel(DM) == 0) {
		DM->PskKPress(67);
		Sleep(2000);
	}

	if (findLevelLabel(DM) == 1) {
		getCurrentLevel(DM);
		getCharacterID(DM);
		ret = 1;
	}
	else {
		generalClose(DM);
		renwuClose(DM);
		mapClose(DM);
	}

	return ret;
}

int TianxiaScript::getCurrentHuoyue(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	DM->PskSetDict(0, "new_huoyue.txt");
	//5E4327-2F2E25
	//bstr = DM->PskOcr(80, 300, 130, 320, "60492F-2C2E28|806340-1D1D17", 1);
	bstr = DM->PskOcr(80, 300, 130, 320, "5E4327-2F2E25", 1);
	string leverString = (_bstr_t)bstr;

	qDebug() << "currentHuoli=" << leverString.c_str();
	//qDebug() << "QuXiaoPiPeiY=" << result[2].c_str();
	TianxiaSingleton* tx = TianxiaSingleton::getInstance();


	long huoliLong = atol(leverString.c_str());

	if (huoliLong < 100 && this->roleIndex != 0) {
		//QHash<int, int>::iterator iter = completeMap.find(roleIndex);


		completeMap.remove(roleIndex);
	}

	if (this->huoli_param <= huoliLong && 300 > huoliLong) {
		//mengxueXiangshi(DM);
		huoyueLingjiang(DM);
		scriptIndex = this->scriptList.size();

		if (this->roleIndex != 0) {
			this->completeMap.insert(roleIndex, roleIndex);

			QTableWidget* table = tx->table;
			int size = completeMap.size();
			table->setItem(index - 1, 6, new QTableWidgetItem(QString::number(size)));
		}
	}

	if (huoliLong < 200) {
		QTableWidget* table = tx->table;
		table->setItem(index - 1, 3, new QTableWidgetItem(QString::fromLocal8Bit(leverString.c_str())));
	}

	return huoliLong;
}


int TianxiaScript::getCurrentLevel(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	DM->PskSetDict(0, "lvl.txt");

	//9C612E-172528
	//bstr = DM->PskOcr(350, 50, 410, 90, "A06937-19282B", 1);//A26C39-17262A
	//bstr = DM->PskOcr(350, 50, 410, 90, "9E6734-1A2A2D", 1);
	bstr = DM->PskOcr(350, 50, 410, 90, "9E6734-1A2A2D|A26C39-17262A", 1);
	string leverString = (_bstr_t)bstr;

	qDebug() << "getCurrentLevel=" << leverString.c_str();
	TianxiaSingleton* tx = TianxiaSingleton::getInstance();


	long level = atol(leverString.c_str());

	if (level > currentLevel && level < 100) {
		currentLevel = level;
		QTableWidget* table = tx->table;
		table->setItem(index - 1, 8, new QTableWidgetItem(QString::fromLocal8Bit(leverString.c_str())));
	}

	return currentLevel;
}

int TianxiaScript::getCharacterID(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	DM->PskSetDict(0, "ID_ziku.txt");

	//9C612E-172528
	//bstr = DM->PskOcr(350, 50, 410, 90, "A06937-19282B", 1);//A26C39-17262A
	//bstr = DM->PskOcr(350, 50, 410, 90, "9E6734-1A2A2D", 1);
	bstr = DM->PskOcr(460, 60, 530, 90, "A26C39-17262A", 0.9);
	string leverString = (_bstr_t)bstr;

	qDebug() << "getCharacterID=" << leverString.c_str();
	TianxiaSingleton* tx = TianxiaSingleton::getInstance();


	long level = atol(leverString.c_str());

	QTableWidget* table = tx->table;
	table->setItem(index - 1, 10, new QTableWidgetItem(QString::fromLocal8Bit(leverString.c_str())));
	tx->scriptIDMap.insert(this->index, leverString);

	return currentLevel;
}

int TianxiaScript::getCurrentJunzi(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	DM->PskSetDict(0, "jinbi.txt");
	//9E642F-192829
	//bstr = DM->PskOcr(330, 295, 390, 315, "A36D39-152323|D759BC-06271E|468BD0-3E1229|ED7D35-0D1C25", 1);
	bstr = DM->PskOcr(330, 295, 390, 315, "9E642F-192829|D759BC-06271E|468BD0-3E1229|ED7D35-0D1C25", 1);
	string leverString = (_bstr_t)bstr;

	qDebug() << "currentJinbi=" << leverString.c_str();
	//qDebug() << "QuXiaoPiPeiY=" << result[2].c_str();
	TianxiaSingleton* tx = TianxiaSingleton::getInstance();


	long junzi = atol(leverString.c_str());

	if (junzi > 200 && junzi < 5000000) {
		QTableWidget* table = tx->table;
		table->setItem(index - 1, 5, new QTableWidgetItem(QString::fromLocal8Bit(leverString.c_str())));

		if (roleIndex != 0) {
			CommonUtil::upateGold(index, roleIndex, junzi);
		}
	}

	return 0;
}

int TianxiaScript::getCurrentJinbi(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	DM->PskSetDict(0, "youjun.txt");
	//9E642F-192829
	//bstr = DM->PskOcr(330, 295, 390, 315, "A36D39-152323|D759BC-06271E|468BD0-3E1229|ED7D35-0D1C25", 1);
	bstr = DM->PskOcr(450, 295, 505, 315, "D759BC-06271E|468BD0-3E1229|5D9826-2F0D26", 0.9);
	string leverString = (_bstr_t)bstr;

	qDebug() << "currentJinbi=" << leverString.c_str();
	//qDebug() << "QuXiaoPiPeiY=" << result[2].c_str();
	TianxiaSingleton* tx = TianxiaSingleton::getInstance();


	long jinbi = atol(leverString.c_str());

	if (jinbi > 200 && jinbi < 100000000) {
		QTableWidget* table = tx->table;
		this->myJinbi = jinbi;
		table->setItem(index - 1, 11, new QTableWidgetItem(QString::fromLocal8Bit(leverString.c_str())));


	}

	return 0;
}

int TianxiaScript::getSaohuoJunzi(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	DM->PskSetDict(0, "youjun.txt");

	bstr = DM->PskOcr(80, 300, 145, 325, "EB7C33-0E1923|ED7322-0D1419|A66C30-1A2721|468BD0-3E1229", 1);
	string leverString = (_bstr_t)bstr;

	qDebug() << "getSaohuoJunzi=" << leverString.c_str();
	//qDebug() << "QuXiaoPiPeiY=" << result[2].c_str();
	TianxiaSingleton* tx = TianxiaSingleton::getInstance();


	long junzi = atol(leverString.c_str());

	if (junzi > 0 && junzi < 5000000) {
		return junzi;
	}

	return 0;
}

int TianxiaScript::getSellPrice(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	DM->PskSetDict(0, "sell2.txt");

	bstr = DM->PskOcr(220, 220, 275, 255, "FC8C4A-022432|B28256-1D2D34|4A9AF0-49230F", 0.9);
	string leverString = (_bstr_t)bstr;

	qDebug() << "getSellPrice=" << leverString.c_str();
	//qDebug() << "QuXiaoPiPeiY=" << result[2].c_str();
	TianxiaSingleton* tx = TianxiaSingleton::getInstance();


	long junzi = atol(leverString.c_str());

	if (junzi > 0 && junzi < 5000000) {
		return junzi;
	}

	return 0;
}

int TianxiaScript::getSaohuoPrice(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	DM->PskSetDict(0, "sao.txt");

	//bstr = DM->PskOcr(265, 100, 305, 140, "EB7C33-0E1923|ED7322-0D1419|A66C30-1A2721", 1);
	bstr = DM->PskOcr(265, 160, 305, 210, "EB7C33-0E1923|ED7322-0D1419|A66C30-1A2721", 1);
	string leverString = (_bstr_t)bstr;

	qDebug() << "currentJinbi=" << leverString.c_str();
	//qDebug() << "QuXiaoPiPeiY=" << result[2].c_str();
	TianxiaSingleton* tx = TianxiaSingleton::getInstance();


	long junzi = atol(leverString.c_str());

	if (junzi > 0 && junzi < 5000000) {
		return junzi;
	}

	return 0;
}

int TianxiaScript::getSaohuoPriceEx(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	DM->PskSetDict(0, "sao.txt");

	bstr = DM->PskOcr(265, 100, 305, 140, "EB7C33-0E1923|ED7322-0D1419|A66C30-1A2721", 1);
	string leverString = (_bstr_t)bstr;

	qDebug() << "currentJinbi=" << leverString.c_str();
	//qDebug() << "QuXiaoPiPeiY=" << result[2].c_str();
	TianxiaSingleton* tx = TianxiaSingleton::getInstance();


	long junzi = atol(leverString.c_str());

	if (junzi > 0 && junzi < 5000000) {
		return junzi;
	}

	return 0;
}

int TianxiaScript::getSellingPrice(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	DM->PskSetDict(0, "sao2.txt");

	bstr = DM->PskOcr(360, 130, 450, 160, "EB7C33-0E1923|ED7322-0D1419|A66C30-1A2721|4A8ED0-2D0D1C", 0.9);
	string leverString = (_bstr_t)bstr;

	qDebug() << "getSellingPrice=" << leverString.c_str();
	//qDebug() << "QuXiaoPiPeiY=" << result[2].c_str();
	TianxiaSingleton* tx = TianxiaSingleton::getInstance();


	long junzi = atol(leverString.c_str());

	if (junzi > 0 && junzi < 5000000) {
		return junzi;
	}

	return 0;
}

int TianxiaScript::getMyHuoli(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	DM->PskSetDict(0, "txzk_huoli2.txt");

	//bstr = DM->PskOcr(295, 280, 350, 350, "9C622D-142121|A36E39-152324", 1);
	bstr = DM->PskOcr(295, 280, 350, 350, "985C27-132021|A36D38-131E1E", 1);
	string leverString = (_bstr_t)bstr;

	qDebug() << "myHuoli=" << leverString.c_str();
	//qDebug() << "QuXiaoPiPeiY=" << result[2].c_str();
	/*TianxiaSingleton* tx = TianxiaSingleton::getInstance();
	QTableWidget* table = tx->table;
	table->setItem(index - 1, 3, new QTableWidgetItem(QString::fromLocal8Bit(leverString.c_str())));*/

	long huoliLong = atol(leverString.c_str());
	this->power = huoliLong;

	TianxiaSingleton *tx = TianxiaSingleton::getInstance();

	QTableWidget* table = tx->table;
	table->setItem(index - 1, 9, new QTableWidgetItem(QString::fromLocal8Bit(leverString.c_str())));
	/*if (100 <= huoliLong && 200 > huoliLong) {
	huoyueLingjiang(DM);
	scriptIndex = this->scriptList.size();
	}*/

	return huoliLong;
}

int TianxiaScript::mengxueXiangshi(Ifire* DM)
{
	if (findMengxueXiangshi(DM) == 0) {
		DM->PskKPress(75);
		Sleep(2000);
		if (getCurrentHuoyue(DM) > 100) {
			return 2;
		}
		Sleep(1000);
		DM->PskMTo(540, 160);
		DM->PskLClick();
		Sleep(3000);


		if (findMengxueXiangshi(DM) == 0) {
			DM->PskKPress(27);
			return 2;
		}
	}

	Sleep(3000);


	//_bstr_t bstr;
	//string str, size;
	//long x, y, l;

	//std::vector<std::string> result;
	//bstr = DM->PskFindPicE(200, 90, 300, 150, "参加按钮.bmp", "000000", 0.9, 0);
	//str = (_bstr_t)bstr;

	//qDebug() << str.c_str();

	//result = CommonUtil::split(str, "|");

	//l = result.size();
	//size = CommonUtil::Long2STR(l);
	//if (l < 3) {
	//	return 0;
	//}

	//x = atol(result[1].c_str());
	//y = atol(result[2].c_str());

	//qDebug() << "CanjiaAnniuX=" << result[1].c_str();
	//qDebug() << "CanjiaAnniuY=" << result[2].c_str();

	//if (x != -1) {
	//	DM->PskMToEx(x + 2, y + 2, 10, 10);
	//	DM->PskLClick();
	//	Sleep(3000);

	//}

	mengxueXiangshiSubScript(DM);

	return 2;
}

int TianxiaScript::huoyueCheck(Ifire* DM)
{
	if (huoliBtn(DM) == 0) {
		DM->PskKPress(75);
		Sleep(2000);
		int huoyue = getCurrentHuoyue(DM);
		Sleep(1000);

		if (huoyue < 100) {
			scriptIndex = 0;
			this->isRepeated = true;
			return 1;
		}

	}

	return 0;
}

int TianxiaScript::mengxueXiangshiSubScript(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(40, 80, 150, 150, "乡试连对.bmp|Xiangshiliandui.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(40, 80, 150, 150, "Xiangshiliandui.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "xiangShiLianDuiX=" << result[1].c_str();
	qDebug() << "xiangShiLianDuiY=" << result[2].c_str();

	long pX, pY;

	if (x != -1) {
		pX = x + 210;
		pY = y + 65;
	}
	else {
		return 0;
	}

	for (int i = 0; i < 10; i++) {
		int random = CommonUtil::generateRandomNumber();
		switch (random) {
		case 0:
		{
			DM->PskMTo(pX, pY);
			DM->PskLClick();
			Sleep(1000);
		}
		break;
		case 1:
		{
			DM->PskMTo(pX + 160, pY);
			DM->PskLClick();
			Sleep(1000);
		}
		break;
		case 2:
		{
			DM->PskMTo(pX, pY + 60);
			DM->PskLClick();
			Sleep(1000);
		}
		break;
		case 3:
		{
			DM->PskMTo(pX + 160, pY + 60);
			DM->PskLClick();
			Sleep(1000);
		}
		break;
		}
	}

	return 0;
}

int TianxiaScript::findMengxueXiangshi(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(70, 80, 450, 250, "蒙学乡试.bmp|MengxueXiangshi.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(70, 80, 450, 350, "MengxueXiangshi.bmp|Mengxuaxiangshi2.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "MengXueXiangshiX=" << result[1].c_str();
	qDebug() << "MengXueXiangshiY=" << result[2].c_str();

	if (x != -1) {
		if (findJikaiqi(DM, x, y) == 1) {
			scriptIndex++;
			return 0;
		}

		if (xiangshiComplete(DM, x, y) == 1) {
			scriptIndex++;
			return 0;
		}

		DM->PskMTo(x + 150, y + 15);
		DM->PskLClick();
		return 1;
	}

	return 0;
}

int TianxiaScript::menpaiBiwuClose(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(480, 300, 580, 460, "比武关闭.bmp|BiwuClose.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(480, 300, 580, 460, "BiwuClose.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "biwuGuanbiX=" << result[1].c_str();
	qDebug() << "biwuGuanbiY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		return 1;
	}

	return 0;
}

int TianxiaScript::shiliClose(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(480, 300, 580, 460, "ChangjianShili.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ChangjianShiliX=" << result[1].c_str();
	qDebug() << "ChangjianShiliY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(485, 60);
		DM->PskLClick();
		return 1;
	}

	return 0;
}

int TianxiaScript::menpaiBiwu(Ifire* DM)
{
	/*if (menpaiBiwuClose(DM) == 1) {
	Sleep(3000);
	DM->PskMTo(180, 240);
	DM->PskLClick();
	Sleep(3000);
	}*/

	if (findMenpaiBiwu(DM) == 0) {
		DM->PskKPress(75);
		Sleep(2000);
		if (getCurrentHuoyue(DM) > 100) {
			return 2;
		}
		Sleep(1000);
		DM->PskMTo(550, 120);
		DM->PskLClick();
		Sleep(3000);

		if (findMenpaiBiwu(DM) == 0) {
			return 2;
		}
		/*Sleep(2000);
		renwuClose(DM);*/
		Sleep(2000);
	}

	menpaiBiwuSubScript(DM);

	return 0;
}

int TianxiaScript::juediQiusheng(Ifire* DM)
{

	if (findJuediQiusheng(DM) == 0) {
		DM->PskKPress(75);
		Sleep(2000);
		if (getCurrentHuoyue(DM) > 100) {
			return 2;
		}
		Sleep(1000);
		DM->PskMTo(540, 160);
		DM->PskLClick();
		Sleep(3000);

		if (findJuediQiusheng(DM) == 0) {
			return 2;
		}
		/*Sleep(2000);
		renwuClose(DM);*/
		Sleep(2000);
	}

	juediQiushengSubScript(DM);

	return 0;
}

int TianxiaScript::juediQiushengSubScript(Ifire* DM) {
	DM->PskMTo(20, 350);
	DM->PskLClick();
	Sleep(2000);
	DM->PskMTo(297, 160);
	DM->PskLClick();
	Sleep(2000);

	if (danrenPaiduiBTN(DM) == 0) {
		generalClose(DM);
		return 0;
	}

	int temp = 0;
	while (juediConfirm(DM) == 0 && getIsEnded() == false) {
		temp++;
		if (temp > 20) {
			break;
		}
		Sleep(3000);
	}

	temp = 0;
	while (juediClose(DM) == 0 && getIsEnded() == false) {
		temp++;
		juediConfirm(DM);
		if (temp > 200) {
			break;
		}
		Sleep(3000);
	}

	temp = 0;
	while (juediClose(DM) == 1 && getIsEnded() == false) {
		temp++;
		juediConfirm(DM);
		if (temp > 200) {
			break;
		}
		Sleep(3000);
	}

	juediEnd(DM);

	return 0;
}

int TianxiaScript::danrenPaiduiBTN(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(450, 60, 560, 180, "DanPaiBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "DanPaiBtnX=" << result[1].c_str();
	qDebug() << "DanPaiBtnY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(1000);

		return 1;
	}

	return 0;
}

int TianxiaScript::zhaoShifu(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(250, 20, 340, 120, "ZhaoShifu.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ZhaoShifuX=" << result[1].c_str();
	qDebug() << "ZhaoShifuY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(485, 60);
		DM->PskLClick();
		Sleep(1000);

		return 1;
	}

	return 0;
}

int TianxiaScript::juediClose(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(550, 0, 600, 60, "JuediClose.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "JuediCloseX=" << result[1].c_str();
	qDebug() << "JuediCloseY=" << result[2].c_str();

	if (x != -1) {
		/*DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();*/
		Sleep(3000);

		return 1;
	}

	return 0;
}

int TianxiaScript::juediEnd(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(500, 300, 565, 380, "JuediEndBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "JuediEndBtnX=" << result[1].c_str();
	qDebug() << "JuediEndBtnY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(3000);

		return 1;
	}

	return 0;
}

int TianxiaScript::juediConfirm(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(180, 120, 275, 230, "JuediCF.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "JuediCFx=" << result[1].c_str();
	qDebug() << "JuediCFy=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(340, 240);
		DM->PskLClick();
		//Sleep(60000);

		return 1;
	}

	return 0;
}

int TianxiaScript::menpaiBiwuSubScript(Ifire* DM)
{
	int ret = 0;
	if (menpaiBiWuBTN(DM) == 0 && menpaiTiaozhanBTN(DM) == 0) {
		generalClose(DM);
		closeShezhiWnd(DM);
		Sleep(1000);
		DM->PskMTo(300, 175);
		DM->PskLClick();
		Sleep(1000);
		generalClose(DM);
		ret = menpaiBiWuBTN(DM);
	}
	else {
		ret = 1;
	}

	if (ret == 1) {

		for (int i = 0; i < 9 && !getIsEnded(); i++) {
			DM->PskMTo(180, 240);
			DM->PskLClick();
			Sleep(3000);

			if (biwuCompleted(DM) == 1) {
				generalClose(DM);
				scriptIndex++;
				return 0;
			}

			if (menpaiTiaozhanBTN(DM) == 0) {
				DM->PskMTo(400, 310);
				DM->PskLClick();
				Sleep(1000);
				DM->PskMTo(340, 240);
				DM->PskLClick();
				Sleep(1000);
				menpaiTiaozhanBTN(DM);
				Sleep(2000);
			}

			int temp = 0;
			while (menpaiTiaozhanBTN(DM) == 1 && getIsEnded() == false) {
				temp++;
				if (temp > 100) {
					break;
				}
				Sleep(2000);
			}

			autoCombat(DM);

			temp = 0;
			while (menpaiBiwuClose(DM) == 0) {
				Sleep(10000);
				autoCombat(DM);
				temp++;
				if (temp > 6) {
					scriptIndex++;
					break;
				}

			}
		}

	}


	Sleep(2000);
	menpaiWndClose(DM);

	return 0;
}

int TianxiaScript::biwuCompleted(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(130, 220, 190, 300, "BiwuWan.bmp|BiwuWan2.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(130, 220, 190, 300, "BiwuWan2.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "BiwuWanX=" << result[1].c_str();
	qDebug() << "BiwuWanY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);

		return 1;
	}

	return 0;
}


int TianxiaScript::menpaiTiaozhanBTN(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(450, 110, 550, 300, "门派挑战.bmp|MenpaiTiaozhanBtn.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(450, 110, 550, 300, "MenpaiTiaozhanBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "MenPaiTiaozhanX=" << result[1].c_str();
	qDebug() << "MenPaiTiaozhanY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(3000);

		return 1;
	}

	return 0;
}

int TianxiaScript::menpaiBiWuBTN(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(450, 200, 550, 265, "门派比武按钮.bmp|MenpaiBiwuBtn.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(450, 200, 550, 265, "MenpaiBiwuBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "MenPaiBiWuBtnX=" << result[1].c_str();
	qDebug() << "MenPaiBiWuBtnY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(1000);

		return 1;
	}

	return 0;
}

int TianxiaScript::jiahuWndClose(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(420, 250, 520, 350, "前往加护.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "qwJiahuX=" << result[1].c_str();
	qDebug() << "qwJiahuY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(525, 40);
		DM->PskLClick();
		return 1;
	}

	return 0;
}

int TianxiaScript::findMenpaiBiwu(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(70, 80, 450, 250, "门派比武.bmp|MenpaiBiwu.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(70, 80, 450, 250, "MenpaiBiwu.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "MenPaiBiWuX=" << result[1].c_str();
	qDebug() << "MenPaiBiWuY=" << result[2].c_str();

	if (x != -1) {

		if (findJikaiqi(DM, x, y) == 1) {
			scriptIndex++;
			return 1;
		}

		DM->PskMTo(x + 150, y + 15);
		DM->PskLClick();
		Sleep(20000);
		richangClose(DM);
		renwuClose(DM);
		return 1;
	}

	return 0;
}

int TianxiaScript::findJuediQiusheng(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(70, 80, 450, 250, "JuediQiusheng.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "JuediQiushengX=" << result[1].c_str();
	qDebug() << "JuediQiushengY=" << result[2].c_str();

	if (x != -1) {

		if (findJikaiqi(DM, x, y) == 1) {
			scriptIndex++;
			return 1;
		}

		DM->PskMTo(x + 150, y + 15);
		DM->PskLClick();
		Sleep(20000);
		richangClose(DM);
		renwuClose(DM);
		return 1;
	}

	return 0;
}

int TianxiaScript::wangchaoMitanCap(Ifire* DM)
{
	renwuClose(DM);

	if (mitanShishi(DM) == 1) {
		Sleep(30000);
		tuichuDuiwu(DM);
	}

	if (findWangchaoMitanCap(DM) == 0) {
		Sleep(1000);
		DM->PskKPress(75);
		Sleep(2000);
		if (getCurrentHuoyue(DM) > 100) {
			return 2;
		}
		Sleep(1000);
		DM->PskMTo(550, 120);
		DM->PskLClick();
		Sleep(2000);

		if (findWangchaoMitanCap(DM) == 0) {
			return 2;
		}

	}


	return 0;
}

int TianxiaScript::wangchaoMitan(Ifire* DM)
{
	renwuClose(DM);

	if (mitanShishi(DM) == 1) {
		Sleep(30000);
		tuichuDuiwu(DM);
	}

	if (findWangchaoMitan(DM) == 0) {
		Sleep(1000);
		DM->PskKPress(75);
		Sleep(2000);
		if (getCurrentHuoyue(DM) > 100) {
			return 2;
		}
		Sleep(1000);
		DM->PskMTo(550, 120);
		DM->PskLClick();
		Sleep(2000);

		if (findWangchaoMitan(DM) == 0) {
			return 2;
		}

	}


	return 0;
}

int TianxiaScript::subMitanNoClick(Ifire* DM) {

	if (findWangchaoMitanNoClick(DM) == 0) {
		Sleep(1000);
		DM->PskKPress(75);
		Sleep(2000);
		if (getCurrentHuoyue(DM) > 100) {
			return 2;
		}
		Sleep(1000);
		DM->PskMTo(540, 105);
		DM->PskLClick();
		Sleep(2000);

		if (findWangchaoMitanNoClick(DM) == 1) {
			DM->PskKPress(27);
			return 1;
		}
	}
	return 0;
}

int TianxiaScript::subMitan(Ifire* DM)
{


	if (findWangchaoMitan(DM) == 0) {
		Sleep(1000);
		DM->PskKPress(75);
		Sleep(2000);
		if (getCurrentHuoyue(DM) > 100) {
			return 2;
		}
		Sleep(1000);
		DM->PskMTo(540, 105);
		DM->PskLClick();
		Sleep(2000);

		if (findWangchaoMitan(DM) == 0) {
			DM->PskKPress(27);
			return 2;
		}
		else {

			Sleep(20000);

			if (findMitanCaozuo(DM) == 1) {
				DM->PskMTo(480, 105);
				DM->PskLClick();
				Sleep(1000);
				DM->PskKPress(27);
				Sleep(3000);
				autoCombat(DM);
				Sleep(1000);

				int tempCounter = 0;
				while (subMitanNoClick(DM) == 1 && getIsEnded() == false) {
					DM->PskKPress(27);
					Sleep(30000);
					tempCounter++;
					if (tempCounter > 20) {
						break;
					}

				}
			}
		}

	}


	return 0;
}

int TianxiaScript::subSuoyaota(Ifire* DM)
{
	if (findSuoyaoTa(DM) == 0) {
		Sleep(1000);
		DM->PskKPress(75);
		Sleep(2000);
		if (getCurrentHuoyue(DM) > 100) {
			return 2;
		}
		Sleep(1000);
		DM->PskMTo(540, 265);
		DM->PskLClick();
		Sleep(2000);

		if (findSuoyaoTa(DM) == 0) {
			DM->PskKPress(27);
			return 2;
		}
		else {

			Sleep(20000);

			if (clickSuoyaota(DM) == 1) {
				DM->PskKDown(87);
				Sleep(6000);
				DM->PskKUp(87);
				Sleep(1000);
				DM->PskKPress(27);
				Sleep(1000);
				autoCombat(DM);
			}
			else {
				DM->PskKPress(27);

			}
		}

	}


	return 0;
}

int TianxiaScript::findWangchaoMitan(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//
	//bstr = DM->PskFindPicE(80, 90, 450, 350, "王朝密探.bmp|WangchaoMitan.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(60, 80, 530, 200, "MitanIcon.bmp|MitanIcon2.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "MitanIconX=" << result[1].c_str();
	qDebug() << "MitanIconY=" << result[2].c_str();

	if (x != -1) {
		if (mitanComplete(DM, x, y) == 1) {
			scriptIndex++;
			return 1;
		}

		if (findJikaiqi(DM, x, y) == 1) {
			scriptIndex++;
			return 1;
		}

		DM->PskMTo(x + 180, y + 5);
		DM->PskLClick();
		return 1;
	}

	bstr = DM->PskFindPicE(80, 90, 450, 200, "WangchaoMitan.bmp|WangzhaoMitanx.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "WangChaoMiTanX=" << result[1].c_str();
	qDebug() << "WangChaoMiTanY=" << result[2].c_str();

	if (x != -1) {
		if (mitanComplete(DM, x, y) == 1) {
			scriptIndex++;
			return 1;
		}

		if (findJikaiqi(DM, x, y) == 1) {
			scriptIndex++;
			return 1;
		}

		DM->PskMTo(x + 150, y + 15);
		DM->PskLClick();
		return 1;
	}

	return 0;
}

int TianxiaScript::findSuoyaoTa(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(60, 80, 530, 200, "Suoyaota.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "SuoyaotaX=" << result[1].c_str();
	qDebug() << "SuoyaotaY=" << result[2].c_str();

	if (x != -1) {
		if (mitanComplete(DM, x, y) == 1) {
			scriptIndex++;
			return 1;
		}

		if (findJikaiqi(DM, x, y) == 1) {
			scriptIndex++;
			return 1;
		}

		DM->PskMTo(x + 160, y + 10);
		DM->PskLClick();
		return 1;
	}


	return 0;
}


int TianxiaScript::findWangchaoMitanNoClick(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//
	//bstr = DM->PskFindPicE(80, 90, 450, 350, "王朝密探.bmp|WangchaoMitan.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(60, 80, 530, 200, "MitanIcon.bmp|MitanIcon2.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "MitanIconX=" << result[1].c_str();
	qDebug() << "MitanIconY=" << result[2].c_str();

	if (x != -1) {
		if (mitanComplete(DM, x, y) == 1) {
			scriptIndex++;
			return 1;
		}

		if (findJikaiqi(DM, x, y) == 1) {
			scriptIndex++;
			return 1;
		}

		return 1;
	}

	bstr = DM->PskFindPicE(80, 90, 450, 200, "WangchaoMitan.bmp|WangzhaoMitanx.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "WangChaoMiTanX=" << result[1].c_str();
	qDebug() << "WangChaoMiTanY=" << result[2].c_str();

	if (x != -1) {
		if (mitanComplete(DM, x, y) == 1) {
			scriptIndex++;
			return 1;
		}

		if (findJikaiqi(DM, x, y) == 1) {
			scriptIndex++;
			return 1;
		}

		return 1;
	}

	return 0;
}

int TianxiaScript::findWangchaoMitanCap(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(80, 90, 450, 350, "王朝密探.bmp|WangchaoMitan.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(80, 90, 450, 350, "WangchaoMitan.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "WangChaoMiTanX=" << result[1].c_str();
	qDebug() << "WangChaoMiTanY=" << result[2].c_str();

	if (x != -1) {
		if (findCishubuxian(DM, x, y) == 0) {
			return 0;
		}
		if (mitanComplete(DM, x, y) == 1) {
			scriptIndex++;
			return 1;
		}

		if (findJikaiqi(DM, x, y) == 1) {
			scriptIndex++;
			return 1;
		}


		return 1;
	}

	return 0;
}

int TianxiaScript::findCishubuxian(Ifire* DM, long pX, long pY)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(pX, pY, pX + 100, pY + 40, "CishuBuxian.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "CishuBuxianX=" << result[1].c_str();
	qDebug() << "CishuBuxianY=" << result[2].c_str();

	if (x != -1) {
		Sleep(1000);

		return 1;
	}

	return 0;
}

int TianxiaScript::mitanShishi(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(245, 0, 290, 52, "密探十十.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "MitanShiX=" << result[1].c_str();
	qDebug() << "MitanShiY=" << result[2].c_str();

	if (x != -1) {
		Sleep(1000);

		return 1;
	}

	return 0;
}


int TianxiaScript::mitanComplete(Ifire* DM, long pX, long pY)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(pX, pY, pX + 180, pY + 40, "密探2020.bmp|Mitan2020.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(pX, pY, pX + 180, pY + 40, "Mitan2020.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "mitan2020X=" << result[1].c_str();
	qDebug() << "mitan2020Y=" << result[2].c_str();

	if (x != -1) {

		return 1;
	}

	return 0;
}

int TianxiaScript::xiangshiComplete(Ifire* DM, long pX, long pY)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(pX, pY, pX + 180, pY + 40, "乡试十十.bmp|Wancheng1010.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(pX, pY, pX + 180, pY + 40, "Wancheng1010.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "xiangshi10x=" << result[1].c_str();
	qDebug() << "xiangshi10y=" << result[2].c_str();

	if (x != -1) {

		return 1;
	}

	return 0;
}

int TianxiaScript::danrenKuaima(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(400, 150, 550, 300, "单人快马.bmp|DanrenKuaima.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(400, 150, 550, 300, "DanrenKuaima.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "danrenKuaimaX=" << result[1].c_str();
	qDebug() << "danrenKuaimaY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		return 1;
	}

	return 0;
}

int TianxiaScript::duihuanjinbiWnd(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(250, 45, 350, 120, "兑换金币窗口.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "duijinbiWndX=" << result[1].c_str();
	qDebug() << "duijinbiWndY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(485, 60);
		DM->PskLClick();
		return 1;
	}

	return 0;
}

int TianxiaScript::yuandiFuhuoBtn(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(260, 220, 350, 300, "原地复活按钮.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "yuandiFuhuoX=" << result[1].c_str();
	qDebug() << "yuandiFuhuoY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		return 1;
	}

	return 0;
}

int TianxiaScript::kuaimaXunhuan(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(250, 0, 290, 60, "快马循环.bmp|KuaimaXunhuan.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(250, 0, 290, 60, "KuaimaXunhuan.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "kuaimaXunhuanX=" << result[1].c_str();
	qDebug() << "kuaimaXunhuanY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(80, 70);
		DM->PskLClick();
		Sleep(5000);
		DM->PskMTo(530, 320);
		DM->PskLClick();
		/*Sleep(5000);
		DM->PskMTo(460, 335);
		DM->PskLClick();*/
		Sleep(20000);
		return 1;
	}
	else {
		generalClose(DM);
	}

	return 0;
}

int TianxiaScript::kuaimaJiabian(Ifire* DM)
{
	renwuClose(DM);

	if (findKuaimaJianbian(DM) == 0) {
		Sleep(1000);
		DM->PskKPress(75);
		Sleep(2000);
		if (getCurrentHuoyue(DM) > 100) {
			return 2;
		}
		Sleep(1000);
		DM->PskMTo(540, 105);
		DM->PskLClick();
		Sleep(5000);

		if (findKuaimaJianbian(DM) == 0) {
			return 2;
		}
		Sleep(2000);
		DM->PskMTo(325, 170);
		DM->PskLClick();
		Sleep(2000);
		dianjiTiaoguo(DM);
		Sleep(2000);
		danrenKuaima(DM);
		Sleep(3000);

		while (kuaimaXunhuan(DM) == 1 && getIsEnded() == false) {
			Sleep(5000);
		}
	}


	return 0;
}

int TianxiaScript::findKuaimaJianbian(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(80, 90, 420, 200, "快马加鞭.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "KuaiMaJiabianX=" << result[1].c_str();
	qDebug() << "KuaiMaJiabianY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(x + 150, y + 15);
		DM->PskLClick();
		return 1;
	}

	return 0;
}


int TianxiaScript::tuiduiBtn(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(50, 250, 150, 350, "退队按钮.bmp|TuiduiBtn.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(50, 250, 150, 350, "TuiduiBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "tuiduiBTNX=" << result[1].c_str();
	qDebug() << "tuiduiBTNY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		return 1;
	}

	return 0;
}

int TianxiaScript::findTuiduiBtn(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(50, 250, 150, 350, "退队按钮.bmp|TuiduiBtn.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(50, 250, 150, 350, "TuiduiBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "tuiduiBTNX=" << result[1].c_str();
	qDebug() << "tuiduiBTNY=" << result[2].c_str();

	if (x != -1) {
		Sleep(1000);
		return 1;
	}

	return 0;
}

int TianxiaScript::yihouZaishuo(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(150, 200, 300, 300, "以后再说.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "yihouzaishuoX=" << result[1].c_str();
	qDebug() << "yihouzaishuoY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		return 1;
	}

	return 0;
}

int TianxiaScript::wansheng(Ifire* DM)
{
	if (findWanshengClose(DM) == 0) {
		wanshengBtn(DM);
		Sleep(2000);
	}

	if (findWanshengClose(DM) == 1) {
		DM->PskMTo(265, 190);
		DM->PskLClick();
		Sleep(1000);
		querenHuafei(DM);

		DM->PskMTo(210, 150);
		DM->PskLClick();
		Sleep(1000);
		querenHuafei(DM);

		DM->PskMTo(250, 95);
		DM->PskLClick();
		Sleep(1000);
		querenHuafei(DM);

		DM->PskMTo(325, 70);
		DM->PskLClick();
		Sleep(1000);
		querenHuafei(DM);

		DM->PskMTo(365, 145);
		DM->PskLClick();
		Sleep(1000);
		querenHuafei(DM);

		DM->PskMTo(450, 200);
		DM->PskLClick();
		Sleep(1000);
		querenHuafei(DM);

		Sleep(1000);
		DM->PskMTo(580, 10);
		DM->PskLClick();

		this->scriptIndex++;
	}
	else {
		generalClose(DM);
		mapClose(DM);
		shangchengClose(DM);
		fuliClose(DM);

		return 2;
	}


	return 0;
}

int TianxiaScript::querenHuafei(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(150, 120, 270, 220, "QuerenHuafei.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "QuerenHuafeiX=" << result[1].c_str();
	qDebug() << "QuerenHuafeiY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(250, 240);
		DM->PskLClick();
		return 1;
	}

	return 0;
}

int TianxiaScript::findWanshengClose(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(520, 0, 600, 100, "WanshengClose.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "WanshengCloseX=" << result[1].c_str();
	qDebug() << "WanshengCloseY=" << result[2].c_str();

	if (x != -1) {
		Sleep(1000);
		return 1;
	}

	return 0;
}

int TianxiaScript::wanshengBtn(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(400, 20, 520, 150, "Wansheng1.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "Wansheng1X=" << result[1].c_str();
	qDebug() << "Wansheng1Y=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		return 1;
	}
	else {
		generalClose(DM);
		richangClose(DM);
		shangchengClose(DM);
	}

	bstr = DM->PskFindPicE(400, 20, 520, 150, "Wansheng2.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "Wansheng2X=" << result[1].c_str();
	qDebug() << "Wansheng2Y=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		return 1;
	}
	else {
		generalClose(DM);
		richangClose(DM);
		shangchengClose(DM);
	}
	return 0;
}

int TianxiaScript::tianlaoZhiyuan(Ifire* DM)
{
	renwuClose(DM);
	zuduiClose(DM);
	richangClose(DM);
	shangchengClose(DM);

	if (isInTianlaoZhiyuan(DM) == 1) {
		Sleep(30000);
		return 0;
	}

	mapSearchTianlaoZhiyuan(DM);
	Sleep(1000);
	findTianlaoZhiyuan(DM);
	baoxiangLingqu(DM);
	//scriptIndex++;
	return 0;
}

int TianxiaScript::guagua(Ifire* DM)
{
	renwuClose(DM);
	zuduiClose(DM);
	richangClose(DM);
	shangchengClose(DM);


	mapSearchGuagua(DM);
	Sleep(1000);


	DM->PskMTo(18, 350);
	DM->PskLClick();
	Sleep(2000);

	DM->PskKDown(65);
	Sleep(8000);
	DM->PskKUp(65);
	Sleep(1000);
	DM->PskMTo(18, 350);
	DM->PskLClick();
	Sleep(2000);
	DM->PskMTo(295, 195);
	DM->PskLClick();
	Sleep(2000);
	if (zhaigua(DM) == 1) {
		scriptIndex++;
	}
	else {
		beibaoClose(DM);
		generalClose(DM);
	}

	return 0;
}

int TianxiaScript::zhaigua(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(250, 80, 360, 180, "ZhaiGua.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ZhaiGuaX=" << result[1].c_str();
	qDebug() << "ZhaiGuaY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(310, 230);
		DM->PskLClick();
		Sleep(2000);

		return 1;
	}

	return 0;
}

int TianxiaScript::renwuJiadian(Ifire* DM)
{
	if (tuijianJiadianEx(DM) == 0) {
		DM->PskKPress(67);

		Sleep(1000);

		duiwuClose(DM);

		Sleep(2000);
	}

	if (tuijianJiadianEx(DM) == 1) {

	}

	scriptIndex++;
	return 0;
}

int TianxiaScript::renwuJiadianNormal(Ifire* DM)
{
	if (tuijianJiadianEx(DM) == 0) {
		DM->PskKPress(67);

		Sleep(1000);

		duiwuClose(DM);

		Sleep(2000);
	}

	if (tuijianJiadianEx(DM) == 1) {

	}

	return 0;
}

int TianxiaScript::findTianlaoZhiyuan(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(450, 200, 580, 300, "深入天牢.bmp|TianlaoBtn.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(450, 200, 580, 300, "TianlaoBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "shenruTianlaoX=" << result[1].c_str();
	qDebug() << "shenruTianlaoY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		scriptIndex++;

		int counter = 0;
		while (getIsEnded() == false) {
			autoCombat(DM);
			counter++;
			DM->PskMTo(200, 200);
			DM->PskLClick();
			if (counter > 15) {
				break;
			}
			Sleep(6000 * 3);
		}

		return 1;
	}
	else {
		renwuClose(DM);
		zuduiClose(DM);
		richangClose(DM);
		generalClose(DM);
		closeShezhiWnd(DM);
		mapClose(DM);
	}

	return 0;
}

int TianxiaScript::isInTianlaoZhiyuan(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(500, 0, 580, 60, "天牢之渊地图.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "tlDituX=" << result[1].c_str();
	qDebug() << "tlDituY=" << result[2].c_str();

	if (x != -1) {

		return 1;
	}

	return 0;
}

int TianxiaScript::mapSearchTianlaoZhiyuan(Ifire* DM)
{
	generalClose(DM);
	map2Jiuli(DM);
	Sleep(5000);
	mapSearchBtn(DM);

	richangClose(DM);

	HWND hFocusHwnd = (HWND)lHWND;

	const wchar_t * msgTemp = L"天";
	PostMessageW(hFocusHwnd, WM_CHAR, *msgTemp, 1);

	msgTemp = L"牢";
	PostMessageW(hFocusHwnd, WM_CHAR, *msgTemp, 1);

	msgTemp = L"守";
	PostMessageW(hFocusHwnd, WM_CHAR, *msgTemp, 1);

	msgTemp = L"备";
	PostMessageW(hFocusHwnd, WM_CHAR, *msgTemp, 1);

	Sleep(1000);

	DM->PskMTo(310, 85);
	DM->PskLClick();

	Sleep(1000);

	DM->PskMTo(250, 110);
	DM->PskLClick();

	Sleep(2000);
	/*DM->PskKDown(87);
	Sleep(1000);
	DM->PskKUp(87);
	Sleep(1000);*/

	DM->PskMTo(350, 240);
	DM->PskLClick();



	Sleep(60000);

	DM->PskMTo(20, 345);
	DM->PskLClick();

	Sleep(2000);

	/*DM->PskMTo(210, 310);
	DM->PskLClick();

	Sleep(2000);*/

	DM->PskMTo(295, 265);
	DM->PskLClick();

	Sleep(2000);

	//_bstr_t bstr;
	//string str, size;
	//long x, y, l;

	//std::vector<std::string> result;
	//bstr = DM->PskFindPicE(150, 200, 300, 300, "以后再说.bmp", "000000", 0.9, 0);
	//str = (_bstr_t)bstr;

	//qDebug() << str.c_str();

	//result = CommonUtil::split(str, "|");

	//l = result.size();
	//size = CommonUtil::Long2STR(l);
	//if (l < 3) {
	//	return 0;
	//}

	//x = atol(result[1].c_str());
	//y = atol(result[2].c_str());

	//qDebug() << "yihouzaishuoX=" << result[1].c_str();
	//qDebug() << "yihouzaishuoY=" << result[2].c_str();

	//if (x != -1) {
	//	DM->PskMToEx(x + 2, y + 2, 10, 10);
	//	DM->PskLClick();
	//	return 1;
	//}

	return 0;
}

int TianxiaScript::mapSearchGuagua(Ifire* DM)
{
	generalClose(DM);
	map2Jiuli(DM);
	Sleep(5000);
	mapSearchBtn(DM);

	richangClose(DM);

	HWND hFocusHwnd = (HWND)lHWND;

	const wchar_t * msgTemp = L"旬";
	PostMessageW(hFocusHwnd, WM_CHAR, *msgTemp, 1);

	/*msgTemp = L"舜";
	PostMessageW(hFocusHwnd, WM_CHAR, *msgTemp, 1);*/

	Sleep(1000);

	DM->PskMTo(310, 85);
	DM->PskLClick();

	Sleep(1000);

	DM->PskMTo(250, 110);
	DM->PskLClick();

	Sleep(2000);
	/*DM->PskKDown(87);
	Sleep(1000);
	DM->PskKUp(87);
	Sleep(1000);*/

	DM->PskMTo(350, 240);
	DM->PskLClick();

	Sleep(30000);



	return 0;
}

int TianxiaScript::mapSearchWCMT(Ifire* DM)
{
	generalClose(DM);
	map2Jiuli(DM);
	Sleep(5000);
	mapSearchWCMT2(DM);

	return 0;
}

int TianxiaScript::mapSearchWCMT2(Ifire* DM)
{

	mapSearchBtn(DM);

	richangClose(DM);

	HWND hFocusHwnd = (HWND)lHWND;

	const wchar_t * msgTemp = L"王";
	PostMessageW(hFocusHwnd, WM_CHAR, *msgTemp, 1);

	msgTemp = L"朝";
	PostMessageW(hFocusHwnd, WM_CHAR, *msgTemp, 1);

	msgTemp = L"公";
	PostMessageW(hFocusHwnd, WM_CHAR, *msgTemp, 1);

	msgTemp = L"告";
	PostMessageW(hFocusHwnd, WM_CHAR, *msgTemp, 1);

	Sleep(1000);

	DM->PskMTo(310, 85);
	DM->PskLClick();

	Sleep(1000);

	DM->PskMTo(250, 110);
	DM->PskLClick();

	Sleep(2000);
	/*DM->PskKDown(87);
	Sleep(1000);
	DM->PskKUp(87);
	Sleep(1000);*/

	DM->PskMTo(350, 240);
	DM->PskLClick();

	Sleep(30000);

	DM->PskMTo(20, 345);
	DM->PskLClick();

	Sleep(2000);


	DM->PskMTo(295, 265);
	DM->PskLClick();

	Sleep(2000);

	return 0;
}

int TianxiaScript::mapClose(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(500, 50, 550, 150, "MapCloseBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "MapCloseBtnX=" << result[1].c_str();
	qDebug() << "MapCloseBtnY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(2000);

		return 1;
	}

	return 0;
}

int TianxiaScript::clickJinruSuoyaoBtn(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(450, 200, 550, 300, "JinrusuoyaoBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "JinrusuoyaoBtnX=" << result[1].c_str();
	qDebug() << "JinrusuoyaoBtnY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(2000);

		return 1;
	}

	return 0;
}

int TianxiaScript::clickSuoyaota(Ifire* DM)
{
	DM->PskMTo(20, 345);
	DM->PskLClick();
	Sleep(1000);
	DM->PskMTo(300, 170);
	DM->PskLClick();
	Sleep(1000);
	if (clickJinruSuoyaoBtn(DM) == 1) {
		return 1;
	}


	return 0;
}

int TianxiaScript::findMitanCaozuo(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(450, 50, 520, 130, "密探操作.bmp|MitanCaozuo.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(450, 50, 520, 130, "MitanCaozuo.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "wangchaoCaozuoX=" << result[1].c_str();
	qDebug() << "wangchaoCaozuoY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);

		return 1;
	}

	return 0;
}

int TianxiaScript::map2Jiuli(Ifire* DM)
{
	renwuClose(DM);
	mapClose(DM);

	DM->PskKPress(77);
	Sleep(2000);

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(40, 160, 100, 300, "地图搜索按钮.bmp|DitusousuoBtn.bmp|DituSousuoBtn2.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ditusousuoX=" << result[1].c_str();
	qDebug() << "ditusousuoY=" << result[2].c_str();

	if (x != -1) {

		if (isMapSousuoOpened(DM) == 1) {
			DM->PskMToEx(x + 2, y + 2, 10, 10);
			DM->PskLClick();
			Sleep(2000);
		}

		DM->PskMTo(530, 250);
		DM->PskLClick();
		Sleep(2000);
		DM->PskMTo(305, 240);
		DM->PskLClick();
		Sleep(2000);
		DM->PskMTo(165, 230);
		DM->PskLClick();
		Sleep(2000);
		DM->PskMTo(160, 230);
		DM->PskLClick();
		Sleep(2000);
		DM->PskMTo(340, 240);
		DM->PskLClick();
		Sleep(2000);

		mapClose(DM);
		return 1;
	}

	return 0;
}

int TianxiaScript::findWutongMap(Ifire* DM)
{
	//renwuClose(DM);
	mapClose(DM);

	DM->PskKPress(77);
	Sleep(2000);

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(220, 120, 350, 280, "MapWutong.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "MapWutongX=" << result[1].c_str();
	qDebug() << "MapWutongY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);
		mapClose(DM);
		return 1;
	}

	mapClose(DM);
	return 0;
}

int TianxiaScript::findOpenMap(Ifire* DM)
{
	renwuClose(DM);
	mapClose(DM);

	DM->PskKPress(77);
	Sleep(2000);

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(40, 160, 100, 300, "地图搜索按钮.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ditusousuoX=" << result[1].c_str();
	qDebug() << "ditusousuoY=" << result[2].c_str();

	if (x != -1) {
		mapClose(DM);
		return 1;
	}

	return 0;
}


int TianxiaScript::isMapSousuoOpened(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(250, 50, 350, 150, "搜索.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ssX=" << result[1].c_str();
	qDebug() << "ssY=" << result[2].c_str();

	if (x != -1) {

		return 1;
	}

	return 0;
}

int TianxiaScript::mapSearchBtn(Ifire* DM)
{
	renwuClose(DM);

	DM->PskKPress(77);
	Sleep(2000);

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(40, 160, 100, 300, "地图搜索按钮.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ditusousuoX=" << result[1].c_str();
	qDebug() << "ditusousuoY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(2000);
		DM->PskMTo(120, 80);
		DM->PskLClick();
		Sleep(2000);
		return 1;
	}

	return 0;
}

int TianxiaScript::fubenChumo(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(80, 170, 180, 250, "副本除魔.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "fubenChumoX=" << result[1].c_str();
	qDebug() << "fubenChumoY=" << result[2].c_str();

	if (x != -1) {

		if (fubenChumoSub(DM, x, y) == 0) {
			DM->PskMToEx(x + 2, y + 2, 10, 10);
			DM->PskLClick();
			Sleep(1000);
		}


		return 1;
	}


	return 0;
}

int TianxiaScript::fubenChumoSub(Ifire* DM, long pX, long pY)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(pX, pY - 10, pX + 150, pY + 25, "除魔展开.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "chumoZhankaiX=" << result[1].c_str();
	qDebug() << "chumoZhankaiY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);

		return 1;
	}


	return 0;
}

int TianxiaScript::menpaiJingjiClose(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(180, 140, 260, 220, "门派竞技.bmp|MenpaiJingji.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(180, 140, 260, 220, "MenpaiJingji.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "menpaiJingjiX=" << result[1].c_str();
	qDebug() << "menpaiJingjiY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(250, 240);
		DM->PskLClick();
		Sleep(1000);

		return 1;
	}


	return 0;
}

int TianxiaScript::huoliChuyao(Ifire* DM) {

	int ret = 0;
	if (huoliBtn(DM) == 0) {
		DM->PskKPress(75);
		Sleep(2000);


		if (getCurrentHuoyue(DM) > 100) {
			return 2;
		}
		Sleep(1000);
		if (huoliBtn(DM) == 1) {
			ret = 1;
		}
		Sleep(2000);

		if (this->huoliFlag == true) {
			huoliZhanyaoIn(DM);
		}
		else {
			getMyHuoli(DM);
			if (this->power > 800) {
				this->huoliFlag = true;
				huoliZhanyaoIn(DM);
			}
		}

		if (this->huoyueCheckBox == false) {
			this->huoliFlag = true;
		}

		Sleep(1000);
		zidongwanchengBtn(DM);
		Sleep(1000);
		huoliChuangkouClose(DM);
		Sleep(1000);
		richangClose(DM);
	}


	return ret;
}

int TianxiaScript::huoliHudie(Ifire* DM) {

	int ret = 0;
	if (huoliBtn(DM) == 0) {
		DM->PskKPress(75);
		Sleep(2000);

		if (getCurrentHuoyue(DM) > 100) {
			return 2;
		}
		Sleep(1000);
		if (huoliBtn(DM) == 1) {
			ret = 1;
		}
		Sleep(2000);


		if (this->huoliFlag == true || this->huoyueCheckBox == false) {
			huoliHudieIn(DM);
		}
		/*else {
		int huoli = getMyHuoli(DM);
		if (huoli > 800) {
		huoliHudieIn(DM);
		}
		}*/

		Sleep(1000);
		zidongwanchengBtn(DM);
		Sleep(1000);
		huoliChuangkouClose(DM);
		Sleep(1000);
		richangClose(DM);
	}


	return ret;
}

int TianxiaScript::huoliWeiji(Ifire* DM) {

	int ret = 0;
	if (huoliBtn(DM) == 0) {
		DM->PskKPress(75);
		Sleep(2000);

		if (getCurrentHuoyue(DM) > 100) {
			return 2;
		}
		Sleep(1000);
		if (huoliBtn(DM) == 1) {
			ret = 1;
		}
		Sleep(2000);


		if (this->huoliFlag == true || this->huoyueCheckBox == false) {
			huoliWeijiIn(DM);
		}

		Sleep(1000);
		zidongwanchengBtn(DM);
		Sleep(1000);
		huoliChuangkouClose(DM);
		Sleep(1000);
		richangClose(DM);
	}


	return ret;
}

int TianxiaScript::huoliWuxing(Ifire* DM) {
	int ret = 0;
	if (huoliBtn(DM) == 0) {
		DM->PskKPress(75);
		Sleep(2000);

		if (getCurrentHuoyue(DM) > 100) {
			return 2;
		}
		Sleep(1000);
		if (huoliBtn(DM) == 1) {
			ret = 1;
		}
		Sleep(2000);


		//if (this->huoliFlag == true) {
			huoliWuxingIn(DM);
		//}


		Sleep(1000);
		zidongwanchengBtn(DM);
		Sleep(1000);
		huoliChuangkouClose(DM);
		Sleep(1000);
		richangClose(DM);
	}


	return ret;
}

int TianxiaScript::huoliJingji(Ifire* DM) {

	int ret = 0;
	if (huoliBtn(DM) == 0) {
		DM->PskKPress(75);
		Sleep(2000);

		if (getCurrentHuoyue(DM) > 100) {
			return 2;
		}
		Sleep(1000);
		if (huoliBtn(DM) == 1) {
			ret = 1;
		}
		Sleep(2000);


		if (this->huoliFlag == true || this->huoyueCheckBox == false) {
			huoliJingjiIn(DM);
		}


		Sleep(1000);
		zidongwanchengBtn(DM);
		Sleep(1000);
		huoliChuangkouClose(DM);
		Sleep(1000);
		richangClose(DM);
	}


	return ret;
}


int TianxiaScript::huoliCanglang(Ifire* DM) {

	int ret = 0;
	if (huoliBtn(DM) == 0) {
		DM->PskKPress(75);
		Sleep(2000);
		if (getCurrentHuoyue(DM) > 100) {
			return 2;
		}
		Sleep(1000);
		if (huoliBtn(DM) == 1) {
			ret = 1;
		}
		Sleep(2000);


		if (this->huoliFlag == true || this->huoyueCheckBox == false) {
			huoliCanglangIn(DM);
		}
		/*else {
		int huoli = getMyHuoli(DM);
		if (huoli > 800) {
		huoliCanglangIn(DM);
		}
		}*/

		Sleep(1000);
		zidongwanchengBtn(DM);
		Sleep(1000);
		huoliChuangkouClose(DM);
		Sleep(1000);
		richangClose(DM);
	}


	return ret;
}

int TianxiaScript::checkBaoguoMan(Ifire* DM) {

	zuduiClose(DM);
	richangClose(DM);
	renwuClose(DM);

	if (findBaoguoMan(DM) == 1) {
		qingliBaoguo(DM);
	}

	return 0;
}

int TianxiaScript::findBaoguoMan(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(350, 220, 430, 330, "包裹满.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "baoguoManX=" << result[1].c_str();
	qDebug() << "baoguoManY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);

		return 1;
	}


	return 0;
}

int TianxiaScript::shimenZhandou(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(40, 180, 120, 250, "师门进入战斗.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "shimenZhandouX=" << result[1].c_str();
	qDebug() << "shimenZhandouY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(1000);

		return 1;
	}


	return 0;
}

int TianxiaScript::huoliHuangquan(Ifire* DM) {

	int ret = 0;
	if (huoliBtn(DM) == 0) {
		DM->PskKPress(75);
		Sleep(2000);
		if (getCurrentHuoyue(DM) > 100) {
			return 2;
		}
		Sleep(1000);
		if (huoliBtn(DM) == 1) {
			ret = 1;
		}
		Sleep(2000);


		if (this->huoliFlag == true || this->huoyueCheckBox == false) {
			huoliHuangquanIn(DM);
		}
		/*else {
		int huoli = getMyHuoli(DM);

		if (huoli > 800) {
		huoliHuangquanIn(DM);
		}
		}*/

		Sleep(1000);
		zidongwanchengBtn(DM);
		Sleep(1000);
		huoliChuangkouClose(DM);
		Sleep(1000);
		richangClose(DM);
	}


	return ret;
}

int TianxiaScript::huoliXiaoyao(Ifire* DM) {

	int ret = 0;
	if (huoliBtn(DM) == 0) {
		DM->PskKPress(75);
		Sleep(2000);
		if (getCurrentHuoyue(DM) > 100) {
			return 2;
		}
		Sleep(1000);
		if (huoliBtn(DM) == 1) {
			ret = 1;
		}
		Sleep(2000);

		if (this->huoliFlag == true || this->huoyueCheckBox == false) {
			huoliXiaoyaoIn(DM);
		}
		/*else {
		int huoli = getMyHuoli(DM);
		if (huoli > 800) {
		huoliXiaoyaoIn(DM);
		}
		}*/

		Sleep(1000);
		zidongwanchengBtn(DM);
		Sleep(1000);
		huoliChuangkouClose(DM);
		Sleep(1000);
		richangClose(DM);
	}


	return ret;
}

int TianxiaScript::huoyueLingjiang(Ifire* DM) {

	if (findHuoliBtn(DM) == 0) {
		DM->PskKPress(75);
		Sleep(2000);

	}

	if (findHuoliBtn(DM) == 1) {
		Sleep(1000);
		DM->PskMTo(190, 290);
		Sleep(1000);
		DM->PskLClick();
		Sleep(1000);
		DM->PskMTo(260, 300);
		Sleep(1000);
		DM->PskLClick();
		Sleep(1000);
		DM->PskMTo(330, 300);
		Sleep(1000);
		DM->PskLClick();
		Sleep(1000);
		DM->PskMTo(390, 300);
		Sleep(1000);
		DM->PskLClick();
		Sleep(1000);
		DM->PskMTo(460, 300);
		Sleep(1000);
		DM->PskLClick();
		Sleep(1000);
		scriptIndex++;
	}
	return 0;
}

int TianxiaScript::lingFuliScript(Ifire* DM) {

	if (findFuliWnd(DM) == 0) {
		DM->PskKPress(85);
		Sleep(2000);

	}

	if (findFuliWnd(DM) == 1) {

		/*Sleep(1000);
		meiriQiandao(DM);
		Sleep(1000);
		qiandaoChoujiang(DM);
		Sleep(1000);
		if (this->isBuqian) {

		int pX = 230;
		int pY = 110;

		for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 7; j++) {
		DM->PskMTo(pX + 42 * j, pY + 42 * i);
		DM->PskLClick();
		Sleep(1000);
		qiandaoChoujiang(DM);
		}
		}

		}

		Sleep(1000);*/
		shengjiLibao(DM);

		Sleep(1000);



		fuliClose(DM);
		scriptIndex++;

		return 1;
	}
	return 0;
}

int TianxiaScript::meiriQiandao(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(70, 50, 200, 300, "每日签到.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "meiriQiandaoX=" << result[1].c_str();
	qDebug() << "meiriQiandaoY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(1000);
		DM->PskMTo(245, 315);
		DM->PskLClick();
		Sleep(1000);
		DM->PskMTo(480, 320);
		DM->PskLClick();
		Sleep(1000);
		zhuxianUseBTN(DM);
		Sleep(1000);
		zhuxianUseBTN(DM);
		Sleep(1000);
		return 1;
	}


	return 0;
}

int TianxiaScript::shengjiLibao(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(70, 50, 200, 300, "升级礼包.bmp|ShengjiLibao.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(70, 50, 200, 300, "ShengjiLibao.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "shengjiLibaoX=" << result[1].c_str();
	qDebug() << "shengjiLibaoY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(1000);

		for (int i = 0; i < 5; i++) {
			libaoLingquBtn(DM);
		}

		Sleep(1000);
		DM->PskMTo(380, 280);
		DM->PskLDown();
		Sleep(1000);
		DM->PskMTo(380, 90);
		DM->PskLUp();
		Sleep(1000);
		DM->PskMTo(380, 280);
		DM->PskLDown();
		Sleep(1000);
		DM->PskMTo(380, 90);
		DM->PskLUp();
		Sleep(1000);

		for (int i = 0; i < 5; i++) {
			libaoLingquBtn(DM);
		}

		return 1;
	}


	return 0;
}

int TianxiaScript::libaoLingquBtn(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(400, 50, 550, 360, "礼包领取按钮.bmp|LibaoLingquBtn.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(400, 50, 550, 360, "LibaoLingquBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "libaoLingquBtnX=" << result[1].c_str();
	qDebug() << "libaoLingquBtnY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(1000);

		return 1;
	}


	return 0;
}


int TianxiaScript::tuichuQueding(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(300, 200, 400, 300, "退出确定.bmp|TuichuQueding.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(300, 200, 400, 300, "TuichuQueding.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "tuichuQuedingX=" << result[1].c_str();
	qDebug() << "tuichuQuedingY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(1000);
		DM->PskLClick();

		return 1;
	}


	return 0;
}

int TianxiaScript::huoliChuangkouClose(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(250, 50, 350, 150, "活力窗口.bmp|HuoliWnd.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(250, 50, 350, 150, "HuoliWnd.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "huoliChuangkouX=" << result[1].c_str();
	qDebug() << "huoliChuangkouY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(x + 215, y + 5);
		DM->PskLClick();
		Sleep(1000);

		return 1;
	}


	return 0;
}


int TianxiaScript::huoliZhanyaoIn(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(100, 60, 520, 300, "活力斩妖.bmp|HuoliZhanyao.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(100, 60, 520, 300, "HuoliZhanyao.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "huoliZhanyaoX=" << result[1].c_str();
	qDebug() << "huoliZhanyaoY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(x - 20, y + 5);
		DM->PskLClick();
		Sleep(1000);

		return 1;
	}


	return 0;
}

int TianxiaScript::huoliWeijiIn(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(100, 60, 520, 300, "HuoliHudie.bmp|HLHudie.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(100, 60, 520, 300, "HuoliWeiji.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "HuoliWeijiX=" << result[1].c_str();
	qDebug() << "HuoliWeijiY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(x - 20, y + 5);
		DM->PskLClick();
		Sleep(1000);

		return 1;
	}


	return 0;
}

int TianxiaScript::huoliWuxingIn(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(100, 60, 520, 300, "HuoliHudie.bmp|HLHudie.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(100, 60, 520, 300, "HuoliWuxing.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "HuoliWuxingX=" << result[1].c_str();
	qDebug() << "HuoliWuxingY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(x - 20, y + 5);
		DM->PskLClick();
		Sleep(1000);

		return 1;
	}


	return 0;
}

int TianxiaScript::huoliJingjiIn(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(100, 60, 520, 300, "HuoliJJ.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "HuoliJJX=" << result[1].c_str();
	qDebug() << "HuoliJJY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(x - 20, y + 5);
		DM->PskLClick();
		Sleep(1000);

		return 1;
	}


	return 0;
}

int TianxiaScript::huoliHudieIn(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(100, 60, 520, 300, "HuoliHudie.bmp|HLHudie.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(100, 60, 520, 300, "HLHudie.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "huoliHudieInX=" << result[1].c_str();
	qDebug() << "huoliHudieInY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(x - 20, y + 5);
		DM->PskLClick();
		Sleep(1000);

		return 1;
	}


	return 0;
}

int TianxiaScript::huoliCanglangIn(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(100, 60, 520, 300, "HuoliCanglang.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "huoliCanglangInX=" << result[1].c_str();
	qDebug() << "huoliCanglangInY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(x - 20, y + 5);
		DM->PskLClick();
		Sleep(1000);

		return 1;
	}


	return 0;
}

int TianxiaScript::huoliHuangquanIn(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(100, 60, 520, 300, "活力黄泉.bmp|HuoliHuangquan.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(100, 60, 520, 300, "HuoliHuangquan.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "huoliHuangquanX=" << result[1].c_str();
	qDebug() << "huoliHuangquanY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(x - 20, y + 5);
		DM->PskLClick();
		Sleep(1000);

		return 1;
	}


	return 0;
}

int TianxiaScript::huoliXiaoyaoIn(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(100, 60, 520, 300, "活力逍遥.bmp|HuoliXiaoyao.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(100, 60, 520, 300, "HuoliXiaoyao.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "huoliXiaoyaoX=" << result[1].c_str();
	qDebug() << "huoliXiaoyaoY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(x - 20, y + 5);
		DM->PskLClick();
		Sleep(1000);

		return 1;
	}


	return 0;
}

int TianxiaScript::huoliBtn(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(350, 50, 450, 150, "活力完成.bmp|HuoliWanchengBtn.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(350, 50, 450, 150, "HuoliWanchengBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "huoliWanchengX=" << result[1].c_str();
	qDebug() << "huoliWanchengY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(55, 85);
		DM->PskLClick();
		Sleep(1000);
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(1000);

		return 1;
	}


	return 0;
}

int TianxiaScript::findHuoliBtn(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(350, 50, 450, 150, "活力完成.bmp|HuoliWanchengBtn.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(350, 50, 450, 150, "HuoliWanchengBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "huoliWanchengX=" << result[1].c_str();
	qDebug() << "huoliWanchengY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);

		return 1;
	}


	return 0;
}

int TianxiaScript::findFuliWnd(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(260, 20, 350, 100, "福利窗口.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "fuliWndX=" << result[1].c_str();
	qDebug() << "fuliWndY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);

		return 1;
	}


	return 0;
}

int TianxiaScript::fuliClose(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(260, 20, 350, 100, "福利窗口.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "fuliWndX=" << result[1].c_str();
	qDebug() << "fuliWndY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(540, 50);
		DM->PskLClick();

		Sleep(1000);

		return 1;
	}


	return 0;
}

int TianxiaScript::zidongwanchengBtn(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(350, 250, 500, 350, "自动完成按钮.bmp|ZidongWanchengBtn.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(350, 250, 500, 350, "ZidongWanchengBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "zidongWanchengX=" << result[1].c_str();
	qDebug() << "zidongWanchengY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(1000);

		return 1;
	}


	return 0;
}

int TianxiaScript::qiehuanJuese(Ifire* DM)
{
	if (findShezhiWnd(DM) == 0) {
		DM->PskKPress(121);
		Sleep(2000);

	}

	qiehuanJueseSubScript(DM);


	return 0;
}


int TianxiaScript::reload(Ifire* DM)
{
	if (findShezhiWnd(DM) == 0) {
		DM->PskKPress(121);
		Sleep(2000);


	}

	reloadSubScript(DM);


	return 0;
}

int TianxiaScript::tuoliKadian(Ifire* DM)
{
	if (findShezhiWnd(DM) == 0) {
		DM->PskKPress(121);
		Sleep(2000);


	}

	if (findShezhiWnd(DM) == 1) {
		DM->PskMTo(440, 230);
		DM->PskLClick();
		Sleep(1000);
		DM->PskMTo(340, 240);
		DM->PskLClick();
		Sleep(10000);

	}


	return 0;
}

int TianxiaScript::reloadSubScript(Ifire* DM)
{

	if (findShezhiWnd(DM) == 1) {
		DM->PskMTo(155, 215);
		DM->PskLClick();
		Sleep(2000);
		chongxuanJueseBtn(DM);

		Sleep(2000);
		reloadWindow(DM);
	}
	else {

		if (findZhankaiBtn(DM) == 1) {
			DM->PskMTo(568, 100);
			DM->PskLClick();
			Sleep(2000);
			clickSysIcon(DM);
			Sleep(1000);
			if (findShezhiWnd(DM) == 1) {
				DM->PskMTo(155, 215);
				DM->PskLClick();
				Sleep(2000);
				chongxuanJueseBtn(DM);

				Sleep(2000);
				reloadWindow(DM);
			}
		}
		else {
			richangClose(DM);
			generalClose(DM);
			renwuClose(DM);
			Sleep(2000);
			if (findZhankaiBtn(DM) == 1) {
				DM->PskMTo(568, 100);
				DM->PskLClick();
				Sleep(2000);
				clickSysIcon(DM);
				Sleep(1000);
				if (findShezhiWnd(DM) == 1) {
					DM->PskMTo(155, 215);
					DM->PskLClick();
					Sleep(2000);
					chongxuanJueseBtn(DM);

					Sleep(2000);
					reloadWindow(DM);
				}
			}
		}
	}


	return 0;
}

int TianxiaScript::qiehuanJueseSubScript(Ifire* DM)
{

	if (findShezhiWnd(DM) == 1) {
		DM->PskMTo(155, 215);
		DM->PskLClick();
		Sleep(2000);
		chongxuanJueseBtn(DM);

		Sleep(2000);
		chongxuanWindow(DM);
	}
	else {
		DM->PskKPress(27);
		/*
		if (findZhankaiBtn(DM) == 1) {
		DM->PskMTo(568, 100);
		DM->PskLClick();
		Sleep(2000);
		clickSysIcon(DM);
		Sleep(1000);
		if (findShezhiWnd(DM) == 1) {
		DM->PskMTo(155, 215);
		DM->PskLClick();
		Sleep(2000);
		chongxuanJueseBtn(DM);

		Sleep(2000);
		chongxuanWindow(DM);
		}
		}
		else {
		richangClose(DM);
		generalClose(DM);
		renwuClose(DM);
		Sleep(2000);
		if (findZhankaiBtn(DM) == 1) {
		DM->PskMTo(568, 100);
		DM->PskLClick();
		Sleep(2000);
		clickSysIcon(DM);
		Sleep(1000);
		if (findShezhiWnd(DM) == 1) {
		DM->PskMTo(155, 215);
		DM->PskLClick();
		Sleep(2000);
		chongxuanJueseBtn(DM);

		Sleep(2000);
		chongxuanWindow(DM);
		}
		}
		}*/
	}


	return 0;
}

int TianxiaScript::clickSysIcon(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(490, 100, 600, 280, "SysIcon.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "SysIconX=" << result[1].c_str();
	qDebug() << "SysIconY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(1000);

		return 1;
	}

	bstr = DM->PskFindPicE(490, 100, 600, 280, "SysIcon2.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "SysIconX=" << result[1].c_str();
	qDebug() << "SysIconY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(1000);

		return 1;
	}


	return 0;
}

int TianxiaScript::chongxuanJueseBtn(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(250, 250, 350, 350, "重选角色.bmp|ChongxuanJueseBtn.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(250, 250, 350, 350, "ChongxuanJueseBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "chongxuanJueseX=" << result[1].c_str();
	qDebug() << "chongxuanJueseY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(1000);
		DM->PskMTo(340, 240);
		DM->PskLClick();
		Sleep(15000);

		return 1;
	}


	return 0;
}

int TianxiaScript::chongxuanWindow(Ifire* DM)
{

	if (findDengluBtn(DM) == 0) {
		Sleep(2000);

		return 0;
	}

	if (roleIndex <= this->character_size - 1) {
		roleIndex++;
	}
	else {
		roleIndex = 1;
	}
	TianxiaSingleton* tx = TianxiaSingleton::getInstance();
	QTableWidget* table = tx->table;
	table->setItem(index - 1, 4, new QTableWidgetItem(QString::number(roleIndex)));
	table->cellClicked(index - 1, 4);

	long pX = 45, pY = 70;

	if (roleIndex <= 5) {
		pY = 70;

		DM->PskMTo(90, 70);
		DM->PskLDown();
		Sleep(1000);
		DM->PskMTo(90, 500);
		DM->PskLUp();
		Sleep(1000);
		DM->PskMTo(90, 70);
		DM->PskLDown();
		Sleep(1000);
		DM->PskMTo(90, 500);
		DM->PskLUp();
		Sleep(1000);

		if (roleIndex == 0) {
			DM->PskMTo(pX, pY);
			DM->PskLClick();
		}
		else {
			DM->PskMTo(pX, pY + (roleIndex - 1) * 50);
			DM->PskLClick();
		}

	}
	else {
		pY = 50;

		DM->PskMTo(90, 275);
		DM->PskLDown();
		Sleep(1000);
		DM->PskMTo(90, -50);
		DM->PskLUp();
		Sleep(1000);
		DM->PskMTo(90, 275);
		DM->PskLDown();
		Sleep(1000);
		DM->PskMTo(90, -50);
		DM->PskLUp();
		Sleep(1000);
		DM->PskMTo(90, 275);
		DM->PskLDown();
		Sleep(1000);
		DM->PskMTo(90, -50);
		DM->PskLUp();
		Sleep(1000);

		DM->PskMTo(pX, pY + (roleIndex - 6) * 50);
		DM->PskLClick();
	}

	Sleep(2000);
	clickDengluBtn(DM);
	Sleep(2000);
	if (dongjieQueding(DM) == 1)
	{


		if (this->roleIndex != 0) {
			CommonUtil::upateGold(index, roleIndex, 0);
			this->completeMap.insert(roleIndex, roleIndex);

			QTableWidget* table = tx->table;
			int size = completeMap.size();
			table->setItem(index - 1, 6, new QTableWidgetItem(QString::number(size)));
		}

		chongxuanWindow(DM);
	}

	return 0;
}

int TianxiaScript::dongjieQueding(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(250, 200, 350, 300, "DongjieQueding.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "DongjieQuedingX=" << result[1].c_str();
	qDebug() << "DongjieQuedingY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(1000);

		return 1;
	}


	return 0;
}

int TianxiaScript::reloadWindow(Ifire* DM)
{

	if (findDengluBtn(DM) == 0) {
		Sleep(2000);

		return 0;
	}



	Sleep(2000);
	clickDengluNormal(DM);

	return 0;
}

int TianxiaScript::findDengluBtn(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(450, 300, 600, 400, "登陆游戏按钮.bmp|Denglu_Btn.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(450, 300, 600, 400, "Denglu_Btn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "dengluBtnX=" << result[1].c_str();
	qDebug() << "dengluBtnY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);

		return 1;
	}


	return 0;
}

int TianxiaScript::clickDengluNormal(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(450, 300, 600, 400, "登陆游戏按钮.bmp|Denglu_Btn.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(450, 300, 600, 400, "Denglu_Btn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "dengluBtnX=" << result[1].c_str();
	qDebug() << "dengluBtnY=" << result[2].c_str();

	if (x != -1) {
		if (findCharaChoose(DM) == 1) {
			characterChooseSubScript(DM);
			Sleep(2000);
		}

		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(1000);

		if (clickChongmingBtn(DM) == 1) {
			DM->PskMTo(355, 330);
			DM->PskLClick();
			Sleep(1000);
			DM->PskMToEx(x + 2, y + 2, 10, 10);
			DM->PskLClick();
			Sleep(2000);
		}

		return 1;
	}


	return 0;
}

int TianxiaScript::lapiaoClose(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(250, 60, 350, 160, "YanbingLapiao.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "YanbingLapiaoX=" << result[1].c_str();
	qDebug() << "YanbingLapiaoY=" << result[2].c_str();

	if (x != -1) {

		DM->PskMTo(300, 240);
		DM->PskLClick();
		Sleep(1000);


		return 1;
	}


	return 0;
}

int TianxiaScript::closeUpdate(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(300, 120, 500, 300, "ForUpdate.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ForUpdateX=" << result[1].c_str();
	qDebug() << "ForUpdateY=" << result[2].c_str();

	if (x != -1) {

		DM->PskMTo(460, 270);
		DM->PskLClick();
		Sleep(1000);
		DM->PskMTo(495, 85);
		DM->PskLClick();
		Sleep(1000);

		return 1;
	}


	return 0;
}

int TianxiaScript::characterChooseSubScript(Ifire* DM) {
	long pX = 35, pY = 55;
	int index = 0;

	if (this->charaChoose <= 6) {

		if (this->charaChoose == 0) {
			index = CommonUtil::generateRandomNumberEx(8);
		}
		else {
			index = this->charaChoose;
		}

		/*if (index == 4) {
		index = 3;
		}*/

		DM->PskMTo(pX, pY + (index - 1) * 50);
		DM->PskLClick();

	}
	else {
		int tempNumber = this->index % 5;

		if (tempNumber == 0) {
			index = 1;
		}
		else {
			index = tempNumber;
		}

		DM->PskMTo(pX, pY + (index - 1) * 50);
		DM->PskLClick();
	}




	return 0;
}

int TianxiaScript::findCharaChoose(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(320, 300, 400, 390, "CharaChoose.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "CharaChooseX=" << result[1].c_str();
	qDebug() << "CharaChooseY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(1000);

		return 1;
	}


	return 0;
}

int TianxiaScript::clickChongmingBtn(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(250, 200, 350, 300, "ChongmingQuedingBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ChongmingQuedingBtnX=" << result[1].c_str();
	qDebug() << "ChongmingQuedingBtnY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(1000);

		return 1;
	}


	return 0;
}

int TianxiaScript::clickDengluBtn(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(450, 300, 600, 400, "登陆游戏按钮.bmp|Denglu_Btn.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(450, 300, 600, 400, "Denglu_Btn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "dengluBtnX=" << result[1].c_str();
	qDebug() << "dengluBtnY=" << result[2].c_str();

	if (x != -1) {
		if (findCharaChoose(DM) == 1) {
			characterChooseSubScript(DM);
			Sleep(2000);
		}

		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(2000);

		if (clickChongmingBtn(DM) == 1) {
			DM->PskMTo(355, 330);
			DM->PskLClick();
			Sleep(1000);
			DM->PskMToEx(x + 2, y + 2, 10, 10);
			DM->PskLClick();
			Sleep(2000);
		}

		QString currentTask;
		QJsonValue value = this->scriptList.at(this->scriptIndex);
		if (value.isString()) {
			currentTask = value.toString();
		}

		qDebug() << "currentTask = " << currentTask;

		if (currentTask != "EMBS") {
			stepIndex = TIANXIA_STEPS::AUTH;
			scriptIndex = 0;
			zhuxianIng = true;
			currentLevel = 0;
			mitanCounter = 0;
			shimenCounter = 0;
			wuxingCounter = 0;
			scriptIndex = 0;
			myJinbi = 0;

			this->startTime = timeGetTime();
			//this->isHided = false;
			this->isRepeated = false;
			this->power = 0;
			this->isShimenGoumai = true;
			this->huoliFlag = false;
		}
		else {
			this->subscriptIndex++;
		}




		return 1;
	}


	return 0;
}

int TianxiaScript::findShezhiWnd(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(250, 50, 350, 150, "设置窗口.bmp|ShezhiWnd.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(250, 50, 350, 150, "ShezhiWnd.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "shezhiWndX=" << result[1].c_str();
	qDebug() << "shezhiWndY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);

		return 1;
	}


	return 0;
}

int TianxiaScript::closeShezhiWnd(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(250, 50, 350, 150, "设置窗口.bmp|ShezhiWnd.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(250, 50, 350, 150, "ShezhiWnd.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "shezhiWndX=" << result[1].c_str();
	qDebug() << "shezhiWndY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(485, 60);
		DM->PskLClick();
		Sleep(1000);

		return 1;
	}


	return 0;
}

int TianxiaScript::wugeBaoguo(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(280, 100, 420, 220, "五格包裹.bmp|WugeBaoguo.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(280, 100, 420, 220, "WugeBaoguo.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "wugeBaoguoX=" << result[1].c_str();
	qDebug() << "wugeBaoguoY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(295, 240);
		DM->PskLClick();
		Sleep(1000);

		return 1;
	}


	return 0;
}

int TianxiaScript::generalFuben(Ifire* DM)
{
	renwuClose(DM);
	richangClose(DM);

	DM->PskKPress(84);
	Sleep(2000);
	if (tuiduiBtn(DM) == 1) {
		Sleep(2000);
		DM->PskMTo(340, 240);
		DM->PskLClick();
		Sleep(2000);
	}


	kuaisuZuduiBTN(DM);
	Sleep(2000);

	fubenChumo(DM);



	return 0;
}

int TianxiaScript::tuichuDuiwu(Ifire* DM)
{
	DM->PskKPress(84);
	Sleep(2000);
	if (tuiduiBtn(DM) == 0) {
		this->isInfuben = false;
		Sleep(1000);
		//duiwuClose(DM);
		generalClose(DM);
		return 0;
	}
	Sleep(2000);
	DM->PskMTo(340, 240);
	DM->PskLClick();
	Sleep(2000);

	this->isInfuben = false;
	//DM->PskKPress(84);
	Sleep(1000);
	//duiwuClose(DM);
	generalClose(DM);
	return 0;
}

int TianxiaScript::chuangjianDuiwu(Ifire* DM)
{
	DM->PskKPress(84);
	Sleep(2000);
	if (findTuiduiBtn(DM) == 0) {

		jianduiBtn(DM);
	}

	Sleep(1000);
	generalClose(DM);
	return 0;
}

int TianxiaScript::jianduiBtn(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(50, 250, 150, 350, "创建队伍.bmp|ChuangjianDuiwuBtn.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(50, 250, 150, 350, "ChuangjianDuiwuBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "jianduiBtnX=" << result[1].c_str();
	qDebug() << "jianduiBtnY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		return 1;
	}

	return 0;
}

int TianxiaScript::kaifuLibao(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(70, 150, 200, 350, "KaifuLibao.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "KaifuLibaoX=" << result[1].c_str();
	qDebug() << "KaifuLibaoY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(500, 75);
		DM->PskLClick();
		return 1;
	}

	return 0;
}

int TianxiaScript::huidaoMenpai(Ifire* DM)
{
	DM->PskKPress(77);
	Sleep(3000);
	DM->PskMTo(440, 100);
	DM->PskLClick();
	Sleep(1000);

	mapClose(DM);

	return 0;
}


int TianxiaScript::jingjiZhidianSelect(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(70, 160, 200, 380, "竞技之巅1.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "jingjizhidian1X=" << result[1].c_str();
	qDebug() << "jingjizhidian1Y=" << result[2].c_str();

	if (x != -1) {

		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(1000);
		return 1;
	}

	bstr = DM->PskFindPicE(70, 160, 200, 380, "竞技之巅2.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "jingjizhidian2X=" << result[1].c_str();
	qDebug() << "jingjizhidian2Y=" << result[2].c_str();

	if (x != -1) {

		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(1000);
		return 1;
	}


	return 0;
}

int TianxiaScript::mitanCapMode0(Ifire* DM) {
	if (index == 1 || index == 6 || index == 11 || index == 16 || index == 21 || index == 26) {
		tuichuDuiwu(DM);

		if (wangchaoMitanCap(DM) == 2) {
			tempCounter++;
		}
		else {
			Sleep(1000);
			chuangjianDuiwu(DM);
			Sleep(1000);

			richangClose(DM);
			Sleep(1000);
			mapSearchWCMT(DM);
			Sleep(1000);


			int flag = 0;

			if (findMitanCaozuo(DM) == 1) {
				DM->PskMTo(480, 105);
				DM->PskLClick();
				Sleep(1000);
				DM->PskMTo(480, 310);
				DM->PskLClick();
				Sleep(1000);
				DM->PskMTo(320, 280);
				DM->PskLClick();
				Sleep(1000);
				DM->PskMTo(450, 280);
				DM->PskLClick();
				Sleep(10000);
				flag = 1;
			}

			while (findMitanCaozuo(DM) == 1 && getIsEnded() == false) {
				DM->PskMTo(480, 105);
				DM->PskLClick();
				Sleep(1000);
				DM->PskMTo(480, 310);
				DM->PskLClick();
				Sleep(1000);
				DM->PskMTo(320, 280);
				DM->PskLClick();
				Sleep(1000);
				DM->PskMTo(450, 280);
				DM->PskLClick();
				Sleep(10000);
			}

			if (flag == 1) {
				generalClose(DM);
				Sleep(1000);
				mapSearchWCMT2(DM);
				Sleep(10000);
				if (findMitanCaozuo(DM) == 1 && getIsEnded() == false) {
					DM->PskMTo(480, 105);
					DM->PskLClick();
					Sleep(1000);
					DM->PskMTo(480, 310);
					DM->PskLClick();
					Sleep(1000);
					DM->PskMTo(320, 280);
					DM->PskLClick();
					Sleep(1000);
					DM->PskMTo(450, 280);
					DM->PskLClick();
					Sleep(10000);
					flag = 1;
				}

				int temp = 0;
				while (isInMitan(DM) == 1 && getIsEnded() == false) {
					Sleep(60000);
					temp++;

					if (temp > 5) {
						break;
					}
				}
			}
			tuichuDuiwu(DM);
		}

		if (tempCounter > 3) {
			tuichuDuiwu(DM);
			Sleep(2000);
			scriptIndex++;
			tempCounter = 0;
			return 0;
		}

	}
	else {
		mitanNotCap(DM);
	}
	return 0;
}

int TianxiaScript::mitanCapMode1(Ifire* DM) {
	if (index == 1 || index == 6 || index == 11 || index == 16 || index == 21 || index == 26 || index == 2 || index == 7 || index == 12 || index == 17 || index == 22 || index == 27) {
		tuichuDuiwu(DM);

		if (wangchaoMitanCap(DM) == 2) {
			tempCounter++;
		}
		else {
			Sleep(1000);
			chuangjianDuiwu(DM);
			Sleep(1000);

			richangClose(DM);
			Sleep(1000);
			mapSearchWCMT(DM);
			Sleep(1000);


			int flag = 0;

			if (findMitanCaozuo(DM) == 1) {
				DM->PskMTo(480, 105);
				DM->PskLClick();
				Sleep(1000);
				DM->PskMTo(480, 310);
				DM->PskLClick();
				Sleep(1000);
				DM->PskMTo(320, 280);
				DM->PskLClick();
				Sleep(1000);
				DM->PskMTo(450, 280);
				DM->PskLClick();
				Sleep(10000);
				flag = 1;
			}

			while (findMitanCaozuo(DM) == 1 && getIsEnded() == false) {
				DM->PskMTo(480, 105);
				DM->PskLClick();
				Sleep(1000);
				DM->PskMTo(480, 310);
				DM->PskLClick();
				Sleep(1000);
				DM->PskMTo(320, 280);
				DM->PskLClick();
				Sleep(1000);
				DM->PskMTo(450, 280);
				DM->PskLClick();
				Sleep(10000);
			}

			if (flag == 1) {
				generalClose(DM);
				Sleep(1000);
				mapSearchWCMT2(DM);
				Sleep(10000);
				if (findMitanCaozuo(DM) == 1 && getIsEnded() == false) {
					DM->PskMTo(480, 105);
					DM->PskLClick();
					Sleep(1000);
					DM->PskMTo(480, 310);
					DM->PskLClick();
					Sleep(1000);
					DM->PskMTo(320, 280);
					DM->PskLClick();
					Sleep(1000);
					DM->PskMTo(450, 280);
					DM->PskLClick();
					Sleep(10000);
					flag = 1;
				}

				int temp = 0;
				while (isInMitan(DM) == 1 && getIsEnded() == false) {
					Sleep(60000);
					temp++;

					if (temp > 5) {
						break;
					}
				}
			}
			tuichuDuiwu(DM);
		}

		if (tempCounter > 3) {
			tuichuDuiwu(DM);
			Sleep(2000);
			scriptIndex++;
			tempCounter = 0;
			return 0;
		}

	}
	else {
		mitanNotCap(DM);
	}
	return 0;
}

int TianxiaScript::getYunsPoint(Ifire* DM)
{
	long pX = 130;
	long pY = 85;

	int num = CommonUtil::generateRandomNumberEx(30);
	int xCounter = num % 5;
	int yCounter = num / 5;

	DM->PskMTo(pX + xCounter * 45, pY + yCounter * 45);
	DM->PskLClick();

	return 0;
}

int TianxiaScript::clickYunsAllPoint(Ifire* DM)
{
	long pX = 130;
	long pY = 85;

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 6; j++) {
			DM->PskMTo(pX + j * 45, pY + i * 45);
			DM->PskLClick();
			Sleep(500);
		}
	}

	return 0;
}

int TianxiaScript::yunshiScript(Ifire* DM, long pX, long pY)
{
	if (findZhankaiBtn(DM) == 0) {
		generalClose(DM);
		duiwuClose(DM);
		richangClose(DM);
		jieriClose(DM);
		Sleep(2000);
	}

	if (findZhankaiBtn(DM) == 1 || findYunshiCloseBtn(DM) == 1) {
		DM->PskMTo(pX, pY);
		DM->PskLClick();
		Sleep(3000);
		/*	tempCounter++;
		if (tempCounter >= 3) {
		tempCounter = 0;
		scriptIndex++;
		return 0;
		}*/

		if (findYunshiCloseBtn(DM) == 1) {
			generalClose(DM);
			for (int i = 0; i < 5; i++) {
				getYunsPoint(DM);
				Sleep(1000);
			}

			clickYunsAllPoint(DM);
			scriptIndex++;
			clickYunshiCloseBtn(DM);

			return 1;
		}
		else {
			if (findZhankaiBtn(DM) == 0) {
				newsClose(DM);
			}

		}

		clickYunshiCloseBtn(DM);
	}


	newsClose(DM);
	return 0;
}

int TianxiaScript::theEmbededScript(Ifire* DM) {
	haoyouWndClose(DM);
	shiliChaqi(DM);
	menpaiJingjiClose(DM);
	zhaixingLou(DM);

	int captainParameter = this->index % 5;
	bool isLeader = false;
	if (captainParameter == this->team_param) {
		isLeader = true;
	}
	else {
		isLeader = false;
	}

	TianxiaSingleton* tianxia = TianxiaSingleton::getInstance();
	QTableWidget* table = tianxia->table;
	QString subTask;
	QJsonValue value = this->subscriptArray.at(subscriptIndex);
	if (value.isString()) {
		subTask = value.toString();
	}

	qDebug() << "subTask = " << subTask;

	if (subTask == "DUIQ") {
		table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("子对齐")));
		if (this->roleIndex == 0) {
			qiehuanJuese(DM);

		}

		return 0;
	}

	if (subTask == "JYOU") {
		table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("子交友")));
		if (getLevel(DM) == 0) {
			return 0;
		}

		if (isLeader) {
			if (findXiaoxiWnd(DM) == 0 && findYoujianWnd(DM) == 0) {
				DM->PskKPress(71);
				Sleep(2000);
				DM->PskMTo(550, 115);
				DM->PskLClick();
				Sleep(1000);
				DM->PskMTo(130, 180);
				DM->PskLClick();
				Sleep(1000);

				this->subscriptIndex++;
			}
		}
		else {
			if (findXiaoxiWnd(DM) == 0 && findYoujianWnd(DM) == 0) {
				DM->PskKPress(71);
				Sleep(2000);
				DM->PskMTo(550, 115);
				DM->PskLClick();
				Sleep(1000);
				if (clickHaoyouBtn(DM) == 1) {
					DM->PskMTo(235, 95);
					DM->PskLClick();
					Sleep(1000);

					int multiParam = (this->index - 1) / 5;

					int captainIndex = 5 * multiParam + this->team_param;

					if (getCaptainIndex(captainIndex) != this->roleIndex) {
						return 0;
					}

					if (tianxia->scriptIDMap.size() >= this->index) {
						QHash<int, string>::iterator iter = tianxia->scriptIDMap.find(captainIndex);
						if (iter != tianxia->scriptIDMap.end()) {
							QString captainID = QString::fromStdString(iter.value());

							int length = captainID.length();
							if (length != 0) {
								this->subscriptIndex++;
								for (int i = 0; i < length; i++) {
									QString tempStr = captainID.at(i);
									this->sendStr(tempStr);
								}

								Sleep(1000);
								DM->PskMTo(455, 95);
								DM->PskLClick();
								Sleep(1000);
								DM->PskMTo(270, 130);
								DM->PskLClick();
								Sleep(1000);
								DM->PskMTo(345, 240);
								DM->PskLClick();
								Sleep(1000);
							}

						}

					}

				}

			}



		}


		return 0;
	}

	if (subTask == "TMPT") {
		table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("锁妖塔")));
		if (isLeader) {
			if (subSuoyaota(DM) == 2) {
				tempCounter++;
			}
			else {
				tempCounter = 0;
			}

			if (tempCounter > 2) {

				if (forceExitYanwu2(DM) == 1) {
					this->subscriptIndex++;
				}
				else {
					DM->PskKPress(27);
					Sleep(1000);
				}

			}
		}
		else {

		}

		return 0;
	}

	if (subTask == "TMMT") {
		table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("子密探")));

		if (isLeader) {
			if (subMitan(DM) == 2) {
				tempCounter++;
			}
			else {
				tempCounter = 0;
			}

			if (tempCounter > 2) {

				if (forceExitYanwu2(DM) == 1) {
					this->subscriptIndex++;
				}
				else {
					if (isInMitan(DM) == 0) {
						this->subscriptIndex++;
					}
					DM->PskKPress(27);
					Sleep(1000);
				}

			}
		}
		else {

		}

		return 0;
	}

	if (subTask == "TEAM") {
		table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("子组队")));
		if (isLeader) {

			if (findTuiduiBtn(DM) == 0) {
				DM->PskKPress(84);
				Sleep(2000);

			}
			if (jianduiBtn(DM) == 1) {

				Sleep(1000);
				DM->PskMTo(550, 165);
				DM->PskLClick();
				Sleep(1000);

				int memberCounter = 0;

				int tempCounter = 0;
				while (memberCounter < 4 && getIsEnded() == false) {
					if (clickJieshouDuiwuBtn(DM) == 1) {
						memberCounter++;
					}
					else {
						DM->PskMTo(320, 45);
						DM->PskLClick();
						Sleep(1000);
					}
					Sleep(1000);
				}
				this->subscriptIndex++;
			}




		}
		else {
			if (findHaoyouWnd(DM) == 0 && findYoujianWnd(DM) == 0) {
				DM->PskKPress(71);
				Sleep(2000);
				DM->PskMTo(550, 165);
				DM->PskLClick();
				Sleep(1000);

				if (findHaoyouWnd(DM) == 1) {
					DM->PskMTo(190, 145);
					DM->PskLClick();
					Sleep(1000);
					if (clickShenqingDuiwuBtn(DM) == 1) {
						this->subscriptIndex++;
					}
					else {
						DM->PskMTo(430, 250);
						DM->PskLClick();
						Sleep(1000);
					}

				}

				generalClose(DM);
			}
		}

		DM->PskKPress(27);
	}

	return 0;
}

int TianxiaScript::clickJieshouDuiwuBtn(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(60, 250, 300, 350, "JieshouRuduiBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "JieshouRuduiBtnX=" << result[1].c_str();
	qDebug() << "JieshouRuduiBtnY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(2000);

		return 1;
	}

	return 0;
}

int TianxiaScript::clickShenqingDuiwuBtn(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(280, 180, 360, 300, "ShenqingRuduiBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ShenqingRuduiBtnX=" << result[1].c_str();
	qDebug() << "ShenqingRuduiBtnY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(2000);

		return 1;
	}

	return 0;
}

int TianxiaScript::clickHaoyouBtn(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(130, 50, 200, 150, "HaoyouBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "HaoyouBtnX=" << result[1].c_str();
	qDebug() << "HaoyouBtnY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(2000);

		return 1;
	}

	return 0;
}


int TianxiaScript::changguiTask(Ifire* DM)
{
	QString currentTask;

	int subRet = 101;
	if (subRet == 101) {

		QJsonValue value = this->scriptList.at(scriptIndex);
		if (value.isString()) {
			currentTask = value.toString();
		}

		qDebug() << "currentTask = " << currentTask;
	}

	if (currentTask != "") {
		duihuanJunziWnd(DM);
		forceExitYanwu2(DM);
		tuichuYanwuEx(DM);
		//yanwuJiesuanQueding(DM);
		mapClose(DM);
		richangClose(DM);
		yuandiFuhuo(DM);

		beibaoClose(DM);

		jiahuWndClose(DM);
		//qiandaoChoujiang(DM);
		shangjiaChenggong(DM);

		hechenClose(DM);
		duihuaHuangtiao(DM);
		tianxiaQianzhuang(DM);
		baoxiangLingqu(DM);
		ChuangShiliWnd(DM);
		clickYunshiCloseBtn(DM);
		fuliClose(DM);
		chushouBtn(DM);
		newsClose(DM);
		closeShezhiWnd(DM);
		shangchengClose(DM);

		submitWndClose(DM);
	}

	xiajiaClose(DM);
	jishouQuhui(DM);
	tanweiClose(DM);
	huoliChuangkouClose(DM);

	if (findWanshengClose(DM) == 1) {
		DM->PskMTo(580, 10);
		DM->PskLClick();
	}

	if (currentLevel < 35) {
		if (getLevel(DM) == 1) {
			if (currentLevel < 35 && currentLevel != 0) {

				this->scriptIndex = this->scriptList.size();

			}
		}
	}

	TianxiaSingleton* tx = TianxiaSingleton::getInstance();
	QTableWidget* table = tx->table;






	if (currentTask == "EMBS") {

		while (this->subscriptIndex <= this->subscriptArray.size() && getIsEnded() == false) {
			theEmbededScript(DM);
		}



		return 0;
	}

	if (currentTask == "SMRW") {

		richangClose(DM);
		generalClose(DM);
		mapClose(DM);

		table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("师门任务")));
		shimenCounter++;
		if (shimenCounter > this->shimen_counter) {
			map2Jiuli(DM);
			scriptIndex++;
			return 0;
		}

		if (shimenEx(DM) == 2) {
			tempCounter++;
		}
		else {
			tempCounter = 0;
		}

		if (tempCounter >= 3) {
			scriptIndex++;
			tempCounter = 0;
		}

		shangchengClose(DM);

		return 0;
	}

	if (currentTask == "JOIS") {

		table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("加入势力")));


		if (findShiliWnd(DM) == 0) {
			DM->PskKPress(118);
			Sleep(1000);

			if (findShiliWnd(DM) == 1) {
				clickShenqingShiliBtn(DM);


			}

			if (findShiliWnd(DM) == 1) {
				DM->PskMTo(520, 40);
				DM->PskLClick();
			}
		}

		if (findXinxiWnd(DM) == 1) {
			DM->PskMTo(520, 40);
			DM->PskLClick();
		}
		scriptIndex++;
		return 0;
	}

	if (currentTask == "YUNS") {
		table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("运势")));

		/*long pX = 455, pY = 55;
		int yunshiCounter = 0;
		while (yunshiScript(DM, pX, pY) == 0) {
			pX = pX - 30;
			Sleep(1000);
			yunshiCounter++;
			if (yunshiCounter > 5) {
				scriptIndex++;
				break;
			}

		}*/

		if (findYunshiCloseBtn(DM) == 0) {
			DM->PskKPress(85);
			Sleep(2000);
		}

		if (findYunshiCloseBtn(DM) == 1) {
			generalClose(DM);
			for (int i = 0; i < 5; i++) {
				getYunsPoint(DM);
				Sleep(1000);
			}

			clickYunsAllPoint(DM);
			scriptIndex++;
			clickYunshiCloseBtn(DM);

			return 1;
		}
		else {
			if (findZhankaiBtn(DM) == 0) {
				newsClose(DM);
			}
			if (this->findFuliWnd(DM) == 1) {
				scriptIndex++;
			}

		}

		clickYunshiCloseBtn(DM);

		this->clickChuanchengCloseBtn(DM);
		newsClose(DM);
		return 0;
	}

	if (currentTask == "") {
		table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("切换角色")));
		this->getCurrentLevel(DM);

		if (isHuoliProtected && currentLevel >= 60 && this->power > 1200 && mitanCounter <= 50 && shimenCounter <= 50 && wuxingCounter <= 50 && tianlaoCounter < 5) {
			if (huoyueCheck(DM) == 1) {
				return 0;
			}
		}

		qiehuanJuese(DM);

		return 0;
	}

	if (currentTask == "CWSM") {
		if (this->isRepeated) {
			scriptIndex++;
			return 0;
		}

		table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("宠物寿命")));
		chongwuShouming(DM);

		return 0;
	}

	if (currentTask == "WXP") {

		table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("五行盘")));
		wuxingCounter++;
		if (wuxingCounter > 30) {
			map2Jiuli(DM);
			scriptIndex++;
			return 0;
		}

		if (wuxingpanEx(DM) == 2) {
			tempCounter++;
		}
		else {
			tempCounter = 0;
		}

		if (tempCounter > 2) {
			tempCounter = 0;
			scriptIndex++;
		}

		return 0;
	}

	if (currentTask == "TLZY") {

		tianlaoCounter++;
		if (tianlaoCounter > 5) {
			scriptIndex++;
			return 0;
		}
		table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("天牢之渊")));

		tianlaoZhiyuan(DM);

		tuichuDuiwu(DM);
		//Sleep(10000);
		return 0;
	}

	if (currentTask == "GG") {

		table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("呱呱")));

		guagua(DM);

		return 0;
	}

	if (currentTask == "WSJ") {

		table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("万盛")));

		if (wansheng(DM) == 2) {
			tempCounter++;
		}

		if (tempCounter > 2) {
			tempCounter = 0;
			scriptIndex++;
		}

		return 0;
	}

	if (currentTask == "SHAJ") {

		if (this->isRepeated) {
			scriptIndex++;
			return 0;
		}

		table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("上架")));

		shangjia(DM);

		shangchengClose(DM);
		//Sleep(10000);
		return 0;
	}

	if (currentTask == "XIAJ") {

		if (this->isRepeated) {
			scriptIndex++;
			return 0;
		}
		table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("下架")));

		xiajia(DM);
		shangchengClose(DM);
		//Sleep(10000);
		return 0;
	}

	if (currentTask == "JHJ") {
		chushouBtn(DM);
		if (this->isRepeated) {
			scriptIndex++;
			return 0;
		}
		table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("金币买军")));

		jinhuanJun(DM);

		return 0;
	}

	if (currentTask == "XUEQ") {
		chushouBtn(DM);
		if (this->isRepeated) {
			scriptIndex++;
			return 0;
		}
		table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("雪球")));

		xueqiu(DM);

		return 0;
	}

	if (currentTask == "SAOH") {
		if (this->isRepeated) {
			scriptIndex++;
			return 0;
		}
		table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("扫货")));

		saoJishou(DM);

		return 0;
	}

	if (currentTask == "LQYJ") {
		if (this->isRepeated) {
			scriptIndex++;
			return 0;
		}
		table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("领取邮件")));

		lingquYoujian(DM);

		return 0;
	}

	if (currentTask == "SJJL") {
		if (this->isRepeated) {
			scriptIndex++;
			return 0;
		}
		table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("升级技能")));

		updateSkill(DM);

		return 0;
	}

	if (currentTask == "RWJD") {
		if (this->isRepeated) {
			scriptIndex++;
			return 0;
		}
		table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("人物加点")));
		renwuJiadian(DM);

		return 0;
	}

	if (currentTask == "JJZD") {

		table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("竞技之巅")));

		generalFuben(DM);
		Sleep(1000);
		jingjiZhidianSelect(DM);
		Sleep(1000);
		zidongPipei(DM);
		Sleep(2000);
		fubenJingcheng(DM);

		return 0;
	}

	if (currentTask == "HLCY") {

		table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("活力除妖")));
		tuichuDuiwu(DM);
		if (huoliChuyao(DM) == 1) {
			this->scriptIndex++;
		}

		return 0;
	}

	if (currentTask == "HLWX") {

		table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("活力五行")));
		tuichuDuiwu(DM);
		if (huoliWuxing(DM) == 1) {
			this->scriptIndex++;
		}

		return 0;
	}

	if (currentTask == "HLWJ") {

		table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("活力危机")));
		tuichuDuiwu(DM);
		if (huoliWeiji(DM) == 1) {
			this->scriptIndex++;
		}

		return 0;
	}

	if (currentTask == "HLJJ") {

		table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("活力竞技")));
		tuichuDuiwu(DM);
		if (huoliJingji(DM) == 1) {
			this->scriptIndex++;
		}

		return 0;
	}

	if (currentTask == "HLHD") {

		if (this->huoliFlag == false && this->huoyueCheckBox == true) {
			this->scriptIndex++;
			return 0;
		}

		table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("活力蝴蝶")));

		tuichuDuiwu(DM);
		if (huoliHudie(DM) == 1) {
			this->scriptIndex++;
		}

		return 0;
	}

	if (currentTask == "HLCL") {

		if (this->huoliFlag == false && this->huoyueCheckBox == true) {
			this->scriptIndex++;
			return 0;
		}

		table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("活力苍狼")));

		tuichuDuiwu(DM);
		if (huoliCanglang(DM) == 1) {
			this->scriptIndex++;
		}

		return 0;
	}

	if (currentTask == "HLXY") {

		if (this->huoliFlag == false && this->huoyueCheckBox == true) {
			this->scriptIndex++;
			return 0;
		}

		table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("活力逍遥")));

		tuichuDuiwu(DM);
		if (huoliXiaoyao(DM) == 1) {
			this->scriptIndex++;
		}

		return 0;
	}

	if (currentTask == "HLHQ") {

		if (this->huoliFlag == false && this->huoyueCheckBox == true) {
			this->scriptIndex++;
			return 0;
		}

		table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("活力黄泉")));

		tuichuDuiwu(DM);
		if (huoliHuangquan(DM) == 1) {
			this->scriptIndex++;
		}

		return 0;
	}

	if (currentTask == "HYLJ") {

		table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("活力领奖")));

		huoyueLingjiang(DM);

		return 0;
	}

	if (currentTask == "LQFL") {
		if (this->isRepeated) {
			scriptIndex++;
			return 0;
		}
		table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("领取福利")));


		if (lingFuliScript(DM) == 1) {

		}
		clickYunshiCloseBtn(DM);
		return 0;
	}

	if (currentTask == "WWXP") {

		generalClose(DM);
		table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("挖五行盘")));
		if (waWuxingpan(DM) == 0) {

			Sleep(3000);
			tempCounter = 0;
		}
		else {
			tempCounter++;

		}

		if (tempCounter > 2) {
			tempCounter = 0;
			scriptIndex++;
		}

		return 0;
	}

	if (currentTask == "QLBG") {
		if (this->isRepeated) {
			scriptIndex++;
			return 0;
		}
		newsClose(DM);
		shangchengClose(DM);
		table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("清理包裹")));
		if (qingliBaoguo(DM) == 0) {


		}
		else {
			tempCounter++;

		}

		if (tempCounter > 1) {
			tempCounter = 0;
			scriptIndex++;
		}

		return 0;
	}

	if (currentTask == "KAIB") {
		if (this->isRepeated) {
			scriptIndex++;
			return 0;
		}
		newsClose(DM);
		shangchengClose(DM);
		table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("开包包")));
		if (kaiBaobao(DM) == 0) {


		}
		else {
			tempCounter++;

		}

		if (tempCounter > 1) {
			tempCounter = 0;
			scriptIndex++;
		}

		return 0;
	}

	if (currentTask == "JIXQ") {
		if (this->isRepeated) {
			scriptIndex++;
			return 0;
		}
		newsClose(DM);
		shangchengClose(DM);
		table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("交雪球")));
		if (submitXueqiu(DM) == 0) {


		}
		else {
			tempCounter++;

		}

		if (tempCounter > 1) {
			tempCounter = 0;
			scriptIndex++;
		}

		return 0;
	}

	if (currentTask == "ZBXL") {
		if (this->isRepeated) {
			scriptIndex++;
			return 0;
		}
		table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("装备修理")));

		if (quanshenXiuli(DM) == 0) {


		}
		else {
			tempCounter++;

		}

		if (tempCounter > 2) {
			tempCounter = 0;
			scriptIndex++;
		}

		return 0;
	}

	if (currentTask == "CUNC") {

		if (this->isRepeated) {
			scriptIndex++;
			return 0;
		}
		table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("存仓库")));
		shangchengClose(DM);
		if (cuncangScript(DM) == 0) {
			tempCounter++;

		}


		if (tempCounter > 1) {
			tempCounter = 0;
			scriptIndex++;
		}

		return 0;
	}
	//蒙学乡试
	if (currentTask == "MXXS") {
		table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("蒙学乡试")));
		int currentTime = CommonUtil::getCurrentTimeInt();
		if (this->xiangshiPrefix > currentTime) {
			scriptIndex++;
			return 0;
		}



		if (mengxueXiangshi(DM) == 2) {
			tempCounter++;
		}
		else {
			tempCounter = 0;
		}

		if (tempCounter > 2) {

			scriptIndex++;
			tempCounter = 0;
			return 0;
		}

		return 0;
	}

	if (currentTask == "MPBW") {

		table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("门派比武")));
		menpaiBiwuClose(DM);
		richangClose(DM);
		beibaoClose(DM);

		tuoliKadian(DM);

		int currentTime = CommonUtil::getCurrentTimeInt();
		if (this->biwuPrefix < currentTime && this->biwuSuffix >  currentTime) {
			scriptIndex++;
			return 0;
		}

		if (menpaiBiwu(DM) == 2) {
			tempCounter++;
		}
		else {
			tempCounter = 0;
		}

		if (tempCounter > 2) {

			scriptIndex++;
			tempCounter = 0;
			return 0;
		}
		return 0;
	}

	if (currentTask == "JDQS") {

		table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("吃基")));
		menpaiBiwuClose(DM);
		richangClose(DM);
		beibaoClose(DM);

		int currentTime = CommonUtil::getCurrentTimeInt();
		if (this->juediPrefix > currentTime || this->juediSuffix <  currentTime) {
			scriptIndex++;
			return 0;
		}

		if (juediQiusheng(DM) == 2) {
			tempCounter++;
		}
		else {
			tempCounter = 0;
		}

		if (tempCounter > 2) {

			scriptIndex++;
			tempCounter = 0;
			return 0;
		}
		return 0;
	}

	if (currentTask == "YWT") {

		table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("演武堂")));
		shangchengClose(DM);
		if (yanwutang(DM) == 2) {
			tempCounter++;
		}
		else {
			tempCounter = 0;
		}

		if (tempCounter > 2) {

			scriptIndex++;
			tempCounter = 0;
			return 0;
		}

		jinruYanwutang(DM);
		Sleep(1000);
		if (jinruYanwuBTN(DM) == 0) {
			generalClose(DM);
			shangchengClose(DM);
			huidaoMenpai(DM);
			closeShezhiWnd(DM);
		}
		else {
			Sleep(2000);
			tuichuYanwuShi(DM);
			if (autoCombat(DM) == 1) {
				forceExitYanwu(DM);
			}
			else {
				Sleep(5000);
			}
			if (forceExitYanwu2(DM) == 1) {
				scriptIndex++;
			}
			//Sleep(60000 * 6);
			Sleep(3000);
		}

		mapClose(DM);
		int temp = 0;
		while (isInYanwu(DM) == 1 && getIsEnded() == false) {
			if (autoCombat(DM) == 1) {
				forceExitYanwu(DM);
			}
			mapClose(DM);
			if (forceExitYanwu2(DM) == 1) {
				scriptIndex++;
			}
			quxiaoClose(DM);
			tuichuYanwuShi(DM);
			temp++;
			if (temp > 5) {
				break;
			}
		}

		tuichuYanwuEx(DM);



		return 0;
	}

	if (currentTask == "MJXX") {


		table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("秘境修行")));
		if (mijingXiuxing(DM) == 2) {
			tempCounter++;
		}
		else {
			tempCounter = 0;
		}

		if (tempCounter > 2) {

			scriptIndex++;
			tempCounter = 0;
			return 0;
		}

		jinruYanwutang(DM);
		Sleep(1000);
		if (jinruMijingBTN(DM) == 1) {
			Sleep(5000);
			DM->PskKDown(87);
			Sleep(5000);

			DM->PskKUp(87);
		}
		else {
			generalClose(DM);
			richangClose(DM);
			shangchengClose(DM);
			tuichuDuiwu(DM);
			closeShezhiWnd(DM);
		}
		/*Sleep(5000);
		DM->PskMTo(480, 250);
		DM->PskLClick();
		Sleep(5000);*/
		Sleep(2000);
		if (isInMijing(DM) == 1 && getIsEnded() == false) {
			DM->PskKDown(87);

			int counter = 0;
			while (getIsEnded() == false && baoxiangLingqu(DM) == 0) {
				DM->PskKDown(87);
				counter++;
				DM->PskMTo(200, 200);
				DM->PskLClick();
				if (counter > 15) {
					break;
				}
				Sleep(6000 * 3);
			}

			DM->PskKUp(87);
		}
		else {
			map2Jiuli(DM);
			return 0;
		}
		DM->PskKUp(87);
		/*DM->PskKDown(87);
		Sleep(5000);*/
		baoxiangLingqu(DM);
		return 0;
	}

	if (currentTask == "WCMT") {
		quxiaoClose(DM);

		//changguiJinxingIn(DM);
		table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("王朝密探")));
		mitanCounter++;
		if (mitanCounter > this->mitan_counter) {
			scriptIndex++;
			return 0;
		}


		if (this->isCaptained) {

			if (this->team_mode == "0") {
				mitanCapMode0(DM);
			}
			else if (this->team_mode == "1") {
				mitanCapMode1(DM);
			}
		}
		else {

			mitanNotCap(DM);
		}


		return 0;
	}




	if (currentTask == "KMJB") {

		richangClose(DM);
		generalClose(DM);
		tuichuDuiwu(DM);
		//changguiJinxingIn(DM);
		table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("快马加鞭")));
		//changguiTaskSubScript(DM);
		//kuaimaEx2(DM);

		if (kuaimaJiabianEx(DM) == 2) {

			tempCounter++;

		}
		else {
			tempCounter = 0;
		}

		if (tempCounter > 2) {
			Sleep(2000);
			scriptIndex++;
			tempCounter = 0;
			return 0;
		}

		return 0;
	}

	renwuClose(DM);

	return 0;
}

int TianxiaScript::mitanNotCap(Ifire* DM) {

	if (wangchaoMitan(DM) == 2) {

		tempCounter++;

	}
	else {
		tempCounter = 0;
	}

	if (tempCounter > 3) {
		tuichuDuiwu(DM);
		Sleep(2000);
		scriptIndex++;
		tempCounter = 0;
		return 0;
	}
	Sleep(2000);
	zidongPipei(DM);

	int temp = 0;
	while (isInMitan(DM) == 1 && getIsEnded() == false) {
		Sleep(60000);
		temp++;

		if (temp > 5) {
			break;
		}
	}

	tuichuDuiwu(DM);
	return 0;
}

int TianxiaScript::kaMijing(Ifire* DM) {
	if (isInMijing(DM) == 1) {
		DM->PskMTo(485, 50);
		DM->PskLClick();
	}
	return 0;
}

int TianxiaScript::baoxiangLingqu(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;
	bstr = DM->PskFindPicE(200, 150, 350, 260, "BaoxiangLingqu.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "BaoxiangLingquX=" << result[1].c_str();
	qDebug() << "BaoxiangLingquY=" << result[2].c_str();

	if (x != -1 && y != -1) {
		DM->PskMTo(300, 300);
		DM->PskLClick();
		Sleep(1000);
		DM->PskMTo(460, 200);
		DM->PskLClick();
		Sleep(1000);
		return 1;
	}
	return 0;
}

int TianxiaScript::isInMijing(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;
	/*bstr = DM->PskFindPicE(500, 0, 580, 60, "秘境地图.bmp|MijingDitu.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
	return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "mijinginX=" << result[1].c_str();
	qDebug() << "mijinginY=" << result[2].c_str();

	if (x != -1 && y != -1) {

	Sleep(1000);
	return 1;
	}*/

	//bstr = DM->PskFindPicE(450, 20, 580, 150, "退副本.bmp|TuibenEx.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(450, 20, 580, 150, "TuibenEx.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "tuiFubenX=" << result[1].c_str();
	qDebug() << "tuiFubenY=" << result[2].c_str();

	if (x != -1 && y != -1) {

		Sleep(1000);
		return 1;
	}

	return 0;
}

int TianxiaScript::youshangTuifuben(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;

	bstr = DM->PskFindPicE(450, 20, 580, 150, "右上退副本.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "tuiFubenX=" << result[1].c_str();
	qDebug() << "tuiFubenY=" << result[2].c_str();

	if (x != -1 && y != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(1000);
		DM->PskMTo(340, 240);
		DM->PskLClick();
		Sleep(1000);
		return 1;
	}

	return 0;
}

int TianxiaScript::tuichuYanwuEx(Ifire* DM) {
	if (tuichuFubenBTN(DM) == 1) {
		Sleep(2000);
		DM->PskMTo(345, 240);
		DM->PskLClick();
		Sleep(1000);
		DM->PskLClick();
		//scriptIndex++;
		Sleep(2000);
		tuichuQueding(DM);
		Sleep(2000);
		yanwuJiesuanQueding(DM);

	}

	/*if (tuichuFubenBTNEx(DM) == 1) {

	Sleep(2000);
	if (mapClose(DM) == 1) {
	Sleep(1000);
	generalClose(DM);
	Sleep(1000);
	richangClose(DM);
	Sleep(1000);
	}

	DM->PskMTo(480, 50);
	DM->PskLClick();
	Sleep(2000);
	DM->PskMTo(345, 240);
	DM->PskLClick();
	Sleep(1000);
	DM->PskLClick();
	scriptIndex++;
	Sleep(2000);
	tuichuQueding(DM);
	Sleep(2000);
	yanwuJiesuanQueding(DM);

	}*/

	yanwuJiesuanQueding(DM);
	return 0;
}

int TianxiaScript::tuichuYanwuShi(Ifire* DM) {


	if (findYanwushi(DM) == 1) {

		Sleep(2000);
		forceExitYanwu(DM);

	}
	return 0;
}

int TianxiaScript::forceExitYanwu(Ifire* DM) {

	if (mapClose(DM) == 1) {
		Sleep(1000);
		generalClose(DM);
		Sleep(1000);
		richangClose(DM);
		Sleep(1000);
	}

	DM->PskMTo(480, 50);
	DM->PskLClick();
	Sleep(2000);
	DM->PskMTo(345, 240);
	DM->PskLClick();
	Sleep(1000);
	DM->PskLClick();
	scriptIndex++;
	Sleep(2000);
	tuichuQueding(DM);
	Sleep(2000);
	yanwuJiesuanQueding(DM);


	return 0;
}

int TianxiaScript::forceExitYanwu2(Ifire* DM) {

	if (mapClose(DM) == 1) {
		Sleep(1000);
		generalClose(DM);
		Sleep(1000);
		richangClose(DM);
		Sleep(1000);
	}

	int ret = 0;
	if (clickTuibenBtn(DM) == 1) {
		ret = 1;
	}
	Sleep(2000);
	DM->PskMTo(345, 240);
	DM->PskLClick();
	Sleep(1000);
	DM->PskLClick();
	//scriptIndex++;
	Sleep(2000);
	tuichuQueding(DM);
	Sleep(2000);
	yanwuJiesuanQueding(DM);


	return ret;
}

int TianxiaScript::clickTuibenBtn(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;

	bstr = DM->PskFindPicE(460, 20, 520, 120, "TuibenBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "TuibenBtn=" << result[1].c_str();
	qDebug() << "TuibenBtn=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(1000);
		return 1;
	}

	return 0;
}

int TianxiaScript::findYanwushi(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(250, 0, 300, 50, "演武十.bmp|YanwuShi.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(250, 0, 300, 50, "YanwuShi.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "yanwuShiX=" << result[1].c_str();
	qDebug() << "yanwuShiY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);
		return 1;
	}

	return 0;
}

int TianxiaScript::findChangguiIn(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(70, 50, 180, 120, "常规IN.bmp|ChangguiIn.bmp|ChangguiIn2.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(70, 50, 180, 120, "ChangguiIn.bmp|ChangguiIn2.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "changguiINx=" << result[1].c_str();
	qDebug() << "changguiINy=" << result[2].c_str();

	if (x != -1) {

		DM->PskMTo(x + 2, y + 35);
		DM->PskLClick();
		return 1;
	}

	return 0;
}

int TianxiaScript::findChangguiInZhuxian(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(70, 50, 180, 120, "ChangguiIn.bmp|ChangguiIn2.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "changguiINx=" << result[1].c_str();
	qDebug() << "changguiINy=" << result[2].c_str();

	if (x != -1) {

		return 1;
	}

	return 0;
}

int TianxiaScript::tongguanJiangli(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(250, 150, 350, 250, "通关奖励.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "tongguanX=" << result[1].c_str();
	qDebug() << "tongguanY=" << result[2].c_str();

	if (x != -1) {

		DM->PskMTo(85, 340);
		DM->PskLClick();
		return 1;
	}

	return 0;
}

int TianxiaScript::deleteShimen(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	int ret = 0;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(70, 90, 170, 300, "师门任务1.bmp", "000000", 0.9, 1);
	//str = (_bstr_t)bstr;

	//qDebug() << str.c_str();

	//result = CommonUtil::split(str, "|");

	//l = result.size();
	//size = CommonUtil::Long2STR(l);
	//if (l < 3) {
	//	return 0;
	//}

	//x = atol(result[1].c_str());
	//y = atol(result[2].c_str());

	//qDebug() << "shimenJX=" << result[1].c_str();
	//qDebug() << "shimenJY=" << result[2].c_str();

	//if (x != -1) {
	//	/*DM->PskMToEx(x + 2, y + 2, 10, 10);
	//	DM->PskLClick();*/
	//	Sleep(2000);
	//	ret = 1;
	//}

	//bstr = DM->PskFindPicE(70, 90, 170, 300, "师门任务2.bmp", "000000", 0.9, 1);
	//str = (_bstr_t)bstr;

	//qDebug() << str.c_str();

	//result = CommonUtil::split(str, "|");

	//l = result.size();
	//size = CommonUtil::Long2STR(l);
	//if (l < 3) {
	//	return 0;
	//}

	//x = atol(result[1].c_str());
	//y = atol(result[2].c_str());

	//qDebug() << "shimenJX=" << result[1].c_str();
	//qDebug() << "shimenJY=" << result[2].c_str();

	//if (x != -1) {
	//	/*DM->PskMToEx(x + 2, y + 2, 10, 10);
	//	DM->PskLClick();*/
	//	Sleep(2000);
	//	ret = 1;
	//}
	ret = 1;
	if (ret == 1) {
		DM->PskMTo(230, 310);
		DM->PskLClick();
		Sleep(2000);
		DM->PskMTo(340, 240);
		DM->PskLClick();
		Sleep(2000);
	}

	if (ret == 0) {
		DM->PskMTo(130, 265);
		DM->PskLDown();
		Sleep(1000);
		DM->PskMTo(130, 85);
		DM->PskLUp();
		Sleep(3000);

		deleteShimen(DM);
	}

	return 0;
}

int TianxiaScript::changguiJinxingIn(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(400, 250, 550, 350, "进行IN.bmp|JinxingIn.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(400, 250, 550, 350, "JinxingIn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "changguiINx=" << result[1].c_str();
	qDebug() << "changguiINy=" << result[2].c_str();

	if (x != -1) {
		/*DM->PskKDown(87);
		Sleep(1000);
		DM->PskKUp(87);
		Sleep(1000);*/
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		return 1;
	}

	return 0;
}

int TianxiaScript::clickGongzhanCloseBtn(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(400, 250, 550, 350, "进行IN.bmp|JinxingIn.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(500, 30, 580, 150, "GongzhanCloseBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "GongzhanCloseBtnX=" << result[1].c_str();
	qDebug() << "GongzhanCloseBtnY=" << result[2].c_str();

	if (x != -1) {

		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(1000);
		return 1;
	}

	return 0;
}

int TianxiaScript::fixNameBug(Ifire* DM) {
	if (this->findJueseGaimingWnd(DM) == 1) {

		DM->PskMTo(260, 185);
		DM->PskLClick();
		Sleep(1000);

		for (int i = 0; i < 4; i++) {
			QString test = CommonUtil::getRandomCNChar();
			this->sendStr(test);
			Sleep(500);
		}

		DM->PskMTo(340, 240);
		DM->PskLClick();
		Sleep(2000);

		DM->PskLClick();
		Sleep(1000);
	}

	return 0;
}

int TianxiaScript::findJueseGaimingWnd(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(250, 80, 350, 180, "JueseGaimingWnd.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "JueseGaimingWndX=" << result[1].c_str();
	qDebug() << "JueseGaimingWndY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);
		return 1;
	}

	return 0;
}


int TianxiaScript::shimenJinXing(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	int ret = 0;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(70, 90, 170, 350, "师门J.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "shimenJX=" << result[1].c_str();
	qDebug() << "shimenJY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(2000);
	}

	bstr = DM->PskFindPicE(70, 90, 170, 350, "师门任务1.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "shimenJX=" << result[1].c_str();
	qDebug() << "shimenJY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(2000);
		ret = 1;
	}

	bstr = DM->PskFindPicE(70, 90, 170, 350, "师门任务2.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "shimenJX=" << result[1].c_str();
	qDebug() << "shimenJY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(2000);
		ret = 1;
	}

	if (ret == 1) {
		//bstr = DM->PskFindPicE(400, 250, 550, 350, "进行IN.bmp|JinxingIn.bmp", "000000", 0.9, 0);
		bstr = DM->PskFindPicE(400, 250, 550, 350, "JinxingIn.bmp", "000000", 0.9, 0);
		str = (_bstr_t)bstr;

		qDebug() << str.c_str();

		result = CommonUtil::split(str, "|");

		l = result.size();
		size = CommonUtil::Long2STR(l);
		if (l < 3) {
			return 0;
		}

		x = atol(result[1].c_str());
		y = atol(result[2].c_str());

		qDebug() << "shiminJinxingX=" << result[1].c_str();
		qDebug() << "shiminJinxingY=" << result[2].c_str();

		if (x != -1) {
			/*DM->PskKDown(87);
			Sleep(1000);
			DM->PskKUp(87);
			Sleep(1000);*/

			DM->PskMToEx(x + 2, y + 2, 10, 10);
			DM->PskLClick();
			ret = 1;
			Sleep(10000);
		}
	}



	if (findJishou(DM) == 1) {
		DM->PskMTo(520, 35);
		DM->PskLClick();
		Sleep(2000);
		DM->PskKPress(76);
		Sleep(2000);
		deleteShimen(DM);
	}

	return ret;
}

int TianxiaScript::findJishou(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(200, 40, 320, 100, "公示物品.bmp|GongshiWupin.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(200, 40, 320, 100, "GongshiWupin.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "changguiINx=" << result[1].c_str();
	qDebug() << "changguiINy=" << result[2].c_str();

	if (x != -1) {

		return 1;
	}

	return 0;
}

int TianxiaScript::jishouGoumaiBtn(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(200, 40, 320, 100, "公示物品.bmp|GongshiWupin.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(400, 270, 480, 360, "JishouGoumaiBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "JishouGoumaiBtnX=" << result[1].c_str();
	qDebug() << "JishouGoumaiBtnY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		return 1;
	}

	return 0;
}

int TianxiaScript::jishouGoumaiShuliang(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(200, 40, 320, 100, "公示物品.bmp|GongshiWupin.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(200, 180, 260, 280, "GoumaiShuliang.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "GoumaiShuliangX=" << result[1].c_str();
	qDebug() << "GoumaiShuliangY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(330, 300);
		DM->PskLClick();
		return 1;
	}

	return 0;
}

int TianxiaScript::junziBuzu(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(200, 40, 320, 100, "公示物品.bmp|GongshiWupin.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(170, 130, 270, 230, "JunziBuzu.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "JunziBuzuX=" << result[1].c_str();
	qDebug() << "JunziBuzuY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(495, 70);
		DM->PskLClick();
		return 1;
	}

	return 0;
}

int TianxiaScript::shimenEx(Ifire* DM)
{
	renwuClose(DM);
	goumaiClose(DM);

	if (findShimen(DM) == 0) {

		Sleep(1000);
		if (richangBai(DM) == 0) {
			DM->PskKPress(75);
		}

		Sleep(2000);
		if (getCurrentHuoyue(DM) > 100) {
			return 2;
		}
		Sleep(1000);
		DM->PskMTo(550, 120);
		DM->PskLClick();
		Sleep(2000);
		DM->PskMTo(55, 85);
		DM->PskLClick();
		Sleep(1000);


		if (findShimen(DM) == 0 && richangBai(DM) == 1) {

			return 2;
		}
		/*else if (findShimen(DM) == 0) {
		return 2;
		}*/

		Sleep(5000);

		int theCounter = 0;
		while (duihuaHuangtiao(DM) == 1 && getIsEnded() == false) {
			theCounter++;
			Sleep(1000);
			if (theCounter > 5) {
				theCounter = 0;
				break;
			}
		}

		if (findJishou(DM) == 1) {
			if (isShimenJun && isShimenGoumai) {
				DM->PskMTo(450, 310);
				DM->PskLClick();
				Sleep(2000);
				jishouGoumaiShuliang(DM);
				Sleep(1000);
				if (junziBuzu(DM) == 1) {
					isShimenGoumai = false;
				}
				if (findJishou(DM) == 1) {
					DM->PskMTo(520, 35);
					DM->PskLClick();
				}

			}
			else {
				DM->PskMTo(520, 35);
				DM->PskLClick();
				Sleep(2000);
				DM->PskKPress(76);
				Sleep(2000);
				deleteShimen(DM);
				Sleep(2000);
				generalClose(DM);
			}

		}

		shimenConfirmCircle(DM);
		taskGoumai(DM);
	}

	return 0;
}

int TianxiaScript::wuxingpanEx(Ifire* DM)
{
	renwuClose(DM);
	generalClose(DM);

	if (findWuxingpan(DM) == 0) {

		Sleep(1000);
		if (richangBai(DM) == 0) {
			DM->PskKPress(75);
		}

		/*Sleep(2000);
		getCurrentHuoyue(DM);*/
		Sleep(1000);
		DM->PskMTo(550, 120);
		DM->PskLClick();
		Sleep(2000);


		if (findWuxingpan(DM) == 0 && richangBai(DM) == 1) {

			return 2;
		}


		Sleep(5000);

		int theCounter = 0;
		while (duihuaHuangtiao(DM) == 1 && getIsEnded() == false) {
			theCounter++;
			Sleep(1000);
			if (theCounter > 5) {
				theCounter = 0;
				break;
			}
		}


	}

	return 0;
}

int TianxiaScript::kuaimaEx2(Ifire* DM)
{
	renwuClose(DM);
	generalClose(DM);

	if (findKuaima(DM) == 0) {

		Sleep(1000);
		DM->PskKPress(75);
		Sleep(2000);
		if (getCurrentHuoyue(DM) > 100) {
			return 2;
		}
		Sleep(1000);
		DM->PskMTo(540, 105);
		DM->PskLClick();
		Sleep(2000);

		if (findKuaima(DM) == 0 && richangBai(DM) == 1) {
			scriptIndex++;;
			return 0;
		}


		Sleep(5000);

		DM->PskMTo(20, 350);
		DM->PskLClick();
		Sleep(1000);
		/*DM->PskMTo(210,310);
		DM->PskLClick();
		Sleep(1000);*/
		DM->PskMTo(300, 200);
		DM->PskLClick();
		Sleep(1000);

		/*int theCounter = 0;
		while (duihuaHuangtiao(DM) == 1) {
		theCounter++;
		Sleep(1000);
		if (theCounter > 5) {
		theCounter = 0;
		break;
		}
		}*/
		dianjiTiaoguo(DM);
		Sleep(3000);
		danrenKuaima(DM);
		Sleep(3000);

		while (kuaimaXunhuan(DM) == 1 && getIsEnded() == false) {
			Sleep(5000);
		}
	}

	return 0;
}

int TianxiaScript::findKuaima(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;

	bstr = DM->PskFindPicE(100, 80, 550, 320, "快马加鞭EX.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "kuaimaExX=" << result[1].c_str();
	qDebug() << "kuaimaExY=" << result[2].c_str();

	if (x != -1) {
		/*if (xiangshiComplete(DM, x, y) == 1) {
		scriptIndex++;
		return 0;
		}*/

		if (findJikaiqi(DM, x, y) == 1) {
			scriptIndex++;
			return 1;
		}

		/*DM->PskKDown(87);
		Sleep(1000);
		DM->PskKUp(87);
		Sleep(1000);*/

		DM->PskMTo(x + 150, y + 15);
		DM->PskLClick();
		return 1;
	}

	return 0;
}

int TianxiaScript::findWuxingpan(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;

	//bstr = DM->PskFindPicE(100, 80, 550, 320, "五行盘EX.bmp|Wuxingpan.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(50, 80, 550, 190, "WuxingICON.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "wuxingpanExX=" << result[1].c_str();
	qDebug() << "wuxingpanExX=" << result[2].c_str();

	if (x != -1) {
		if (xiangshiComplete(DM, x, y) == 1) {
			scriptIndex++;
			return 0;
		}

		if (findJikaiqi(DM, x, y) == 1) {
			scriptIndex++;
			return 1;
		}

		/*DM->PskKDown(87);
		Sleep(1000);
		DM->PskKUp(87);
		Sleep(1000);*/

		DM->PskMTo(x + 190, y + 5);
		DM->PskLClick();
		Sleep(10000);
		return 1;
	}

	bstr = DM->PskFindPicE(80, 80, 550, 320, "Wuxingpan.bmp|Wuxingpan2.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "wuxingpanExX=" << result[1].c_str();
	qDebug() << "wuxingpanExX=" << result[2].c_str();

	if (x != -1) {
		if (xiangshiComplete(DM, x, y) == 1) {
			scriptIndex++;
			return 0;
		}

		if (findJikaiqi(DM, x, y) == 1) {
			scriptIndex++;
			return 1;
		}

		/*DM->PskKDown(87);
		Sleep(1000);
		DM->PskKUp(87);
		Sleep(1000);*/

		DM->PskMTo(x + 150, y + 15);
		DM->PskLClick();
		Sleep(10000);
		return 1;
	}

	return 0;
}

int TianxiaScript::clickShenqingShiliBtn(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;

	bstr = DM->PskFindPicE(70, 280, 180, 380, "ShenqingShiliBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ShenqingShiliBtnX=" << result[1].c_str();
	qDebug() << "ShenqingShiliBtnY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(1000);
		return 1;
	}

	return 0;
}

int TianxiaScript::findShiliWnd(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;

	bstr = DM->PskFindPicE(250, 10, 350, 100, "ShiliWnd.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ShiliWndX=" << result[1].c_str();
	qDebug() << "ShiliWndY=" << result[2].c_str();

	if (x != -1) {
		Sleep(1000);
		return 1;
	}

	return 0;
}

int TianxiaScript::findXinxiWnd(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;

	bstr = DM->PskFindPicE(250, 10, 350, 100, "XinxiWnd.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "findXinxiWndX=" << result[1].c_str();
	qDebug() << "findXinxiWndY=" << result[2].c_str();

	if (x != -1) {
		Sleep(1000);
		return 1;
	}

	return 0;
}

int TianxiaScript::findShimen(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;

	//bstr = DM->PskFindPicE(100, 80, 550, 180, "师门任务EX.bmp|ShimenRenwu.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(55, 80, 550, 180, "ShimenJun.bmp|ShimenRenwu2.bmp|ShimenRenwu.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "shimenRwX=" << result[1].c_str();
	qDebug() << "shimenRwY=" << result[2].c_str();

	if (x != -1) {
		if (mitanComplete(DM, x, y) == 1) {
			scriptIndex++;
			return 0;
		}

		if (findJikaiqi(DM, x, y) == 1) {
			scriptIndex++;
			return 1;
		}

		DM->PskMTo(x + 180, y + 5);
		DM->PskLClick();
		Sleep(10000);
		taskGoumai(DM);
		if (this->generalDZCheckBox == true) {
			DM->PskKPress(27);
			Sleep(1000);
			DM->PskKPress(76);
			Sleep(1000);
			if (findGeneralDingzhi(DM, 200, 80) == 1) {
				deleteShimen(DM);
			}
			DM->PskKPress(27);
		}

		return 1;
	}

	bstr = DM->PskFindPicE(100, 80, 550, 180, "ShimenRenwu.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "shimenRwX=" << result[1].c_str();
	qDebug() << "shimenRwY=" << result[2].c_str();

	if (x != -1) {
		if (mitanComplete(DM, x, y) == 1) {
			scriptIndex++;
			return 0;
		}

		if (findJikaiqi(DM, x, y) == 1) {
			scriptIndex++;
			return 1;
		}

		/*DM->PskKDown(65);
		Sleep(300);
		DM->PskKUp(65);
		Sleep(1000);
		DM->PskKDown(68);DM->PskKPress(76);
		Sleep(300);
		DM->PskKUp(68);
		Sleep(1000);*/


		DM->PskMTo(x + 150, y + 15);
		DM->PskLClick();
		Sleep(10000);
		taskGoumai(DM);
		if (this->generalDZCheckBox == true) {
			DM->PskKPress(27);
			Sleep(1000);
			//DM->PskKPress(76);
			DM->PskKPress(76);
			Sleep(1000);
			if (findGeneralDingzhi(DM, 200, 80) == 1) {
				deleteShimen(DM);
			}
			DM->PskKPress(27);
		}

		return 1;
	}
	return 0;
}

int TianxiaScript::richangBai(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;

	//bstr = DM->PskFindPicE(500, 50, 580, 165, "日常白.bmp|RichangBai.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(500, 50, 580, 165, "RichangBai.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "richangbaiX=" << result[1].c_str();
	qDebug() << "richangbaiY=" << result[2].c_str();

	if (x != -1) {

		return 1;
	}

	return 0;
}

int TianxiaScript::tudibaoMing(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;

	//bstr = DM->PskFindPicE(500, 50, 580, 165, "日常白.bmp|RichangBai.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(220, 30, 350, 130, "TudiBaoming.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "TudiBaomingX=" << result[1].c_str();
	qDebug() << "TudiBaomingY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(485, 65);
		DM->PskLClick();
		Sleep(1000);
		return 1;
	}

	return 0;
}


int TianxiaScript::waWuxingpan(Ifire* DM)
{

	richangClose(DM);
	renwuClose(DM);
	duiwuClose(DM);
	generalClose(DM);
	Sleep(2000);

	if (zhengliBeibao(DM) == 0) {
		DM->PskKPress(66);
		Sleep(3000);
		DM->PskMTo(550, 115);
		DM->PskLClick();
		Sleep(2000);

		shangchengClose(DM);

	}

	if (zhengliBeibao(DM) == 0) {
		generalClose(DM);
	}

	int counter = 0;

	while (waWuxingpanSubScript(DM) == 1 && getIsEnded() == false) {
		//zhengliBeibao(DM);
		Sleep(1000);
		//wuxingShiyong(DM);
		if (qingbaoSub4LeftShiyong(DM, 150, 200) == 1) {
			Sleep(60000 * 2);
		}

		counter++;
		if (counter > 50) {
			break;
		}
	}

	if (waWuxingpanSubScript(DM) == 0) {
		return 2;
	}

	return 0;
}

int TianxiaScript::quanshenXiuli(Ifire* DM)
{
	generalClose(DM);
	Sleep(2000);

	if (zhengliBeibao(DM) == 0) {
		//duiClose(DM);
		DM->PskKPress(66);
		Sleep(3000);
		DM->PskMTo(550, 115);
		DM->PskLClick();
		Sleep(2000);
	}

	Sleep(2000);

	getCurrentJunzi(DM);
	Sleep(1000);

	if (xiuliSubScript(DM) == 0) {
		return 2;
	}

	return 0;
}

int TianxiaScript::xiuliSubScript(Ifire* DM)
{
	DM->PskMTo(265, 110);
	DM->PskLClick();
	Sleep(2000);

	qingbaoSub4GengduoEx(DM, 310, 250);
	Sleep(2000);
	quanshenXiuliBtn(DM, 310, 180);
	Sleep(2000);
	DM->PskMTo(345, 240);
	DM->PskLClick();
	Sleep(1000);
	DM->PskMTo(290, 240);
	DM->PskLClick();
	Sleep(1000);
	beibaoClose(DM);

	return 0;
}

int TianxiaScript::quanshenXiuliBtn(Ifire* DM, long pX, long pY)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(pX, pY, pX + 150, pY + 85, "QuanshenXiuli.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "quanshenXiuliX=" << result[1].c_str();
	qDebug() << "quanshenXiuliY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 5, y + 5, 10, 10);
		DM->PskLClick();
		Sleep(2000);
		scriptIndex++;

		return 1;
	}

	return 0;
}

int TianxiaScript::xueqiu(Ifire* DM)
{
	zuduiClose(DM);
	renwuClose(DM);
	Sleep(2000);

	if (zhengliBeibao(DM) == 0) {
		generalClose(DM);
		zuduiClose(DM);
		DM->PskKPress(66);
		Sleep(3000);
		DM->PskMTo(550, 115);
		DM->PskLClick();
		Sleep(2000);
	}
	else {
		generalClose(DM);
		chongfanClose(DM);
	}


	Sleep(2000);


	if (zhengliBeibao(DM) == 1) {
		Sleep(1000);
		getCurrentJunzi(DM);
		Sleep(1000);

		if (findBaobaoXueqiu(DM) == 1) {
			clickZengsongBtn(DM);
			DM->PskMTo(145, 285);
			DM->PskLClick();
			Sleep(1000);

			int length = this->idField.length();
			for (int i = 0; i < length; i++) {
				QString tempStr = idField.at(i);
				this->sendStr(tempStr);
			}
			Sleep(1000);
			DM->PskMTo(225, 285);
			DM->PskLClick();
			Sleep(1000);

			if (clickZhufuBtn(DM) == 1) {
				DM->PskMTo(300, 200);
				DM->PskLClick();
				Sleep(1000);
				DM->PskMTo(375, 125);
				DM->PskLClick();
				Sleep(1000);
				DM->PskMTo(350, 240);
				DM->PskLClick();
				Sleep(1000);
			}


		}
	}
	scriptIndex++;

	return 0;
}

int TianxiaScript::findBaobaoXueqiu(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(450, 30, 560, 120, "背包全部.bmp|BeibaoQuanbu.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(300, 80, 530, 300, "Xueqiu.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "XueqiuX=" << result[1].c_str();
	qDebug() << "XueqiuY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(2000);


		return 1;
	}


	return 0;
}

int TianxiaScript::clickZengsongBtn(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(450, 30, 560, 120, "背包全部.bmp|BeibaoQuanbu.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(150, 200, 260, 310, "ZengzongBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ZengzongBtnX=" << result[1].c_str();
	qDebug() << "ZengzongBtnY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(2000);


		return 1;
	}


	return 0;
}

int TianxiaScript::clickZhufuBtn(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(450, 30, 560, 120, "背包全部.bmp|BeibaoQuanbu.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(460, 90, 525, 120, "ZhufuBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ZhufuBtn=" << result[1].c_str();
	qDebug() << "ZhufuBtn=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(2000);


		return 1;
	}


	return 0;
}


int TianxiaScript::zengsong(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(450, 30, 560, 120, "背包全部.bmp|BeibaoQuanbu.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(450, 30, 560, 120, "BeibaoQuanbu.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "shimenJX=" << result[1].c_str();
	qDebug() << "shimenJY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(2000);
		DM->PskMTo(x + 2, y + 35);
		DM->PskLClick();

		return 1;
	}


	return 0;
}

int TianxiaScript::qingliBaoguo(Ifire* DM)
{
	zuduiClose(DM);
	renwuClose(DM);
	Sleep(2000);

	if (zhengliBeibao(DM) == 0) {
		generalClose(DM);
		zuduiClose(DM);
		DM->PskKPress(66);
		Sleep(3000);
		DM->PskMTo(550, 115);
		DM->PskLClick();
		Sleep(2000);
	}
	else {
		generalClose(DM);
		chongfanClose(DM);
	}


	Sleep(2000);


	if (zhengliBeibao(DM) == 1) {
		Sleep(1000);
		getCurrentJunzi(DM);
		getCurrentJinbi(DM);
		Sleep(1000);

		if (qingliBaoguoSubScript(DM) == 0) {
			return 2;
		}
		else {
			getCurrentJunzi(DM);
			getCurrentJinbi(DM);
		}
	}
	else {
		return 2;
	}


	return 0;
}

int TianxiaScript::kaiBaobao(Ifire* DM)
{
	zuduiClose(DM);
	renwuClose(DM);
	Sleep(2000);

	if (zhengliBeibao(DM) == 0) {
		generalClose(DM);
		zuduiClose(DM);
		DM->PskKPress(66);
		Sleep(3000);
		DM->PskMTo(550, 115);
		DM->PskLClick();
		Sleep(2000);
	}
	else {
		generalClose(DM);
		chongfanClose(DM);
		DM->PskKPress(27);
	}


	Sleep(2000);


	if (zhengliBeibao(DM) == 1) {
		Sleep(1000);
		getCurrentJunzi(DM);
		getCurrentJinbi(DM);
		Sleep(1000);

		if (this->myJinbi < 1000000) {

			scriptIndex++;
			return 0;
		}

		if (kaiBaobaoSubscript(DM) == 1) {
			scriptIndex++;
		}
		else {
			getCurrentJunzi(DM);
			getCurrentJinbi(DM);
		}
	}
	else {
		return 2;
	}

	return 0;
}

int TianxiaScript::kaiBaobaoSubscript(Ifire* DM)
{
	int ret = 0;
	for (int i = 0; i < 4; i++) {
		DM->PskMTo(415, 280);
		DM->PskLDown();
		Sleep(1000);
		DM->PskMTo(415, 110);
		DM->PskLUp();
		Sleep(1000);
		if (clickKaiqigezi(DM) == 1) {
			ret = 1;
			break;
		}
	}

	if (ret == 0) {
		if (clickKaiqigezi(DM) == 1) {
			ret = 1;
		}
	}
	wugeBaoguo(DM);
	return ret;
}

int TianxiaScript::clickKaiqigezi(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(300, 170, 530, 350, "KaiqiGezi.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "KaiqiGeziX=" << result[1].c_str();
	qDebug() << "KaiqiGeziY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(1000);
		kaibaoConfirm(DM);

		return 1;
	}


	return 0;
}

int TianxiaScript::kaibaoConfirm(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(300, 120, 420, 250, "BaoguoRongliangT.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "BaoguoRongliangTX=" << result[1].c_str();
	qDebug() << "BaoguoRongliangTY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(340, 240);
		DM->PskLClick();
		Sleep(1000);

		return 1;
	}


	return 0;
}


int TianxiaScript::submitXueqiu(Ifire* DM)
{
	zuduiClose(DM);
	renwuClose(DM);
	Sleep(2000);

	if (zhengliBeibao(DM) == 0) {
		generalClose(DM);
		zuduiClose(DM);
		DM->PskKPress(66);
		Sleep(3000);
		DM->PskMTo(550, 115);
		DM->PskLClick();
		Sleep(2000);
	}
	else {
		generalClose(DM);
		chongfanClose(DM);
	}


	Sleep(2000);


	if (zhengliBeibao(DM) == 1) {
		Sleep(1000);
		getCurrentJunzi(DM);
		Sleep(1000);

		if (duiXuerenSubScript(DM) == 0) {
			return 2;
		}
		else {
			getCurrentJunzi(DM);
		}
	}
	else {
		return 2;
	}


	return 0;
}

int TianxiaScript::cuncangScript(Ifire* DM)
{
	zuduiClose(DM);
	renwuClose(DM);
	Sleep(2000);

	if (zhengliBeibao(DM) == 0) {
		zuduiClose(DM);
		generalClose(DM);
		DM->PskKPress(66);
		Sleep(3000);
		DM->PskMTo(550, 115);
		DM->PskLClick();
		Sleep(2000);
	}


	Sleep(2000);

	zhengliBeibao(DM);
	Sleep(1000);
	DM->PskMTo(550, 170);
	DM->PskLClick();
	Sleep(1000);
	findNewCuncSubScript(DM);

	cuncangSubScript(DM);


	return 0;
}

int TianxiaScript::findNewCunc(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(250, 10, 340, 100, "培养窗口.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "peiyangWndX=" << result[1].c_str();
	qDebug() << "peiyangWndY=" << result[2].c_str();

	if (x != -1) {
		Sleep(1000);

		return 1;
	}

	return 0;
}

int TianxiaScript::findCangkuJunzi(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(50, 50, 300, 350, "JunziZi.bmp|JunziHuang.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(50, 50, 300, 350, "JunziHuang.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "JunziZiX=" << result[1].c_str();
	qDebug() << "JunziZiY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 5, y + 5, 10, 10);
		DM->PskLClick();
		Sleep(1000);

		return 1;
	}

	return 0;
}

int TianxiaScript::findCangkuXueqiu(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(50, 50, 300, 350, "JunziZi.bmp|JunziHuang.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(50, 50, 300, 350, "Xueqiu.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "XueqiuX=" << result[1].c_str();
	qDebug() << "XueqiuY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 5, y + 5, 10, 10);
		DM->PskLClick();
		Sleep(1000);

		return 1;
	}

	return 0;
}

int TianxiaScript::findCangkuLihe(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(50, 50, 300, 350, "HuodongHezi.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "HuodongHeziX=" << result[1].c_str();
	qDebug() << "HuodongHeziY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 5, y + 5, 10, 10);
		DM->PskLClick();
		Sleep(1000);

		return 1;
	}

	return 0;
}

int TianxiaScript::quhuiBaoguo(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(250, 150, 450, 350, "QuhuiBaoguo.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "QuhuiBaoguoX=" << result[1].c_str();
	qDebug() << "QuhuiBaoguoY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(1000);

		return 1;
	}

	return 0;
}

int TianxiaScript::findNewCuncSubScript(Ifire* DM)
{
	int cuncIndex = 1;
	if (findCangkuLihe(DM) == 1) {
		quhuiBaoguo(DM);
	}
	if (findCangkuJunzi(DM) == 1) {
		quhuiBaoguo(DM);
	}

	while (isCangkuMan(DM) && getIsEnded() == false) {
		cuncIndex++;
		Sleep(1000);


		cuncSelector(DM, cuncIndex);
		Sleep(1000);

		if (findCangkuLihe(DM) == 1) {
			quhuiBaoguo(DM);
		}
		if (findCangkuJunzi(DM) == 1) {
			quhuiBaoguo(DM);
		}
		if (findCangkuXueqiu(DM) == 1) {
			quhuiBaoguo(DM);
		}
	}

	return 0;
}

int TianxiaScript::cuncSelector(Ifire* DM, int cuncIndex)
{
	DM->PskMTo(120, 70);
	DM->PskLClick();
	Sleep(1000);

	switch (cuncIndex)
	{
	case 2:
	{
		DM->PskMTo(175, 110);
		DM->PskLClick();
		Sleep(1000);
		if (JiesuoCangku(DM) == 1) {
			DM->PskMTo(175, 110);
			DM->PskLClick();
			Sleep(1000);
		}
	}
	break;
	case 3:
	{
		DM->PskMTo(250, 110);
		DM->PskLClick();
		Sleep(1000);
		if (JiesuoCangku(DM) == 1) {
			DM->PskMTo(250, 110);
			DM->PskLClick();
			Sleep(1000);
		}
	}
	break;
	case 4:
	{
		DM->PskMTo(110, 150);
		DM->PskLClick();
		Sleep(1000);
		if (JiesuoCangku(DM) == 1) {
			DM->PskMTo(110, 150);
			DM->PskLClick();
			Sleep(1000);
		}
	}
	break;
	case 5:
	{
		DM->PskMTo(175, 150);
		DM->PskLClick();
		Sleep(1000);
		if (JiesuoCangku(DM) == 1) {
			DM->PskMTo(175, 150);
			DM->PskLClick();
			Sleep(1000);
		}
	}
	break;
	case 6:
	{
		DM->PskMTo(250, 150);
		DM->PskLClick();
		Sleep(1000);
		if (JiesuoCangku(DM) == 1) {
			DM->PskMTo(250, 150);
			DM->PskLClick();
			Sleep(1000);
		}
	}
	break;
	default:
		break;
	}

	return 0;
}

int TianxiaScript::isCangkuMan(Ifire* DM)
{
	int ret = 0;
	DM->PskMTo(260, 270);
	DM->PskLClick();
	Sleep(2000);
	ret = findQuhuiBaoguoBtn(DM);
	DM->PskMTo(410, 30);
	DM->PskLDoubleClick();

	return ret;
}

int TianxiaScript::JiesuoCangku(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(250, 120, 350, 220, "JiesuoCang.bmp|JiesuoCangku.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(250, 120, 350, 220, "JiesuoCangku.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "JiesuoCangX=" << result[1].c_str();
	qDebug() << "JiesuoCangY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(340, 240);
		DM->PskLClick();
		Sleep(1000);

		return 1;
	}

	return 0;
}

int TianxiaScript::ChuangShiliWnd(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(250, 50, 350, 220, "ChuangShiliWnd.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "JiesuoCangX=" << result[1].c_str();
	qDebug() << "JiesuoCangY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(485, 65);
		DM->PskLClick();
		Sleep(1000);

		return 1;
	}

	return 0;
}

int TianxiaScript::findQuhuiBaoguoBtn(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(300, 200, 380, 300, "QuhuiBaoguoBtn.bmp|QuhuiBtn.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(300, 200, 380, 300, "QuhuiBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "QuhuiBaoguoBtnX=" << result[1].c_str();
	qDebug() << "QuhuiBaoguoBtnY=" << result[2].c_str();

	if (x != -1) {
		Sleep(1000);

		return 1;
	}

	return 0;
}


int TianxiaScript::findPeiyangWnd(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(250, 10, 340, 100, "培养窗口.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "peiyangWndX=" << result[1].c_str();
	qDebug() << "peiyangWndY=" << result[2].c_str();

	if (x != -1) {
		Sleep(1000);

		return 1;
	}

	return 0;
}

int TianxiaScript::chongwuShouming(Ifire* DM)
{
	generalClose(DM);
	renwuClose(DM);
	Sleep(2000);
	if (findPeiyangWnd(DM) == 0) {
		DM->PskKPress(88);
		Sleep(2000);
		DM->PskMTo(550, 165);
		DM->PskLClick();
		Sleep(1000);
	}

	if (findPeiyangWnd(DM) == 1) {
		DM->PskMTo(460, 250);
		DM->PskLClick();
		Sleep(1000);
		DM->PskMTo(435, 200);
		DM->PskLClick();
		Sleep(1000);
		DM->PskMTo(415, 290);
		DM->PskLClick();
		Sleep(1000);
		DM->PskMTo(435, 200);
		DM->PskLClick();
		Sleep(1000);
		/*DM->PskMTo(250, 205);
		DM->PskLClick();
		Sleep(2000);
		if (taskGoumai(DM) == 1) {
		Sleep(1000);
		shangchengClose(DM);
		Sleep(2000);
		DM->PskMTo(415, 290);
		DM->PskLClick();
		Sleep(1000);
		DM->PskMTo(435, 200);
		DM->PskLClick();
		Sleep(1000);
		}*/

		generalClose(DM);
		scriptIndex++;
	}

	return 0;
}

int TianxiaScript::cuncangSubScript(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	long pX = 330, pY = 105;

	for (int j = 0; j < 5 && getIsEnded() == false; j++) {
		for (int i = 0; i < 5 && getIsEnded() == false; i++) {
			DM->PskMTo(pX + 45 * i, pY + 45 * j);
			DM->PskLClick();
			Sleep(2000);
			/*DM->PskMTo(380,75);
			DM->PskLClick();
			Sleep(1000);*/
			if (cuncangSub4WXP(DM) == 1) {

			}
			else if (cuncangSub4Xueqiu(DM) == 1) {

			}
			else if (cuncangSub4JieriBaoxiang(DM) == 1) {

			}
			else if (cuncangSub4Yuezuan(DM) == 1) {

			}
			else if (cuncangSub4Jinbi(DM) == 1) {

			}
			else if (cuncangSub4Junzi(DM) == 1) {

			}
			else if (cuncangSub4Rizuan(DM) == 1) {

			}
			else if (cuncangSub4Wuxingshi(DM) == 1) {

			}
			else if (cuncangSub4Liuyaoshi(DM) == 1) {

			}
			else if (cuncangSub4BiwuJiajiang(DM) == 1) {

			}
			else if (cuncangSub4Dahuandan(DM) == 1) {

			}
			else if (cuncang4Juexingdan(DM) == 1) {

			}
			else if (cuncang4Fangcun(DM) == 1) {

			}
			else if (cuncang4JinJiaoyi(DM) == 1) {

			}
			else {
				if (findLeftCuncang(DM) == 0 && findRightCuncang(DM) == 0) {
					if (j >= 3) {
						scriptIndex++;
					}

					return 0;
				}
			}


			DM->PskMTo(410, 30);
			DM->PskLDoubleClick();
			Sleep(1000);
		}
	}

	return 0;
}

int TianxiaScript::qingliBaoguoSubScript(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	long pX = 330, pY = 105;

	for (int j = 0; j < 5 && getIsEnded() == false; j++) {
		for (int i = 0; i < 5 && getIsEnded() == false; i++) {
			DM->PskMTo(pX + 45 * i, pY + 45 * j);
			DM->PskLClick();
			Sleep(2000);
			/*DM->PskMTo(380,75);
			DM->PskLClick();
			Sleep(1000);*/
			int tempRet = qingbaoTaozhuang(DM);

			if (qingbaoSub4Gengduo(DM) == 1) {


				if (qingbaoSub4Weiling(DM) != 1) {

				}
				else {
					/*if (jiagaoTishiCancel(DM) == 0) {
					if (tempRet == 1) {
					zhenpinCancel(DM);
					}
					else {
					zhenpinConfirm(DM);
					}
					}*/
					if (tempRet == 1) {
						zhenpinCancel(DM);
					}
					else {
						zhenpinConfirm(DM);
					}
				}
			}
			else if (qingbaoSub4LeftZhuangbei(DM) == 1) {

			}
			else if (qingbaoSub4Xueqiu(DM) == 1) {

			}
			else if (qingbaoSub4Canhun(DM) == 1) {

			}
			else if (qingbaoSub4Lihe(DM) == 1) {

			}
			else if (qingbaoSub4WXP(DM) == 1) {

			}
			else if (qingbaoSub4Dahuandan(DM) == 1) {
				/*qingbaoSub4Dahuandan(DM);
				qingbaoSub4Yuye(DM);*/
			}
			else if (qingbaoSub4Yuye(DM) == 1) {

			}
			else if (qingbaoSub4BiwuJiajiang(DM) == 1) {

			}
			else if (qingbaoSub4Jinbi(DM) == 1) {

			}
			else if (qingbaoSub4Rizuan(DM) == 1) {

			}
			else if (qingbaoSub4Liuyaoshi(DM) == 1) {

			}
			else if (qingbaoSub4Junzi(DM) == 1) {

			}
			else if (qingbaoSub4Yuezuan(DM) == 1) {

			}
			else if (qingbaoSub4ZhuangbeiLibao(DM) == 1) {

			}
			/*else if (qingbaoSub4Xumingdan(DM) == 1) {

			}*/
			else if (qingbaoSub4QuandeKuizeng(DM) == 1) {

			}
			else if (qingbaoSub4ShimingLibao(DM) == 1) {

			}
			else if (qingbaoSub4Huaxuedan(DM) == 1) {

			}
			else if (qingbaoSub4Wuxingshi(DM) == 1) {

			}
			else if (qingbaoSub4Huilingdan(DM) == 1) {

			}
			else if (qingbaoSub4DuizhangLibao(DM) == 1) {

			}
			else if (qingbaoSub4QifuTiadeng(DM) == 1) {

			}
			else if (qingbaoSub4Hecheng(DM) == 1) {

			}
			else {
				if (findQingbaoGengduo(DM) == 0 && findQingbaoShiyong(DM) == 0) {
					if (j >= 3) {
						scriptIndex++;
					}
					break;
				}
				//break;
			}

			DM->PskMTo(410, 30);
			DM->PskLDoubleClick();
			Sleep(1000);
		}
	}

	return 0;
}

int TianxiaScript::duiXuerenSubScript(Ifire* DM)
{

	clickDuixueItem(DM);
	if (submitDuixueItem(DM) == 1) {
		Sleep(10000);
		if (submitDuixueItemStep2(DM) == 1) {
			Sleep(2000);
			DM->PskMTo(330, 220);
			DM->PskLClick();
			Sleep(1000);
			DM->PskMTo(440, 180);
			DM->PskLClick();
			Sleep(500);
			DM->PskLClick();
			Sleep(500);
			DM->PskLClick();
			Sleep(500);
			DM->PskLClick();
			Sleep(500);
			DM->PskLClick();
			Sleep(1000);
			DM->PskMTo(295, 290);
			DM->PskLClick();
			Sleep(1000);
			if (submitWndClose(DM) == 1) {
				scriptIndex++;
			}
		}

		return 1;
	}


	return 0;
}

int TianxiaScript::clickDuixueItem(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(305, 80, 525, 350, "DuixuerenIcon.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "DuixuerenIconY=" << result[1].c_str();
	qDebug() << "DuixuerenIconX=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 5, y + 5, 10, 10);
		DM->PskLClick();
		Sleep(1000);

		return 1;
	}

	return 0;
}

int TianxiaScript::submitDuixueItem(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(180, 220, 250, 300, "SubmitXueduiItemBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "SubmitXueduiItemBtnX=" << result[1].c_str();
	qDebug() << "SubmitXueduiItemBtnY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 5, y + 5, 10, 10);
		DM->PskLClick();
		Sleep(1000);

		return 1;
	}

	return 0;
}

int TianxiaScript::submitDuixueItemStep2(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(460, 215, 550, 300, "Wolaila.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "WolailaX=" << result[1].c_str();
	qDebug() << "WolailaY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 5, y + 5, 10, 10);
		DM->PskLClick();
		Sleep(1000);

		return 1;
	}

	return 0;
}

int TianxiaScript::submitWndClose(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(250, 30, 350, 120, "SubmitWnd.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "SubmitWndX=" << result[1].c_str();
	qDebug() << "SubmitWndY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(485, 60);
		DM->PskLClick();
		Sleep(1000);

		return 1;
	}

	return 0;
}

int TianxiaScript::qingbaoSub4Gengduo(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(280, 200, 540, 350, "清包更多.bmp|QingbaoGengduo.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(280, 200, 540, 350, "QingbaoGengduo.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "qingbaoGengduoX=" << result[1].c_str();
	qDebug() << "qingbaoGengduoY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 5, y + 5, 10, 10);
		DM->PskLClick();
		Sleep(2000);

		return 1;
	}

	return 0;
}

int TianxiaScript::shangtongClose(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(450, 20, 510, 130, "伤害统计关闭.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "shangtongCloseX=" << result[1].c_str();
	qDebug() << "shangtongCloseY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 5, y + 5, 10, 10);
		DM->PskLClick();
		Sleep(2000);

		return 1;
	}

	return 0;
}

int TianxiaScript::qingbaoSub4BiwuJiajiang(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(80, 100, 300, 200, "比武嘉奖.bmp|BiwuJiajiang.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(80, 100, 300, 200, "BiwuJiajiang.bmp|Libao.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "biwuJiajiangX=" << result[1].c_str();
	qDebug() << "biwuJiajiangY=" << result[2].c_str();

	if (x != -1) {
		qingbaoSub4LeftShiyong(DM, 150, 200);
		Sleep(1000);

		return 1;
	}

	return 0;
}

int TianxiaScript::cuncangSub4BiwuJiajiang(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(80, 100, 300, 200, "比武嘉奖.bmp|BiwuJiajiang.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(80, 100, 300, 200, "BiwuJiajiang.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "biwuJiajiangX=" << result[1].c_str();
	qDebug() << "biwuJiajiangY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);

		return 1;
	}

	return 0;
}

int TianxiaScript::qingbaoSub4QuandeKuizeng(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(80, 100, 300, 200, "QuandeKuizen.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "quandeKuizengX=" << result[1].c_str();
	qDebug() << "quandeKuizengY=" << result[2].c_str();

	if (x != -1) {
		qingbaoSub4LeftShiyong(DM, 150, 200);
		Sleep(1000);

		return 1;
	}

	return 0;
}

int TianxiaScript::qingbaoSub4ShimingLibao(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(80, 100, 300, 200, "实名认证.bmp|ShimingLihe.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(80, 100, 300, 200, "ShimingLihe.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "shimingX=" << result[1].c_str();
	qDebug() << "shimingY=" << result[2].c_str();

	if (x != -1) {
		qingbaoSub4LeftShiyong(DM, 150, 200);
		Sleep(1000);

		return 1;
	}

	return 0;
}

int TianxiaScript::qingbaoSub4ZhuangbeiLibao(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(80, 100, 300, 200, "装备礼包.bmp|Fuyunjiaozi.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "zhuangbeiLibaoX=" << result[1].c_str();
	qDebug() << "zhuangbeiLibaoY=" << result[2].c_str();

	if (x != -1) {
		qingbaoSub4LeftShiyong(DM, 150, 220);
		Sleep(1000);

		return 1;
	}

	return 0;
}

int TianxiaScript::qingbaoSub4DuizhangLibao(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(80, 100, 300, 200, "DuiZhangLibao1.bmp|DuizhangLibao2.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "duizhangLibaoX=" << result[1].c_str();
	qDebug() << "duizhangLibaoY=" << result[2].c_str();

	if (x != -1) {
		qingbaoSub4LeftShiyong(DM, 150, 200);
		Sleep(1000);

		return 1;
	}

	return 0;
}

int TianxiaScript::qingbaoSub4QifuTiadeng(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(50, 100, 300, 200, "祈福天灯.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "qifuTiandengX=" << result[1].c_str();
	qDebug() << "qifuTiandengY=" << result[2].c_str();

	if (x != -1) {
		qingbaoSub4LeftShiyong(DM, 150, 200);
		Sleep(1000);

		return 1;
	}

	return 0;
}

int TianxiaScript::qingbaoSub4Hecheng(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(180, 220, 240, 300, "合成按钮.bmp|HechengBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "hechengX=" << result[1].c_str();
	qDebug() << "hechengY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(1000);
		DM->PskMTo(300, 280);
		DM->PskLClick();
		Sleep(1000);
		DM->PskLClick();
		Sleep(1000);
		DM->PskLClick();
		Sleep(1000);
		DM->PskLClick();
		Sleep(1000);
		DM->PskLClick();
		Sleep(1000);
		hechenClose(DM);
		return 1;
	}

	return 0;
}


int TianxiaScript::timerChecker()
{
	DWORD onlineTime = timeGetTime() - this->startTime;

	long timeMin = onlineTime / 1000 / 60;

	TianxiaSingleton* tx = TianxiaSingleton::getInstance();
	QTableWidget* table = tx->table;

	table->setItem(index - 1, 7, new QTableWidgetItem(QString::number(timeMin)));
	//table->setItem(index - 1, 1, new QTableWidgetItem(QString::fromLocal8Bit("000000")));

	if (timeMin > 60) {
		if (this->stepIndex == TIANXIA_STEPS::ZHUXIAN) {
			this->stepIndex = TIANXIA_STEPS::CHANGGUI;
			this->scriptIndex = this->scriptList.size();
		}

	}

	if (timeMin > time_limit) {
		if (this->stepIndex == TIANXIA_STEPS::CHANGGUI || this->stepIndex == TIANXIA_STEPS::ZHUXIAN) {
			//this->stepIndex = TIANXIA_STEPS::CHANGGUI;
			this->scriptIndex = this->scriptList.size();
		}

	}
	return 0;
}


int TianxiaScript::hechenClose(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(250, 35, 350, 120, "HechengWnd.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "hechengX=" << result[1].c_str();
	qDebug() << "hechengY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(485, 65);
		DM->PskLClick();
		Sleep(1000);
		return 1;
	}

	return 0;
}

int TianxiaScript::qingbaoSub4WXP(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(50, 100, 300, 200, "五行盘.bmp|QingbaoWuxing.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(50, 100, 300, 200, "QingbaoWuxing.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "wuxingpanX=" << result[1].c_str();
	qDebug() << "wuxingpanY=" << result[2].c_str();

	if (x != -1) {
		qingbaoSub4LeftShiyong(DM, 150, 200);
		Sleep(60000);

		return 1;
	}

	return 0;
}

int TianxiaScript::cuncangSub4Yuezuan(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(80, 100, 300, 200, "QingbaoYuezuan.bmp|Zhizuoshu.bmp|QuandeKuizen.bmp|DuiZhangLibao1.bmp|DuizhangLibao2.bmp|Fuyunjiaozi.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "qingbaoYuezuanX=" << result[1].c_str();
	qDebug() << "qingbaoYuezuanY=" << result[2].c_str();

	if (x != -1) {
		/*qingbaoSub4ChushouEx(DM, 70, 220);
		Sleep(1000);
		chushouBtn(DM);*/
		Sleep(1000);

		return 1;
	}

	return 0;
}

int TianxiaScript::cuncangSub4WXP(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(50, 100, 300, 200, "五行盘.bmp||QingbaoWuxing.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(50, 100, 300, 200, "QingbaoWuxing.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "wuxingpanX=" << result[1].c_str();
	qDebug() << "wuxingpanY=" << result[2].c_str();

	if (x != -1) {
		//qingbaoSub4LeftShiyong(DM, 150, 200);
		Sleep(1000);

		return 1;
	}

	Sleep(500);
	return 0;
}

int TianxiaScript::cuncangSub4Xueqiu(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(50, 100, 300, 200, "五行盘.bmp||QingbaoWuxing.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(50, 80, 300, 200, "XiaoXuedui.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "XueqiuX=" << result[1].c_str();
	qDebug() << "XueqiuY=" << result[2].c_str();

	if (x != -1) {
		//qingbaoSub4LeftShiyong(DM, 150, 200);
		Sleep(1000);

		return 1;
	}

	Sleep(500);
	return 0;
}

int TianxiaScript::cuncangSub4Junzi(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;

	//bstr = DM->PskFindPicE(80, 100, 300, 220, "清包军资.bmp|QingbaoJunzi.bmp|JunziP.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(80, 100, 300, 220, "QingbaoJunzi.bmp|JunziP.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "qingbaoJunziX=" << result[1].c_str();
	qDebug() << "qingbaoJunziY=" << result[2].c_str();

	if (x != -1) {
		//qingbaoSub4LeftShiyongQuanbu(DM, 50, 200);
		Sleep(1000);

		return 1;
	}

	Sleep(500);
	//bstr = DM->PskFindPicE(80, 100, 300, 220, "Junzi1500.bmp", "000000", 0.9, 0);
	//str = (_bstr_t)bstr;

	//qDebug() << str.c_str();

	//result = CommonUtil::split(str, "|");

	//l = result.size();
	//size = CommonUtil::Long2STR(l);
	//if (l < 3) {
	//	return 0;
	//}

	//x = atol(result[1].c_str());
	//y = atol(result[2].c_str());

	//qDebug() << "qingbaoJunziX=" << result[1].c_str();
	//qDebug() << "qingbaoJunziY=" << result[2].c_str();

	//if (x != -1) {
	//	//qingbaoSub4LeftShiyongQuanbu(DM, 50, 200);
	//	Sleep(1000);

	//	return 1;
	//}
	return 0;
}

int TianxiaScript::qingbaoSub4Huilingdan(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(80, 100, 300, 200, "Huilingdan.bmp|Jingyanfu.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "huidingdanX=" << result[1].c_str();
	qDebug() << "huidingdanY=" << result[2].c_str();

	if (x != -1) {
		qingbaoSub4LeftShiyong(DM, 150, 200);
		//qingbaoSub4LeftShiyongQuanbu(DM, 150, 200);
		Sleep(1000);

		return 1;
	}
	Sleep(500);
	return 0;
}

int TianxiaScript::findQingbaoGengduo(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(50, 100, 300, 350, "QingbaoGengduo.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "QingbaoGengduoX=" << result[1].c_str();
	qDebug() << "QingbaoGengduoY=" << result[2].c_str();

	if (x != -1) {
		Sleep(1000);

		return 1;
	}
	Sleep(500);
	return 0;
}

int TianxiaScript::findQingbaoShiyong(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(100, 100, 350, 350, "QingbaoShiyong.bmp|QingbaoShiyongBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "findQingbaoShiyong=" << result[1].c_str();
	qDebug() << "findQingbaoShiyong=" << result[2].c_str();

	if (x != -1) {
		Sleep(1000);

		return 1;
	}
	Sleep(500);
	return 0;
}

int TianxiaScript::qingbaoSub4Rizuan(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(80, 100, 300, 200, "清包日钻.bmp|QingbaoRizuan.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(80, 100, 300, 200, "QingbaoRizuan.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "qingbaoRizuanX=" << result[1].c_str();
	qDebug() << "qingbaoRizuanY=" << result[2].c_str();

	if (x != -1) {
		if (this->rizuanBox) {
			qingbaoSub4ChushouEx(DM, 70, 220);
			Sleep(1000);
			chushouBtn(DM);
			Sleep(1000);
		}

		return 1;
	}
	Sleep(500);
	return 0;
}

int TianxiaScript::cuncangSub4Rizuan(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(80, 100, 300, 200, "清包日钻.bmp|QingbaoRizuan", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(80, 100, 300, 200, "QingbaoRizuan|Huilingdan.bmp|Jingyanfu.bmp|Libao.bmp|JiuJiu.bmp|Zizhidan.bmp|DuiZhangLibao1.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "qingbaoRizuanX=" << result[1].c_str();
	qDebug() << "qingbaoRizuanY=" << result[2].c_str();

	if (x != -1) {
		/*qingbaoSub4ChushouEx(DM, 70, 220);
		Sleep(1000);
		chushouBtn(DM);*/
		Sleep(1000);

		return 1;
	}
	Sleep(500);
	return 0;
}

int TianxiaScript::qingbaoSub4Yuezuan(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(80, 100, 300, 200, "QingbaoYuezuan.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "qingbaoYuezuanX=" << result[1].c_str();
	qDebug() << "qingbaoYuezuanY=" << result[2].c_str();

	if (x != -1) {
		if (this->yuezuanBox) {
			qingbaoSub4ChushouEx(DM, 70, 220);
			Sleep(1000);
			chushouBtn(DM);
			Sleep(1000);
		}

		return 1;
	}
	Sleep(500);
	return 0;
}

int TianxiaScript::qingbaoSub4Wuxingshi(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(80, 100, 300, 200, "五行石.bmp|Wuxingshi.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(80, 100, 300, 200, "Wuxingshi.bmp|WuxiaZhiyu.bmp|Zhizuoshu.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "wuxingshiX=" << result[1].c_str();
	qDebug() << "wuxingshiY=" << result[2].c_str();

	if (x != -1) {
		qingbaoSub4ChushouEx(DM, 70, 220);
		Sleep(1000);
		chushouBtn(DM);
		Sleep(1000);

		return 1;
	}
	Sleep(500);
	return 0;
}

int TianxiaScript::cuncangSub4Wuxingshi(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(80, 100, 300, 200, "五行石.bmp|Wuxingshi.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(80, 100, 300, 200, "Wuxingshi.bmp|WuxiaZhiyu.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "wuxingshiX=" << result[1].c_str();
	qDebug() << "wuxingshiY=" << result[2].c_str();

	if (x != -1) {
		/*qingbaoSub4ChushouEx(DM, 70, 220);
		Sleep(1000);
		chushouBtn(DM);*/
		Sleep(1000);

		return 1;
	}
	Sleep(500);
	return 0;
}

int TianxiaScript::qingbaoSub4Liuyaoshi(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(80, 100, 300, 200, "清包六爻石.bmp|QingbaoLiuyao.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(80, 100, 300, 200, "QingbaoLiuyao.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "qingbaoliuyaoshiX=" << result[1].c_str();
	qDebug() << "qingbaoliuyaoshiY=" << result[2].c_str();

	if (x != -1) {
		if (this->liuyaoBox) {
			qingbaoSub4ChushouEx(DM, 70, 220);
			Sleep(1000);
			chushouBtn(DM);
			Sleep(1000);
		}

		return 1;
	}
	Sleep(500);
	return 0;
}

int TianxiaScript::cuncangSub4Liuyaoshi(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(80, 100, 300, 200, "清包六爻石.bmp|QingbaoLiuyao.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(80, 100, 300, 200, "QingbaoLiuyao.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "qingbaoliuyaoshiX=" << result[1].c_str();
	qDebug() << "qingbaoliuyaoshiY=" << result[2].c_str();

	if (x != -1) {
		/*qingbaoSub4ChushouEx(DM, 70, 220);
		Sleep(1000);
		chushouBtn(DM);*/
		Sleep(1000);

		return 1;
	}
	Sleep(500);
	return 0;
}

int TianxiaScript::jiangchiLingjiang(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(220, 250, 340, 350, "JiangchiLingjiang.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "JiangchiLingjiangX=" << result[1].c_str();
	qDebug() << "JiangchiLingjiangY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(1000);
		DM->PskMTo(560, 25);
		DM->PskLClick();
		Sleep(1000);

		return 1;
	}

	return 0;
}



int TianxiaScript::qingbaoSub4Jinbi(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(80, 100, 300, 200, "清包金币.bmp|Qingbaojinbi1.bmp|QingbaoJinbi2.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(80, 100, 300, 200, "Qingbaojinbi1.bmp|QingbaoJinbi2.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "qingbaoJinbiX=" << result[1].c_str();
	qDebug() << "qingbaoJinbiY=" << result[2].c_str();

	if (x != -1) {
		qingbaoSub4LeftShiyongQuanbu(DM, 50, 200);
		Sleep(1000);

		return 1;
	}

	Sleep(500);
	return 0;
}

int TianxiaScript::qingbaoSub4Lihe(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(80, 100, 300, 200, "Lihe.bmp|LibaoHuang.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "LiheX=" << result[1].c_str();
	qDebug() << "LiheY=" << result[2].c_str();

	if (x != -1) {
		qingbaoSub4LeftShiyongQuanbu(DM, 50, 200);
		Sleep(1000);
		tianxiaQianzhuang(DM);

		return 1;
	}
	Sleep(500);
	return 0;
}

int TianxiaScript::tianxiaQianzhuang(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(240, 20, 350, 90, "TianxiaQianzhuang.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "TianxiaQianzhuangX=" << result[1].c_str();
	qDebug() << "TianxiaQianzhuangY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(520, 35);
		DM->PskLClick();
		Sleep(1000);

		return 1;
	}

	return 0;
}

int TianxiaScript::cuncangSub4Jinbi(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(80, 100, 300, 200, "Qingbaojinbi1.bmp|QingbaoJinbi2.bmp", "000000", 0.9, 0);

	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "qingbaoJinbiX=" << result[1].c_str();
	qDebug() << "qingbaoJinbiY=" << result[2].c_str();

	if (x != -1) {
		//qingbaoSub4LeftShiyongQuanbu(DM, 50, 200);
		Sleep(1000);

		return 1;
	}

	Sleep(500);

	return 0;
}

int TianxiaScript::cuncangSub4JieriBaoxiang(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(120, 50, 300, 150, "JieriBaoxiang.bmp|Baoxiang.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "JieriBaoxiangX=" << result[1].c_str();
	qDebug() << "JieriBaoxiangY=" << result[2].c_str();

	if (x != -1) {
		//qingbaoSub4LeftShiyongQuanbu(DM, 50, 200);
		Sleep(1000);

		return 1;
	}
	Sleep(500);
	return 0;
}

int TianxiaScript::qingbaoSub4Junzi(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(80, 100, 300, 220, "清包军资.bmp|QingbaoJunzi.bmp|JunziP.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(80, 100, 300, 220, "QingbaoJunzi.bmp|JunziP.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "qingbaoJunziX=" << result[1].c_str();
	qDebug() << "qingbaoJunziY=" << result[2].c_str();

	if (x != -1) {
		if (isYongjun) {
			qingbaoSub4LeftShiyongQuanbu(DM, 50, 200);
		}
		//qingbaoSub4LeftShiyongQuanbu(DM, 50, 200);
		Sleep(1000);

		return 1;
	}

	bstr = DM->PskFindPicE(80, 100, 300, 220, "Junzi1500.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "Junzi1500X=" << result[1].c_str();
	qDebug() << "Junzi1500Y=" << result[2].c_str();

	if (x != -1) {
		if (isYongjun) {
			qingbaoSub4LeftShiyongQuanbu(DM, 50, 200);
		}
		Sleep(1000);

		return 1;
	}
	return 0;
}

int TianxiaScript::leftCuncang(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(100, 200, 290, 320, "存仓按钮.bmp|CuncangBtn.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(100, 200, 290, 320, "CuncangBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "cuncangBtnX=" << result[1].c_str();
	qDebug() << "cuncangBtnY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(1000);

		return 1;
	}

	return 0;
}


int TianxiaScript::findLeftCuncang(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(100, 200, 290, 320, "存仓按钮.bmp|CuncangBtn.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(100, 200, 290, 320, "CuncangBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "cuncangBtnX=" << result[1].c_str();
	qDebug() << "cuncangBtnY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);

		return 1;
	}

	return 0;
}

int TianxiaScript::findRightCuncang(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(100, 200, 290, 320, "存仓按钮.bmp|CuncangBtn.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(350, 200, 550, 380, "RightCuncangBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "RightCuncangBtnX=" << result[1].c_str();
	qDebug() << "RightCuncangBtnY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);

		return 1;
	}

	return 0;
}


int TianxiaScript::rightCuncang(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(350, 260, 550, 380, "存仓按钮.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "cuncangBtnX=" << result[1].c_str();
	qDebug() << "cuncangBtnY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(1000);

		return 1;
	}

	return 0;
}

int TianxiaScript::qingbaoSub4LeftShiyong(Ifire* DM, long pX, long pY)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(pX, pY, pX + 150, pY + 80, "清包使用.bmp|QingbaoShiyong.bmp|QingbaoShiyongBtn.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(pX, pY, pX + 150, pY + 80, "QingbaoShiyong.bmp|QingbaoShiyongBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "qingbaoShiyongX=" << result[1].c_str();
	qDebug() << "qingbaoShiyongY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(1000);

		return 1;
	}

	return 0;
}

int TianxiaScript::qingbaoSub4LeftShiyongQuanbu(Ifire* DM, long pX, long pY)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(pX, pY, pX + 150, pY + 80, "清包使用全部.bmp|ShiyongQuanbu.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(pX, pY, pX + 150, pY + 80, "ShiyongQuanbu.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "qingbaoShiyongAllX=" << result[1].c_str();
	qDebug() << "qingbaoShiyongAllY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(1000);

		return 1;
	}

	return 0;
}

int TianxiaScript::qingbaoSub4Dahuandan(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(80, 120, 165, 200, "大还丹.bmp|Dahuandan.bmp", "000000", 0.9, 0);

	bstr = DM->PskFindPicE(80, 120, 165, 200, "Dahuandan.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "dahuandanX=" << result[1].c_str();
	qDebug() << "dahuandanY=" << result[2].c_str();

	if (x != -1) {

		Sleep(2000);
		qingbaoSub4GengduoEx(DM, x - 50, y + 30);
		Sleep(1000);
		qingbaoSub4ChushouEx(DM, x - 50, y + 20);
		Sleep(1000);
		chushouBtn(DM);
		return 1;
	}

	return 0;
}

int TianxiaScript::qingbaoSub4Canhun(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(80, 120, 165, 200, "大还丹.bmp|Dahuandan.bmp", "000000", 0.9, 0);

	bstr = DM->PskFindPicE(80, 120, 165, 200, "CanHun.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "CanHunX=" << result[1].c_str();
	qDebug() << "CanHunY=" << result[2].c_str();

	if (x != -1) {

		Sleep(2000);
		qingbaoSub4GengduoEx(DM, x - 100, y + 60);
		Sleep(1000);
		qingbaoSub4ChushouEx(DM, x - 100, y + 60);
		Sleep(1000);
		chushouBtn(DM);
		return 1;
	}

	return 0;
}

int TianxiaScript::qingbaoSub4Xueqiu(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(80, 120, 165, 200, "大还丹.bmp|Dahuandan.bmp", "000000", 0.9, 0);

	bstr = DM->PskFindPicE(80, 80, 165, 200, "QingbaoXueqiu.bmp|XiaoXuedui.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "XueqiuX=" << result[1].c_str();
	qDebug() << "XueqiuY=" << result[2].c_str();

	if (x != -1) {

		qingbaoSub4GengduoEx(DM, x - 50, y + 70);
		Sleep(1000);
		qingbaoSub4LeftShiyongQuanbu(DM, 50, 200);
		Sleep(1000);

		return 1;
	}

	return 0;
}

int TianxiaScript::cuncangSub4Dahuandan(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(80, 120, 165, 200, "大还丹.bmp|Dahuandan.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(80, 120, 165, 200, "Dahuandan.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "dahuandanX=" << result[1].c_str();
	qDebug() << "dahuandanY=" << result[2].c_str();

	if (x != -1) {

		/*Sleep(2000);
		qingbaoSub4GengduoEx(DM, x - 50, y + 30);
		Sleep(1000);
		qingbaoSub4ChushouEx(DM, x - 50, y + 20);*/
		Sleep(1000);
		//chushouBtn(DM);
		return 1;
	}
	Sleep(500);
	return 0;
}

int TianxiaScript::qingbaoSub4Xumingdan(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(80, 120, 165, 200, "续命丹小.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "xumingdanX=" << result[1].c_str();
	qDebug() << "xumingdanY=" << result[2].c_str();

	if (x != -1) {

		Sleep(2000);
		qingbaoSub4GengduoEx(DM, x - 50, y + 30);
		Sleep(1000);
		qingbaoSub4ChushouEx(DM, x - 50, y + 20);
		Sleep(1000);
		chushouBtn(DM);
		return 1;
	}

	bstr = DM->PskFindPicE(80, 120, 165, 200, "续命丹大.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "xumingdanX=" << result[1].c_str();
	qDebug() << "xumingdanX=" << result[2].c_str();

	if (x != -1) {

		Sleep(2000);
		qingbaoSub4GengduoEx(DM, x - 50, y + 30);
		Sleep(1000);
		qingbaoSub4ChushouEx(DM, x - 50, y + 20);
		Sleep(1000);
		chushouBtn(DM);
		return 1;
	}

	return 0;
}

int TianxiaScript::qingbaoSub4Huaxuedan(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(80, 120, 165, 200, "化雪丹.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "huaxuedanX=" << result[1].c_str();
	qDebug() << "huaxuedanY=" << result[2].c_str();

	if (x != -1) {

		Sleep(2000);
		qingbaoSub4GengduoEx(DM, x - 50, y + 30);
		Sleep(1000);
		qingbaoSub4ChushouEx(DM, x - 50, y + 20);
		Sleep(1000);
		chushouBtn(DM);
		return 1;
	}


	return 0;
}

int TianxiaScript::cuncang4Juexingdan(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(70, 120, 200, 200, "明心丹.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "mingxindanX=" << result[1].c_str();
	qDebug() << "mingxindanY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);
		leftCuncang(DM);

		return 1;
	}

	return 0;
}

int TianxiaScript::cuncang4Qilin(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(70, 120, 200, 200, "麒麟.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "qilinX=" << result[1].c_str();
	qDebug() << "qilinY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);
		leftCuncang(DM);

		return 1;
	}

	return 0;
}

int TianxiaScript::cuncang4JinJiaoyi(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(45, 120, 130, 270, "禁止交易.bmp|JinzhiJiaoyi.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(45, 120, 130, 270, "JinzhiJiaoyi.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "jinjiaoyiX=" << result[1].c_str();
	qDebug() << "jinjiaoyiY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);
		leftCuncang(DM);

		return 1;
	}

	return 0;
}

int TianxiaScript::cuncang4Fangcun(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(70, 100, 200, 200, "方寸灵台.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "fangcunX=" << result[1].c_str();
	qDebug() << "fangcunY=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);
		leftCuncang(DM);

		return 1;
	}

	return 0;
}

int TianxiaScript::qingbaoSub4Yuye(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(80, 120, 165, 200, "玉液.bmp|QingbaoYuye.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(80, 120, 165, 200, "QingbaoYuye.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "yuyeX=" << result[1].c_str();
	qDebug() << "yuyeY=" << result[2].c_str();

	if (x != -1) {

		Sleep(2000);
		qingbaoSub4GengduoEx(DM, x - 50, y + 30);
		Sleep(1000);
		qingbaoSub4ChushouEx(DM, x - 50, y + 20);
		Sleep(1000);
		chushouBtn(DM);
		return 1;
	}

	return 0;
}

int TianxiaScript::chushouBtn(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	/*bstr = DM->PskFindPicE(250, 240, 350, 350, "出售按钮.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
	return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "chushouX=" << result[1].c_str();
	qDebug() << "chushouY=" << result[2].c_str();

	if (x != -1) {

	DM->PskMToEx(x + 2, y + 2, 10, 10);
	DM->PskLClick();
	return 1;
	}
	*/
	//bstr = DM->PskFindPicE(200, 150, 300, 250, "清包售价.bmp|QingbaoShoujia.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(200, 150, 300, 250, "QingbaoShoujia.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "shoujiaX=" << result[1].c_str();
	qDebug() << "shoujiaY=" << result[2].c_str();

	if (x != -1) {

		DM->PskMTo(300, 300);
		DM->PskLClick();
		return 1;
	}

	return 0;
}


int TianxiaScript::qingbaoSub4GengduoEx(Ifire* DM, long pX, long pY)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(pX, pY, pX + 150, pY + 85, "清包更多.bmp|QingbaoGengduo.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(pX, pY, pX + 150, pY + 85, "QingbaoGengduo.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "qingbaoGengduoX=" << result[1].c_str();
	qDebug() << "qingbaoGengduoY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 5, y + 5, 10, 10);
		DM->PskLClick();
		Sleep(2000);

		return 1;
	}

	return 0;
}

int TianxiaScript::qingbaoSub4ChushouEx(Ifire* DM, long pX, long pY)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(pX, pY, pX + 150, pY + 85, "清包出售.bmp|QingbaoChushou.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(pX, pY, pX + 150, pY + 85, "QingbaoChushou.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "qingbaoGengduoX=" << result[1].c_str();
	qDebug() << "qingbaoGengduoY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 5, y + 5, 10, 10);
		DM->PskLClick();
		Sleep(2000);

		return 1;
	}

	return 0;
}

int TianxiaScript::qingbaoSub4Weiling(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(280, 50, 540, 200, "清包喂灵.bmp|QingbaoWeiling.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(280, 50, 540, 200, "QingbaoWeiling.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "qingbaoWeilingX=" << result[1].c_str();
	qDebug() << "qingbaoWeilingY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 5, y + 5, 10, 10);
		DM->PskLClick();
		Sleep(2000);

		return 1;
	}

	return 0;
}

int TianxiaScript::qingbaoSub4LeftZhuangbei(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(280, 50, 540, 200, "清包喂灵.bmp|QingbaoWeiling.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(150, 220, 300, 350, "LeftZhuangbei.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "LeftZhuangbeiX=" << result[1].c_str();
	qDebug() << "LeftZhuangbeiY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(1000);
		qingbaoSub4ZhuangbeiJJY(DM);

		return 1;
	}

	return 0;
}

int TianxiaScript::qingbaoSub4ZhuangbeiJJY(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(280, 50, 540, 200, "清包喂灵.bmp|QingbaoWeiling.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(250, 120, 350, 250, "ZhuagbeiJjy.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ZhuagbeiJjyX=" << result[1].c_str();
	qDebug() << "ZhuagbeiJjyY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(340, 240);
		DM->PskLClick();
		Sleep(1000);

		return 1;
	}

	return 0;
}

int TianxiaScript::qingbaoTaozhuang(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(300, 200, 380, 280, "Taozhuang5.bmp|Taozhuang6.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(300, 200, 380, 280, "Taozhuang6.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "Taozhuang5x=" << result[1].c_str();
	qDebug() << "Taozhuang5y=" << result[2].c_str();

	if (x != -1) {

		Sleep(1000);

		return 1;
	}

	return 0;
}

int TianxiaScript::waWuxingpanSubScript(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(290, 60, 500, 350, "五行盘ICON.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "wuxingX=" << result[1].c_str();
	qDebug() << "wuxingY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 5, y + 5, 10, 10);
		DM->PskLClick();
		//Sleep(20000);

		return 1;
	}

	bstr = DM->PskFindPicE(290, 60, 540, 350, "挖草ICON.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "wacaoX=" << result[1].c_str();
	qDebug() << "wacaoY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 5, y + 5, 10, 10);
		DM->PskLClick();
		//Sleep(20000);

		return 1;
	}

	return 0;
}


int TianxiaScript::wuxingShiyong(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(70, 100, 160, 200, "五行使用.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "wuxingShiyongX=" << result[1].c_str();
	qDebug() << "wuxingShiyongY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(x + 100, y + 105);
		DM->PskLClick();
		Sleep(10000);
	}


	return 0;
}

int TianxiaScript::zhengliBeibao(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(450, 30, 560, 120, "背包全部.bmp|BeibaoQuanbu.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(450, 30, 560, 120, "BeibaoQuanbu.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "shimenJX=" << result[1].c_str();
	qDebug() << "shimenJY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(2000);
		DM->PskMTo(x + 2, y + 35);
		DM->PskLClick();

		return 1;
	}


	return 0;
}

int TianxiaScript::beibaoClose(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(450, 30, 560, 120, "背包全部.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "beibaoX=" << result[1].c_str();
	qDebug() << "beibaoY=" << result[2].c_str();

	if (x != -1) {
		DM->PskKPress(66);
		Sleep(2000);

		return 1;
	}


	return 0;
}

int TianxiaScript::chongfanClose(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(450, 30, 560, 150, "ChongfanClose.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "beibaoX=" << result[1].c_str();
	qDebug() << "beibaoY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(2000);

		return 1;
	}


	return 0;
}

int TianxiaScript::jiahuClose(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(250, 5, 350, 120, "加护窗口.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "jiahuWndX=" << result[1].c_str();
	qDebug() << "jiahuWndY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(520, 40);
		DM->PskLClick();
		Sleep(2000);

		return 1;
	}


	return 0;
}


int TianxiaScript::wuxingJinxing(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	int ret = 0;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(70, 90, 170, 300, "五行J.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "wuxingX=" << result[1].c_str();
	qDebug() << "wuxingY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(2000);
		ret = 1;
	}


	bstr = DM->PskFindPicE(70, 90, 170, 300, "五行盘1.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "wuxing1X=" << result[1].c_str();
	qDebug() << "wuxing1Y=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(2000);
		ret = 1;
	}

	bstr = DM->PskFindPicE(70, 90, 170, 300, "五行盘2.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "wuxing2X=" << result[1].c_str();
	qDebug() << "wuxing2Y=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(2000);
		ret = 1;
	}

	if (ret == 0) {
		return 0;
	}

	bstr = DM->PskFindPicE(400, 250, 550, 350, "进行IN.bmp|JinxingIn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "changguiINx=" << result[1].c_str();
	qDebug() << "changguiINy=" << result[2].c_str();

	if (x != -1) {
		/*DM->PskKDown(87);
		Sleep(1000);
		DM->PskKUp(87);
		Sleep(1000);*/
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		return 1;
	}

	return 0;
}

int TianxiaScript::changguiSuojin(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(70, 50, 180, 150, "常规IN.bmp|ChangguiIn.bmp|ChangguiIn2.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(70, 50, 180, 150, "ChangguiIn.bmp|ChangguiIn2.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "changguiINx=" << result[1].c_str();
	qDebug() << "changguiINy=" << result[2].c_str();

	if (x != -1) {

		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		return 1;
	}

	return 0;
}

int TianxiaScript::dianjiTiaoguo(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(530, 0, 600, 120, "点击跳过.bmp|DianjiTiaoguo.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(530, 0, 600, 120, "DianjiTiaoguo.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "dianjiTiaoguox=" << result[1].c_str();
	qDebug() << "dianjiTiaoguoy=" << result[2].c_str();

	if (x != -1) {

		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		return 1;
	}

	return 0;
}

int TianxiaScript::changguiTaskSelector(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(70, 50, 180, 120, "常规IN.bmp|ChangguiIn.bmp|ChangguiIn2.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(70, 50, 180, 120, "ChangguiIn.bmp|ChangguiIn2.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "changguiInX=" << result[1].c_str();
	qDebug() << "changguiInY=" << result[2].c_str();

	if (x != -1 && zhuxianIng == true) {


		if (changguiFindZhuxian(DM, x - 20, y) == 1) {
			DM->PskMToEx(x + 2, y + 2, 10, 10);
			DM->PskLClick();

			Sleep(2000);

			if (changguiFindZhuxian(DM, x - 20, y) == 1) {
				this->stepIndex = TIANXIA_STEPS::ZHUXIAN;
			}
		}

	}
	else {
		DM->PskMTo(5, 85);
		DM->PskLClick();
		Sleep(1000);
	}

	return 0;
}

int TianxiaScript::changguiJieshouIn(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	/*bstr = DM->PskFindPicE(70, 50, 180, 120, "常规IN.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
	return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "changguiInX=" << result[1].c_str();
	qDebug() << "changguiInY=" << result[2].c_str();

	if (x != -1) {

	if (changguiFindZhuxian(DM, x - 20, y) == 1) {
	DM->PskMToEx(x + 2, y + 2, 10, 10);
	DM->PskLClick();

	Sleep(2000);

	if (changguiFindZhuxian(DM, x - 20, y) == 1) {
	this->stepIndex = 3;
	}
	}

	}
	else {
	DM->PskMTo(5, 85);
	DM->PskLClick();
	Sleep(1000);
	}
	*/
	//bstr = DM->PskFindPicE(400, 200, 550, 360, "接受IN.bmp|JieshouIn.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(400, 200, 550, 360, "JieshouIn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "changguiJieshouX=" << result[1].c_str();
	qDebug() << "changguiJieshouX=" << result[2].c_str();

	if (x != -1) {
		/*DM->PskKDown(87);
		Sleep(1000);
		DM->PskKUp(87);
		Sleep(1000);*/

		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		return 1;
	}

	return 0;
}

int TianxiaScript::tuijianJiadian(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(150, 60, 300, 150, "推荐加点.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "tuijianJiadianx=" << result[1].c_str();
	qDebug() << "tuijianJiadiany=" << result[2].c_str();

	if (x != -1) {

		tuijianJiadianSubScript(DM);
		return 1;
	}

	return 0;
}

int TianxiaScript::changguiFindWCMT(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(150, 60, 300, 150, "FD王朝密探.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "FDwangchaoMTx=" << result[1].c_str();
	qDebug() << "FDwangchaoMTy=" << result[2].c_str();

	if (x != -1) {

		return 1;
	}

	return 0;
}

int TianxiaScript::jinengPeizhi(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(200, 70, 300, 150, "技能配置.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "jinengPeizhiX=" << result[1].c_str();
	qDebug() << "jinengPeizhiY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(475, 310);
		Sleep(1000);
		DM->PskLClick();
		Sleep(3000);
		DM->PskMTo(560, 135);
		Sleep(1000);
		DM->PskLClick();
		Sleep(3000);
		DM->PskMTo(425, 150);
		Sleep(1000);
		DM->PskLClick();
		Sleep(3000);

		return 1;
	}

	return 0;
}

int TianxiaScript::tuijianJiadianEx(Ifire* DM)
{


	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(300, 300, 420, 350, "加点按钮.bmp|JiadianBtn.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(300, 300, 420, 350, "JiadianBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "tuijianJiadianx=" << result[1].c_str();
	qDebug() << "tuijianJiadiany=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(2000);
		DM->PskMTo(370, 290);
		Sleep(500);
		DM->PskLClick();
		Sleep(1000);
		DM->PskMTo(450, 290);
		Sleep(500);
		DM->PskLClick();
		Sleep(1000);
		DM->PskMTo(490, 60);
		Sleep(500);
		DM->PskLClick();
		Sleep(1000);
		DM->PskMTo(520, 40);
		Sleep(500);
		DM->PskLClick();
		return 1;
	}

	return 0;
}

int TianxiaScript::duiwuClose(Ifire* DM)
{


	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(90, 250, 150, 350, "队伍标记.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "duiwuBiaojiX=" << result[1].c_str();
	qDebug() << "duiwuBiaojiY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(520, 40);
		DM->PskLClick();
		Sleep(2000);


		return 1;
	}

	return 0;
}

int TianxiaScript::tongxinhuanpei(Ifire* DM)
{


	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(300, 120, 400, 220, "同心环佩.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "tongxinhuanpeiX=" << result[1].c_str();
	qDebug() << "tongxinhuanpeiY=" << result[2].c_str();

	if (x != -1) {
		DM->PskMTo(250, 240);
		DM->PskLClick();
		Sleep(2000);


		return 1;
	}

	return 0;
}

int TianxiaScript::tuijianJiadianSubScript(Ifire* DM)
{
	changguiJinxingIn(DM);
	/*DM->PskKPress(76);
	Sleep(1000);
	DM->PskKPress(67);
	Sleep(2000);*/
	Sleep(2000);
	DM->PskMTo(35, 20);
	DM->PskLClick();
	Sleep(2000);

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(300, 300, 420, 350, "加点按钮.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "tuijianJiadianx=" << result[1].c_str();
	qDebug() << "tuijianJiadiany=" << result[2].c_str();

	if (x != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(2000);
		DM->PskMTo(370, 290);
		Sleep(500);
		DM->PskLClick();
		Sleep(1000);
		DM->PskMTo(450, 290);
		Sleep(500);
		DM->PskLClick();

		return 1;
	}

	return 0;
}


int TianxiaScript::changguiTaskSubScript(Ifire* DM)
{
	bool isInDuihua = false;
	if (duihuaHuangtiao(DM) == 1) {
		isInDuihua = true;
	}

	yuandiFuhuo(DM);
	renwuClose(DM);

	if (findChangguiIn(DM) == 0 && isInDuihua == false) {
		DM->PskKPress(76);
		Sleep(2000);
		zhuxianConfirmCircle(DM);
	}


	if (changguiJieshouIn(DM) == 0) {
		Sleep(1000);
		DM->PskMTo(545, 160);
		DM->PskLClick();
		/*Sleep(2000);
		changguiTurnZhuxian(DM);*/
		Sleep(1000);
		DM->PskMTo(545, 110);
		DM->PskLClick();
		Sleep(2000);
	}


	if (zhuxianQinggong(DM) == 1) {
		return 0;
	}

	/*if (tuijianJiadian(DM) == 1) {
	return 0;
	}
	if (jinengPeizhi(DM) == 1) {
	return 0;
	}*/


	if (findChangguiIn(DM) == 1) {

		zhuxianConfirmCircle(DM);
	}


	/*if (changguiFindWCMT(DM) == 1) {
	return SCRIPT_STEPS::WCMT;
	}*/

	if (zhuxianQinggong(DM) == 1) {
		return 0;
	}

	return 101;
}

int TianxiaScript::shimenTask(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(70, 70, 200, 300, "师门任务1.bmp", "000000", 0.9, 0);
	//str = (_bstr_t)bstr;

	//qDebug() << str.c_str();

	//result = CommonUtil::split(str, "|");

	//l = result.size();
	//size = CommonUtil::Long2STR(l);
	//if (l < 3) {
	//	return 0;
	//}

	//x = atol(result[1].c_str());
	//y = atol(result[2].c_str());

	//qDebug() << "shimen1x=" << result[1].c_str();
	//qDebug() << "shimen1y=" << result[2].c_str();

	//if (x != -1) {

	//	DM->PskMToEx(x + 2, y + 2, 10, 10);
	//	DM->PskLClick();
	//	return 1;
	//}

	//bstr = DM->PskFindPicE(70, 70, 200, 300, "师门任务2.bmp", "000000", 0.9, 0);
	//str = (_bstr_t)bstr;

	//qDebug() << str.c_str();

	//result = CommonUtil::split(str, "|");

	//l = result.size();
	//size = CommonUtil::Long2STR(l);
	//if (l < 3) {
	//	return 0;
	//}

	//x = atol(result[1].c_str());
	//y = atol(result[2].c_str());

	//qDebug() << "shimen2x=" << result[1].c_str();
	//qDebug() << "shimen2y=" << result[2].c_str();

	//if (x != -1) {

	//	DM->PskMToEx(x + 2, y + 2, 10, 10);
	//	DM->PskLClick();
	//	return 1;
	//}

	bstr = DM->PskFindPicE(70, 70, 200, 350, "师门接受1.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "shimenJieshou1x=" << result[1].c_str();
	qDebug() << "shimenJieshou1y=" << result[2].c_str();

	if (x != -1) {

		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		return 1;
	}

	str = DM->PskFindPicE(70, 70, 200, 350, "师门接受2.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "shimenJieshou2x=" << result[1].c_str();
	qDebug() << "shimenJieshou2y=" << result[2].c_str();

	if (x != -1) {

		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		return 1;
	}

	return 0;
}

int TianxiaScript::wuxingTask(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	int ret = 0;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(70, 70, 200, 300, "五行盘1.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "wuxingpan1X=" << result[1].c_str();
	qDebug() << "wuxingpan1Y=" << result[2].c_str();

	if (x != -1) {

		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(1000);

		ret = 1;
	}

	bstr = DM->PskFindPicE(70, 70, 200, 300, "五行盘2.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "wuxingpan2X=" << result[1].c_str();
	qDebug() << "wuxingpan2Y=" << result[2].c_str();

	if (x != -1) {

		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		ret = 1;
	}

	if (ret != 1) {
		return 0;
	}

	//bstr = DM->PskFindPicE(400, 250, 550, 350, "进行IN.bmp|JinxingIn.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(400, 250, 550, 350, "JinxingIn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "jinxingX=" << result[1].c_str();
	qDebug() << "jinxingY=" << result[2].c_str();

	if (x != -1) {
		/*DM->PskKDown(87);
		Sleep(1000);
		DM->PskKUp(87);
		Sleep(1000);*/

		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		return 1;
	}

	//bstr = DM->PskFindPicE(400, 250, 550, 350, "接受IN.bmp|JieshouIn.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(400, 250, 550, 350, "JieshouIn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "jieshouX=" << result[1].c_str();
	qDebug() << "jieshouY=" << result[2].c_str();

	if (x != -1) {
		/*DM->PskKDown(87);
		Sleep(1000);
		DM->PskKUp(87);
		Sleep(1000);*/

		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		return 1;
	}

	return 0;
}

int TianxiaScript::kuaimaJiabianEx(Ifire* DM)
{
	if (findChangguiIn(DM) == 0) {
		DM->PskKPress(76);
		Sleep(2000);
		zhuxianConfirmCircle(DM);
	}

	DM->PskMTo(545, 160);
	DM->PskLClick();
	Sleep(3000);


	_bstr_t bstr;
	string str, size;
	long x, y, l;
	int ret = 0;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(70, 70, 200, 350, "快马IN1.bmp|KuaimaIn2.bmp|KuaimaIn1.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(70, 70, 200, 350, "KuaimaIn2.bmp|KuaimaIn1.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "wuxingpan1X=" << result[1].c_str();
	qDebug() << "wuxingpan1Y=" << result[2].c_str();

	if (x != -1) {

		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(1000);
		ret = 1;
	}



	if (ret == 0) {
		return 2;
	}

	//bstr = DM->PskFindPicE(400, 200, 550, 360, "接受IN.bmp|JieshouIn.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(400, 200, 550, 360, "JieshouIn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "zhuxianJieshouINx=" << result[1].c_str();
	qDebug() << "zhuxianJieshouIny=" << result[2].c_str();

	if (x != -1) {


		DM->PskMTo(x + 20, y + 5);
		DM->PskLClick();

		Sleep(1000);
		dianjiTiaoguo(DM);
		Sleep(1000);
		danrenKuaima(DM);

		Sleep(1000);
		generalClose(DM);
		Sleep(2000);


		while (kuaimaXunhuan(DM) == 1 && getIsEnded() == false) {
			mapClose(DM);
			Sleep(5000);
		}

		//return 1;
	}



	return ret;
}

int TianxiaScript::kuaisuZuduiBTN(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(420, 280, 550, 380, "快速组队按钮.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "wuxingpan1X=" << result[1].c_str();
	qDebug() << "wuxingpan1Y=" << result[2].c_str();

	if (x != -1) {

		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(1000);

		return 1;
	}


	return 0;
}

int TianxiaScript::jieriClose(Ifire* DM)
{

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(520, 0, 600, 100, "JieriClose.bmp|JiaoziClose.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "JieriCloseX=" << result[1].c_str();
	qDebug() << "JieriCloseY=" << result[2].c_str();

	if (x != -1) {

		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(1000);

		return 1;
	}


	return 0;
}

int TianxiaScript::changguiFindZhuxian(Ifire* DM, long pX, long pY)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = DM->PskFindPicE(pX, pY, pX + 150, pY + 50, "主线IN.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "cgZhuxianInX=" << result[1].c_str();
	qDebug() << "cgZhuxianInY=" << result[2].c_str();

	if (x != -1) {
		return 1;
	}

	return 0;
}

int TianxiaScript::zhuxian3RD(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(60, 80, 200, 320, "三章1.bmp|Sanzhang1.bmp|Sanzhang2.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(60, 80, 200, 320, "Sanzhang1.bmp|Sanzhang2.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "sanZhangX=" << result[1].c_str();
	qDebug() << "sanZhangY=" << result[2].c_str();

	if (x != -1) {
		return 1;
	}


	return 0;
}

int TianxiaScript::changguiTurnZhuxian(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(70, 70, 200, 300, "主线任务IN.bmp|ZhuxianIn.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(70, 70, 200, 300, "ZhuxianIn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "turnZhuxianInX=" << result[1].c_str();
	qDebug() << "turnZhuxianInY=" << result[2].c_str();

	if (x != -1) {
		if (zhuxianFindTaskTitle(DM, x, y + 20) == 0 && zhuxianIng == true) {
			this->stepIndex = TIANXIA_STEPS::ZHUXIAN;
			return 1;
		}

	}

	return 0;
}

int TianxiaScript::zhuxianFindTaskTitle(Ifire* DM, long pX, long pY)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(pX, pY, pX + 60, pY + 30, "节日任务.bmp|JieriRenwu.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(pX, pY, pX + 60, pY + 30, "JieriRenwu.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "jieriRenwucX=" << result[1].c_str();
	qDebug() << "jieriRenwucY=" << result[2].c_str();

	if (x != -1) {
		return 1;
	}

	return 0;
}

int TianxiaScript::zhuxianSuojinIn(Ifire* DM, long pX, long pY)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(pX, pY, pX + 150, pY + 30, "缩进IN.bmp|SuojinIn.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(pX, pY, pX + 150, pY + 30, "SuojinIn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "zhuxianSuojinINx=" << result[1].c_str();
	qDebug() << "zhuxianSuojinINy=" << result[2].c_str();

	if (x != -1) {

		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();

		Sleep(1000);

		DM->PskMTo(x - 50, y + 40);
		DM->PskLClick();
		return 1;
	}
	/*else {
	DM->PskMTo(pX, pY + 40);
	DM->PskLClick();
	}*/

	if (zhuxianFindTaskTitle(DM, pX, pY + 30) == 1) {
		return 2;
	}

	return 0;
}

int TianxiaScript::zhuxianJieshouIn(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(70, 70, 200, 200, "主线任务IN.bmp|ZhuxianIn.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(70, 70, 200, 200, "ZhuxianIn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "zhuxianINx=" << result[1].c_str();
	qDebug() << "zhuxianINy=" << result[2].c_str();

	if (x != -1) {
		if (zhuxianSuojinIn(DM, x, y) == 2) {
			tempCounter++;
			if (tempCounter > 3) {
				tempCounter = 0;
				this->stepIndex = TIANXIA_STEPS::CHANGGUI;
			}

			return 0;
		}
		else {
			tempCounter = 0;
		}
		DM->PskMTo(x + 2, y + 40);
		DM->PskLClick();

		Sleep(1000);
	}
	else {
		changguiSuojin(DM);
		//changguiTask(DM);
		Sleep(3000);

		//bstr = DM->PskFindPicE(70, 70, 200, 300, "主线任务IN.bmp|ZhuxianIn.bmp", "000000", 0.9, 0);
		bstr = DM->PskFindPicE(70, 70, 200, 300, "ZhuxianIn.bmp", "000000", 0.9, 0);
		str = (_bstr_t)bstr;

		qDebug() << str.c_str();

		result = CommonUtil::split(str, "|");

		l = result.size();
		size = CommonUtil::Long2STR(l);
		if (l < 3) {
			return 0;
		}

		x = atol(result[1].c_str());
		y = atol(result[2].c_str());

		qDebug() << "zhuxianINx=" << result[1].c_str();
		qDebug() << "zhuxianINy=" << result[2].c_str();

		if (x != -1) {
			if (zhuxianSuojinIn(DM, x, y) == 2) {
				tempCounter++;
				if (tempCounter > 3) {
					tempCounter = 0;
					this->stepIndex = TIANXIA_STEPS::CHANGGUI;
				}

				return 0;
			}
			else {
				tempCounter = 0;
			}
			Sleep(1000);
			DM->PskMTo(x + 2, y + 40);
			DM->PskLClick();
		}
		else {
			changguiSuojin(DM);
			//changguiTask(DM);


			Sleep(3000);
		}
	}

	if (zhuxian3RD(DM) == 1) {
		zhuxianIng = false;
		stepIndex = TIANXIA_STEPS::CHANGGUI;
		return 0;
	}

	//bstr = DM->PskFindPicE(400, 200, 550, 360, "接受IN.bmp|JieshouIn.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(400, 200, 550, 360, "JieshouIn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "zhuxianJieshouINx=" << result[1].c_str();
	qDebug() << "zhuxianJieshouIny=" << result[2].c_str();

	if (x != -1) {

		/*DM->PskKDown(87);
		Sleep(1000);
		DM->PskKUp(87);
		Sleep(1000);*/

		DM->PskMTo(x + 20, y + 5);
		DM->PskLClick();
		//Sleep(20000);
		return 1;
	}

	return 0;
}

int TianxiaScript::findZhuxianIn(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(70, 70, 200, 360, "主线任务IN.bmp|ZhuxianIn.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(70, 70, 200, 360, "ZhuxianIn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "zhuxianINx=" << result[1].c_str();
	qDebug() << "zhuxianINy=" << result[2].c_str();

	if (x != -1) {

		/*DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();*/
		return 1;
	}

	return 0;
}

int TianxiaScript::zhuxianGuankan(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(400, 200, 550, 300, "主线观看.bmp|Guankan.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(400, 200, 550, 300, "Guankan.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "zhuxianGuankanx=" << result[1].c_str();
	qDebug() << "zhuxianGuankany=" << result[2].c_str();

	if (x != -1) {

		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(60000 * 5);
		return 1;
	}

	return 0;
}

int TianxiaScript::findLoginScreen(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;
	bstr = DM->PskFindPicE(250, 200, 450, 350, "点击换服.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "huanFux=" << result[1].c_str();
	qDebug() << "huanFuy=" << result[2].c_str();

	if (x != -1) {
		Sleep(2000);
		DM->PskMTo(x + 25, y + 2);
		DM->PskLClick();
		return 1;
	}

	return 0;
}

int TianxiaScript::findSelectedZoneSubScript(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(0, 0, 180, 150, "服务器推荐.bmp|FWQ_Tuijian.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(0, 0, 180, 150, "FWQ_Tuijian.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "XXfuwuqituijianx=" << result[1].c_str();
	qDebug() << "XXfuwuqituijiany=" << result[2].c_str();

	if (x != -1) {

		long pX = x + 120;
		long pY = y + 20;

		int zone = this->zone_number.toInt();
		if (zone <= 12) {
			int row = zone / 2;

			if (zone % 2 == 1) {

				DM->PskMTo(pX, pY + row * 40);
				Sleep(1000);
				DM->PskLClick();
			}
			else {
				DM->PskMTo(pX + 180, pY + (row - 1) * 40);
				Sleep(1000);
				DM->PskLClick();
			}


		}
		else {
			zone = zone - 12;
			int row = zone / 2;

			DM->PskMTo(368, 268);
			Sleep(1000);
			int ret = DM->PskLDown();
			Sleep(1000);
			DM->PskMTo(368, 78);
			Sleep(1000);
			DM->PskLUp();
			Sleep(1000);
			DM->PskMTo(368, 268);
			Sleep(1000);
			ret = DM->PskLDown();
			Sleep(1000);
			DM->PskMTo(368, 78);
			Sleep(1000);
			DM->PskLUp();
			Sleep(1000);

			//pY = pY;

			if (zone % 2 == 1) {

				DM->PskMTo(pX, pY + row * 40);
				Sleep(1000);
				DM->PskLClick();
			}
			else {
				DM->PskMTo(pX + 180, pY + (row - 1) * 40);
				Sleep(1000);
				DM->PskLClick();
			}

			this->stepIndex = TIANXIA_STEPS::AUTH;
		}


		return 1;
	}

	return 0;
}

int TianxiaScript::findSelectedZone(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(0, 0, 180, 150, "服务器推荐.bmp|FWQ_Tuijian.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(0, 0, 180, 150, "FWQ_Tuijian.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "fuwuqituijianx=" << result[1].c_str();
	qDebug() << "fuwuqituijiany=" << result[2].c_str();

	if (x != -1) {
		if (this->daqu == "yitong") {
			DM->PskMTo(x + 2, y + 30);
			DM->PskLClick();
		}

		if (this->daqu == "huaxia") {
			DM->PskMTo(x + 2, y + 60);
			DM->PskLClick();
		}

		Sleep(3000);

		findSelectedZoneSubScript(DM);

		Sleep(3000);

		selectCharacter(DM);

		return 1;
	}

	return 0;
}

int TianxiaScript::findScanPic(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;
	bstr = DM->PskFindPicE(0, 0, 150, 100, "天下ICON.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "tianxiaICONx=" << result[1].c_str();
	qDebug() << "tianxiaICONy=" << result[2].c_str();

	if (x != -1 && y != -1) {

		return 1;
	}
	else {
		clickYunshiCloseBtn(DM);
	}

	return 0;
}

int TianxiaScript::yanwutang(Ifire* DM)
{
	richangClose(DM);
	mapClose(DM);
	generalClose(DM);

	if (findYanwutang(DM) == 0) {
		DM->PskKPress(75);
		Sleep(2000);
		if (getCurrentHuoyue(DM) > 100) {
			return 2;
		}
		Sleep(1000);
		DM->PskMTo(550, 265);
		DM->PskLClick();
		Sleep(2000);

		if (findYanwutang(DM) == 0) {
			return 2;
		}
		Sleep(2000);
		renwuClose(DM);
		Sleep(2000);
	}

	return 1;
}

int TianxiaScript::mijingXiuxing(Ifire* DM)
{

	zuduiClose(DM);

	if (findMijing(DM) == 0) {
		DM->PskKPress(75);
		Sleep(2000);
		if (getCurrentHuoyue(DM) > 100) {
			return 2;
		}
		Sleep(1000);
		DM->PskMTo(540, 265);
		DM->PskLClick();
		Sleep(3000);

		if (findMijing(DM) == 0) {
			return 2;
		}
		Sleep(2000);
		renwuClose(DM);
		Sleep(2000);
	}

	return 1;
}

int TianxiaScript::findMijing(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;
	bstr = DM->PskFindPicE(80, 90, 450, 180, "秘境修行.bmp|MijingXiuxing.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "mijingXiuxingX=" << result[1].c_str();
	qDebug() << "mijingXiuxingY=" << result[2].c_str();

	if (x != -1 && y != -1) {
		if (findJikaiqi(DM, x, y) == 1) {
			scriptIndex++;
			return 0;
		}

		DM->PskMTo(x + 150, y + 15);
		DM->PskLClick();
		Sleep(1000);
		richangClose(DM);
		Sleep(30000);
		return 1;
	}

	return 0;
}

int TianxiaScript::jinruYanwutang(Ifire* DM)
{

	DM->PskMTo(20, 350);
	DM->PskLClick();
	Sleep(1000);
	/*DM->PskMTo(210,310);
	DM->PskLClick();
	Sleep(1000);*/
	DM->PskMTo(300, 200);
	DM->PskLClick();
	Sleep(1000);

	return 1;
}

int TianxiaScript::jinruYanwuBTN(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;
	bstr = DM->PskFindPicE(450, 150, 560, 220, "进入演武按钮.bmp|YanwuBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "JRyanwuBTNx=" << result[1].c_str();
	qDebug() << "JRyanwuBTNx=" << result[2].c_str();

	if (x != -1 && y != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		//Sleep(30000);
		return 1;
	}

	return 0;
}

int TianxiaScript::jinruMijingBTN(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;
	bstr = DM->PskFindPicE(450, 150, 560, 220, "进入秘境按钮.bmp|MijingBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "jinruMijingBtnX=" << result[1].c_str();
	qDebug() << "jinruMijingBtnY=" << result[2].c_str();

	if (x != -1 && y != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(2000);
		if (mijingLingjiang(DM) == 0) {
			scriptIndex++;
			//Sleep(60000 * 5);
		}

		return 1;
	}

	return 0;
}

int TianxiaScript::mijingLingjiang(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;
	//bstr = DM->PskFindPicE(250, 30, 330, 90, "秘境奖励.bmp|MijingJiangli.bmp", "000000", 0.9, 0);
	bstr = DM->PskFindPicE(250, 30, 330, 90, "MijingJiangli.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "mijingJiangliX=" << result[1].c_str();
	qDebug() << "mijingJiangliY=" << result[2].c_str();

	if (x != -1 && y != -1) {

		Sleep(1000);
		mijingLingjiangBtn(DM);
		Sleep(1000);
		DM->PskMTo(480, 60);
		DM->PskLClick();
		Sleep(1000);
		return 1;
	}

	return 0;
}

int TianxiaScript::mijingLingjiangBtn(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;
	bstr = DM->PskFindPicE(380, 80, 520, 360, "秘境领奖按钮.bmp|MijingLingjiangBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "mijingLingjBtnX=" << result[1].c_str();
	qDebug() << "mijingLingjBtnX=" << result[2].c_str();

	if (x != -1 && y != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(1000);
		return 1;
	}

	return 0;
}

int TianxiaScript::yanwuJiesuanQueding(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;
	bstr = DM->PskFindPicE(320, 280, 400, 380, "结算确定.bmp|JiesuanQueding.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "jiesuanQuedingX=" << result[1].c_str();
	qDebug() << "jiesuanQuedingY=" << result[2].c_str();

	if (x != -1 && y != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(30000);
		return 1;
	}

	return 0;
}

int TianxiaScript::yanWuIng(Ifire* DM) {
	if (isInYanwu(DM) == 1) {
		this->stepIndex = TIANXIA_STEPS::CHANGGUI;
		while (isInYanwu(DM) == 1 && getIsEnded() == false) {
			autoCombat(DM);
			tuichuYanwuShi(DM);
		}
	}

	return 0;
}

int TianxiaScript::isInYanwu(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;
	bstr = DM->PskFindPicE(500, 0, 580, 60, "演武副本.bmp|YanwuFB.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "JRyanwuBTNx=" << result[1].c_str();
	qDebug() << "JRyanwuBTNx=" << result[2].c_str();

	if (x != -1 && y != -1) {

		Sleep(3000);
		return 1;
	}



	bstr = DM->PskFindPicE(250, 0, 320, 50, "演武关.bmp|YanwuGuan.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "yanwuGuanX=" << result[1].c_str();
	qDebug() << "yanwuGuanY=" << result[2].c_str();

	if (x != -1 && y != -1) {

		Sleep(3000);
		return 1;
	}

	bstr = DM->PskFindPicE(280, 70, 380, 150, "战斗要点.bmp|ZhandouYaodian.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "yaodianX=" << result[1].c_str();
	qDebug() << "yaodianY=" << result[2].c_str();

	if (x != -1 && y != -1) {

		Sleep(3000);
		return 1;
	}

	if (findQuxiaoBtn(DM) == 1) {
		return 1;
	}
	return 0;
}

int TianxiaScript::autoCombat(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;
	bstr = DM->PskFindPicE(420, 220, 500, 310, "战斗ING.bmp|ZhandouIng.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "zhandouINGx=" << result[1].c_str();
	qDebug() << "zhandouINGy=" << result[2].c_str();

	if (x != -1 && y != -1) {

		return 1;
	}
	else {
		DM->PskMTo(480, 250);
		DM->PskLClick();
	}

	return 0;
}

int TianxiaScript::tuichuFubenBTN(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;
	bstr = DM->PskFindPicE(200, 220, 300, 360, "退出副本按钮.bmp|TuiYanwuBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "tuiFubenX=" << result[1].c_str();
	qDebug() << "tuiFubenY=" << result[2].c_str();

	if (x != -1 && y != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(2000);
		return 1;
	}

	return 0;
}

int TianxiaScript::clickChuanchengCloseBtn(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;
	bstr = DM->PskFindPicE(450, 50, 600, 200, "ChuanchengClose.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "ChuanchengCloseX=" << result[1].c_str();
	qDebug() << "ChuanchengCloseY=" << result[2].c_str();

	if (x != -1 && y != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		Sleep(2000);
		return 1;
	}

	return 0;
}

int TianxiaScript::tuichuFubenBTNEx(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;
	bstr = DM->PskFindPicE(450, 20, 520, 150, "TuibenEx.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "TuibenExX=" << result[1].c_str();
	qDebug() << "TuibenExY=" << result[2].c_str();

	if (x != -1 && y != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();

		return 1;
	}

	return 0;
}


int TianxiaScript::findYanwutang(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;
	bstr = DM->PskFindPicE(80, 90, 450, 160, "Yanwutang.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "yanwutangX=" << result[1].c_str();
	qDebug() << "yanwutangY=" << result[2].c_str();

	if (x != -1 && y != -1) {
		if (findJikaiqi(DM, x, y) == 1) {
			scriptIndex++;
			Sleep(2000);
		}

		DM->PskMTo(x + 150, y + 15);
		DM->PskLClick();
		Sleep(2000);
		richangClose(DM);
		Sleep(30000);


		return 1;
	}

	return 0;
}

int TianxiaScript::findJikaiqi(Ifire* DM, long pX, long pY)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;
	bstr = DM->PskFindPicE(pX, pY, pX + 250, pY + 40, "级开启.bmp|Jikaiqi.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "jikaiqiX=" << result[1].c_str();
	qDebug() << "jikaiqiY=" << result[2].c_str();

	if (x != -1 && y != -1) {

		return 1;
	}

	return 0;
}

int TianxiaScript::findGeneralDingzhi(Ifire* DM, long pX, long pY)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;
	bstr = DM->PskFindPicE(pX, pY, pX + 250, pY + 100, "GeneralDingzhi.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "GeneralDingzhiX=" << result[1].c_str();
	qDebug() << "GeneralDingzhiY=" << result[2].c_str();

	if (x != -1 && y != -1) {

		return 1;
	}

	return 0;
}

int TianxiaScript::fubenJingcheng(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;
	bstr = DM->PskFindPicE(250, 120, 350, 220, "副本进程.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "fubenJinchengX=" << result[1].c_str();
	qDebug() << "fubenJinchengY=" << result[2].c_str();

	if (x != -1 && y != -1) {
		DM->PskMTo(350, 240);
		DM->PskLClick();
		return 1;
	}

	return 0;
}

int TianxiaScript::menpaiWndClose(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;
	bstr = DM->PskFindPicE(250, 10, 350, 90, "MenpaiWnd.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "MenpaiWndX=" << result[1].c_str();
	qDebug() << "MenpaiWndY=" << result[2].c_str();

	if (x != -1 && y != -1) {
		DM->PskMTo(520, 40);
		DM->PskLClick();
		return 1;
	}

	return 0;
}

int TianxiaScript::zhaixingLou(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;
	bstr = DM->PskFindPicE(180, 120, 260, 220, "Zhaixinglou.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "zhaiXinglouX=" << result[1].c_str();
	qDebug() << "zhaiXinglouY=" << result[2].c_str();

	if (x != -1 && y != -1) {
		DM->PskMTo(260, 240);
		DM->PskLClick();
		return 1;
	}

	return 0;
}

int TianxiaScript::gongzhanClose(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;
	bstr = DM->PskFindPicE(450, 20, 550, 150, "共战关闭.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "gongzhanCloseX=" << result[1].c_str();
	qDebug() << "gongzhanCloseY=" << result[2].c_str();

	if (x != -1 && y != -1) {
		DM->PskMToEx(x + 2, y + 2, 10, 10);
		DM->PskLClick();
		return 1;
	}

	return 0;
}

int TianxiaScript::generalClose(Ifire* DM)
{
	_bstr_t bstr;
	string str, size;
	long x, y, l;


	std::vector<std::string> result;
	bstr = DM->PskFindPicE(500, 10, 580, 250, "GeneralCloseBtn.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "geneCloseX=" << result[1].c_str();
	qDebug() << "geneCloseY=" << result[2].c_str();

	if (x != -1 && y != -1) {
		DM->PskMTo(520, 40);
		DM->PskLClick();
		return 1;
	}

	bstr = DM->PskFindPicE(500, 10, 580, 250, "GeneClose.bmp", "000000", 0.9, 0);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, "|");

	l = result.size();
	size = CommonUtil::Long2STR(l);
	if (l < 3) {
		return 0;
	}

	x = atol(result[1].c_str());
	y = atol(result[2].c_str());

	qDebug() << "GeneCloseX=" << result[1].c_str();
	qDebug() << "GeneCloseY=" << result[2].c_str();

	if (x != -1 && y != -1) {
		DM->PskMTo(520, 40);
		DM->PskLClick();
		return 1;
	}

	return 0;
}

Ifire* TianxiaScript::initDM() {
	Ifire* DM = DMSoft::getInstance()->newDMObject();
	qDebug() << DM->PskVer();

#if 0

	qDebug() << DM->GetID();
	qDebug() << DM->GetMachineCode();
	DM->Release();

	return 0;
#endif


	int result = 0;

	DM->PskSetShowErrorMsg(0);
	string code = DM->GetMachineCode();


	result = DM->PskReg("pskfire20928db6b002f54b0b0f1d5dcc665316", "ambition");
	qDebug() << "machineCode=";
	qDebug() << code.c_str();
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
	}

	return DM;
}

void TianxiaScript::startScript()
{
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	HANDLE handle;
	ScriptParam* param = new ScriptParam;
	param->lHWND = this->lHWND;
	param->config = this->jsonConfig;
	param->index = this->index;
	param->threadId = this->threadId;

	Ifire* DM = this->initDM();
	param->DM = DM;

	handle = (HANDLE)_beginthreadex(NULL, 0, &TianxiaScript::ThreadFun, param, 0, NULL);

}

void TianxiaScript::getConfig(QString config) {
	QJsonParseError jsonError;
	QByteArray byteArray = config.toLatin1();
	qDebug() << "config = " << config;

	QJsonDocument document = QJsonDocument::fromJson(byteArray, &jsonError);

	if (!document.isNull() && (jsonError.error == QJsonParseError::NoError)) {
		if (document.isObject()) {

			QJsonObject object = document.object();  // 转化为对象
			if (object.contains("daqu")) {
				QJsonValue value = object.value("daqu");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "daqu : " << strName;
					this->daqu = strName;
				}
			}

			if (object.contains("mengyan")) {
				QJsonValue value = object.value("mengyan");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "mengyan : " << strName;
					if (value == "0") {
						mengyan = false;
					}
					else {
						mengyan = true;
					}
				}
			}

			if (object.contains("qicai")) {
				QJsonValue value = object.value("qicai");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "qicai : " << strName;
					if (value == "0") {
						qicai = false;
					}
					else {
						qicai = true;
					}
				}
			}

			if (object.contains("idField")) {
				QJsonValue value = object.value("idField");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "idField : " << strName;

					this->idField = strName;

				}
			}

			if (object.contains("goldController")) {
				QJsonValue value = object.value("goldController");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "goldController : " << strName;
					this->goldController = strName.toInt();
				}
			}

			if (object.contains("safeJunzi")) {
				QJsonValue value = object.value("safeJunzi");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "safeJunzi : " << strName;
					this->safeJunzi = strName.toInt();
				}
			}

			if (object.contains("saoPointer")) {
				QJsonValue value = object.value("saoPointer");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "saoPointer : " << strName;
					this->saoPointer = strName.toInt();
				}
			}

			if (object.contains("jianding")) {
				QJsonValue value = object.value("jianding");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "jianding : " << strName;
					if (value == "0") {
						jianding = false;
					}
					else {
						jianding = true;
					}
				}
			}

			if (object.contains("sao")) {
				QJsonValue value = object.value("sao");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "sao : " << strName;
					this->sao = strName;
				}
			}

			if (object.contains("charaChoose")) {
				QJsonValue value = object.value("charaChoose");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "charaChoose : " << strName;
					this->charaChoose = strName.toInt();
				}
			}

			if (object.contains("rizuanBox")) {
				QJsonValue value = object.value("rizuanBox");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "rizuanBox : " << strName;
					if (value == "0") {
						rizuanBox = false;
					}
					else {
						rizuanBox = true;
					}
				}
			}

			if (object.contains("yuezuanBox")) {
				QJsonValue value = object.value("yuezuanBox");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "yuezuanBox : " << strName;
					if (value == "0") {
						yuezuanBox = false;
					}
					else {
						yuezuanBox = true;
					}
				}
			}

			if (object.contains("liuyaoBox")) {
				QJsonValue value = object.value("liuyaoBox");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "liuyaoBox : " << strName;
					if (value == "0") {
						liuyaoBox = false;
					}
					else {
						liuyaoBox = true;
					}
				}
			}

			if (object.contains("isZhuxianEnabled")) {
				QJsonValue value = object.value("isZhuxianEnabled");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "isZhuxianEnabled : " << strName;
					if (value == "0") {
						isZhuxianEnabled = false;
					}
					else {
						isZhuxianEnabled = true;
					}
				}
			}

			if (object.contains("generalDZCheckBox")) {
				QJsonValue value = object.value("generalDZCheckBox");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "generalDZCheckBox : " << strName;
					if (value == "0") {
						generalDZCheckBox = false;
					}
					else {
						generalDZCheckBox = true;
					}
				}
			}

			if (object.contains("huoyueCheckBox")) {
				QJsonValue value = object.value("huoyueCheckBox");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "huoyueCheckBox : " << strName;
					if (value == "0") {
						huoyueCheckBox = false;
					}
					else {
						huoyueCheckBox = true;
					}
				}
			}

			if (object.contains("isCaptained")) {
				QJsonValue value = object.value("isCaptained");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "isCaptained : " << strName;
					if (value == "0") {
						isCaptained = false;
					}
					else {
						isCaptained = true;
					}
				}
			}

			if (object.contains("isShimenJun")) {
				QJsonValue value = object.value("isShimenJun");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "isShimenJun : " << strName;
					if (value == "0") {
						isShimenJun = false;
					}
					else {
						isShimenJun = true;
					}
				}
			}

			if (object.contains("isYongjun")) {
				QJsonValue value = object.value("isYongjun");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "isYongjun : " << strName;
					if (value == "0") {
						isYongjun = false;
					}
					else {
						isYongjun = true;
					}
				}
			}

			if (object.contains("team_mode")) {
				QJsonValue value = object.value("team_mode");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "team_mode : " << strName;
					team_mode = strName;
				}
			}

			if (object.contains("huoli_param")) {
				QJsonValue value = object.value("huoli_param");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "huoli_param : " << strName;
					huoli_param = strName.toInt();
				}
			}
			//team_param
			if (object.contains("team_param")) {
				QJsonValue value = object.value("team_param");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "team_param : " << strName;
					team_param = strName.toInt();
				}
			}
			//time_limit
			if (object.contains("time_limit")) {
				QJsonValue value = object.value("time_limit");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "time_limit : " << strName;
					time_limit = strName.toInt();
				}
			}
			//mitan_counter
			if (object.contains("mitan_counter")) {
				QJsonValue value = object.value("mitan_counter");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "mitan_counter : " << strName;
					mitan_counter = strName.toInt();
				}
			}
			//shimen_counter
			if (object.contains("shimen_counter")) {
				QJsonValue value = object.value("shimen_counter");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "shimen_counter : " << strName;
					shimen_counter = strName.toInt();
				}
			}

			if (object.contains("zhuxian_level")) {
				QJsonValue value = object.value("zhuxian_level");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "zhuxian_level : " << strName;
					zhuxian_level = strName.toInt();
				}
			}

			if (object.contains("isHuoliProtected")) {
				QJsonValue value = object.value("isHuoliProtected");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "isHuoliProtected : " << strName;
					if (value == "0") {
						isHuoliProtected = false;
					}
					else {
						isHuoliProtected = true;
					}
				}
			}

			if (object.contains("isBuqian")) {
				QJsonValue value = object.value("isBuqian");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "isBuqian : " << strName;
					if (value == "0") {
						isBuqian = false;
					}
					else {
						isBuqian = true;
					}
				}
			}

			if (object.contains("zone_num")) {
				QJsonValue value = object.value("zone_num");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "zone_num : " << strName;
					this->zone_number = strName;
				}
			}

			//character_size
			if (object.contains("character_size")) {
				QJsonValue value = object.value("character_size");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "character_size : " << strName;
					this->character_size = strName.toInt();
				}
			}


			if (object.contains("isAutoChangeRole")) {
				QJsonValue value = object.value("isAutoChangeRole");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "isAutoChangeRole : " << strName;
					this->isAutoChangeRole = strName;
				}
			}

			if (object.contains("isAutoLogin")) {
				QJsonValue value = object.value("isAutoLogin");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "isAutoLogin : " << strName;
					this->isAutoLogin = strName;
				}
			}

			if (object.contains("character1")) {
				QJsonValue value = object.value("character1");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "character1 : " << strName;
					this->character1 = strName;
				}
			}

			if (object.contains("character2")) {
				QJsonValue value = object.value("character2");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "character2 : " << strName;
					this->character2 = strName;
				}
			}

			if (object.contains("character3")) {
				QJsonValue value = object.value("character3");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "character3 : " << strName;
					this->character3 = strName;
				}
			}

			if (object.contains("character4")) {
				QJsonValue value = object.value("character4");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "character4 : " << strName;
					this->character4 = strName;
				}
			}

			if (object.contains("character5")) {
				QJsonValue value = object.value("character5");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "character5 : " << strName;
					this->character5 = strName;
				}
			}

			if (object.contains("character6")) {
				QJsonValue value = object.value("character6");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "character6 : " << strName;
					this->character6 = strName;
				}
			}

			if (object.contains("character7")) {
				QJsonValue value = object.value("character7");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "character7 : " << strName;
					this->character7 = strName;
				}
			}

			if (object.contains("character8")) {
				QJsonValue value = object.value("character8");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "character8 : " << strName;
					this->character8 = strName;
				}
			}

			if (object.contains("character9")) {
				QJsonValue value = object.value("character9");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "character9 : " << strName;
					this->character9 = strName;
				}
			}

			if (object.contains("character10")) {
				QJsonValue value = object.value("character10");
				if (value.isString()) {
					QString strName = value.toString();
					qDebug() << "character10 : " << strName;
					this->character10 = strName;
				}
			}

			if (object.contains("scriptArray")) {
				QJsonValue value = object.value("scriptArray");
				if (value.isArray()) {  // Version 的 value 是数组
					QJsonArray array = value.toArray();
					int nSize = array.size();
					for (int i = 0; i < nSize; ++i) {
						QJsonValue value = array.at(i);
						if (value.isString()) {
							QString scriptStr = QString::fromLocal8Bit(value.toString().toLocal8Bit().data());
							qDebug() << "scriptArray : " << scriptStr;
						}
					}
					this->scriptList = array;
				}
			}

			if (object.contains("subscriptArray")) {
				QJsonValue value = object.value("subscriptArray");
				if (value.isArray()) {  // Version 的 value 是数组
					QJsonArray array = value.toArray();
					int nSize = array.size();
					for (int i = 0; i < nSize; ++i) {
						QJsonValue value = array.at(i);
						if (value.isString()) {
							QString scriptStr = QString::fromLocal8Bit(value.toString().toLocal8Bit().data());
							qDebug() << "subscriptArray : " << scriptStr;
						}
					}
					this->subscriptArray = array;
				}
			}
		}
	}
}

unsigned __stdcall TianxiaScript::ThreadFun(void * pParam) {
	ScriptParam* param;
	param = (struct ScriptParam*)pParam;
	long hwnd = param->lHWND;
	int index = param->index;
	DWORD threadId = param->threadId;
	QString configString = param->config;
	qDebug() << "configString" << configString;
	Ifire* DM = param->DM;

	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	try {


		char buf[1000];
		GetCurrentDirectoryA(1000, buf);  //得到当前工作路径
		string path;
		path.assign(buf);
		path.append("\\tianxia");

		DM->PskSetPath(path.c_str());
		string xx = DM->GetMachineCode();
		//DM->PskSetDict(1, "txzk_huoli.txt");
		qDebug() << "machineCode=";
		qDebug() << xx.c_str();
		//int bindRet = DM->PskBindWindowEx(hwnd, "dx3", "windows", "windows", "dx.mouse.raw.input|dx.public.anti.api|dx.public.memory", 0);
		int bindRet = DM->PskBindWndEx(hwnd, "dx2", "windows", "windows", "", 103);
		//int bindRet = DM->PskBindWindowEx(hwnd, "dx.graphic.3d.10plus", "windows", "windows", "dx.public.graphic.speed", 103);
		//int cret = DM->PskCapture(0, 0, 1080, 300, "test.bmp");
		if (bindRet == 0) {
			MessageBoxA(NULL, "绑定失败!请联系客服", "", MB_OK);
			return 0;
		}

		TianxiaScript script;
		script.stepIndex = 0;
		script.lHWND = hwnd;
		script.index = index;
		script.scriptIndex = 0;
		script.subscriptIndex = 0;

		script.zhuxianIng = true;
		script.tempCounter = 0;
		script.threadId = threadId;
		script.isInfuben = true;
		script.roleIndex = 0;
		script.startTime = timeGetTime();
		script.currentLevel = 0;
		script.isHided = false;
		script.isRepeated = false;
		script.power = 0;
		script.isShimenGoumai = true;
		script.huoliFlag = false;

		script.myJinbi = 0;
		script.mitanCounter = 0;
		script.shimenCounter = 0;
		script.wuxingCounter = 0;
		script.tianlaoCounter = 0;

		script.getConfig(configString);

		int counter = 0;

		string todayStr = CommonUtil::getCurrentDateStr(0);
		todayStr.append(" 20:30:00");
		int biwuPrefixTime = CommonUtil::GetTimeStampByStr(todayStr.c_str());

		todayStr = CommonUtil::getCurrentDateStr(0);
		todayStr.append(" 22:00:00");
		int biwuSuffixTime = CommonUtil::GetTimeStampByStr(todayStr.c_str());


		script.biwuPrefix = biwuPrefixTime;
		script.biwuSuffix = biwuSuffixTime;

		todayStr = CommonUtil::getCurrentDateStr(0);
		todayStr.append(" 12:00:00");
		int xiangshiPrefixTime = CommonUtil::GetTimeStampByStr(todayStr.c_str());
		todayStr = CommonUtil::getCurrentDateStr(1);
		//todayStr.append(" 24:00:00");
		int xiangshiSuffixTime = CommonUtil::GetTimeStampByStr(todayStr.c_str());


		script.xiangshiPrefix = xiangshiPrefixTime;
		script.xiangshiSuffix = xiangshiSuffixTime;

		todayStr = CommonUtil::getCurrentDateStr(0);
		todayStr.append(" 14:30:00");
		int juediPrefixTime = CommonUtil::GetTimeStampByStr(todayStr.c_str());

		todayStr = CommonUtil::getCurrentDateStr(0);
		todayStr.append(" 21:00:00");
		int juediSuffixTime = CommonUtil::GetTimeStampByStr(todayStr.c_str());


		script.juediPrefix = juediPrefixTime;
		script.juediSuffix = juediSuffixTime;



		TianxiaSingleton* tx = TianxiaSingleton::getInstance();
		QTableWidget* table = tx->table;


		while (script.getIsEnded() == false) {
			Sleep(3000);
			if (script.getIsPaued() == true) {
				Sleep(10000);
				continue;
			}

			if (script.find12Chongzhifanli(DM) == 1) {
				DM->PskMTo(580, 10);
				DM->PskLClick();
				Sleep(1000);
			}
			//DM->PskCapture(0, 0, 300, 300, "test.jpg");
			script.findBattery(DM);
			script.shiliChaqi(DM);
			script.dahuangGuaiti(DM);
			script.goumaiClose(DM);
			//script.yuyiClose(DM);
			script.menpaiJingjiClose(DM);
			script.zhaixingLou(DM);
			script.chongfanClose(DM);
			//script.yihouZaishuo(DM);
			script.richangClose(DM);//20180106
			script.clickGongzhanCloseBtn(DM);
			script.fixNameBug(DM);
			script.clickChuanchengCloseBtn(DM);
			script.clickYunshiCloseBtn(DM);

			if (script.authIDCardName(DM) == 1) {
				Sleep(1000);
				script.authIDCardNumber(DM);
				Sleep(1000);
				script.authPhoneNumber(DM);
				Sleep(1000);
				script.authQuerenBTN(DM);
				DM->PskMTo(300, 290);
				DM->PskLClick();
				Sleep(3000);
			}

			script.yanWuIng(DM);
			//script.tongguanJiangli(DM);
			//script.gongzhanClose(DM);
			script.tuichuYanwuShi(DM);
			script.mijingLingjiang(DM);

			//script.jiahuClose(DM);
			script.getWindowIsExist(DM);
			//script.kaMijing(DM);
			//script.querenQiangzhi(DM);
			script.yuandiFuhuoEx(DM);
			script.quxiaoClose(DM);
			//script.zhaoShifu(DM);
			script.closeUpdate(DM);
			script.dongjieQueding(DM);

			script.duihuaHuangtiao(DM);
			//script.tuoliKadian(DM);

			script.jiangchiLingjiang(DM);
			script.tongjiClose(DM);
			script.saomaClose(DM);
			script.kaifuLibao(DM);
			script.tudibaoMing(DM);
			script.jieriClose(DM);
			script.lapiaoClose(DM);

			script.timerChecker();
			if (script.isHided == false) {
				script.hideTheOthers(DM);
			}



			int size = script.completeMap.size();
			table->setItem(index - 1, 6, new QTableWidgetItem(QString::number(size)));
			table->setItem(index - 1, 4, new QTableWidgetItem(QString::number(script.roleIndex)));

			if (size >= script.character_size) {
				table->setItem(index - 1, 0, new QTableWidgetItem(QString::fromLocal8Bit("222221")));
			}

			if (script.tuichuFubenBTN(DM) == 1) {
				Sleep(2000);
				DM->PskMTo(345, 240);
				DM->PskLClick();
				Sleep(1000);
				DM->PskLClick();
				//scriptIndex++;
				Sleep(2000);
				script.tuichuQueding(DM);
				Sleep(2000);
				script.yanwuJiesuanQueding(DM);
			}

			counter++;
			/*if (counter == 10) {
			if (script.stepIndex > script.LOGIN && script.index < script.CHANGGUI) {
			script.reload(DM);
			}

			}*/



			if (counter >= 20) {
				//script.huidaoMenpai(DM);
				//script.map2Jiuli(DM);
				script.clickDengluNormal(DM);
				script.wugeBaoguo(DM);
				//script.shangtongClose(DM);
				script.menpaiBiwuClose(DM);
				//script.clickDengluBtn(DM);
				//script.tongxinhuanpei(DM);
				//script.duihuanjinbiWnd(DM);
				script.duihuaSuojin(DM);
				script.getLevel(DM);
				script.shiliClose(DM);
				counter = 0;

				QString currentTask;

				QJsonValue value = script.scriptList.at(script.scriptIndex);
				if (value.isString()) {
					currentTask = value.toString();
				}

				qDebug() << "currentTask = " << currentTask;

				if (currentTask == "SMRW" || currentTask == "WXP" || currentTask == "MPBW") {
					script.tuoliKadian(DM);
					//script.map2Jiuli(DM);
				}
				script.pindaoClose(DM);
				if (script.stepIndex != TIANXIA_STEPS::CHANGGUI) {
					script.tuoliKadian(DM);
					//script.map2Jiuli(DM);
					script.renwuJiadianNormal(DM);
					script.updateSkillNormal(DM);
				}

				//script.checkBaoguoMan(DM);

				todayStr = CommonUtil::getCurrentDateStr(0);
				todayStr.append(" 20:30:00");
				int biwuPrefixTime = CommonUtil::GetTimeStampByStr(todayStr.c_str());
				todayStr = CommonUtil::getCurrentDateStr(0);
				todayStr.append(" 22:00:00");
				int biwuSuffixTime = CommonUtil::GetTimeStampByStr(todayStr.c_str());
				todayStr = CommonUtil::getCurrentDateStr(0);

				script.biwuPrefix = biwuPrefixTime;
				script.biwuSuffix = biwuSuffixTime;

				todayStr = CommonUtil::getCurrentDateStr(0);
				todayStr.append(" 12:00:00");
				int xiangshiPrefixTime = CommonUtil::GetTimeStampByStr(todayStr.c_str());
				todayStr = CommonUtil::getCurrentDateStr(1);
				//todayStr.append(" 24:00:00");
				int xiangshiSuffixTime = CommonUtil::GetTimeStampByStr(todayStr.c_str());
				todayStr = CommonUtil::getCurrentDateStr(0);

				script.xiangshiPrefix = xiangshiPrefixTime;
				script.xiangshiSuffix = xiangshiSuffixTime;


				todayStr = CommonUtil::getCurrentDateStr(-1);
				//todayStr.append(" 20:30:00");
				script.resetPrefixTime = CommonUtil::GetTimeStampByStr(todayStr.c_str());
				todayStr = CommonUtil::getCurrentDateStr(0);
				todayStr.append(" 01:00:00");
				script.resetSuffixTime = CommonUtil::GetTimeStampByStr(todayStr.c_str());

				//凌晨充值
				int currentTime = CommonUtil::getCurrentTimeInt();
				if (currentTime > script.resetPrefixTime && currentTime < script.resetSuffixTime) {
					script.completeMap.clear();
				}

				//script.dazaoClose(DM);
				//script.qiehuanJueseSubScript(DM);

				//script.gongzhanClose(DM);
			}

			//int testR = CommonUtil::generateRandomNumber();

			qDebug() << "running...";

			if (script.stepIndex <= TIANXIA_STEPS::WAIT_SCAN) {
				script.waitForScanFunction(DM);
				script.stepIndex = TIANXIA_STEPS::WAIT_SCAN;
			}

			if (script.stepIndex <= TIANXIA_STEPS::LOGIN) {
				while (script.findLoginScreen(DM) == 1 && script.getIsEnded() == false) {
					script.stepIndex = TIANXIA_STEPS::LOGIN;
					Sleep(10000);
				}
				Sleep(3000);
				script.findSelectedZone(DM);

				int temp = 0;
				while (script.findDengluBtn(DM) == 0 && script.findZhankaiBtn(DM) == 0 && script.findScanPic(DM) == 0 && script.getIsEnded() == false) {
					Sleep(3000);
					temp++;
					if (temp > 30) {
						break;
					}
				}
				script.clickDengluNormal(DM);
				Sleep(3000);
				if (script.dongjieQueding(DM) == 1)
				{

					CommonUtil::upateGold(index, script.roleIndex, 0);
					script.chongxuanWindow(DM);
				}
				Sleep(5000);
				script.closeUpdate(DM);
			}


			if (script.stepIndex <= TIANXIA_STEPS::AUTH) {
				if (script.authIDCard(DM) == 1) {
					script.stepIndex = TIANXIA_STEPS::AUTH;
				}

				//script.findSelectedZone(DM);

			}

			if (script.stepIndex <= TIANXIA_STEPS::KAICHANG) {
				if (script.findYaogan(DM) == 1) {
					script.stepIndex = TIANXIA_STEPS::KAICHANG;
					script.zouGuangquan(DM);

				}
				script.findSelectedZone(DM);
			}

			if (script.zhuxianIng == true) {
				if (script.stepIndex <= TIANXIA_STEPS::ZHUXIAN) {
					if (script.zhuxianTask(DM) == 1) {
						script.stepIndex = TIANXIA_STEPS::ZHUXIAN;
						script.yuandiFuhuo(DM);
					}
					//script.findSelectedZone(DM);
				}
			}


			if (script.stepIndex == TIANXIA_STEPS::CHANGGUI) {
				qDebug() << "changgui";

				//script.findSelectedZone(DM);
				script.changguiTask(DM);
				//script.stepIndex = TIANXIA_STEPS::CHANGGUI;
			}


		}

		DM->PskUnBindWnd();
		DM->Release();

		QTableWidgetItem* item = table->item(index - 1, 1);
		if (item == NULL) {
			return 0;
		}

		QString text = item->text();
		if (text == "000008") {
			table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("已结束")));
			table->setItem(index - 1, 1, new QTableWidgetItem(QString::fromLocal8Bit("000000")));
		}



		item = table->item(index - 1, 0);
		if (item == NULL) {
			return 0;
		}

		text = item->text();
		if (text == "222220") {
			table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("已停止")));
			table->setItem(index - 1, 0, new QTableWidgetItem(QString::fromLocal8Bit("222222")));
		}

		if (text == "222221") {
			table->setItem(index - 1, 2, new QTableWidgetItem(QString::fromLocal8Bit("已完成")));
			table->setItem(index - 1, 0, new QTableWidgetItem(QString::fromLocal8Bit("222222")));
		}
	}
	catch (exception& e) {
		qFatal("error");
		qFatal(e.what());
	}



	return 0;
}

bool TianxiaScript::getIsEnded()
{
	TianxiaSingleton* tx = TianxiaSingleton::getInstance();
	QTableWidget* table = tx->table;
	QTableWidgetItem* item = table->item(index - 1, 1);
	if (item == NULL) {
		return false;
	}

	QString tHWND = item->text();
	if (tHWND == "000000" || tHWND == "000008") {
		return true;
	}

	item = table->item(index - 1, 0);
	if (item == NULL) {
		return false;
	}

	tHWND = item->text();
	if (tHWND == "222220" || tHWND == "222222" || tHWND == "222220" || tHWND == "222221") {
		return true;
	}

	return false;
}

bool TianxiaScript::getIsPaued()
{
	TianxiaSingleton* tx = TianxiaSingleton::getInstance();
	QTableWidget* table = tx->table;
	QTableWidgetItem* item = table->item(index - 1, 0);
	if (item == NULL) {
		return false;
	}

	QString tHWND = item->text();
	if (tHWND == "111111") {
		return true;
	}

	return false;
}


void TianxiaScript::testCapture(Ifire* DM)
{


	int cret = DM->PskCapture(0, 0, 1080, 300, "test2.bmp");

}