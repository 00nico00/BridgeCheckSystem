#include "BSInfoWidget.h"

BSInfoWidget::BSInfoWidget(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	// Set to delete this object when the window is closed
	setAttribute(Qt::WA_DeleteOnClose);

	connect(ui.saveBtn, &QPushButton::clicked,
		[this] {
			if (isEditsEmpty()) {
				QMessageBox::warning(this, "保存失败", "有未填入的数据项");
				return;
			}

			emit send_BSInfo_Info(BSInfo(
				ui.mainGirderEdit->text().trimmed(),
				ui.mainArchRibEdit->text().trimmed(),
				ui.bridgeTowerEdit->text().trimmed(),
				ui.structureAboveArchEdit->text().trimmed(),
				ui.mainCableEdit->text().trimmed(),
				ui.bridgeSurfaceCoatingEdit->text().trimmed(),
				ui.sidewalkEdit->text().trimmed(),
				ui.lightingEdit->text().trimmed(),
				ui.coneSlopeEdit->text().trimmed(),
				ui.wingWallEdit->text().trimmed(),
				ui.foundationEdit->text().trimmed(),
				ui.bearingEdit->text().trimmed(),
				ui.crashBarrierEdit->text().trimmed(),
				ui.beaconEdit->text().trimmed()
			));

			clearEdits();

			this->close();
		}
	);

	connect(ui.exitBtn, &QPushButton::clicked, this, &BSInfoWidget::close);

}

BSInfoWidget::~BSInfoWidget()
{}


bool BSInfoWidget::isEditNotEmpty() {
	auto edits = findChildren<QLineEdit*>();
	for (auto& edit : edits) {
		if (!edit->text().isEmpty()) {
			return true;
		}
	}

	return false;
}

bool BSInfoWidget::isEditsEmpty() {
	auto edits = findChildren<QLineEdit*>();
	for (auto& edit : edits) {
		if (edit->text().isEmpty()) {
			return true;
		}
	}

	return false;
}

void BSInfoWidget::closeEvent(QCloseEvent* event) {
	if (isEditNotEmpty()) {
		auto result = QMessageBox::question(this, "确认", "有未提交的表单，确定要退出吗？", QMessageBox::Yes | QMessageBox::Cancel);
		if (result == QMessageBox::Yes) {
			event->accept();
		} else {
			event->ignore();
		}
	}
}

void BSInfoWidget::clearEdits() {
	auto edits = findChildren<QLineEdit*>();
	for (auto& edit : edits) {
		edit->clear();
	}
}

void BSInfoWidget::receive_BSInfo_info(const BSInfo& info) {
	ui.mainGirderEdit->setText(info.getMainGirder());
	ui.mainArchRibEdit->setText(info.getMainArchRib());
	ui.bridgeTowerEdit->setText(info.getBridgeTower());
	ui.structureAboveArchEdit->setText(info.getStructureAboveArch());
	ui.mainCableEdit->setText(info.getMainCable());
	ui.bridgeSurfaceCoatingEdit->setText(info.getBridgeSurfaceCoating());
	ui.sidewalkEdit->setText(info.getSidewalk());
	ui.lightingEdit->setText(info.getLighting());
	ui.coneSlopeEdit->setText(info.getConeSlope());
	ui.wingWallEdit->setText(info.getWingWall());
	ui.foundationEdit->setText(info.getFoundation());
	ui.bearingEdit->setText(info.getBearing());
	ui.crashBarrierEdit->setText(info.getCrashBarrier());
	ui.beaconEdit->setText(info.getBeacon());
}