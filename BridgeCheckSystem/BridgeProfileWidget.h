#pragma once

#include <QWidget>
#include "ui_BridgeProfileWidget.h"

#include <optional>

#include "ADMID.h"
#include "ADMIDWidget.h"
#include "Logger.hpp"

class BridgeProfileWidget : public QWidget
{
	Q_OBJECT

signals:
	void send_type(ADMID::Type type);

public:
	BridgeProfileWidget(QWidget* parent = nullptr);
	~BridgeProfileWidget();

	void on_ADMIDBtn_clicked();
	void on_BTSBtn_clicked();
	void on_BSInfoBtn_clicked();
	void on_BRDBtn_clicked();
	void on_BMAHBtn_clicked();
	void on_MDRBtn_clicked();
	void on_OtherBtn_clicked();

	void receive_bridgeType(const QString& typeStr);

private:
	std::optional<ADMID::Type> type = std::nullopt;
	std::optional<ADMID> admid = std::nullopt;

private:
	Ui::BridgeProfileWidgetClass ui;
};
