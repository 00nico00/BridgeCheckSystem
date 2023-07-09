#include "BridgeProfileWidget.h"

BridgeProfileWidget::BridgeProfileWidget(const QString& mode, QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	// Set to delete this object when the window is closed
	setAttribute(Qt::WA_DeleteOnClose);

	mode_ = mode;
	if (mode_ == "update") {
		ui.saveBtn->setText("修改");
	}

	// connect
	connect(ui.ADMIDBtn, &QPushButton::clicked, this, &BridgeProfileWidget::on_ADMIDBtn_clicked);
	connect(ui.BTIBtn, &QPushButton::clicked, this, &BridgeProfileWidget::on_BTIBtn_clicked);
	connect(ui.BSInfoBtn, &QPushButton::clicked, this, &BridgeProfileWidget::on_BSInfoBtn_clicked);
	connect(ui.BRDBtn, &QPushButton::clicked, this, &BridgeProfileWidget::on_BRDBtn_clicked);
	connect(ui.BMAHBtn, &QPushButton::clicked, this, &BridgeProfileWidget::on_BMAHBtn_clicked);
	connect(ui.MDRBtn, &QPushButton::clicked, this, &BridgeProfileWidget::on_MDRBtn_clicked);
	connect(ui.OtherBtn, &QPushButton::clicked, this, &BridgeProfileWidget::on_OtherBtn_clicked);

	// delete
	connect(ui.deleteBtn, &QPushButton::clicked,
		[this] {
			auto id = (*admid_).getBridgeNumber();

			BTIDao::deleteBTI(id);
			BSInfoDao::deleteBSInfo(id);
			BRDDao::deleteBRD(id);
			BMAHDao::deleteBMAH(id);
			MDRDao::deleteMDR(id);
			OtherDao::deleteOther(id);
			ADMIDDao::deleteADMID(id);

			emit trigger_reloadBridgeNames();

			clearInfo();

			this->close();
		}
	);

	if (mode_ == "new") {
		connect(ui.saveBtn, &QPushButton::clicked,
			[this] {

				if (isInfoEmpty()) {
					QMessageBox::warning(this, "保存失败", "有未填入的数据项");
					return;
				}

				auto id = (*admid_).getBridgeNumber();

				ADMIDDao::insertADMID(admid_.value());
				BTIDao::insertBTI(id, bti_.value());
				BSInfoDao::insertBSInfo(id, bsinfo_.value());
				BRDDao::insertBRD(id, brd_.value());
				BMAHDao::insertBMAH(id, bmah_.value());
				MDRDao::insertMDR(id, mdr_.value());
				OtherDao::insertOther(id, other_.value());

				emit trigger_reloadBridgeNames();

				clearInfo();

				this->close();
			}
		);
	} else {
		connect(ui.saveBtn, &QPushButton::clicked,
			[this] {

				if (isInfoEmpty()) {
					QMessageBox::warning(this, "修改失败", "有未填入的数据项");
					return;
				}

				auto id = (*admid_).getBridgeNumber();

				ADMIDDao::updateADMID(id, admid_.value());
				BTIDao::updateBTI(id, bti_.value());
				BSInfoDao::updateBSInfo(id, bsinfo_.value());
				BRDDao::updateBRD(id, brd_.value());
				BMAHDao::updateBMAH(id, bmah_.value());
				MDRDao::updateMDR(id, mdr_.value());
				OtherDao::updateOther(id, other_.value());

				emit trigger_reloadBridgeNames();

				clearInfo();

				this->close();
			}
		);
	}

	connect(ui.exitBtn, &QPushButton::clicked, this, &BridgeProfileWidget::close);
}

BridgeProfileWidget::~BridgeProfileWidget()
{}

void BridgeProfileWidget::on_ADMIDBtn_clicked() {
	ADMIDWidget* admidWidget = new ADMIDWidget();
	admidWidget->setWindowModality(Qt::ApplicationModal);	// 模态窗口，阻塞一切窗口
	connect(this, &BridgeProfileWidget::send_type, admidWidget, &ADMIDWidget::receive_type);
	connect(admidWidget, &ADMIDWidget::send_ADMID_Info, this, &BridgeProfileWidget::receive_ADMID_Info); // 接收信息
	if (type_) {
		emit send_type(type_.value());
	} else {
		DEBUG("type stored no value");
	}

	// send info
	connect(this, &BridgeProfileWidget::send_ADMID_info, admidWidget, &ADMIDWidget::receive_ADMID_info);
	if (admid_) {
		emit send_ADMID_info(admid_.value());
	}

	admidWidget->show();
}

void BridgeProfileWidget::on_BTIBtn_clicked() {
	BTIWidget* btiWidget = new BTIWidget();
	btiWidget->setWindowModality(Qt::ApplicationModal);
	connect(btiWidget, &BTIWidget::send_BTI_Info, this, &BridgeProfileWidget::receive_BTI_Info);

	connect(this, &BridgeProfileWidget::send_BTI_info, btiWidget, &BTIWidget::receive_BTI_info);
	if (bti_) {
		emit send_BTI_info(bti_.value());
	}

	btiWidget->show();
}

void BridgeProfileWidget::on_BSInfoBtn_clicked() {
	BSInfoWidget* widget = new BSInfoWidget();
	widget->setWindowModality(Qt::ApplicationModal);
	connect(widget, &BSInfoWidget::send_BSInfo_Info, this, &BridgeProfileWidget::receive_BSInfo_Info);

	connect(this, &BridgeProfileWidget::send_BSInfo_info, widget, &BSInfoWidget::receive_BSInfo_info);
	if (bsinfo_) {
		emit send_BSInfo_info(bsinfo_.value());
	}

	widget->show();
}

void BridgeProfileWidget::on_BRDBtn_clicked() {
	BRDWidget* widget = new BRDWidget();
	widget->setWindowModality(Qt::ApplicationModal);
	connect(widget, &BRDWidget::send_BRD_Info, this, &BridgeProfileWidget::receive_BRD_Info);

	connect(this, &BridgeProfileWidget::send_BRD_info, widget, &BRDWidget::receive_BRD_info);
	if (brd_) {
		emit send_BRD_info(brd_.value());
	}

	widget->show();
}

void BridgeProfileWidget::on_BMAHBtn_clicked() {
	BMAHWidget* widget = new BMAHWidget();
	widget->setWindowModality(Qt::ApplicationModal);
	connect(widget, &BMAHWidget::send_BMAH_Info, this, &BridgeProfileWidget::receive_BMAH_Info);

	connect(this, &BridgeProfileWidget::send_BMAH_info, widget, &BMAHWidget::receive_BMAH_info);
	if (bmah_) {
		emit send_BMAH_info(bmah_.value());
	}

	widget->show();
}

void BridgeProfileWidget::on_MDRBtn_clicked() {
	MDRWidget* widget = new MDRWidget();
	widget->setWindowModality(Qt::ApplicationModal);
	connect(widget, &MDRWidget::send_MDR_Info, this, &BridgeProfileWidget::receive_MDR_Info);

	connect(this, &BridgeProfileWidget::send_MDR_info, widget, &MDRWidget::receive_MDR_info);
	if (mdr_) {
		emit send_MDR_info(mdr_.value());
	}

	widget->show();
}

void BridgeProfileWidget::on_OtherBtn_clicked() {
	OtherWidget* widget = new OtherWidget();
	widget->setWindowModality(Qt::ApplicationModal);
	connect(widget, &OtherWidget::send_Other_Info, this, &BridgeProfileWidget::receive_Other_Info);

	connect(this, &BridgeProfileWidget::send_Other_info, widget, &OtherWidget::receive_Other_info);
	if (other_) {
		emit send_Other_info(other_.value());
	}

	widget->show();
}

void BridgeProfileWidget::receive_bridgeType(const QString& typeStr) {
	type_ = std::make_optional(ADMID::strToType[typeStr]);
}

void BridgeProfileWidget::receive_ADMID_Info(const ADMID& info) {
	admid_ = std::make_optional(info);
}

void BridgeProfileWidget::receive_BTI_Info(const BTI& info) {
	bti_ = std::make_optional(info);
}

void BridgeProfileWidget::receive_BSInfo_Info(const BSInfo& info) {
	bsinfo_ = std::make_optional(info);
}

void BridgeProfileWidget::receive_BRD_Info(const BRD& info) {
	brd_ = std::make_optional(info);
}

void BridgeProfileWidget::receive_BMAH_Info(const BMAH& info) {
	bmah_ = std::make_optional(info);
}

void BridgeProfileWidget::receive_MDR_Info(const MDR& info) {
	mdr_ = std::make_optional(info);
}

void BridgeProfileWidget::receive_Other_Info(const Other& info) {
	other_ = std::make_optional(info);
}

bool BridgeProfileWidget::isInfoNotEmpty() const {
	return admid_ || bti_ || bsinfo_ || brd_ || bmah_ || mdr_ || other_;
}

bool BridgeProfileWidget::isInfoEmpty() const {
	return !admid_ || !bti_ || !bsinfo_ || !brd_ || !bmah_ || !mdr_ || !other_;
}

void BridgeProfileWidget::clearInfo() {
	admid_ = std::nullopt;
	bti_ = std::nullopt;
	bsinfo_ = std::nullopt;
	brd_ = std::nullopt;
	bmah_ = std::nullopt;
	mdr_ = std::nullopt;
	other_ = std::nullopt;
}

void BridgeProfileWidget::closeEvent(QCloseEvent* event) {
	if (isInfoNotEmpty()) {
		auto result = QMessageBox::question(this, "确认", "有未提交的表单，确定要退出吗？", QMessageBox::Yes | QMessageBox::Cancel);
		if (result == QMessageBox::Yes) {
			event->accept();
		} else {
			event->ignore();
		}
	}
}

void BridgeProfileWidget::receive_bridge_info(
	const ADMID& amdid,
	const BTI& bti,
	const BSInfo& bsinfo,
	const BRD& brd,
	const BMAH& bmah,
	const MDR& mdr,
	const Other& other
) {
	admid_ = amdid;
	bti_ = bti;
	bsinfo_ = bsinfo;
	brd_ = brd;
	bmah_ = bmah;
	mdr_ = mdr;
	other_ = other;
}