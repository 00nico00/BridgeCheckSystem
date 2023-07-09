#include "BRDWidget.h"

BRDWidget::BRDWidget(QWidget* parent)
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

			emit send_BRD_Info(BRD(
				BRD::strToBRDType[ui.designDrawingsOption->currentText()],
				BRD::strToBRDType[ui.designDocOption->currentText()],
				BRD::strToBRDType[ui.recordDrawingsOption->currentText()],
				BRD::strToBRDType[ui.acceptanceDocOption->currentText()],
				BRD::strToBRDType[ui.ADDocOption->currentText()],
				BRD::strToBRDType[ui.PMSOption->currentText()],
				BRD::strToBRDType[ui.SISOption->currentText()],
				BRD::strToBRDType[ui.RRROption->currentText()],
				ui.otherArchiveEdit->text(),
				BRD::strToArchiveType[ui.archiveTypeOption->currentText()],
				ui.filingDateEdit->dateTime()
			));

			clearEdits();

			this->close();
		}
	);

	connect(ui.exitBtn, &QPushButton::clicked, this, &BRDWidget::close);
}

BRDWidget::~BRDWidget()
{}


bool BRDWidget::isEditNotEmpty() {
	return !ui.otherArchiveEdit->text().isEmpty();
}

bool BRDWidget::isEditsEmpty() {
	return ui.otherArchiveEdit->text().isEmpty();
}

void BRDWidget::closeEvent(QCloseEvent* event) {
	if (isEditNotEmpty()) {
		auto result = QMessageBox::question(this, "确认", "有未提交的表单，确定要退出吗？", QMessageBox::Yes | QMessageBox::Cancel);
		if (result == QMessageBox::Yes) {
			event->accept();
		} else {
			event->ignore();
		}
	}
}

void BRDWidget::clearEdits() {
	ui.otherArchiveEdit->clear();
}

void BRDWidget::receive_BRD_info(const BRD& info) {
	ui.designDrawingsOption->setCurrentText(BRD::BRDtypeToStr[info.getDesignDrawings()]);
	ui.designDocOption->setCurrentText(BRD::BRDtypeToStr[info.getDesignDoc()]);
	ui.recordDrawingsOption->setCurrentText(BRD::BRDtypeToStr[info.getRecordDrawings()]);
	ui.acceptanceDocOption->setCurrentText(BRD::BRDtypeToStr[info.getAcceptanceDoc()]);
	ui.ADDocOption->setCurrentText(BRD::BRDtypeToStr[info.getADDoc()]);
	ui.PMSOption->setCurrentText(BRD::BRDtypeToStr[info.getPMS()]);
	ui.SISOption->setCurrentText(BRD::BRDtypeToStr[info.getSIS()]);
	ui.RRROption->setCurrentText(BRD::BRDtypeToStr[info.getRRR()]);
	ui.otherArchiveEdit->setText(info.getOtherArchive());
	ui.archiveTypeOption->setCurrentText(BRD::archiveTypeToStr[info.getArchiveType()]);
	ui.filingDateEdit->setDateTime(info.getFilingDate());
}