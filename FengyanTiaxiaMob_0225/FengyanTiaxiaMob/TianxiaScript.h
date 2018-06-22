#pragma once
#include "DMSoft.h"
#include <process.h>  
#include <QtCore/QDebug>
#include "TianxiaSingleton.h"
#include <QtWidgets/QTableWidget>
#include <QJsonArray>
#include <QJsonParseError>
#include <QJsonObject>
#include "CommonUtil.h"
#include "IDGenerator.h"


class TianxiaScript
{
private:
	Ifire* DM;
	static unsigned __stdcall ThreadFun(void * pParam);
	long lHWND;
	void TianxiaScript::testCapture(Ifire* DM);
	QString jsonConfig;

	DWORD threadId;
	int index;
	int stepIndex;
	int scriptIndex;
	int subscriptIndex;

	QString team_mode;
	DWORD startTime;
	int huoli_param;
	int team_param;
	int time_limit;
	int mitan_counter;
	QString forceIdField;
	int shimen_counter;
	int zhuxian_level;
	long myJinbi;

	bool isEquiped;

	int tempCounter;

	bool zhuxianIng;
	bool isInfuben;
	bool isZhuxianEnabled;
	bool generalDZCheckBox;
	bool huoyueCheckBox;
	bool isCaptained;
	bool isShimenJun;

	bool rizuanBox;
	bool yuezuanBox;
	bool liuyaoBox;

	bool isShimenGoumai;

	bool isHuoliProtected;
	bool isBuqian;
	bool isYongjun;

	bool mengyan;
	bool jianding;
	bool qicai;
	bool isHided;
	bool isRepeated;

	QString idField;
	int power;

	int biwuPrefix;
	int biwuSuffix;

	int xiangshiPrefix;
	int xiangshiSuffix;

	int resetPrefixTime;
	int resetSuffixTime;
	QHash<int, int> completeMap;

	int juediPrefix;
	int juediSuffix;
	int liuguangPrefix;
	int liuguangSuffix;
	
	bool huoliFlag;

	int roleIndex;
	int mitanCounter;
	int shimenCounter;
	int wuxingCounter;
	int tianlaoCounter;
	int juediCounter;

	int currentLevel;
	int goldController;
	int safeJunzi;
	int saoPointer;

	int charaChoose;

	QString daqu;

	QString sao;

	int character_size;
	QString zone_number;
	QString isAutoChangeRole;
	QString isAutoLogin;
	QString character1;
	QString character2;
	QString character3;
	QString character4;
	QString character5;
	QString character6;
	QString character7;
	QString character8;
	QString character9;
	QString character10;
	QJsonArray scriptList;
	QJsonArray subscriptArray;
	void TianxiaScript::getConfig(QString config);
	bool TianxiaScript::getIsEnded();
public:
	enum TIANXIA_STEPS { WAIT_SCAN, LOGIN, AUTH, KAICHANG, ZHUXIAN, CHANGGUI };
	enum SCRIPT_STEPS {SMRW, WXP, WCMT};

	TianxiaScript();
	~TianxiaScript();
	TianxiaScript(long HWNDLong);
	TianxiaScript(long HWNDLong, QString config);
	TianxiaScript(long HWNDLong, QString config, int windowCount);
	TianxiaScript(long HWNDLong, QString config, int windowCount, DWORD threadId);
	void TianxiaScript::startScript();
	
	int TianxiaScript::findGeneralDingzhi(Ifire* DM, long pX, long pY);
	int TianxiaScript::findScanPic(Ifire* DM);
	int TianxiaScript::findLoginScreen(Ifire* DM);
	int TianxiaScript::waitForScanFunction(Ifire* DM);
	int TianxiaScript::findSelectedZone(Ifire* DM);
	int TianxiaScript::findSelectedZoneSubScript(Ifire* DM);
	int TianxiaScript::selectCharacter(Ifire* DM);
	int TianxiaScript::authIDCard(Ifire* DM);
	int TianxiaScript::authIDCardName(Ifire* DM);
	int TianxiaScript::authIDCardNumber(Ifire* DM);
	int TianxiaScript::authPhoneNumber(Ifire* DM);
	int TianxiaScript::authQuerenBTN(Ifire* DM);

	int TianxiaScript::zouGuangquan(Ifire* DM);
	int TianxiaScript::findYaogan(Ifire* DM);

	int TianxiaScript::zhuxianTask(Ifire* DM);
	int TianxiaScript::zhuxianSubScript(Ifire* DM);
	int TianxiaScript::findZhuxianIn(Ifire* DM);
	int TianxiaScript::zhuxianJinxingIn(Ifire* DM);

	int TianxiaScript::zhuxianJieshouIn(Ifire* DM);
	int TianxiaScript::zhuxianConfirmCircle(Ifire* DM);
	int TianxiaScript::zhuxianZhanchangClose(Ifire* DM);
	int TianxiaScript::zhuxianJinben(Ifire* DM);
	int TianxiaScript::zhuxianShangwuju(Ifire* DM);
	int TianxiaScript::zhuxianHaoyou(Ifire* DM);
	int TianxiaScript::zhuxianQinggong(Ifire* DM);
	int TianxiaScript::zhuxianSuojinIn(Ifire* DM, long pX, long pY);
	int TianxiaScript::zhuxianInFuben(Ifire* DM);
	int TianxiaScript::zhuxianInFubenSub(Ifire* DM);
	int TianxiaScript::taskGoumai(Ifire* DM);

	int TianxiaScript::changguiTask(Ifire* DM);
	int TianxiaScript::zhuxianGuankan(Ifire* DM);
	int TianxiaScript::zhuxianFindTaskTitle(Ifire* DM, long pX, long pY);

	int TianxiaScript::yuandiFuhuo(Ifire* DM);
	int TianxiaScript::zhuxianUseBTN(Ifire* DM);

	int TianxiaScript::duihuaSuojin(Ifire* DM);

	int TianxiaScript::changguiFindZhuxian(Ifire* DM, long pX, long pY);
	int TianxiaScript::changguiTaskSubScript(Ifire* DM);
	int TianxiaScript::findChangguiIn(Ifire* DM);
	int TianxiaScript::changguiJinxingIn(Ifire* DM);
	int TianxiaScript::changguiJieshouIn(Ifire* DM);

	int TianxiaScript::shimenTask(Ifire* DM);

	int TianxiaScript::renwuClose(Ifire* DM);
	int TianxiaScript::changguiSuojin(Ifire* DM);
	int TianxiaScript::dianjiTiaoguo(Ifire* DM);
	int TianxiaScript::duihuaHuangtiao(Ifire* DM);
	int TianxiaScript::shiliChaqi(Ifire* DM);
	int TianxiaScript::jinruBtn(Ifire* DM);
	int TianxiaScript::tuijianJiadian(Ifire* DM);
	int TianxiaScript::tuijianJiadianSubScript(Ifire* DM);
	int TianxiaScript::changguiTaskSelector(Ifire* DM);

	int TianxiaScript::changguiFindWCMT(Ifire* DM);
	int TianxiaScript::zidongPipei(Ifire* DM);
	int TianxiaScript::dengdaiPipei(Ifire* DM);
	int TianxiaScript::changguiTurnZhuxian(Ifire* DM);

	int TianxiaScript::dahuangGuaiti(Ifire* DM);
	int TianxiaScript::wuxingTask(Ifire* DM);
	int TianxiaScript::jinengPeizhi(Ifire* DM);
	int TianxiaScript::mengxueXiangshi(Ifire* DM);
	int TianxiaScript::findMengxueXiangshi(Ifire* DM);
	int TianxiaScript::mengxueXiangshiSubScript(Ifire* DM);
	int TianxiaScript::menpaiBiwu(Ifire* DM);
	int TianxiaScript::findMenpaiBiwu(Ifire* DM);
	int TianxiaScript::menpaiTiaozhanBTN(Ifire* DM);
	int TianxiaScript::menpaiBiwuSubScript(Ifire* DM);
	int TianxiaScript::shimenJinXing(Ifire* DM);
	int TianxiaScript::huidaoMenpai(Ifire* DM);
	int TianxiaScript::zhuxian3RD(Ifire* DM);

	int TianxiaScript::wangchaoMitan(Ifire* DM);
	int TianxiaScript::findWangchaoMitan(Ifire* DM);
	int TianxiaScript::tuichuDuiwu(Ifire* DM);
	int TianxiaScript::menpaiBiwuClose(Ifire* DM);
	int TianxiaScript::zuduiClose(Ifire* DM);

	int TianxiaScript::tuiduiBtn(Ifire* DM);
	int TianxiaScript::goumaiClose(Ifire* DM);
	int TianxiaScript::wuxingJinxing(Ifire* DM);
	int TianxiaScript::findKuaimaJianbian(Ifire* DM);
	int TianxiaScript::kuaimaJiabian(Ifire* DM);
	int TianxiaScript::danrenKuaima(Ifire* DM);
	int TianxiaScript::kuaimaXunhuan(Ifire* DM);

	int TianxiaScript::kuaimaJiabianEx(Ifire* DM);
	int TianxiaScript::waWuxingpan(Ifire* DM);

	int TianxiaScript::zhengliBeibao(Ifire* DM);
	int TianxiaScript::wuxingShiyong(Ifire* DM);
	int TianxiaScript::waWuxingpanSubScript(Ifire* DM);
	int TianxiaScript::yuyiClose(Ifire* DM);

	int TianxiaScript::findJishou(Ifire* DM);
	int TianxiaScript::deleteShimen(Ifire* DM);
	int TianxiaScript::yihouZaishuo(Ifire* DM);

	int TianxiaScript::tianlaoZhiyuan(Ifire* DM);
	int TianxiaScript::findTianlaoZhiyuan(Ifire* DM);

	int TianxiaScript::mapSearchTianlaoZhiyuan(Ifire* DM);
	int TianxiaScript::mapSearchBtn(Ifire* DM);
	int TianxiaScript::map2Jiuli(Ifire* DM);
	int TianxiaScript::mapClose(Ifire* DM);
	int TianxiaScript::richangClose(Ifire* DM);

	//HKL TianxiaScript::InitHklRPC();

	int TianxiaScript::isInTianlaoZhiyuan(Ifire* DM);

	int TianxiaScript::generalFuben(Ifire* DM);

	int TianxiaScript::kuaisuZuduiBTN(Ifire* DM);
	int TianxiaScript::fubenChumo(Ifire* DM);
	int TianxiaScript::fubenChumoSub(Ifire* DM, long pX, long pY);
	int TianxiaScript::jingjiZhidianSelect(Ifire* DM);
	int TianxiaScript::menpaiJingjiClose(Ifire* DM);

	int TianxiaScript::yanwutang(Ifire* DM);
	int TianxiaScript::findYanwutang(Ifire* DM);
	int TianxiaScript::jinruYanwutang(Ifire* DM);
	int TianxiaScript::jinruYanwuBTN(Ifire* DM);
	int TianxiaScript::isInYanwu(Ifire* DM);
	int TianxiaScript::autoCombat(Ifire* DM);

	int TianxiaScript::tuichuFubenBTN(Ifire* DM);
	int TianxiaScript::isMapSousuoOpened(Ifire* DM);
	int TianxiaScript::qingliBaoguo(Ifire* DM);
	int TianxiaScript::submitXueqiu(Ifire* DM);

	int TianxiaScript::qingliBaoguoSubScript(Ifire* DM);
	int TianxiaScript::qingbaoSub4Gengduo(Ifire* DM);
	int TianxiaScript::qingbaoSub4Weiling(Ifire* DM);
	int TianxiaScript::qingbaoSub4Dahuandan(Ifire* DM);
	int TianxiaScript::qingbaoSub4GengduoEx(Ifire* DM, long pX, long pY);

	int TianxiaScript::qingbaoSub4ChushouEx(Ifire* DM, long pX, long pY);
	int TianxiaScript::qingbaoSub4Yuye(Ifire* DM);
	int TianxiaScript::chushouBtn(Ifire* DM);
	int TianxiaScript::qingbaoSub4BiwuJiajiang(Ifire* DM);
	int TianxiaScript::qingbaoSub4LeftShiyong(Ifire* DM, long pX, long pY);
	int TianxiaScript::qingbaoSub4Jinbi(Ifire* DM);
	int TianxiaScript::qingbaoSub4LeftShiyongQuanbu(Ifire* DM, long pX, long pY);
	int TianxiaScript::qingbaoSub4Rizuan(Ifire* DM);
	int TianxiaScript::qingbaoSub4Liuyaoshi(Ifire* DM);
	int TianxiaScript::yanwuJiesuanQueding(Ifire* DM);
	int TianxiaScript::mijingXiuxing(Ifire* DM);
	int TianxiaScript::findMijing(Ifire* DM);
	int TianxiaScript::jinruMijingBTN(Ifire* DM);
	int TianxiaScript::isInMijing(Ifire* DM);

	int TianxiaScript::findJikaiqi(Ifire* DM, long pX, long pY);

	int TianxiaScript::tuichuQueding(Ifire* DM);
	int TianxiaScript::huoliChuyao(Ifire* DM);
	int TianxiaScript::huoliBtn(Ifire* DM);
	int TianxiaScript::huoliZhanyaoIn(Ifire* DM);
	int TianxiaScript::huoliHudieIn(Ifire* DM);
	int TianxiaScript::huoliCanglang(Ifire* DM);
	int TianxiaScript::huoliCanglangIn(Ifire* DM);

	int TianxiaScript::zidongwanchengBtn(Ifire* DM);

	int TianxiaScript::huoliChuangkouClose(Ifire* DM);
	int TianxiaScript::mitanComplete(Ifire* DM, long pX, long pY);

	int TianxiaScript::tongguanJiangli(Ifire* DM);
	int TianxiaScript::beibaoClose(Ifire* DM);

	int TianxiaScript::qiehuanJuese(Ifire* DM);
	int TianxiaScript::findShezhiWnd(Ifire* DM);

	int TianxiaScript::fubenJingcheng(Ifire* DM);
	int TianxiaScript::chongxuanJueseBtn(Ifire* DM);
	int TianxiaScript::zhuxianZhang(Ifire* DM);
	int TianxiaScript::jiahuWndClose(Ifire* DM);

	int TianxiaScript::jingjiPipeiIng(Ifire* DM);
	int TianxiaScript::findKaichangPugong(Ifire* DM);
	int TianxiaScript::findZhankaiBtn(Ifire* DM);

	int TianxiaScript::chongxuanWindow(Ifire* DM);
	int TianxiaScript::findDengluBtn(Ifire* DM);
	int TianxiaScript::clickDengluBtn(Ifire* DM);

	int TianxiaScript::zhuxianTianqiong(Ifire* DM);
	int TianxiaScript::findQiehuanBtn(Ifire* DM);
	int TianxiaScript::findOpenMap(Ifire* DM);

	int TianxiaScript::tuichuYanwuEx(Ifire* DM);

	int TianxiaScript::dazaoClose(Ifire* DM);
	int TianxiaScript::jiagaoTishiCancel(Ifire* DM);
	int TianxiaScript::jiagaoTishiConfirm(Ifire* DM);
	int TianxiaScript::zhenpinCancel(Ifire* DM);
	int TianxiaScript::zhenpinConfirm(Ifire* DM);

	int TianxiaScript::getCurrentHuoyue(Ifire* DM);

	int TianxiaScript::huoliHuangquan(Ifire* DM);
	int TianxiaScript::huoliHuangquanIn(Ifire* DM);
	int TianxiaScript::huoyueLingjiang(Ifire* DM);
	int TianxiaScript::findHuoliBtn(Ifire* DM);
	int TianxiaScript::renwuJiadian(Ifire* DM);
	int TianxiaScript::tuijianJiadianEx(Ifire* DM);

	int TianxiaScript::duiwuClose(Ifire* DM);

	int TianxiaScript::qiehuanJueseSubScript(Ifire* DM);
	int TianxiaScript::saomaClose(Ifire* DM);
	int TianxiaScript::gongzhanClose(Ifire* DM);

	int TianxiaScript::qingbaoSub4Junzi(Ifire* DM);
	int TianxiaScript::qingbaoSub4Yuezuan(Ifire* DM);

	int TianxiaScript::wugeBaoguo(Ifire* DM);

	int TianxiaScript::huoliXiaoyao(Ifire* DM);
	int TianxiaScript::huoliXiaoyaoIn(Ifire* DM);

	int TianxiaScript::lingFuliScript(Ifire* DM);
	int TianxiaScript::findFuliWnd(Ifire* DM);
	int TianxiaScript::fuliClose(Ifire* DM);
	int TianxiaScript::meiriQiandao(Ifire* DM);
	int TianxiaScript::shengjiLibao(Ifire* DM);
	int TianxiaScript::libaoLingquBtn(Ifire* DM);
	int TianxiaScript::qingbaoSub4ZhuangbeiLibao(Ifire* DM);

	int TianxiaScript::shangtongClose(Ifire* DM);

	int TianxiaScript::getMyHuoli(Ifire* DM);
	int TianxiaScript::checkBaoguoMan(Ifire* DM);
	int TianxiaScript::findBaoguoMan(Ifire* DM);

	int TianxiaScript::findJinengWnd(Ifire* DM);
	int TianxiaScript::updateSkill(Ifire* DM);
	int TianxiaScript::quanbuShengjiBtn(Ifire* DM);
	int TianxiaScript::closeJinengWnd(Ifire* DM);

	int TianxiaScript::findYoujianWnd(Ifire* DM);
	int TianxiaScript::closeYoujianWnd(Ifire* DM);
	int TianxiaScript::lingquYoujian(Ifire* DM);
	int TianxiaScript::youjianLingquBtn(Ifire* DM);

	int TianxiaScript::findXiaoxiWnd(Ifire* DM);
	int TianxiaScript::closeXiaoxiWnd(Ifire* DM);
	int TianxiaScript::getCurrentJunzi(Ifire* DM);

	int TianxiaScript::jinhuanJun(Ifire* DM);
	int TianxiaScript::findShangchengWnd(Ifire* DM);
	int TianxiaScript::closeShangchengWnd(Ifire* DM);

	int TianxiaScript::jhjGaoshu(Ifire* DM);
	int TianxiaScript::jhjLeizuan(Ifire* DM);
	int TianxiaScript::jhjXixinshi(Ifire* DM);
	
	int TianxiaScript::shangchengGoumai(Ifire* DM);
	int TianxiaScript::yuanbaoBuzu(Ifire* DM);
	int TianxiaScript::duihuanJunziWnd(Ifire* DM);
	int TianxiaScript::findZhenbaoJinbi(Ifire* DM, long pX, long pY);

	int TianxiaScript::qingbaoSub4Xumingdan(Ifire* DM);
	int TianxiaScript::qingbaoSub4QuandeKuizeng(Ifire* DM);
	int TianxiaScript::qingbaoSub4ShimingLibao(Ifire* DM);

	int TianxiaScript::qingbaoSub4Huaxuedan(Ifire* DM);
	int TianxiaScript::qingbaoSub4Wuxingshi(Ifire* DM);
	int TianxiaScript::qingbaoSub4WXP(Ifire* DM);
	
	int TianxiaScript::qiandaoChoujiang(Ifire* DM);
	int TianxiaScript::yuandiFuhuoBtn(Ifire* DM);
	int TianxiaScript::cuncangScript(Ifire* DM);
	int TianxiaScript::cuncangSubScript(Ifire* DM);

	int TianxiaScript::leftCuncang(Ifire* DM);
	int TianxiaScript::rightCuncang(Ifire* DM);
	int TianxiaScript::cuncang4Juexingdan(Ifire* DM);
	int TianxiaScript::cuncang4Fangcun(Ifire* DM);

	int TianxiaScript::qingbaoSub4Huilingdan(Ifire* DM);

	int TianxiaScript::findYanwushi(Ifire* DM);
	int TianxiaScript::tuichuYanwuShi(Ifire* DM);

	int TianxiaScript::quanshenXiuli(Ifire* DM);

	int TianxiaScript::mijingLingjiang(Ifire* DM);
	int TianxiaScript::mijingLingjiangBtn(Ifire* DM);

	int TianxiaScript::zhaixingLou(Ifire* DM);
	int TianxiaScript::xiuliSubScript(Ifire* DM);
	int TianxiaScript::quanshenXiuliBtn(Ifire* DM, long pX, long pY);

	int TianxiaScript::jiahuClose(Ifire* DM);

	int TianxiaScript::mitanShishi(Ifire* DM);
	int TianxiaScript::qingbaoSub4DuizhangLibao(Ifire* DM);

	int TianxiaScript::qingbaoSub4QifuTiadeng(Ifire* DM);

	int TianxiaScript::getSaohuoJunzi(Ifire* DM);
	int TianxiaScript::saoJishou(Ifire* DM);
	int TianxiaScript::findJishouWnd(Ifire* DM);
	bool TianxiaScript::getIsPaued();
	int TianxiaScript::getSaohuoPrice(Ifire* DM);
	
	int TianxiaScript::getWindowIsExist(Ifire* DM);
	int TianxiaScript::yanWuIng(Ifire* DM);

	int TianxiaScript::shangchengClose(Ifire* DM);
	int TianxiaScript::xiangshiComplete(Ifire* DM, long pX, long pY);
	int TianxiaScript::findChangguiInZhuxian(Ifire* DM);
	
	int TianxiaScript::generalClose(Ifire* DM);

	int TianxiaScript::zhuxianZhiyin(Ifire* DM, long pY);
	int TianxiaScript::tongxinhuanpei(Ifire* DM);

	int TianxiaScript::kaMijing(Ifire* DM);
	int TianxiaScript::shimenZhandou(Ifire* DM);
	int TianxiaScript::querenQiangzhi(Ifire* DM);

	Ifire* TianxiaScript::initDM();

	int TianxiaScript::youshangTuifuben(Ifire* DM);

	int TianxiaScript::chongwuShouming(Ifire* DM);
	int TianxiaScript::findPeiyangWnd(Ifire* DM);
	int TianxiaScript::findShimen(Ifire* DM);

	int TianxiaScript::shimenEx(Ifire* DM);
	int TianxiaScript::richangBai(Ifire* DM);

	int TianxiaScript::wuxingpanEx(Ifire* DM);
	int TianxiaScript::findWuxingpan(Ifire* DM);

	int TianxiaScript::kuaimaEx2(Ifire* DM);
	int TianxiaScript::findKuaima(Ifire* DM);

	int TianxiaScript::duihuanjinbiWnd(Ifire* DM);
	int TianxiaScript::shimenConfirmCircle(Ifire* DM);

	int TianxiaScript::getSellPrice(Ifire* DM);
	int TianxiaScript::yuandiFuhuoEx(Ifire* DM);

	int TianxiaScript::getIsDead(Ifire* DM);
	int TianxiaScript::dangqianFuhuo(Ifire* DM);
	int TianxiaScript::bangdingFuhuo(Ifire* DM);

	int TianxiaScript::shangjia(Ifire* DM);
	int TianxiaScript::sellClose(Ifire* DM);
	int TianxiaScript::getSellingPrice(Ifire* DM);
	int TianxiaScript::shangjiaSubScript(Ifire* DM);

	int TianxiaScript::shangjiaChenggong(Ifire* DM);
	int TianxiaScript::saoJishouSelecter(Ifire* DM, int number);

	int TianxiaScript::digitClicker(Ifire* DM, int digit);
	int TianxiaScript::saoSubScript(Ifire* DM);

	int TianxiaScript::xiaofeiQueren(Ifire* DM);
	int TianxiaScript::getSaohuoPriceEx(Ifire* DM);
	int TianxiaScript::saohuoPointSelector(Ifire* DM, int point);

	int TianxiaScript::mapSearchWCMT(Ifire* DM);
	int TianxiaScript::findMitanCaozuo(Ifire* DM);
	int TianxiaScript::findWangchaoMitanCap(Ifire* DM);

	int TianxiaScript::chuangjianDuiwu(Ifire* DM);
	int TianxiaScript::jianduiBtn(Ifire* DM);

	int TianxiaScript::wangchaoMitanCap(Ifire* DM);
	int TianxiaScript::mapSearchWCMT2(Ifire* DM);

	int TianxiaScript::isInMitan(Ifire* DM);

	int TianxiaScript::xiajia(Ifire* DM);
	int TianxiaScript::jishouQuhui(Ifire* DM);
	int TianxiaScript::cuncang4Qilin(Ifire* DM);
	int TianxiaScript::cuncang4JinJiaoyi(Ifire* DM);
	int TianxiaScript::qingbaoSub4Hecheng(Ifire* DM);


	int TianxiaScript::hechenClose(Ifire* DM);
	int TianxiaScript::kaweiMY(Ifire* DM);
	int TianxiaScript::kaweiMYSub(Ifire* DM);

	int TianxiaScript::xiajiaClose(Ifire* DM);
	int TianxiaScript::findTanweiFei(Ifire* DM);

	int TianxiaScript::huoyueCheck(Ifire* DM);

	int TianxiaScript::tanweiClose(Ifire* DM);

	int TianxiaScript::findJiandingDi(Ifire* DM);

	int TianxiaScript::xiajiaBtn(Ifire* DM);
	int TianxiaScript::findShoujiaItem(Ifire* DM);

	int TianxiaScript::findTuiduiBtn(Ifire* DM);

	int TianxiaScript::timerChecker();
	int TianxiaScript::findDuiwuWnd(Ifire* DM);
	int TianxiaScript::findMitanTarget(Ifire* DM);

	int TianxiaScript::mitanNotCap(Ifire* DM);
	int TianxiaScript::isInJiuli(Ifire* DM);
	int TianxiaScript::findJianmu(Ifire* DM);

	int TianxiaScript::getCurrentLevel(Ifire* DM);
	int TianxiaScript::findLevelLabel(Ifire* DM);
	int TianxiaScript::getLevel(Ifire* DM);

	int TianxiaScript::hideTheOthers(Ifire* DM);
	int TianxiaScript::menpaiBiWuBTN(Ifire* DM);
	int TianxiaScript::biwuCompleted(Ifire* DM);
	int TianxiaScript::menpaiWndClose(Ifire* DM);
	int TianxiaScript::quxiaoClose(Ifire* DM);

	int TianxiaScript::qingbaoTaozhuang(Ifire* DM);
	int TianxiaScript::findNewCunc(Ifire* DM);
	int TianxiaScript::findNewCuncSubScript(Ifire* DM);
	int TianxiaScript::isCangkuMan(Ifire* DM);
	int TianxiaScript::findQuhuiBaoguoBtn(Ifire* DM);
	int TianxiaScript::cuncSelector(Ifire* DM, int cuncIndex);
	int TianxiaScript::JiesuoCangku(Ifire* DM);

	int TianxiaScript::cuncangSub4WXP(Ifire* DM);
	int TianxiaScript::huoliHudie(Ifire* DM);
	int TianxiaScript::yuandiFuhuoPic(Ifire* DM);

	int TianxiaScript::juediQiusheng(Ifire* DM);
	int TianxiaScript::findJuediQiusheng(Ifire* DM);
	int TianxiaScript::juediQiushengSubScript(Ifire* DM);

	int TianxiaScript::danrenPaiduiBTN(Ifire* DM);
	int TianxiaScript::juediConfirm(Ifire* DM);
	int TianxiaScript::juediClose(Ifire* DM);
	int TianxiaScript::juediEnd(Ifire* DM);

	int TianxiaScript::passConfirm(Ifire* DM);
	int TianxiaScript::clickSysIcon(Ifire* DM);

	int TianxiaScript::wansheng(Ifire* DM);
	int TianxiaScript::querenHuafei(Ifire* DM);
	int TianxiaScript::wanshengBtn(Ifire* DM);
	int TianxiaScript::findWanshengClose(Ifire* DM);

	int TianxiaScript::guagua(Ifire* DM);
	int TianxiaScript::zhaigua(Ifire* DM);
	int TianxiaScript::mapSearchGuagua(Ifire* DM);

	int TianxiaScript::tuoliKadian(Ifire* DM);

	int TianxiaScript::cuncangSub4Junzi(Ifire* DM);

	int TianxiaScript::closeShezhiWnd(Ifire* DM);

	int TianxiaScript::cuncangSub4Yuezuan(Ifire* DM);
	int TianxiaScript::cuncangSub4Jinbi(Ifire* DM);
	int TianxiaScript::cuncangSub4Rizuan(Ifire* DM);
	int TianxiaScript::cuncangSub4Wuxingshi(Ifire* DM);
	int TianxiaScript::cuncangSub4Liuyaoshi(Ifire* DM);
	int TianxiaScript::cuncangSub4Dahuandan(Ifire* DM);

	int TianxiaScript::zhaoShifu(Ifire* DM);
	int TianxiaScript::reload(Ifire* DM);
	int TianxiaScript::reloadSubScript(Ifire* DM);
	int TianxiaScript::reloadWindow(Ifire* DM);
	int TianxiaScript::clickDengluNormal(Ifire* DM);

	int TianxiaScript::findWutongMap(Ifire* DM);
	int TianxiaScript::xieliFuben(Ifire* DM);
	int TianxiaScript::xieliFubenJindu(Ifire* DM);

	int TianxiaScript::mitanCapMode0(Ifire* DM);
	int TianxiaScript::mitanCapMode1(Ifire* DM);

	int TianxiaScript::findMapShili(Ifire* DM);
	int TianxiaScript::findCharaChoose(Ifire* DM);

	int TianxiaScript::characterChooseSubScript(Ifire* DM);
	int TianxiaScript::closeUpdate(Ifire* DM);

	int TianxiaScript::findQiCai(Ifire* DM);
	int TianxiaScript::shiliClose(Ifire* DM);
	int TianxiaScript::cuncangSub4JieriBaoxiang(Ifire* DM);
	int TianxiaScript::chongfanClose(Ifire* DM);
	int TianxiaScript::findCangkuLihe(Ifire* DM);
	int TianxiaScript::quhuiBaoguo(Ifire* DM);
	int TianxiaScript::dongjieQueding(Ifire* DM);
	int TianxiaScript::qingbaoSub4Lihe(Ifire* DM);
	int TianxiaScript::tianxiaQianzhuang(Ifire* DM);

	int TianxiaScript::findCangkuJunzi(Ifire* DM);
	int TianxiaScript::cuncangSub4BiwuJiajiang(Ifire* DM);

	int TianxiaScript::jiangchiLingjiang(Ifire* DM);

	int TianxiaScript::updateSkillNormal(Ifire* DM);
	int TianxiaScript::renwuJiadianNormal(Ifire* DM);

	int TianxiaScript::tuichuFubenBTNEx(Ifire* DM);
	int TianxiaScript::baoxiangLingqu(Ifire* DM);

	int TianxiaScript::ChuangShiliWnd(Ifire* DM);
	int TianxiaScript::findYunshiCloseBtn(Ifire* DM);
	int TianxiaScript::getYunsPoint(Ifire* DM);
	int TianxiaScript::clickYunsAllPoint(Ifire* DM);
	int TianxiaScript::closeQiehuanBtn(Ifire* DM);

	int TianxiaScript::clickYunshiCloseBtn(Ifire* DM);
	int TianxiaScript::find12Chongzhifanli(Ifire* DM);

	int TianxiaScript::tongjiClose(Ifire* DM);
	int TianxiaScript::findBattery(Ifire* DM);

	int TianxiaScript::yunshiScript(Ifire* DM, long pX, long pY);
	int TianxiaScript::findCishubuxian(Ifire* DM, long pX, long pY);

	int TianxiaScript::zhuxianTuibenCancel(Ifire* DM);
	int TianxiaScript::pindaoClose(Ifire* DM);

	int TianxiaScript::kaifuLibao(Ifire* DM);

	int TianxiaScript::newsClose(Ifire* DM);
	int TianxiaScript::tudibaoMing(Ifire* DM);
	int TianxiaScript::jishouGoumaiBtn(Ifire* DM);
	int TianxiaScript::jishouGoumaiShuliang(Ifire* DM);

	int TianxiaScript::junziBuzu(Ifire* DM);

	int TianxiaScript::jieriClose(Ifire* DM);
	int TianxiaScript::lapiaoClose(Ifire* DM);

	int TianxiaScript::clickChongmingBtn(Ifire* DM);
	int TianxiaScript::xueqiu(Ifire* DM);

	int TianxiaScript::cuncangSub4Xueqiu(Ifire* DM);
	int TianxiaScript::findCangkuXueqiu(Ifire* DM);

	int TianxiaScript::zengsong(Ifire* DM);
	int TianxiaScript::sendStr(QString str);
	int TianxiaScript::sendString(QString str);


	int TianxiaScript::findBaobaoXueqiu(Ifire* DM);
	int TianxiaScript::clickZengsongBtn(Ifire* DM);
	int TianxiaScript::clickZhufuBtn(Ifire* DM);


	int TianxiaScript::forceExitYanwu(Ifire* DM);
	int TianxiaScript::findLeftCuncang(Ifire* DM);
	int TianxiaScript::findRightCuncang(Ifire* DM);
	int TianxiaScript::qingbaoSub4Canhun(Ifire* DM);

	int TianxiaScript::findQingbaoGengduo(Ifire* DM);
	int TianxiaScript::findQingbaoShiyong(Ifire* DM);
	int TianxiaScript::findQuxiaoBtn(Ifire* DM);
	int TianxiaScript::qingbaoSub4Xueqiu(Ifire* DM);

	int TianxiaScript::getCharacterID(Ifire* DM);
	int TianxiaScript::forceExitYanwu2(Ifire* DM);
	int TianxiaScript::clickTuibenBtn(Ifire* DM);

	int TianxiaScript::findShiliWnd(Ifire* DM);
	int TianxiaScript::clickShenqingShiliBtn(Ifire* DM);
	int TianxiaScript::theEmbededScript(Ifire* DM);
	int TianxiaScript::huoliWeiji(Ifire* DM);
	int TianxiaScript::huoliWeijiIn(Ifire* DM);

	int TianxiaScript::findXinxiWnd(Ifire* DM);
	int TianxiaScript::duiXuerenSubScript(Ifire* DM);
	int TianxiaScript::clickDuixueItem(Ifire* DM);
	int TianxiaScript::submitDuixueItem(Ifire* DM);
	int TianxiaScript::submitDuixueItemStep2(Ifire* DM);

	int TianxiaScript::submitWndClose(Ifire* DM);
	int TianxiaScript::clickHaoyouBtn(Ifire* DM);
	int TianxiaScript::qingbaoSub4LeftZhuangbei(Ifire* DM);
	int TianxiaScript::qingbaoSub4ZhuangbeiJJY(Ifire* DM);
	int TianxiaScript::haoyouWndClose(Ifire* DM);

	int TianxiaScript::findHaoyouWnd(Ifire* DM);
	int TianxiaScript::clickShenqingDuiwuBtn(Ifire* DM);
	int TianxiaScript::clickJieshouDuiwuBtn(Ifire* DM);

	int TianxiaScript::getCaptainIndex(int index);
	int TianxiaScript::subMitan(Ifire* DM);

	int TianxiaScript::findWangchaoMitanNoClick(Ifire* DM);
	int TianxiaScript::subMitanNoClick(Ifire* DM);
	int TianxiaScript::subSuoyaota(Ifire* DM);
	int TianxiaScript::findSuoyaoTa(Ifire* DM);
	int TianxiaScript::clickSuoyaota(Ifire* DM);

	int TianxiaScript::clickJinruSuoyaoBtn(Ifire* DM);
	int TianxiaScript::getCurrentJinbi(Ifire* DM);
	int TianxiaScript::kaiBaobao(Ifire* DM);
	int TianxiaScript::kaiBaobaoSubscript(Ifire* DM);
	int TianxiaScript::clickKaiqigezi(Ifire* DM);
	int TianxiaScript::kaibaoConfirm(Ifire* DM);

	int TianxiaScript::huoliJingji(Ifire* DM);
	int TianxiaScript::huoliJingjiIn(Ifire* DM);

	int TianxiaScript::clickGongzhanCloseBtn(Ifire* DM);
	int TianxiaScript::findJueseGaimingWnd(Ifire* DM);
	int TianxiaScript::fixNameBug(Ifire* DM);
	int TianxiaScript::clickChuanchengCloseBtn(Ifire* DM);
	int TianxiaScript::huoliWuxing(Ifire* DM);
	int TianxiaScript::huoliWuxingIn(Ifire* DM);
	int TianxiaScript::kuaiLvJiabianEx(Ifire* DM);
	int TianxiaScript::clickKuailvCenterPanel(Ifire* DM);

	int TianxiaScript::lvrenBaoxiangClose(Ifire* DM);
	int TianxiaScript::clickKuailvJianbian(Ifire* DM);
	int TianxiaScript::clickKuailvTitle(Ifire* DM);

	int TianxiaScript::findMapSearchBtn(Ifire* DM);
	int TianxiaScript::wuxingpanExY(Ifire* DM);

	int TianxiaScript::clickWuxingInPanel(Ifire* DM);
	int TianxiaScript::clickAcceptInPanel(Ifire* DM);
	int TianxiaScript::clickRunInPanel(Ifire* DM);

	int TianxiaScript::weima(Ifire* DM);
	int TianxiaScript::findLingshouWnd(Ifire* DM);
	int TianxiaScript::findWeishiWnd(Ifire* DM);
	int TianxiaScript::closeWeishiWnd(Ifire* DM);
	int TianxiaScript::clickQingbaoZLBtn(Ifire* DM);
	int TianxiaScript::ShizhuangCloseBtnClose(Ifire* DM);
	int TianxiaScript::submitLiuli(Ifire* DM);
	int TianxiaScript::clickLiuliItem(Ifire* DM);
	int TianxiaScript::submitLiuliItem(Ifire* DM);
	int TianxiaScript::menpaiBiwuSubScriptNew(Ifire* DM);
	int TianxiaScript::menpaiPanelBTN(Ifire* DM);
	int TianxiaScript::menpaiBiwuNew(Ifire* DM);
	int TianxiaScript::cuncang4TimeLimitedItem(Ifire* DM);

	int TianxiaScript::findBeibao(Ifire* DM);
	int TianxiaScript::qingbaoSub4ZhuangbeiLihe(Ifire* DM);
	int TianxiaScript::clickYouxiaZhuangbeiBtn(Ifire* DM);

	int TianxiaScript::clickFuyunCloseBtn(Ifire* DM);
	int TianxiaScript::clickJijinCloseBtn(Ifire* DM);

	int TianxiaScript::findPetSkill(Ifire* DM);

	int TianxiaScript::liuguangJunziEx(Ifire* DM);
	int TianxiaScript::findLiuguangJunzi(Ifire* DM);
	int TianxiaScript::clickJunziGaoji(Ifire* DM);
	int TianxiaScript::juediQiushengSubScriptEx(Ifire* DM);
	int TianxiaScript::clickDanrenpaiduiBtn(Ifire* DM);
	int TianxiaScript::findCaptchaPic(Ifire* DM, int &x, int &y);
	int TianxiaScript::moveScrollBtn(Ifire* DM, long pX);

	int TianxiaScript::findPipeiSuccess(Ifire* DM);
	int TianxiaScript::clickConfirmBtn(Ifire* DM);
	int TianxiaScript::clickJiutianBtn(Ifire* DM);
	int TianxiaScript::clickHuodongCloseBtn(Ifire* DM);
	int TianxiaScript::clickJiutianCansaiBtn(Ifire* DM);

	int TianxiaScript::findShoujiaTitle(Ifire* DM);
	int TianxiaScript::findChijiMap(Ifire* DM);
	int TianxiaScript::IsInJuedi(Ifire* DM);
	int TianxiaScript::clickKuaimaJianbian(Ifire* DM);

	int TianxiaScript::findCreateForcePanel(Ifire* DM);
	int TianxiaScript::closeCreateForcePanel(Ifire* DM);
	int TianxiaScript::getIsEquiped(Ifire* DM);
	int TianxiaScript::findDeadBlood(Ifire* DM);

	int TianxiaScript::IsInTianlao(Ifire* DM);
	int TianxiaScript::findTianyuanMap(Ifire* DM);

	int TianxiaScript::getIsDeadNew(Ifire* DM);
	int TianxiaScript::findDeathLine(Ifire* DM);
	int TianxiaScript::checkIsDead(Ifire* DM);
	int TianxiaScript::closeCombatRecordPanel(Ifire* DM);
	int TianxiaScript::closeLiuguangBelongingPanel(Ifire* DM);

	int TianxiaScript::clickJieriCloseBtn(Ifire* DM);
};



struct ScriptParam {
	long lHWND;
	QString config;
	int index;
	DWORD threadId;
	Ifire* DM;
};

