#include "TimeCheckThread.h"
#define MAX_ERROR_NUM 5   // �����ݴ���������������޸�
#include <Windows.h>

TimeCheckThread::TimeCheckThread(QObject *parent)
	: QThread(parent)
{
}

TimeCheckThread::~TimeCheckThread()
{
}

TimeCheckThread::TimeCheckThread(QLabel *timeLabel)
{
	this->timeLabel = timeLabel;
}

TimeCheckThread::TimeCheckThread()
{
	
}

void TimeCheckThread::run() {
	int nErrorCount = 0;
	int nResult = 0;
	TianxiaSingleton* tianxia = TianxiaSingleton::getInstance();



	while (true)
	{
		string todayStr = CommonUtil::getCurrentDateStr(-1);
		int resetPrefixTime = CommonUtil::GetTimeStampByStr(todayStr.c_str());
		todayStr = CommonUtil::getCurrentDateStr(0);
		todayStr.append(" 01:00:00");
		int resetSuffixTime = CommonUtil::GetTimeStampByStr(todayStr.c_str());
		
		reInitializer(resetPrefixTime, resetSuffixTime);
		Sleep(5000);
		
		nResult = GetRegCodeTimeW();
		if (nResult > 0)
		{
			nErrorCount = 0;
			timeLabel->setText(QString::number(nResult));

			//g_csRemainTime.Format(_T("ע����ʣ��ʱ�䣺%dСʱ%d����"), (int)(nResult / 60), nResult % 60); // ��¼ʣ��ʱ��
		}
		else
		{
			nErrorCount++;
			if (nErrorCount > MAX_ERROR_NUM)
			{
				TCHAR buffer[1024] = { 0 };
				GetLastErrorInfoW(buffer, 1024);
				//::AfxMessageBox(_T("ע����ʹ�ý�����ԭ��") + CString(buffer));
				exit(-1);
			}
		}
		Sleep(60 * 1000);
	}
}

int TimeCheckThread::reInitializer(int resetPrefixTime, int resetSuffixTime) {
	int currentTime = CommonUtil::getCurrentTimeInt();
	if (currentTime > resetPrefixTime && currentTime < resetSuffixTime) {
		allStart();
	}
	return 0;
}

void TimeCheckThread::allStart() {
	TianxiaSingleton* tianxia = TianxiaSingleton::getInstance();
	qDebug() << "allStart";

	if (tianxia->isAutoRestart == false) {
		return;
	}

	for (int i = 0; i < tianxia->windowCount; i++) {

		QTableWidgetItem* item = tianxia->table->item(i, 0);
		if (item == NULL) {
			return;
		}

		QString tHWND = item->text();
		qDebug() << tHWND;

		if ("222222" != tHWND || "000000" == tHWND) {
			continue;
		}

		QString config = tianxia->config;


		QString file = "";
		OpenWindowThread* thread = new OpenWindowThread(512, file.toStdString(), config, i);

		tianxia->table->setItem(i, 2, new QTableWidgetItem(QString::fromLocal8Bit("��ʼ��")));
		tianxia->table->setItem(i, 0, new QTableWidgetItem(QString::fromLocal8Bit("RUNNING")));
		thread->start();

		Sleep(1000);
	}
}