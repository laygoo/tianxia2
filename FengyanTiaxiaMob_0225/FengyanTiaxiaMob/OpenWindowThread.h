#pragma once
#include <QThread>
#include <QDebug>
#include "CommonUtil.h"
#include "TianxiaSingleton.h"
#include "TianxiaScript.h"

class OpenWindowThread : public QThread
{
public:
	OpenWindowThread(int count, string path, QString config);
	OpenWindowThread(int count, string path, QString config, int row);
	~OpenWindowThread();

private:
	OpenWindowThread();
	
	int count;
	string path;
	QString config;
	void OpenWindowThread::getWindowInfo(long lHWND);
	void OpenWindowThread::createGameThread();
	void OpenWindowThread::createGameThreadSingle();
	void OpenWindowThread::resumeGameThread();
	void run();

	int row;
};

