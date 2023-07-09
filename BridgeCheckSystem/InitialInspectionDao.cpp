#include "InitialInspectionDao.h"


void InitialInspectionDao::insertInitialInspection(const QString& bridgeNumber, const InitialInspection& info) {
	auto sql = QString("INSERT INTO initial_inspection (bridgeNumber, bridgeRepair, inspectionDate, \
staticLoadResult, dynamicLoadResult, recorder, inspectionOrganization) VALUES(?, ?, ?, ?, ?, ?, ?);");
	DEBUG(sql);

	QSqlQuery query{};
	query.prepare(sql);
	query.addBindValue(bridgeNumber);
	query.addBindValue(info.getBridgeRepair());
	query.addBindValue(info.getInspectionDate());
	query.addBindValue(info.getStaticLoadResult());
	query.addBindValue(info.getDynamicLoadResult());
	query.addBindValue(info.getRecorder());
	query.addBindValue(info.getInspectionOrganization());

	bool isSuccess = query.exec();
	if (!isSuccess) {
		CRITICAL("Failed to insert InitialInspection");
	}
}

auto InitialInspectionDao::queryInitialInspection(const QString& bridgeNumber) -> std::optional<InitialInspection> {
	auto sql = QString("SELECT * FROM initial_inspection WHERE bridgeNumber = ?;");
	DEBUG(sql);

	QSqlQuery query{};
	query.prepare(sql);
	query.addBindValue(bridgeNumber);

	if (query.exec() && query.next()) {
		return InitialInspection(
			query.value("bridgeRepair").toString(),
			query.value("inspectionDate").toDateTime(),
			query.value("staticLoadResult").toFloat(),
			query.value("dynamicLoadResult").toFloat(),
			query.value("recorder").toString(),
			query.value("inspectionOrganization").toString()
		);
	}

	return std::nullopt;
}

void InitialInspectionDao::updateInitialInspection(const QString& bridgeNumber, const InitialInspection& info) {
	auto sql = QString("UPDATE initial_inspection SET bridgeRepair = ?, inspectionDate = ?, \
staticLoadResult = ?, dynamicLoadResult = ?, recorder = ?, inspectionOrganization = ? WHERE bridgeNumber = ?;");
	DEBUG(sql);

	QSqlQuery query{};
	query.prepare(sql);
	query.addBindValue(info.getBridgeRepair());
	query.addBindValue(info.getInspectionDate());
	query.addBindValue(info.getStaticLoadResult());
	query.addBindValue(info.getDynamicLoadResult());
	query.addBindValue(info.getRecorder());
	query.addBindValue(info.getInspectionOrganization());
	query.addBindValue(bridgeNumber);

	bool isSuccess = query.exec();
	if (!isSuccess) {
		CRITICAL(QString("Failed to update fields for initial_inspection '%1'").arg(bridgeNumber));
	}

}