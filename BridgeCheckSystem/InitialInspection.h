#pragma once

#include <QString>
#include <QDateTime>

#define GAS(type, funcname, valname) \
void set##funcname(type valname) noexcept { valname##_ = valname; } \
type get##funcname() const noexcept { return valname##_; }

#define GASR(type, funcname, valname) \
void set##funcname(const type& valname) noexcept { valname##_ = valname; } \
void set##funcname(type&& valname) noexcept { valname##_ = std::move(valname); } \
type get##funcname() const noexcept { return valname##_; }

// 初始检查

class InitialInspection {
public:
	InitialInspection() = delete;
	InitialInspection(
		const QString& bridgeRepair,
		const QDateTime& inspectionDate,
		float staticLoadResult,
		float dynamicLoadResult,
		const QString& recorder,
		const QString& inspectionOrganization
	) noexcept;
	InitialInspection(
		QString&& bridgeRepair,
		QDateTime&& inspectionDate,
		float staticLoadResult,
		float dynamicLoadResult,
		QString&& recorder,
		QString&& inspectionOrganization
	) noexcept;

	void setBridgeRepair(const QString& bridgeRepair) noexcept { bridgeRepair_ = bridgeRepair; }
	void setBridgeRepair(QString&& bridgeRepair) noexcept { bridgeRepair_ = std::move(bridgeRepair); }
	QString getBridgeRepair() const noexcept { return bridgeRepair_; }

	void setInspectionDate(const QDateTime& inspectionTime) noexcept { inspectionDate_ = inspectionTime; }
	void setInspectionDate(QDateTime&& inspectionTime) noexcept { inspectionDate_ = std::move(inspectionTime); }
	QDateTime getInspectionDate() const noexcept { return inspectionDate_; }

	void setStaticLoadResult(float staticLoadResult) noexcept { staticLoadResult_ = staticLoadResult; }
	float getStaticLoadResult() const noexcept { return staticLoadResult_; }

	void setDynamicLoadResult(float dynamicLoadResult) noexcept { dynamicLoadResult_ = dynamicLoadResult; }
	float getDynamicLoadResult() const noexcept { return dynamicLoadResult_; }

	void setRecorder(const QString& recorder) noexcept { recorder_ = recorder; }
	void setRecorder(QString&& recorder) noexcept { recorder_ = std::move(recorder); }
	QString getRecorder() const noexcept { return recorder_; }

	void setInspectionOrganization(const QString& inspectionOrganization) noexcept { inspectionOrganization_ = inspectionOrganization; }
	void setInspectionOrganization(QString&& inspectionOrganization) noexcept { inspectionOrganization_ = std::move(inspectionOrganization); }
	QString getInspectionOrganization() const noexcept { return inspectionOrganization_; }


private:
	QString bridgeRepair_;		// 桥梁维修情况的描述
	QDateTime inspectionDate_;	// 检查日期
	float staticLoadResult_;	// 静载荷测试
	float dynamicLoadResult_;	// 动载荷测试
	QString recorder_;
	QString inspectionOrganization_;
};

