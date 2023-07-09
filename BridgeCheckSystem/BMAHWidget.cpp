#include "BMAHWidget.h"

BMAHWidget::BMAHWidget(QWidget* parent)
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

			emit send_BMAH_Info(BMAH(
				ui.assessmentTimeEdit->dateTime(),
				BMAH::strToInspectionType[ui.typeOption->currentText()],
				ui.resultEdit->text().trimmed(),
				ui.remedialMeasuresEdit->text().trimmed(),
				ui.nextInspectionTimeEdit->dateTime()
			));

			clearEdits();

			this->close();
		}
	);

	connect(ui.exitBtn, &QPushButton::clicked, this, &BMAHWidget::close);
}

BMAHWidget::~BMAHWidget()
{}


bool BMAHWidget::isEditNotEmpty() {
	return !ui.resultEdit->text().isEmpty() || !ui.remedialMeasuresEdit->text().isEmpty();
}

bool BMAHWidget::isEditsEmpty() {
	return ui.resultEdit->text().isEmpty() || ui.remedialMeasuresEdit->text().isEmpty();
}

void BMAHWidget::closeEvent(QCloseEvent* event) {
	if (isEditNotEmpty()) {
		auto result = QMessageBox::question(this, "确认", "有未提交的表单，确定要退出吗？", QMessageBox::Yes | QMessageBox::Cancel);
		if (result == QMessageBox::Yes) {
			event->accept();
		} else {
			event->ignore();
		}
	}
}

void BMAHWidget::clearEdits() {
	ui.resultEdit->clear();
	ui.remedialMeasuresEdit->clear();
}

void BMAHWidget::receive_BMAH_info(const BMAH& info) {
	ui.assessmentTimeEdit->setDateTime(info.getAssessmentTime());
	ui.typeOption->setCurrentText(BMAH::inspectionTypeToStr[info.getType()]);
	ui.resultEdit->setText(info.getResult());
	ui.remedialMeasuresEdit->setText(info.getRemedialMeasures());
	ui.nextInspectionTimeEdit->setDateTime(info.getNextInspectionTime());
}