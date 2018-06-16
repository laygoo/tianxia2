#include "ScripterMain.h"
#include <Windows.h>
#include <QtWidgets/QApplication>
#include <QMutex>
#include <QDateTime>
#include <iostream>  
#include <exception>  
#include <dbghelp.h>
#include <stdlib.h>  
#pragma comment(lib, "dbghelp.lib")  

using namespace std;

//LONG ApplicationCrashHandler(EXCEPTION_POINTERS *pException) {//��ʽ�쳣����  
//															  /*
//															  ***�������ݴ���***
//															  */
//															  //���� Dump �ļ�  
//	HANDLE hDumpFile = CreateFileA("%s%s\\%s-%04d%02d%02d-%02d%02d%02d-%ld-%ld.dmp", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
//	if (hDumpFile != INVALID_HANDLE_VALUE) {
//		//Dump��Ϣ  
//		MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
//		dumpInfo.ExceptionPointers = pException;
//		dumpInfo.ThreadId = GetCurrentThreadId();
//		dumpInfo.ClientPointers = TRUE;
//		//д��Dump�ļ�����  
//		MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hDumpFile, MiniDumpNormal, &dumpInfo, NULL, NULL);
//	}
//	//���ﵯ��һ������Ի����˳�����  
//	EXCEPTION_RECORD* record = pException->ExceptionRecord;
//	QString errCode(QString::number(record->ExceptionCode, 16)), errAdr(QString::number((uint)record->ExceptionAddress, 16)), errMod;
//	QMessageBox::critical(NULL, "��ʽ����", "<FONT size=4><div><b>���ڷ����Ĵ��󣬱�ʾ��ֿ��Ǹ��</b><br/></div>" +
//		QString("<div>������룺%1</div><div>�����ַ��%2</div></FONT>").arg(errCode).arg(errAdr),
//		QMessageBox::Ok);
//	return EXCEPTION_EXECUTE_HANDLER;
//}

inline BOOL IsDataSectionNeeded(const WCHAR* pModuleName)
{
	if (pModuleName == 0)
	{
		return FALSE;
	}

	WCHAR szFileName[_MAX_FNAME] = L"";
	_wsplitpath(pModuleName, NULL, NULL, szFileName, NULL);

	if (_wcsicmp(szFileName, L"ntdll") == 0)
		return TRUE;

	return FALSE;
}

inline BOOL CALLBACK MiniDumpCallback(PVOID                            pParam,
	const PMINIDUMP_CALLBACK_INPUT   pInput,
	PMINIDUMP_CALLBACK_OUTPUT        pOutput)
{
	if (pInput == 0 || pOutput == 0)
		return FALSE;

	switch (pInput->CallbackType)
	{
	case ModuleCallback:
		if (pOutput->ModuleWriteFlags & ModuleWriteDataSeg)
			if (!IsDataSectionNeeded(pInput->Module.FullPath))
				pOutput->ModuleWriteFlags &= (~ModuleWriteDataSeg);
	case IncludeModuleCallback:
	case IncludeThreadCallback:
	case ThreadCallback:
	case ThreadExCallback:
		return TRUE;
	default:;
	}

	return FALSE;
}

inline void CreateMiniDump(PEXCEPTION_POINTERS pep, LPCTSTR strFileName)
{
	HANDLE hFile = CreateFile(strFileName, GENERIC_READ | GENERIC_WRITE,
		FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if ((hFile != NULL) && (hFile != INVALID_HANDLE_VALUE))
	{
		MINIDUMP_EXCEPTION_INFORMATION mdei;
		mdei.ThreadId = GetCurrentThreadId();
		mdei.ExceptionPointers = pep;
		mdei.ClientPointers = NULL;

		MINIDUMP_CALLBACK_INFORMATION mci;
		mci.CallbackRoutine = (MINIDUMP_CALLBACK_ROUTINE)MiniDumpCallback;
		mci.CallbackParam = 0;

		::MiniDumpWriteDump(::GetCurrentProcess(), ::GetCurrentProcessId(), hFile, MiniDumpNormal, (pep != 0) ? &mdei : 0, NULL, &mci);

		CloseHandle(hFile);
	}
}

LONG __stdcall MyUnhandledExceptionFilter(PEXCEPTION_POINTERS pExceptionInfo)
{
	CreateMiniDump(pExceptionInfo, L"core.dmp");
	/*EXCEPTION_RECORD* record = pExceptionInfo->ExceptionRecord;
	QString errCode(QString::number(record->ExceptionCode, 16)), errAdr(QString::number((uint)record->ExceptionAddress, 16)), errMod;
	QMessageBox::critical(NULL, "��ʽ����", "<FONT size=4><div><b>���ڷ����Ĵ��󣬱�ʾ��ֿ��Ǹ��</b><br/></div>" +
		QString("<div>������룺%1</div><div>�����ַ��%2</div></FONT>").arg(errCode).arg(errAdr),
		QMessageBox::Ok);*/
	EXCEPTION_RECORD* record = pExceptionInfo->ExceptionRecord;
	MessageBox(0, L"�뱣����ļ��������core.dmp", L"��ʽ����", MB_OK);
	/*printf("Error   address   %x/n", pExceptionInfo->ExceptionRecord->ExceptionAddress);
	printf("CPU   register:/n");
	printf("eax   %x   ebx   %x   ecx   %x   edx   %x/n", pExceptionInfo->ContextRecord->Eax,
	pExceptionInfo->ContextRecord->Ebx, pExceptionInfo->ContextRecord->Ecx,
	pExceptionInfo->ContextRecord->Edx);*/
	return   EXCEPTION_EXECUTE_HANDLER;
}

// �˺���һ���ɹ����ã�֮��� SetUnhandledExceptionFilter �ĵ��ý���Ч  
void DisableSetUnhandledExceptionFilter()
{
	void* addr = (void*)GetProcAddress(LoadLibrary(L"kernel32.dll"),
		"SetUnhandledExceptionFilter");

	if (addr)
	{
		unsigned char code[16];
		int size = 0;

		code[size++] = 0x33;
		code[size++] = 0xC0;
		code[size++] = 0xC2;
		code[size++] = 0x04;
		code[size++] = 0x00;

		DWORD dwOldFlag, dwTempFlag;
		VirtualProtect(addr, size, PAGE_READWRITE, &dwOldFlag);
		WriteProcessMemory(GetCurrentProcess(), addr, code, size, NULL);
		VirtualProtect(addr, size, dwOldFlag, &dwTempFlag);
	}
}

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
	//qInstallMessageHandler(outputMessage);


	QApplication a(argc, argv);

	//SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);//ע���쳣������  
	SetUnhandledExceptionFilter(MyUnhandledExceptionFilter);

	QWidget* parent = new QWidget;

	ScripterMain* w = new ScripterMain(parent);
	w->show();
	w->activateWindow();
	int result = a.exec();

	/*QWidget* parent2;
	ScripterMain* w2 = new ScripterMain(parent2);*/

	delete parent;

	/*ScripterMain* w = new ScripterMain();
	w->show();
	w->activateWindow();
	int result = a.exec();*/
	return result;
	
}


