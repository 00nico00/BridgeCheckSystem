#pragma once

#include <QWidget>
#include "ui_BSInfoWidget.h"

#include <QValidator>
#include <QRegularExpressionValidator>
#include <QCloseEvent>
#include <QMessageBox>

#include "BSInfo.h"

class BSInfoWidget : public QWidget
{
	Q_OBJECT

signals:
	// to BridgeProfileWidget
	void send_BSInfo_Info(const BSInfo& info);

public:
	BSInfoWidget(QWidget* parent = nullptr);
	~BSInfoWidget();

	bool isEditNotEmpty();

	bool isEditsEmpty();

	void closeEvent(QCloseEvent* event);

	void clearEdits();

	void receive_BSInfo_info(const BSInfo& info);

private:
	Ui::BSInfoWidgetClass ui;
};
