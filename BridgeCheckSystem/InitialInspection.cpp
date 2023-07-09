#include "InitialInspection.h"

InitialInspection::InitialInspection(
	const QString& bridgeRepair,
	const QDateTime& inspectionDate,
	float staticLoadResult,
	float dynamicLoadResult,
	const QString& recorder,
	const QString& inspectionOrganization
) noexcept :
	bridgeRepair_(bridgeRepair),
	inspectionDate_(inspectionDate),
	staticLoadResult_(staticLoadResult),
	dynamicLoadResult_(dynamicLoadResult),
	recorder_(recorder),
	inspectionOrganization_(inspectionOrganization)
{}

InitialInspection::InitialInspection(
	QString&& bridgeRepair,
	QDateTime&& inspectionDate,
	float staticLoadResult,
	float dynamicLoadResult,
	QString&& recorder,
	QString&& inspectionOrganization
) noexcept :
	bridgeRepair_(std::move(bridgeRepair)),
	inspectionDate_(std::move(inspectionDate)),
	staticLoadResult_(staticLoadResult),
	dynamicLoadResult_(dynamicLoadResult),
	recorder_(std::move(recorder)),
	inspectionOrganization_(std::move(inspectionOrganization))
{}