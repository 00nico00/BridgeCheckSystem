#pragma once

#include <QWidget>
#include "ui_BMAHWidget.h"

#include <QValidator>
#include <QRegularExpressionValidator>
#include <QCloseEvent>
#include <QMessageBox>

#include "BMAH.h"

class BMAHWidget : public QWidget
{
	Q_OBJECT

signals:
	// to BridgeProfileWidget
	void send_BMAH_Info(const BMAH& info);

public:
	BMAHWidget(QWidget* parent = nullptr);
	~BMAHWidget();

	bool isEditNotEmpty();

	bool isEditsEmpty();

	void closeEvent(QCloseEvent* event);

	void clearEdits();

	void receive_BMAH_info(const BMAH& info);

private:
	Ui::BMAHWidgetClass ui;
};
