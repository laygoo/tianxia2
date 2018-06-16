#include "ScripterMain.h"
#include <QtWidgets/QApplication>
#include <QMutex>
#include <QDateTime>
#include <iostream>  
#include <exception>  

using namespace std;

//#pragma execution_character_set("utf-8")

void outputMessage(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
	static QMutex mutex;
	mutex.lock();

	QString text;
	switch (type)
	{
	case QtDebugMsg:
		text = QString("Debug:");
		break;

	case QtWarningMsg:
		text = QString("Warning:");
		break;

	case QtCriticalMsg:
		text = QString("Critical:");
		break;

	case QtFatalMsg:
		text = QString("Fatal:");
	}

	QString context_info = QString("File:(%1) Line:(%2)").arg(QString(context.file)).arg(context.line);
	QString current_date_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss ddd");
	QString current_date = QString("(%1)").arg(current_date_time);
	QString message = QString("%1 %2 %3 %4").arg(text).arg(context_info).arg(msg).arg(current_date);

	//QFile file("log.txt");
	//file.open(QIODevice::WriteOnly | QIODevice::Append);
	
	//text_stream << message << "\r\n";
	

	QFile outFile1("debuglog1.txt");
	QFile outFile2("debuglog2.txt");
	QTextStream text_stream(&outFile1);
	outFile1.open(QIODevice::WriteOnly | QIODevice::Append);
	if (outFile1.size() >= 1024 * 200)
	{
		outFile1.close();
		outFile2.remove();
		QFile::copy("debuglog1.txt", "debuglog2.txt");
		outFile1.remove();

		QFile outFile3("debuglog1.txt");
		outFile3.open(QIODevice::WriteOnly | QIODevice::Append);
		QTextStream ts(&outFile3);
		text_stream << message << "\r\n";
	}
	else
	{
		QTextStream ts(&outFile1);
		text_stream << message << "\r\n";
	}

	outFile1.flush();
	outFile1.close();
	mutex.unlock();
}



int main(int argc, char *argv[])
{
	qInstallMessageHandler(outputMessage);

	try {
		QApplication a(argc, argv);


		QWidget* parent = new QWidget;

		ScripterMain* w = new ScripterMain(parent);
		w->show();
		w->activateWindow();
		int result = a.exec();

		delete parent;

		/*ScripterMain* w = new ScripterMain();
		w->show();
		w->activateWindow();
		int result = a.exec();*/
		return result;
	}
	catch (exception& e) {
		qFatal(e.what());
	}
	
}


