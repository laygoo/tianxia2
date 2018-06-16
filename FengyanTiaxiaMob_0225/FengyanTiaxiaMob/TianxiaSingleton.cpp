#include "TianxiaSingleton.h"



TianxiaSingleton::TianxiaSingleton()
{
	this->isAutoRestart = false;
	this->MAX_ALLOWED = 0;
}


TianxiaSingleton::~TianxiaSingleton()
{
}

TianxiaSingleton* TianxiaSingleton::instance;
TianxiaSingleton* TianxiaSingleton::getInstance() {
	if (instance == NULL) {
		instance = new TianxiaSingleton();
	}
	return instance;
}
