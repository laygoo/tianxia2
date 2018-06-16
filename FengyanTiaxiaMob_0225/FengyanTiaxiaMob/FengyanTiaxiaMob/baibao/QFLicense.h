#ifndef QFLICENSE_H_
#define QFLICENSE_H_
#pragma comment(lib,"WebZCM.lib")

// ��ʼ��DLL
int __stdcall InitDll(const char* token/*in*/, const char* proid/*in*/);
int __stdcall InitDllW(const wchar_t* token/*in*/, const wchar_t* proid/*in*/);

// ע�����¼�����Զ���֤��Ч��
unsigned int __stdcall LoginRegCodeAuto(const char* regcode/*in*/);
unsigned int __stdcall LoginRegCodeAutoW(const wchar_t* regcode/*in*/);
// ע�����¼ ��Ҫ�Լ�д�������
unsigned int __stdcall LoginRegCode(const char* regcode/*in*/);
unsigned int __stdcall LoginRegCodeW(const wchar_t* regcode/*in*/);
// ע�����¼�����Զ���֤��Ч��
unsigned int __stdcall LoginRegCodeEx(const char* regcode,const char* remark);
unsigned int __stdcall LoginRegCodeExW(const wchar_t* regcode,const wchar_t* remark);
// ע�����¼ ��Ҫ�Լ�д�������
unsigned int __stdcall LoginRegCodeAutoEx(const char* regcode,const char* remark);
unsigned int __stdcall LoginRegCodeAutoExW(const wchar_t* regcode,const wchar_t* remark);

// ���õ�¼
unsigned int __stdcall TryLogin();
unsigned int __stdcall TryLoginW();
// ��ȡ���õ�ʣ��ʱ��
unsigned int __stdcall GetTryTime();
unsigned int __stdcall GetTryTimeW();

// ��ȡע��������
unsigned int __stdcall CheckRegCode(char* result/*out*/, unsigned int nMax/*in*/);
unsigned int __stdcall CheckRegCodeW(wchar_t* result/*out*/, unsigned int nMax/*in*/);
// ��ȡע�����ʣ��ʱ��
unsigned int __stdcall GetRegCodeTime();
unsigned int __stdcall GetRegCodeTimeW();
// ���
unsigned int __stdcall Ubind(const char* regcode/*in*/, const char* pwd/*in*/);
unsigned int __stdcall UbindW(const wchar_t* regcode/*in*/, const wchar_t* pwd/*in*/);
// ����ע����ı�ע��Ϣ
unsigned int __stdcall SetRegCodeRemark(const char* remark/*in*/);
unsigned int __stdcall SetRegCodeRemarkW(const wchar_t* remark/*in*/);
// ��ȡע����ı�ע����
unsigned int __stdcall GetRegCodeRemark(char* result/*out*/, unsigned int nMax/*in*/);
unsigned int __stdcall GetRegCodeRemarkW(wchar_t* result/*out*/, unsigned int nMax/*in*/);
// �����ļ�
int __stdcall UpdateFile(const char* version/*in*/);
int __stdcall UpdateFileW(const wchar_t* version/*in*/);
// �����ļ� ��չģʽ
unsigned int __stdcall UpdateFileEx(const char* version/*in*/, bool autoRun);
unsigned int __stdcall UpdateFileExW(const wchar_t* version/*in*/, bool autoRun);
// ��ȡ��Ŀ����
unsigned int __stdcall GetPlacard(char* result/*out*/, unsigned int nMax/*in*/);
unsigned int __stdcall GetPlacardW(wchar_t* result/*out*/, unsigned int nMax/*in*/);
// ���ͼ����Ϣ
unsigned int __stdcall SendMonitorMsg(const char* name/*in*/, const char* msg/*in*/);
unsigned int __stdcall SendMonitorMsgW(const wchar_t* name/*in*/, const wchar_t* msg/*in*/);
// ��ȡ�Զ�������
unsigned int __stdcall GetCustom(const char* key/*in*/, char* result/*out*/, unsigned int nMax/*in*/);
unsigned int __stdcall GetCustomW(const wchar_t* key/*in*/, wchar_t* result/*out*/, unsigned int nMax/*in*/);
// ��ȡ��������Ϣ����
unsigned int __stdcall GetLastErrorInfo(char* result/*out*/, unsigned int nMax/*in*/);
unsigned int __stdcall GetLastErrorInfoW(wchar_t* result/*out*/, unsigned int nMax/*in*/);
// ��ȡ��������ϢID
unsigned int __stdcall GetLastErrorInfoID();
unsigned int __stdcall GetLastErrorInfoIDW();
// ��ȡ��DLL�汾��
unsigned int __stdcall PluginVersion(char *result/*out*/, unsigned int nMax/*in*/);
unsigned int __stdcall PluginVersionW(wchar_t *result/*out*/, unsigned int nMax/*in*/);
// ��ȡ��ע�����¼�ķ�������
unsigned int __stdcall GetRegCodeKey(char *result/*out*/, unsigned int nMax/*in*/);
unsigned int __stdcall GetRegCodeKeyW(wchar_t *result/*out*/, unsigned int nMax/*in*/);

// ʹ����չģʽ�������õ�¼
unsigned int __stdcall TryLoginEx(char *result/*out*/, unsigned int nMax/*in*/);
unsigned int __stdcall TryLoginExW(wchar_t *result/*out*/, unsigned int nMax/*in*/);

// ��ע������г�ֵ
unsigned int __stdcall Charge(const char *newcard/*in*/, const char *oldcard/*in*/);
unsigned int __stdcall ChargeW(const wchar_t *newcard/*in*/, const wchar_t *oldcard/*in*/);

// ע�����˳���¼
unsigned int __stdcall RegCodeLogOut();

// ���û������ȡ��ģʽ
void __stdcall SetMachineMode(unsigned int flag/*in*/);
// ���ÿͻ�����Ϣ
unsigned int __stdcall SetClientInfo(const char* remark/*in*/);
unsigned int __stdcall SetClientInfoW(const wchar_t* remark/*in*/);

//ע����ϵͳͨ��ͨѶ�ӿ�
int __stdcall CommonInterface(const char *arg,char* result,unsigned int nMax);
int __stdcall CommonInterfaceW(const wchar_t *arg,wchar_t* result,unsigned int nMax);

//����Ϊ�㷨����
// MD5�㷨
unsigned int __stdcall MD5(const char *str/*in*/, char* result/*out*/, unsigned int nMax/*in*/);
unsigned int __stdcall MD5W(const wchar_t *str/*in*/, wchar_t* result/*out*/, unsigned int nMax/*in*/);
// ��ȡ������
unsigned int __stdcall GetMachinecode(char* result/*out*/, unsigned int nMax/*in*/);
unsigned int __stdcall GetMachinecodeW(wchar_t* result/*out*/, unsigned int nMax/*in*/);

//Ϊ�ͻ�����������������
int _stdcall SetMachinecode(const char *arg);
int _stdcall SetMachinecodeW(const wchar_t *arg);

//��ע������صĿͻ�������
unsigned int __stdcall ClientOffline(const char * regcode,const char * machinecode);
unsigned int __stdcall ClientOfflineW(const wchar_t *str,const wchar_t * machinecode);

// AES����
unsigned int __stdcall AesEncrypt(const char *str/*in*/, const char *key/*in*/, char* result/*out*/, unsigned int nMax/*in*/);
unsigned int __stdcall AesEncryptW(const wchar_t *str/*in*/, const wchar_t *key/*in*/, wchar_t* result/*out*/, unsigned int nMax/*in*/);
// AES����
unsigned int __stdcall AesDecrypt(const char *str/*in*/,const char *key/*in*/,char* result/*out*/,unsigned int nMax/*in*/);
unsigned int __stdcall AesDecryptW(const wchar_t *str/*in*/,const wchar_t *key/*in*/,wchar_t* result/*out*/,unsigned int nMax/*in*/);
// DES ����
unsigned int __stdcall DesEncrypt(const char *str/*in*/,const char *key/*in*/,char* result/*out*/,unsigned int nMax/*in*/);
unsigned int __stdcall DesEncryptW(const wchar_t *str/*in*/,const wchar_t *key/*in*/,wchar_t* result/*out*/,unsigned int nMax/*in*/);
// DES ����
unsigned int __stdcall DesDecrypt(const char *str/*in*/,const char *key/*in*/,char* result/*out*/,unsigned int nMax/*in*/);
unsigned int __stdcall DesDecryptW(const wchar_t *str/*in*/,const wchar_t *key/*in*/,wchar_t* result/*out*/,unsigned int nMax/*in*/);
// Blowfish ����
unsigned int __stdcall BlowfishEncrypt(const char *str/*in*/,const char *key/*in*/,char* result/*out*/,unsigned int nMax/*in*/);
unsigned int __stdcall BlowfishEncryptW(const wchar_t *str/*in*/,const wchar_t *key/*in*/,wchar_t* result/*out*/,unsigned int nMax/*in*/);
// Blowfish ����
unsigned int __stdcall BlowfishDecrypt(const char *str/*in*/,const char *key/*in*/,char* result/*out*/,unsigned int nMax/*in*/);
unsigned int __stdcall BlowfishDecryptW(const wchar_t *str/*in*/,const wchar_t *key/*in*/,wchar_t* result/*out*/,unsigned int nMax/*in*/);
// TEA ����
unsigned int __stdcall TeaEncrypt(const char *str/*in*/,const char *key/*in*/,char* result/*out*/,unsigned int nMax/*in*/);
unsigned int __stdcall TeaEncryptW(const wchar_t *str/*in*/,const wchar_t *key/*in*/,wchar_t* result/*out*/,unsigned int nMax/*in*/);
// TEA ����
unsigned int __stdcall TeaDecrypt(const char *str/*in*/,const char *key/*in*/,char* result/*out*/,unsigned int nMax/*in*/);
unsigned int __stdcall TeaDecryptW(const wchar_t *str/*in*/,const wchar_t *key/*in*/,wchar_t* result/*out*/,unsigned int nMax/*in*/);
// RC2 ����
unsigned int __stdcall Rc2Encrypt(const char *str/*in*/,const char *key/*in*/,char* result/*out*/,unsigned int nMax/*in*/);
unsigned int __stdcall Rc2EncryptW(const wchar_t *str/*in*/,const wchar_t *key/*in*/,wchar_t* result/*out*/,unsigned int nMax/*in*/);
// RC2 ����
unsigned int __stdcall Rc2Decrypt(const char *str/*in*/,const char *key/*in*/,char* result/*out*/,unsigned int nMax/*in*/);
unsigned int __stdcall Rc2DecryptW(const wchar_t *str/*in*/,const wchar_t *key/*in*/,wchar_t* result/*out*/,unsigned int nMax/*in*/);
// RC5 ����
unsigned int __stdcall Rc5Encrypt(const char *str/*in*/,const char *key/*in*/,char* result/*out*/,unsigned int nMax/*in*/);
unsigned int __stdcall Rc5EncryptW(const wchar_t *str/*in*/,const wchar_t *key/*in*/,wchar_t* result/*out*/,unsigned int nMax/*in*/);
// RC5 ����
unsigned int __stdcall Rc5Decrypt(const char *str/*in*/,const char *key/*in*/,char* result/*out*/,unsigned int nMax/*in*/);
unsigned int __stdcall Rc5DecryptW(const wchar_t *str/*in*/,const wchar_t *key/*in*/,wchar_t* result/*out*/,unsigned int nMax/*in*/);
// RC6 ����
unsigned int __stdcall Rc6Encrypt(const char *str/*in*/,const char *key/*in*/,char* result/*out*/,unsigned int nMax/*in*/);
unsigned int __stdcall Rc6EncryptW(const wchar_t *str/*in*/,const wchar_t *key/*in*/,wchar_t* result/*out*/,unsigned int nMax/*in*/);
// RC6 ����
unsigned int __stdcall Rc6Decrypt(const char *str/*in*/,const char *key/*in*/,char* result/*out*/,unsigned int nMax/*in*/);
unsigned int __stdcall Rc6DecryptW(const wchar_t *str/*in*/,const wchar_t *key/*in*/,wchar_t* result/*out*/,unsigned int nMax/*in*/);



#endif