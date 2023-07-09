#pragma once

#include <QWidget>
#include "ui_BRDWidget.h"

#include <QValidator>
#include <QRegularExpressionValidator>
#include <QCloseEvent>
#include <QMessageBox>

#include "BRD.h"

class BRDWidget : public QWidget
{
	Q_OBJECT

signals:
	// to BridgeProfileWidget
	void send_BRD_Info(const BRD& info);

public:
	BRDWidget(QWidget* parent = nullptr);
	~BRDWidget();

	bool isEditNotEmpty();

	bool isEditsEmpty();

	void closeEvent(QCloseEvent* event);

	void clearEdits();

	void receive_BRD_info(const BRD& info);

private:
	Ui::BRDWidgetClass ui;
};
