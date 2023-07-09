#pragma once

#include <QWidget>
#include "ui_MDRWidget.h"

#include <QValidator>
#include <QRegularExpressionValidator>
#include <QCloseEvent>
#include <QMessageBox>

#include "MDR.h"

class MDRWidget : public QWidget
{
	Q_OBJECT

signals:
	// to BridgeProfileWidget
	void send_MDR_Info(const MDR& info);

public:
	MDRWidget(QWidget* parent = nullptr);
	~MDRWidget();

	bool isEditNotEmpty();

	bool isEditsEmpty();

	void closeEvent(QCloseEvent* event);

	void clearEdits();

	void receive_MDR_info(const MDR& info);

private:
	Ui::MDRWidgetClass ui;
};
