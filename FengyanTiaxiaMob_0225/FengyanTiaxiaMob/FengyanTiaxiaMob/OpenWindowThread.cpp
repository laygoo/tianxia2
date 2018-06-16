#include "OpenWindowThread.h"



OpenWindowThread::OpenWindowThread()
{
}

OpenWindowThread::OpenWindowThread(int count, string path, QString config)
{
	this->count = count;
	this->path = path;
	this->config = config;
}

OpenWindowThread::OpenWindowThread(int count, string path, QString config, int row)
{
	this->count = count;
	this->path = path;
	this->config = config;
	this->row = row;
}

OpenWindowThread::~OpenWindowThread()
{
}

void OpenWindowThread::run()
{
	qDebug() << "hello from worker thread " << thread()->currentThreadId();

	if (count == 1024) {
		createGameThreadSingle();
		
	}
	else if (count == 512) {
		resumeGameThread();
	}
	else {
		for (int i = 0; i < count; i++) {
			createGameThread();
		}
	}
	
}

void OpenWindowThread::createGameThreadSingle() {
	
	TianxiaSingleton* tianxia = TianxiaSingleton::getInstance();

	STARTUPINFOA si;
	memset(&si, 0, sizeof(STARTUPINFO));//初始化si在内存块中的值（详见memset函数）
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_SHOW;
	PROCESS_INFORMATION pi;//必备参数设置结束
	if (!CreateProcessA(path.c_str(),
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

		tianxia->table->setItem(row, 0, new QTableWidgetItem(QString::fromLocal8Bit("RUNNING")));
		tianxia->table->setItem(row, 1, new QTableWidgetItem(QString::number(lHWND)));

		//threadMap.remove(row);
		tianxia->threadMap.insert(row, pi.dwProcessId);
		//string test = CommonUtil::getIDNumber();
		tianxia->scriptThreadIdMap.insert(row, pi.dwThreadId);

		DEVMODE NewDevMode;
		EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &NewDevMode);
		SetWindowPos((HWND)lHWND, 0, NewDevMode.dmPelsWidth - 600, 0, 600, 400, SWP_SHOWWINDOW | SWP_NOZORDER);
		//不使用的句柄最好关掉
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);

		

		TianxiaScript* tianxia = new TianxiaScript(lHWND, this->config, row + 1, pi.dwThreadId);
		tianxia->startScript();


	}


}

void OpenWindowThread::resumeGameThread() {
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

void OpenWindowThread::createGameThread() {
	
	TianxiaSingleton* tianxia = TianxiaSingleton::getInstance();
#if MAX_ALLOWED == 15
	if (tianxia->windowCount >= 15) {
		MessageBoxA(NULL, "您已经到达开启限制！", "已经15个了", ERROR);
		return;
	}
#endif
	STARTUPINFOA si;
	memset(&si, 0, sizeof(STARTUPINFO));//初始化si在内存块中的值（详见memset函数）
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_SHOW;
	PROCESS_INFORMATION pi;//必备参数设置结束
	if (!CreateProcessA(path.c_str(),
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


		getWindowInfo(lHWND);

		/*for (int i = 0; i < 200; i++) {
		CommonUtil::getRandomCNChar();
		}*/

		tianxia->threadMap.insert(tianxia->windowCount, pi.dwProcessId);
		//string test = CommonUtil::getIDNumber();
		tianxia->scriptThreadIdMap.insert(tianxia->windowCount, pi.dwThreadId);
		DEVMODE NewDevMode;
		EnumDisplaySettings(0, ENUM_CURRENT_SETTINGS, &NewDevMode);
		SetWindowPos((HWND)lHWND, 0, NewDevMode.dmPelsWidth - 600, 0, 600, 400, SWP_SHOWWINDOW | SWP_NOZORDER);
		//不使用的句柄最好关掉
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);

		//QString config = loadScriptConfig();
		tianxia->windowCount++;

		TianxiaScript* tianxiaScript = new TianxiaScript(lHWND, this->config, tianxia->windowCount, pi.dwThreadId);
		tianxiaScript->startScript();


	}


}

void OpenWindowThread::getWindowInfo(long lHWND) {

	TianxiaSingleton* tianxia = TianxiaSingleton::getInstance();

	tianxia->table->setItem(tianxia->windowCount, 0, new QTableWidgetItem(QString::fromLocal8Bit("RUNNING")));
	tianxia->table->setItem(tianxia->windowCount, 1, new QTableWidgetItem(QString::number(lHWND)));

}