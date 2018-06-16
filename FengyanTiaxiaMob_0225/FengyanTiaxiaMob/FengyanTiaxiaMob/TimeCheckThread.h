#pragma once

#include <QThread>
#include <QLabel>

#include "baibao\QFLicense.h"
#include "CommonUtil.h"
#include "TianxiaSingleton.h"
#include "OpenWindowThread.h"

class TimeCheckThread : public QThread
{
	Q_OBJECT

public:
	TimeCheckThread(QLabel* timeLabel);
	TimeCheckThread(QObject *parent);
	TimeCheckThread();
	~TimeCheckThread();

private:
	QLabel *timeLabel;
	void run();
	int TimeCheckThread::reInitializer(int resetPrefixTime, int resetSuffixTime);
	void TimeCheckThread::allStart();
};
