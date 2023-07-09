#include "InitialInspectionWidget.h"

InitialInspectionWidget::InitialInspectionWidget(const QString& mode, QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	setAttribute(Qt::WA_DeleteOnClose);

	auto matchNumber = new QRegularExpressionValidator(QRegularExpression("^[+-]?\\d+(\\.\\d+)?$"), this);
	ui.staticLoadResultEdit->setValidator(matchNumber);
	ui.dynamicLoadResultEdit->setValidator(matchNumber);

	if (mode == "new") {
		connect(ui.saveBtn, &QPushButton::clicked,
			[this] {
				if (isEditsEmpty()) {
					QMessageBox::warning(this, "保存失败", "有未填入的数据项");
					return;
				}

				auto bridgeNumber = ADMIDDao::queryBridgeNumber(ui.bridgeNameEdit->text());

				InitialInspectionDao::insertInitialInspection(
					bridgeNumber.value(),
					InitialInspection(
						ui.bridgeRepairEdit->text(),
						ui.inspectionDateEdit->dateTime(),
						ui.staticLoadResultEdit->text().toFloat(),
						ui.dynamicLoadResultEdit->text().toFloat(),
						ui.recorderEdit->text(),
						ui.inspectionOrganizationEdit->text()
					)
				);

				clearEdits();

				this->close();
			}
		);
	} else if (mode == "update") {
		connect(ui.saveBtn, &QPushButton::clicked,
			[this] {
				if (isEditsEmpty()) {
					QMessageBox::warning(this, "保存失败", "有未填入的数据项");
					return;
				}

				auto bridgeNumber = ADMIDDao::queryBridgeNumber(ui.bridgeNameEdit->text());

				InitialInspectionDao::updateInitialInspection(
					bridgeNumber.value(),
					InitialInspection(
						ui.bridgeRepairEdit->text(),
						ui.inspectionDateEdit->dateTime(),
						ui.staticLoadResultEdit->text().toFloat(),
						ui.dynamicLoadResultEdit->text().toFloat(),
						ui.recorderEdit->text(),
						ui.inspectionOrganizationEdit->text()
					)
				);

				clearEdits();

				this->close();
			}
		);
	}


	connect(ui.exitBtn, &QPushButton::clicked, this, &InitialInspectionWidget::close);
}

InitialInspectionWidget::~InitialInspectionWidget()
{}

void InitialInspectionWidget::receive_bridgeName_udpate(const QString& name) {
	auto bridgeNumber = ADMIDDao::queryBridgeNumber(name);
	auto bridgeEngineer = OtherDao::queryBridgeEngineer(bridgeNumber.value());
	auto initInspec = InitialInspectionDao::queryInitialInspection(bridgeNumber.value());

	ui.bridgeNameEdit->setText(name);
	ui.bridgeRepairEdit->setText(initInspec.value().getBridgeRepair());
	ui.inspectionDateEdit->setDateTime(initInspec.value().getInspectionDate());
	ui.staticLoadResultEdit->setText(QString::number(initInspec.value().getStaticLoadResult(), 'f', 2));
	ui.dynamicLoadResultEdit->setText(QString::number(initInspec.value().getDynamicLoadResult(), 'f', 2));
	ui.bridgeEngineerEdit->setText(bridgeEngineer.value());
	ui.recorderEdit->setText(initInspec.value().getRecorder());
	ui.inspectionOrganizationEdit->setText(initInspec.value().getInspectionOrganization());
}

void InitialInspectionWidget::receive_bridgeName_new(const QString& name) {
	auto bridgeNumber = ADMIDDao::queryBridgeNumber(name);
	auto bridgeEngineer = OtherDao::queryBridgeEngineer(bridgeNumber.value());

	ui.bridgeNameEdit->setText(name);
	ui.bridgeEngineerEdit->setText(bridgeEngineer.value());
}

bool InitialInspectionWidget::isEditNotEmpty() const {
	return !ui.bridgeRepairEdit->text().isEmpty() ||
		!ui.staticLoadResultEdit->text().isEmpty() ||
		!ui.dynamicLoadResultEdit->text().isEmpty() ||
		!ui.recorderEdit->text().isEmpty() ||
		!ui.inspectionOrganizationEdit->text().isEmpty();
}

bool InitialInspectionWidget::isEditsEmpty() const {
	return ui.bridgeRepairEdit->text().isEmpty() ||
		ui.staticLoadResultEdit->text().isEmpty() ||
		ui.dynamicLoadResultEdit->text().isEmpty() ||
		ui.recorderEdit->text().isEmpty() ||
		ui.inspectionOrganizationEdit->text().isEmpty();
}

void InitialInspectionWidget::closeEvent(QCloseEvent* event) {
	if (isEditNotEmpty()) {
		auto result = QMessageBox::question(this, "确认", "有未提交的表单，确定要退出吗？", QMessageBox::Yes | QMessageBox::Cancel);
		if (result == QMessageBox::Yes) {
			event->accept();
		} else {
			event->ignore();
		}
	}
}

void InitialInspectionWidget::clearEdits() {
	ui.bridgeRepairEdit->clear();
	ui.staticLoadResultEdit->clear();
	ui.dynamicLoadResultEdit->clear();
	ui.recorderEdit->clear();
	ui.inspectionOrganizationEdit->clear();
}