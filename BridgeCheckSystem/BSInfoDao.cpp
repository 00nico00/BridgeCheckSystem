#include "BSInfoDao.h"


void BSInfoDao::insertBSInfo(const QString& bridgeNumber, const BSInfo& bsInfo) {
	auto sql = QString("INSERT INTO bsinfo (bridgeNumber, mainGirder, mainArchRib, \
bridgeTower, structureAboveArch, mainCable, bridgeSurfaceCoating, sidewalk, lighting, \
coneSlope, wingWall, foundation, bearing, crashBarrier, beacon) VALUES (?, ?, ?, ?, ?, \
?, ?, ?, ?, ?, ?, ?, ?, ?, ?);");
	DEBUG(sql);

	QSqlQuery query{};
	query.prepare(sql);
	query.addBindValue(bridgeNumber);
	query.addBindValue(bsInfo.getMainGirder());
	query.addBindValue(bsInfo.getMainArchRib());
	query.addBindValue(bsInfo.getBridgeTower());
	query.addBindValue(bsInfo.getStructureAboveArch());
	query.addBindValue(bsInfo.getMainCable());
	query.addBindValue(bsInfo.getBridgeSurfaceCoating());
	query.addBindValue(bsInfo.getSidewalk());
	query.addBindValue(bsInfo.getLighting());
	query.addBindValue(bsInfo.getConeSlope());
	query.addBindValue(bsInfo.getWingWall());
	query.addBindValue(bsInfo.getFoundation());
	query.addBindValue(bsInfo.getBearing());
	query.addBindValue(bsInfo.getCrashBarrier());
	query.addBindValue(bsInfo.getBeacon());

	bool flag = query.exec();
	if (!flag) {
		CRITICAL("Failed to insert bsInfo");
	}
}

void BSInfoDao::deleteBSInfo(const QString& bridgeNumber) {
	auto sql = QString("DELETE FROM bsinfo WHERE bridgeNumber = ?;");
	DEBUG(sql);

	QSqlQuery query{};
	query.prepare(sql);
	query.addBindValue(bridgeNumber);

	query.exec();
}

std::optional<BSInfo> BSInfoDao::queryBSInfo(const QString& bridgeNumber) {
	auto sql = QString("SELECT * FROM bsinfo WHERE bridgeNumber = ?;");
	DEBUG(sql);

	QSqlQuery query{};
	query.prepare(sql);
	query.addBindValue(bridgeNumber);

	if (query.exec() && query.next()) {
		return BSInfo(
			query.value("mainGirder").toString(),
			query.value("mainArchRib").toString(),
			query.value("bridgeTower").toString(),
			query.value("structureAboveArch").toString(),
			query.value("mainCable").toString(),
			query.value("bridgeSurfaceCoating").toString(),
			query.value("sidewalk").toString(),
			query.value("lighting").toString(),
			query.value("coneSlope").toString(),
			query.value("wingWall").toString(),
			query.value("foundation").toString(),
			query.value("bearing").toString(),
			query.value("crashBarrier").toString(),
			query.value("beacon").toString()
		);
	}

	return std::nullopt;
}

std::optional<QString> BSInfoDao::queryMainGirder(const QString& bridgeNumber) {
	auto sql = QString("SELECT * FROM bsinfo WHERE bridgeNumber = ?;");
	DEBUG(sql);

	QSqlQuery query{};
	query.prepare(sql);
	query.addBindValue(bridgeNumber);

	if (query.exec() && query.next()) {
		return query.value("mainGirder").toString();
	}

	return std::nullopt;
}


std::optional<QString> BSInfoDao::queryMainArchRib(const QString& bridgeNumber) {
	auto sql = QString("SELECT * FROM bsinfo WHERE bridgeNumber = ?;");
	DEBUG(sql);

	QSqlQuery query{};
	query.prepare(sql);
	query.addBindValue(bridgeNumber);

	if (query.exec() && query.next()) {
		return query.value("mainArchRib").toString();
	}

	return std::nullopt;
}

std::optional<QString> BSInfoDao::queryBridgeTower(const QString& bridgeNumber) {
	auto sql = QString("SELECT * FROM bsinfo WHERE bridgeNumber = ?;");
	DEBUG(sql);

	QSqlQuery query{};
	query.prepare(sql);
	query.addBindValue(bridgeNumber);

	if (query.exec() && query.next()) {
		return query.value("bridgeTower").toString();
	}

	return std::nullopt;
}

std::optional<QString> BSInfoDao::queryStructureAboveArch(const QString& bridgeNumber) {
	auto sql = QString("SELECT * FROM bsinfo WHERE bridgeNumber = ?;");
	DEBUG(sql);

	QSqlQuery query{};
	query.prepare(sql);
	query.addBindValue(bridgeNumber);

	if (query.exec() && query.next()) {
		return query.value("structureAboveArch").toString();
	}

	return std::nullopt;
}

std::optional<QString> BSInfoDao::queryMainCable(const QString& bridgeNumber) {
	auto sql = QString("SELECT * FROM bsinfo WHERE bridgeNumber = ?;");
	DEBUG(sql);

	QSqlQuery query{};
	query.prepare(sql);
	query.addBindValue(bridgeNumber);

	if (query.exec() && query.next()) {
		return query.value("mainCable").toString();
	}

	return std::nullopt;
}

std::optional<QString> BSInfoDao::queryBridgeSurfaceCoating(const QString& bridgeNumber) {
	auto sql = QString("SELECT * FROM bsinfo WHERE bridgeNumber = ?;");
	DEBUG(sql);

	QSqlQuery query{};
	query.prepare(sql);
	query.addBindValue(bridgeNumber);

	if (query.exec() && query.next()) {
		return query.value("bridgeSurfaceCoating").toString();
	}

	return std::nullopt;
}

std::optional<QString> BSInfoDao::querySidewalk(const QString& bridgeNumber) {
	auto sql = QString("SELECT * FROM bsinfo WHERE bridgeNumber = ?;");
	DEBUG(sql);

	QSqlQuery query{};
	query.prepare(sql);
	query.addBindValue(bridgeNumber);

	if (query.exec() && query.next()) {
		return query.value("sidewalk").toString();
	}

	return std::nullopt;
}

std::optional<QString> BSInfoDao::queryLighting(const QString& bridgeNumber) {
	auto sql = QString("SELECT * FROM bsinfo WHERE bridgeNumber = ?;");
	DEBUG(sql);

	QSqlQuery query{};
	query.prepare(sql);
	query.addBindValue(bridgeNumber);

	if (query.exec() && query.next()) {
		return query.value("lighting").toString();
	}

	return std::nullopt;
}
#include <optional>

std::optional<QString> BSInfoDao::queryConeSlope(const QString& bridgeNumber) {
	auto sql = QString("SELECT * FROM bsinfo WHERE bridgeNumber = ?;");
	DEBUG(sql);

	QSqlQuery query{};
	query.prepare(sql);
	query.addBindValue(bridgeNumber);

	if (query.exec() && query.next()) {
		return query.value("coneSlope").toString();
	}

	return std::nullopt;
}

std::optional<QString> BSInfoDao::queryWingWall(const QString& bridgeNumber) {
	auto sql = QString("SELECT * FROM bsinfo WHERE bridgeNumber = ?;");
	DEBUG(sql);

	QSqlQuery query{};
	query.prepare(sql);
	query.addBindValue(bridgeNumber);

	if (query.exec() && query.next()) {
		return query.value("wingWall").toString();
	}

	return std::nullopt;
}

std::optional<QString> BSInfoDao::queryFoundation(const QString& bridgeNumber) {
	auto sql = QString("SELECT * FROM bsinfo WHERE bridgeNumber = ?;");
	DEBUG(sql);

	QSqlQuery query{};
	query.prepare(sql);
	query.addBindValue(bridgeNumber);

	if (query.exec() && query.next()) {
		return query.value("foundation").toString();
	}

	return std::nullopt;
}

std::optional<QString> BSInfoDao::queryBearing(const QString& bridgeNumber) {
	auto sql = QString("SELECT * FROM bsinfo WHERE bridgeNumber = ?;");
	DEBUG(sql);

	QSqlQuery query{};
	query.prepare(sql);
	query.addBindValue(bridgeNumber);

	if (query.exec() && query.next()) {
		return query.value("bearing").toString();
	}

	return std::nullopt;
}

std::optional<QString> BSInfoDao::queryCrashBarrier(const QString& bridgeNumber) {
	auto sql = QString("SELECT * FROM bsinfo WHERE bridgeNumber = ?;");
	DEBUG(sql);

	QSqlQuery query{};
	query.prepare(sql);
	query.addBindValue(bridgeNumber);

	if (query.exec() && query.next()) {
		return query.value("crashBarrier").toString();
	}

	return std::nullopt;
}

std::optional<QString> BSInfoDao::queryBeacon(const QString& bridgeNumber) {
	auto sql = QString("SELECT * FROM bsinfo WHERE bridgeNumber = ?;");
	DEBUG(sql);

	QSqlQuery query{};
	query.prepare(sql);
	query.addBindValue(bridgeNumber);

	if (query.exec() && query.next()) {
		return query.value("beacon").toString();
	}

	return std::nullopt;
}

void BSInfoDao::updateBSInfo(const QString& bridgeNumber, const BSInfo& info) {
	auto sql = QString("UPDATE bsinfo SET mainGirder = ?, mainArchRib = ?, bridgeTower = ?, \
structureAboveArch = ?, mainCable = ?, bridgeSurfaceCoating = ?, sidewalk = ?, lighting = ?, \
coneSlope = ?, wingWall = ?, foundation = ?, bearing = ?, crashBarrier = ?, beacon = ? WHERE bridgeNumber = ?;");
	DEBUG(sql);

	QSqlQuery query{};
	query.prepare(sql);
	query.addBindValue(info.getMainGirder());
	query.addBindValue(info.getMainArchRib());
	query.addBindValue(info.getBridgeTower());
	query.addBindValue(info.getStructureAboveArch());
	query.addBindValue(info.getMainCable());
	query.addBindValue(info.getBridgeSurfaceCoating());
	query.addBindValue(info.getSidewalk());
	query.addBindValue(info.getLighting());
	query.addBindValue(info.getConeSlope());
	query.addBindValue(info.getWingWall());
	query.addBindValue(info.getFoundation());
	query.addBindValue(info.getBearing());
	query.addBindValue(info.getCrashBarrier());
	query.addBindValue(info.getBeacon());
	query.addBindValue(bridgeNumber);

	bool isSuccess = query.exec();
	if (!isSuccess) {
		CRITICAL(QString("Failed to update data for bridge '%1'").arg(bridgeNumber));
	}
}


void BSInfoDao::updateMainGirder(const QString& bridgeNumber, const QString& mainGirder) {
	auto sql = QString("UPDATE bsinfo SET mainGirder = ? WHERE bridgeNumber = ?;");
	DEBUG(sql);

	QSqlQuery query{};
	query.prepare(sql);
	query.addBindValue(mainGirder);
	query.addBindValue(bridgeNumber);

	bool flag = query.exec();
	if (!flag) {
		CRITICAL(QString("Failed to update '%1'").arg(mainGirder));
	}
}



void BSInfoDao::updateMainArchRib(const QString& bridgeNumber, const QString& mainArchRib) {
	auto sql = QString("UPDATE bsinfo SET mainArchRib = ? WHERE bridgeNumber = ?;");
	DEBUG(sql);

	QSqlQuery query{};
	query.prepare(sql);
	query.addBindValue(mainArchRib);
	query.addBindValue(bridgeNumber);

	bool flag = query.exec();
	if (!flag) {
		CRITICAL(QString("Failed to update '%1'").arg(mainArchRib));
	}
}

void BSInfoDao::updateBridgeTower(const QString& bridgeNumber, const QString& bridgeTower) {
	auto sql = QString("UPDATE bsinfo SET bridgeTower = ? WHERE bridgeNumber = ?;");
	DEBUG(sql);

	QSqlQuery query{};
	query.prepare(sql);
	query.addBindValue(bridgeTower);
	query.addBindValue(bridgeNumber);

	bool flag = query.exec();
	if (!flag) {
		CRITICAL(QString("Failed to update '%1'").arg(bridgeTower));
	}
}

void BSInfoDao::updateStructureAboveArch(const QString& bridgeNumber, const QString& structureAboveArch) {
	auto sql = QString("UPDATE bsinfo SET structureAboveArch = ? WHERE bridgeNumber = ?;");
	DEBUG(sql);

	QSqlQuery query{};
	query.prepare(sql);
	query.addBindValue(structureAboveArch);
	query.addBindValue(bridgeNumber);

	bool flag = query.exec();
	if (!flag) {
		CRITICAL(QString("Failed to update '%1'").arg(structureAboveArch));
	}
}

void BSInfoDao::updateMainCable(const QString& bridgeNumber, const QString& mainCable) {
	auto sql = QString("UPDATE bsinfo SET mainCable = ? WHERE bridgeNumber = ?;");
	DEBUG(sql);

	QSqlQuery query{};
	query.prepare(sql);
	query.addBindValue(mainCable);
	query.addBindValue(bridgeNumber);

	bool flag = query.exec();
	if (!flag) {
		CRITICAL(QString("Failed to update '%1'").arg(mainCable));
	}
}

void BSInfoDao::updateBridgeSurfaceCoating(const QString& bridgeNumber, const QString& bridgeSurfaceCoating) {
	auto sql = QString("UPDATE bsinfo SET bridgeSurfaceCoating = ? WHERE bridgeNumber = ?;");
	DEBUG(sql);

	QSqlQuery query{};
	query.prepare(sql);
	query.addBindValue(bridgeSurfaceCoating);
	query.addBindValue(bridgeNumber);

	bool flag = query.exec();
	if (!flag) {
		CRITICAL(QString("Failed to update '%1'").arg(bridgeSurfaceCoating));
	}
}

void BSInfoDao::updateSidewalk(const QString& bridgeNumber, const QString& sidewalk) {
	auto sql = QString("UPDATE bsinfo SET sidewalk = ? WHERE bridgeNumber = ?;");
	DEBUG(sql);

	QSqlQuery query{};
	query.prepare(sql);
	query.addBindValue(sidewalk);
	query.addBindValue(bridgeNumber);

	bool flag = query.exec();
	if (!flag) {
		CRITICAL(QString("Failed to update '%1'").arg(sidewalk));
	}
}

void BSInfoDao::updateLighting(const QString& bridgeNumber, const QString& lighting) {
	auto sql = QString("UPDATE bsinfo SET lighting = ? WHERE bridgeNumber = ?;");
	DEBUG(sql);

	QSqlQuery query{};
	query.prepare(sql);
	query.addBindValue(lighting);
	query.addBindValue(bridgeNumber);

	bool flag = query.exec();
	if (!flag) {
		CRITICAL(QString("Failed to update '%1'").arg(lighting));
	}
}
void BSInfoDao::updateConeSlope(const QString& bridgeNumber, const QString& coneSlope) {
	auto sql = QString("UPDATE bsinfo SET coneSlope = ? WHERE bridgeNumber = ?;");
	DEBUG(sql);

	QSqlQuery query{};
	query.prepare(sql);
	query.addBindValue(coneSlope);
	query.addBindValue(bridgeNumber);

	bool flag = query.exec();
	if (!flag) {
		CRITICAL(QString("Failed to update '%1'").arg(coneSlope));
	}
}

void BSInfoDao::updateWingWall(const QString& bridgeNumber, const QString& wingWall) {
	auto sql = QString("UPDATE bsinfo SET wingWall = ? WHERE bridgeNumber = ?;");
	DEBUG(sql);

	QSqlQuery query{};
	query.prepare(sql);
	query.addBindValue(wingWall);
	query.addBindValue(bridgeNumber);

	bool flag = query.exec();
	if (!flag) {
		CRITICAL(QString("Failed to update '%1'").arg(wingWall));
	}
}

void BSInfoDao::updateFoundation(const QString& bridgeNumber, const QString& foundation) {
	auto sql = QString("UPDATE bsinfo SET foundation = ? WHERE bridgeNumber = ?;");
	DEBUG(sql);

	QSqlQuery query{};
	query.prepare(sql);
	query.addBindValue(foundation);
	query.addBindValue(bridgeNumber);

	bool flag = query.exec();
	if (!flag) {
		CRITICAL(QString("Failed to update '%1'").arg(foundation));
	}
}

void BSInfoDao::updateBearing(const QString& bridgeNumber, const QString& bearing) {
	auto sql = QString("UPDATE bsinfo SET bearing = ? WHERE bridgeNumber = ?;");
	DEBUG(sql);

	QSqlQuery query{};
	query.prepare(sql);
	query.addBindValue(bearing);
	query.addBindValue(bridgeNumber);

	bool flag = query.exec();
	if (!flag) {
		CRITICAL(QString("Failed to update '%1'").arg(bearing));
	}
}

void BSInfoDao::updateCrashBarrier(const QString& bridgeNumber, const QString& crashBarrier) {
	auto sql = QString("UPDATE bsinfo SET crashBarrier = ? WHERE bridgeNumber = ?;");
	DEBUG(sql);

	QSqlQuery query{};
	query.prepare(sql);
	query.addBindValue(crashBarrier);
	query.addBindValue(bridgeNumber);

	bool flag = query.exec();
	if (!flag) {
		CRITICAL(QString("Failed to update '%1'").arg(crashBarrier));
	}
}

void BSInfoDao::updateBeacon(const QString& bridgeNumber, const QString& beacon) {
	auto sql = QString("UPDATE bsinfo SET beacon = ? WHERE bridgeNumber = ?;");
	DEBUG(sql);

	QSqlQuery query{};
	query.prepare(sql);
	query.addBindValue(beacon);
	query.addBindValue(bridgeNumber);

	bool flag = query.exec();
	if (!flag) {
		CRITICAL(QString("Failed to update '%1'").arg(beacon));
	}
}