#pragma once

#include <QWidget>
#include <QFile>

#include "ui_MainWindow.h"
#include "wke.h"
#include "BridgeProfileWidget.h"
#include "callJsFunc.hpp"
#include "InitialInspectionWidget.h"
#include "InitialInspectionDao.h"

class MainWindow : public QWidget
{
	Q_OBJECT

signals:
	// to BridgeProfileWidget
	void send_bridgeType(const QString& typeStr);
	// to BridgeProfileWidget
	void send_bridge_info(
		const ADMID& amdid,
		const BTI& bti,
		const BSInfo& bsinfo,
		const BRD& brd,
		const BMAH& bmah,
		const MDR& mdr,
		const Other& other
	);
	// to InitialInspectionWidget
	void send_bridgeName_update(const QString& name);
	void send_bridgeName_new(const QString& name);

public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow() {}

	void showAmap();

	void on_newProfileBtn_clicked();
	void on_showProfileBtn_clicked();
	void on_showInitialInspectionBtn_clicked();

	void loadAllBridgeNames();

	void reloadBridgeNames();

	void on_bridgeNames_currentTextChanged(const QString& text);

private:
	wkeWebView webView{}; // miniblink container

private:
	Ui::MainWindowClass ui;
};
