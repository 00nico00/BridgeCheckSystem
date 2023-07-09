#pragma once

#include <QSqlQuery>
#include <optional>

#include "InitialInspection.h"
#include "Logger.hpp"

class InitialInspectionDao {
public:
	// insert
	static void insertInitialInspection(const QString& bridgeNumber, const InitialInspection& info);

	// query
	static auto queryInitialInspection(const QString& bridgeNumber) -> std::optional<InitialInspection>;

	// update
	static void updateInitialInspection(const QString& bridgeNumber, const InitialInspection& info);
};

