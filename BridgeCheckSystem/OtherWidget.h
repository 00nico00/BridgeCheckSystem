#pragma once

#include <QWidget>
#include "ui_OtherWidget.h"

#include <QValidator>
#include <QRegularExpressionValidator>
#include <QCloseEvent>
#include <QMessageBox>

#include "Other.h"

class OtherWidget : public QWidget
{
	Q_OBJECT

signals:
	// to BridgeProfileWidget
	void send_Other_Info(const Other& info);

public:
	OtherWidget(QWidget* parent = nullptr);
	~OtherWidget();

	bool isEditNotEmpty();

	bool isEditsEmpty();

	void closeEvent(QCloseEvent* event);

	void clearEdits();

	void receive_Other_info(const Other& info);

private:
	Ui::OtherWidgetClass ui;
};
