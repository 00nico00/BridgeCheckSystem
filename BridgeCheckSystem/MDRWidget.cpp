#include "MDRWidget.h"

MDRWidget::MDRWidget(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	// Set to delete this object when the window is closed
	setAttribute(Qt::WA_DeleteOnClose);

	// lineEdit filter
	auto matchPositiveNumber = new QRegularExpressionValidator(QRegularExpression("^[1-9]\\d*(\\.\\d+)?$"), this);
	ui.projectCostEdit->setValidator(matchPositiveNumber);

	connect(ui.saveBtn, &QPushButton::clicked,
		[this] {
			if (isEditsEmpty()) {
				QMessageBox::warning(this, "保存失败", "有未填入的数据项");
				return;
			}

			emit send_MDR_Info(MDR(
				ui.timeEdit->dateTime(),
				MDR::strToRemedialActionType[ui.typeOption->currentText()],
				ui.remedialActionReasonEdit->text().trimmed(),
				ui.remedialActionScopeEdit->text().trimmed(),
				ui.projectCostEdit->text().toFloat(),
				ui.fundingSourceEdit->text().trimmed(),
				ui.RAQAEdit->text().trimmed()
			));

			clearEdits();

			this->close();
		}
	);

	connect(ui.exitBtn, &QPushButton::clicked, this, &MDRWidget::close);
}

MDRWidget::~MDRWidget()
{}


bool MDRWidget::isEditNotEmpty() {
	return !ui.remedialActionReasonEdit->text().isEmpty() ||
		!ui.remedialActionScopeEdit->text().isEmpty() ||
		!ui.projectCostEdit->text().isEmpty() ||
		!ui.fundingSourceEdit->text().isEmpty() ||
		!ui.RAQAEdit->text().isEmpty();
}

bool MDRWidget::isEditsEmpty() {
	return ui.remedialActionReasonEdit->text().isEmpty() ||
		ui.remedialActionScopeEdit->text().isEmpty() ||
		ui.projectCostEdit->text().isEmpty() ||
		ui.fundingSourceEdit->text().isEmpty() ||
		ui.RAQAEdit->text().isEmpty();
}

void MDRWidget::closeEvent(QCloseEvent* event) {
	if (isEditNotEmpty()) {
		auto result = QMessageBox::question(this, "确认", "有未提交的表单，确定要退出吗？", QMessageBox::Yes | QMessageBox::Cancel);
		if (result == QMessageBox::Yes) {
			event->accept();
		} else {
			event->ignore();
		}
	}
}

void MDRWidget::clearEdits() {
	ui.remedialActionReasonEdit->clear();
	ui.remedialActionScopeEdit->clear();
	ui.projectCostEdit->clear();
	ui.fundingSourceEdit->clear();
	ui.RAQAEdit->clear();
}

void MDRWidget::receive_MDR_info(const MDR& info) {
	ui.timeEdit->setDateTime(info.getTime());
	ui.typeOption->setCurrentText(MDR::remedialActionTypeToStr[info.getType()]);
	ui.remedialActionReasonEdit->setText(info.getRemedialActionReason());
	ui.remedialActionScopeEdit->setText(info.getRemedialActionScope());
	ui.projectCostEdit->setText(QString::number(info.getProjectCost()));
	ui.fundingSourceEdit->setText(info.getFundingSource());
	ui.RAQAEdit->setText(info.getRAQA());
}