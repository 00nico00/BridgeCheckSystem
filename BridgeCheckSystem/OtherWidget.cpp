#include "OtherWidget.h"

OtherWidget::OtherWidget(QWidget* parent)
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

			emit send_Other_Info(Other(
				ui.bridgeEngineerEdit->text().trimmed(),
				ui.cardFillerEdit->text().trimmed(),
				ui.cardTimeEdit->dateTime()
			));

			clearEdits();

			this->close();
		}
	);

	connect(ui.exitBtn, &QPushButton::clicked, this, &OtherWidget::close);
}

OtherWidget::~OtherWidget()
{}

bool OtherWidget::isEditNotEmpty() {
	return !ui.bridgeEngineerEdit->text().isEmpty() ||
		!ui.cardFillerEdit->text().isEmpty();
}

bool OtherWidget::isEditsEmpty() {
	return ui.bridgeEngineerEdit->text().isEmpty() ||
		ui.cardFillerEdit->text().isEmpty();
}

void OtherWidget::closeEvent(QCloseEvent* event) {
	if (isEditNotEmpty()) {
		auto result = QMessageBox::question(this, "确认", "有未提交的表单，确定要退出吗？", QMessageBox::Yes | QMessageBox::Cancel);
		if (result == QMessageBox::Yes) {
			event->accept();
		} else {
			event->ignore();
		}
	}
}

void OtherWidget::clearEdits() {
	ui.bridgeEngineerEdit->clear();
	ui.cardFillerEdit->clear();
}

void OtherWidget::receive_Other_info(const Other& info) {
	ui.bridgeEngineerEdit->setText(info.getBridgeEngineer());
	ui.cardFillerEdit->setText(info.getCardFiller());
	ui.cardTimeEdit->setDateTime(info.getCardTime());
}