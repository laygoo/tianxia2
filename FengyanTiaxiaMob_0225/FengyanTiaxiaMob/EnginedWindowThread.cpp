#include "EnginedWindowThread.h"



EnginedWindowThread::EnginedWindowThread()
{
}

EnginedWindowThread::EnginedWindowThread(int count, QString config, long engineHWND, Ifire* clicker)
{
	this->count = count;
	this->config = config;
	this->engineHWND = engineHWND;
	this->clicker = clicker;
}

EnginedWindowThread::EnginedWindowThread(int count, QString config, long engineHWND, Ifire* clicker, int row)
{
	this->count = count;
	this->config = config;
	this->row = row;

	this->engineHWND = engineHWND;
	this->clicker = clicker;
}

EnginedWindowThread::~EnginedWindowThread()
{
}

void EnginedWindowThread::getWindowInfo(long lHWND) {

	TianxiaSingleton* tianxia = TianxiaSingleton::getInstance();

	tianxia->table->setItem(tianxia->windowCount, 0, new QTableWidgetItem(QString::fromLocal8Bit("RUNNING")));
	tianxia->table->setItem(tianxia->windowCount, 1, new QTableWidgetItem(QString::number(lHWND)));

}

void EnginedWindowThread::run()
{
	qDebug() << "hello from worker thread " << thread()->currentThreadId();

	if (count == 1024) {
		clicker->PskKDown(18);
		clicker->PskKPress(82);
		clicker->PskKUp(18);
		Sleep(5000);
		createGameThreadSingle();

	}
	else if (count == 512) {
		resumeGameThread();
	}
	else {
		for (int i = 0; i < count; i++) {
			clicker->PskKDown(18);
			clicker->PskKPress(82);
			clicker->PskKUp(18);
			Sleep(5000);

			createGameThread();

			Sleep(8000);
		}
	}

}


void EnginedWindowThread::createGameThreadSingle() {

	TianxiaSingleton* tianxia = TianxiaSingleton::getInstance();

	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = clicker->PskEnumWindow(0, "", "Messiah_Game", 2 + 4 + 32);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, ",");

	int resultCount = result.size();
	int mapSize = result.size() - 1;
	if (mapSize < 0) {
		return;
	}

	int lHWND = atol(result[mapSize].c_str());

	//getWindowInfo(lHWND);
	DWORD processID = clicker->PskGetWndProcId(lHWND);

	tianxia->threadMap.insert(row, processID);

	DEVMODE NewDevMode;
	EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &NewDevMode);
	SetWindowPos((HWND)lHWND, 0, NewDevMode.dmPelsWidth - 600, 0, 600, 400, SWP_SHOWWINDOW | SWP_NOZORDER);
	//不使用的句柄最好关掉
	tianxia->table->setItem(row, 0, new QTableWidgetItem(QString::fromLocal8Bit("RUNNING")));
	tianxia->table->setItem(row, 1, new QTableWidgetItem(QString::number(lHWND)));

	TianxiaScript* tianxiaScript = new TianxiaScript(lHWND, this->config, row + 1, 0);
	tianxiaScript->startScript();


}

void EnginedWindowThread::resumeGameThread() {
	TianxiaSingleton* tianxia = TianxiaSingleton::getInstance();

	QTableWidgetItem* item = tianxia->table->item(row, 1);
	if (item == NULL) {
		return;
	}

	QString tHWND = item->text();

	QHash<int, DWORD>::iterator iter = tianxia->scriptThreadIdMap.find(row);

	DWORD pid = iter.value();

	long temp = tHWND.toLong();
	TianxiaScript* script = new TianxiaScript(temp, this->config, row + 1, pid);
	script->startScript();

}

int EnginedWindowThread::createGameThread() {

	TianxiaSingleton* tianxia = TianxiaSingleton::getInstance();
	
#if MAX_ALLOWED == 15
	if (tianxia->windowCount >= 15) {
		MessageBoxA(NULL, "您已经到达开启限制！", "已经15个了", ERROR);
		return 0;
	}
#endif
	_bstr_t bstr;
	string str, size;
	long x, y, l;

	std::vector<std::string> result;
	bstr = clicker->PskEnumWindow(0, "", "Messiah_Game", 2+4+32);
	str = (_bstr_t)bstr;

	qDebug() << str.c_str();

	result = CommonUtil::split(str, ",");

	int resultCount = result.size();
	int mapSize = result.size() - 1;
	if (mapSize < 0) {
		return 0;
	}
	/*if (mapSize >= result.size()) {
		return 0;
	}*/

	int lHWND = atol(result[mapSize].c_str());

	getWindowInfo(lHWND);
	DWORD processID = clicker->PskGetWndProcId(lHWND);

	tianxia->threadMap.insert(tianxia->windowCount, processID);

	DEVMODE NewDevMode;
	EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &NewDevMode);

	SetWindowPos((HWND)lHWND, 0, NewDevMode.dmPelsWidth - 600, 0, 600, 400, SWP_SHOWWINDOW | SWP_NOZORDER);
	//不使用的句柄最好关掉
	

	
	tianxia->windowCount++;

	TianxiaScript* tianxiaScript = new TianxiaScript(lHWND, this->config, tianxia->windowCount, 0);
	tianxiaScript->startScript();


	
	return 0;

}