#pragma once

#include <QWidget>
#include "ui_InitialInspectionWidget.h"

#include <optional>
#include <QValidator>
#include <QRegularExpressionValidator>
#include <QCloseEvent>
#include <QMessageBox>

#include "InitialInspection.h"
#include "InitialInspectionDao.h"
#include "ADMIDDao.h"
#include "OtherDao.h"

class InitialInspectionWidget : public QWidget
{
	Q_OBJECT

public:
	InitialInspectionWidget(const QString& mode, QWidget* parent = nullptr);
	~InitialInspectionWidget();

	// 是否有 LineEdit 不为空
	bool isEditNotEmpty() const;

	// 是否全部的 LineEdit 都为空
	bool isEditsEmpty() const;

	void closeEvent(QCloseEvent* event);

	void clearEdits();

public:
	void receive_bridgeName_udpate(const QString& name);
	void receive_bridgeName_new(const QString& name);

private:
	Ui::InitialInspectionWidgetClass ui;
};
