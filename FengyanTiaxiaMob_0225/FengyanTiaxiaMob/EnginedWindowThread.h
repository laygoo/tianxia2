#pragma once
#include "qthread.h"
#include <QDebug>
#include "CommonUtil.h"
#include "TianxiaSingleton.h"
#include "TianxiaScript.h"

class EnginedWindowThread :
	public QThread
{
public:
	EnginedWindowThread(int count, QString config, long engineHWND, Ifire* clicker);
	EnginedWindowThread(int count, QString config, long engineHWND, Ifire* clicker, int row);

	EnginedWindowThread();
	~EnginedWindowThread();

private:

	Ifire* clicker;
	int count;
	string path;
	QString config;
	int row;
	long engineHWND;

	void EnginedWindowThread::getWindowInfo(long lHWND);
	int EnginedWindowThread::createGameThread();
	void EnginedWindowThread::createGameThreadSingle();
	void EnginedWindowThread::resumeGameThread();
	void run();

	
};

