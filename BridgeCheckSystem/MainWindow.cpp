#include "MainWindow.h"

MainWindow::MainWindow(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	// Set to delete this object when the window is closed
	setAttribute(Qt::WA_DeleteOnClose);

	// show the amap on miniblink webview
	showAmap();

	connect(ui.newProfileBtn, &QPushButton::clicked, this, &MainWindow::on_newProfileBtn_clicked);
	connect(ui.showProfileBtn, &QPushButton::clicked, this, &MainWindow::on_showProfileBtn_clicked);
	connect(ui.showInitialInspectionBtn, &QPushButton::clicked, this, &MainWindow::on_showInitialInspectionBtn_clicked);

	loadAllBridgeNames();

	connect(ui.bridgeNames, &QComboBox::currentTextChanged, this, &MainWindow::on_bridgeNames_currentTextChanged);
}

void MainWindow::showAmap() {
	const QString mapPath = "F:/Demo/project/BridgeCheckSystem/BridgeCheckSystem/amap/amap.html";
	webView = wkeCreateWebWindow(WKE_WINDOW_TYPE_CONTROL, (HWND)ui.mapWidget->winId(), 0, 0, 1100, 800);
	wkeShowWindow(webView, TRUE);
	QFile file(mapPath);
	file.open(QIODevice::ReadOnly);
	wkeLoadHTML(webView, file.read(file.bytesAvailable()));
}

void MainWindow::on_newProfileBtn_clicked() {
	BridgeProfileWidget* bpWidget = new BridgeProfileWidget("new");
	bpWidget->setWindowModality(Qt::ApplicationModal);	// 模态窗口，阻塞一切窗口
	auto title = QString("新建资料卡 类型: %1").arg(ui.bridgeTypes->currentText());
	bpWidget->setWindowTitle(title);

	// send bridge type to bpWidget
	connect(this, &MainWindow::send_bridgeType, bpWidget, &BridgeProfileWidget::receive_bridgeType);
	emit send_bridgeType(ui.bridgeTypes->currentText());

	connect(bpWidget, &BridgeProfileWidget::trigger_reloadBridgeNames, this, &MainWindow::reloadBridgeNames);

	bpWidget->show();
}

void MainWindow::on_showProfileBtn_clicked() {
	BridgeProfileWidget* bpWidget = new BridgeProfileWidget("update");
	bpWidget->setWindowModality(Qt::ApplicationModal);	// 模态窗口，阻塞一切窗口
	bpWidget->setWindowTitle(ui.bridgeNames->currentText());

	// send bridge info
	connect(this, &MainWindow::send_bridge_info, bpWidget, &BridgeProfileWidget::receive_bridge_info);
	auto bridgeNumber = ADMIDDao::queryBridgeNumber(ui.bridgeNames->currentText());
	emit send_bridge_info(
		ADMIDDao::queryADMID(bridgeNumber.value()).value(),
		BTIDao::queryBTI(bridgeNumber.value()).value(),
		BSInfoDao::queryBSInfo(bridgeNumber.value()).value(),
		BRDDao::queryBRD(bridgeNumber.value()).value(),
		BMAHDao::queryBMAH(bridgeNumber.value()).value(),
		MDRDao::queryMDR(bridgeNumber.value()).value(),
		OtherDao::queryOther(bridgeNumber.value()).value()
	);

	connect(bpWidget, &BridgeProfileWidget::trigger_reloadBridgeNames, this, &MainWindow::reloadBridgeNames);

	bpWidget->show();
}

void MainWindow::loadAllBridgeNames() {
	ui.bridgeNames->clear();
	auto bridges = ADMIDDao::queryAllBridgeNames();
	if (bridges) {
		for (int i = 0; i < bridges.value().size(); i++) {
			ui.bridgeNames->addItem(bridges.value()[i]);
		}
	}
}

void MainWindow::reloadBridgeNames() {
	loadAllBridgeNames();
}

void MainWindow::on_bridgeNames_currentTextChanged(const QString& text) {
	// loadAllBridgeNames()时也会触发，导致悬空引用
	if (text.isEmpty()) {
		return;
	}
	auto bridgeNumber = ADMIDDao::queryBridgeNumber(text);
	auto pos = ADMIDDao::queryLnglat(bridgeNumber.value());
	callJsFunc::jumpTo(webView, pos.value());
}

void MainWindow::on_showInitialInspectionBtn_clicked() {
	auto bridgeNumber = ADMIDDao::queryBridgeNumber(ui.bridgeNames->currentText());
	auto initInspec = InitialInspectionDao::queryInitialInspection(bridgeNumber.value());
	if (!initInspec) {
		auto result = QMessageBox::question(this, "注意", "没有找到初始检查表，要新建吗", QMessageBox::Yes | QMessageBox::Cancel);
		if (result == QMessageBox::Yes) {
			InitialInspectionWidget* widget = new InitialInspectionWidget("new");
			widget->setWindowModality(Qt::ApplicationModal);
			connect(this, &MainWindow::send_bridgeName_new, widget, &InitialInspectionWidget::receive_bridgeName_new);
			emit send_bridgeName_new(ui.bridgeNames->currentText());
			widget->show();
		}
	} else {
		InitialInspectionWidget* widget = new InitialInspectionWidget("update");
		widget->setWindowModality(Qt::ApplicationModal);
		connect(this, &MainWindow::send_bridgeName_update, widget, &InitialInspectionWidget::receive_bridgeName_udpate);
		emit send_bridgeName_update(ui.bridgeNames->currentText());
		widget->show();
	}
}