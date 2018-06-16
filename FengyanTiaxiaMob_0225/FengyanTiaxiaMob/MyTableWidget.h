#pragma once

#include <QTableWidget>

class MyTableWidget : public QTableWidget
{
	Q_OBJECT

public:
	MyTableWidget(QWidget *parent);
	~MyTableWidget();
};
