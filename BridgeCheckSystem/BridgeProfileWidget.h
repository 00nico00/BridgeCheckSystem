#pragma once

#include <QWidget>
#include "ui_BridgeProfileWidget.h"

#include <optional>

#include "ADMID.h"
#include "ADMIDWidget.h"
#include "ADMIDDao.h"
#include "BTI.h"
#include "BTIWidget.h"
#include "BTIDao.h"
#include "BSInfo.h"
#include "BSInfoWidget.h"
#include "BSInfoDao.h"
#include "BRD.h"
#include "BRDWidget.h"
#include "BRDDao.h"
#include "BMAH.h"
#include "BMAHWidget.h"
#include "BMAHDao.h"
#include "MDR.h"
#include "MDRWidget.h"
#include "MDRDao.h"
#include "Other.h"
#include "OtherWidget.h"
#include "OtherDao.h"
#include "Logger.hpp"

class BridgeProfileWidget : public QWidget
{
	Q_OBJECT

signals:
	void send_type(ADMID::Type type);
	void send_ADMID_info(const ADMID& info);
	void send_BTI_info(const BTI& info);
	void send_BSInfo_info(const BSInfo& info);
	void send_BRD_info(const BRD& info);
	void send_BMAH_info(const BMAH& info);
	void send_MDR_info(const MDR& info);
	void send_Other_info(const Other& info);
	void trigger_reloadBridgeNames();

public:
	BridgeProfileWidget(const QString& mode, QWidget* parent = nullptr);
	~BridgeProfileWidget();

	void on_ADMIDBtn_clicked();
	void on_BTIBtn_clicked();
	void on_BSInfoBtn_clicked();
	void on_BRDBtn_clicked();
	void on_BMAHBtn_clicked();
	void on_MDRBtn_clicked();
	void on_OtherBtn_clicked();

public:
	// slots
	// from MainWindow
	void receive_bridgeType(const QString& typeStr);
	// from ADMIDWidget
	void receive_ADMID_Info(const ADMID& info);
	// from BTIWidget
	void receive_BTI_Info(const BTI& info);
	// from BSInfoWidget
	void receive_BSInfo_Info(const BSInfo& info);
	// from BRDWidget
	void receive_BRD_Info(const BRD& info);
	// from BMAHWidget
	void receive_BMAH_Info(const BMAH& info);
	// from MDRWidget
	void receive_MDR_Info(const MDR& info);
	// from OtherWidget
	void receive_Other_Info(const Other& info);
	// from MainWindow
	void receive_bridge_info(
		const ADMID& amdid,
		const BTI& bti,
		const BSInfo& bsinfo,
		const BRD& brd,
		const BMAH& bmah,
		const MDR& mdr,
		const Other& other
	);

public:
	void closeEvent(QCloseEvent* event);
	bool isInfoNotEmpty() const;
	bool isInfoEmpty() const;
	void clearInfo();

private:
	QString mode_;

	std::optional<ADMID::Type> type_ = std::nullopt;
	std::optional<ADMID> admid_ = std::nullopt;
	std::optional<BTI> bti_ = std::nullopt;
	std::optional<BSInfo> bsinfo_ = std::nullopt;
	std::optional<BRD> brd_ = std::nullopt;
	std::optional<BMAH> bmah_ = std::nullopt;
	std::optional<MDR> mdr_ = std::nullopt;
	std::optional<Other> other_ = std::nullopt;

private:
	Ui::BridgeProfileWidgetClass ui;
};
