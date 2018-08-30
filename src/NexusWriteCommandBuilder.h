#pragma once

#include <nlohmann/json.hpp>

namespace {

struct Attribute {
  const std::string name;
  const std::string value;
};

enum class NodeType { DATASET, GROUP };

nlohmann::json createNode(const std::string &name, const NodeType nodeType,
                          const std::vector<Attribute> &attributes) {
  auto node = nlohmann::json::object();

  node["name"] = name;

  if (nodeType == NodeType::DATASET) {
    node["type"] = "dataset";
  } else if (nodeType == NodeType::GROUP) {
    node["type"] = "group";
    node["children"] = nlohmann::json::array();
  } else {
    throw std::runtime_error("Unhandled NodeType in createNode");
  }

  if (!attributes.empty()) {
    node["attributes"] = {};
    for (const auto &attribute : attributes) {
      node["attributes"].push_back(
          {{"name", attribute.name}, {"values", attribute.value}});
    }
  }

  return node;
}

template <typename T>
nlohmann::json createDataset(const std::string &name,
                             const std::string &typeStr, T value,
                             const std::vector<Attribute> &attributes = {}) {
  auto dataset = createNode(name, NodeType::DATASET, attributes);
  dataset["values"] = value;
  dataset["dataset"] = {{"type", typeStr}, {"size", {"unlimited"}}};

  return dataset;
}

nlohmann::json createGroup(const std::string &name,
                           const std::vector<Attribute> &attributes = {}) {
  return createNode(name, NodeType::GROUP, attributes);
}

template <typename T>
nlohmann::json
createLogGroup(const std::string &name, const std::string &typeStr,
               const T &values, const std::vector<float> &times,
               const std::string &startTime, const std::string &units) {
  auto logGroup = createGroup(name, {{"NX_class", "NXlog"}});
  logGroup["children"].push_back(createDataset<std::vector<float>>(
      "time", "float", times, {{"start", startTime}, {"units", "second"}}));
  if (!units.empty()) {
    logGroup["children"].push_back(
        createDataset<T>("value", typeStr, values, {{"units", units}}));
  } else {
    logGroup["children"].push_back(createDataset<T>("value", typeStr, values));
  }
  return logGroup;
}
}

class NexusWriteCommandBuilder {
public:
  NexusWriteCommandBuilder(const std::string &instrumentName, int32_t runNumber,
                           const std::string &broker,
                           const std::string &runCycle,
                           const std::string &startTimeIso8601);

  // Get the output command messages as strings
  std::string startMessageAsString();
  std::string stopMessageAsString();

  // Add stuff to the file
  void addMonitor(uint32_t monitorNumber, uint32_t spectrumNumber);
  void addSample(float height, float thickness, float width,
                 double distance = 0.0, const std::string &shape = "",
                 const std::string &name = "", const std::string &type = "",
                 const std::string &id = "");
  void addEndTime(const std::string &endTimeIso8601);
  void addCollectionTime(float collectionTimeInSeconds);
  void addDuration(float durationInSeconds);
  void addTitle(const std::string &title);
  void addTotalCounts(uint64_t totalCounts);
  void addMonitorEventsNotSaved(int64_t monitorEventsNotSaved);
  void addTotalUncountedCounts(int32_t uncountedCounts);
  void addSeciConfig(const std::string &SeciConfig);
  void addDetector(uint32_t detectorNumber, float sourceDetectorDistance);
  void addMeasurement(const std::string &label = "", const std::string &id = "",
                      const std::string &subId = "",
                      const std::string &type = "", int32_t firstRun = 0);
  void addEventDataSource(uint32_t detectorNumber,
                          const std::string &sourceName);
  void addSELogSources(const std::vector<std::string> &pVs);
  void addProgramName(const std::string &programName,
                      const std::string &version);
  void addNexusDefinition(const std::string &name, const std::string &version,
                          const std::string &url);
  void addLocalNexusDefinition(const std::string &name,
                               const std::string &version,
                               const std::string &url);
  void addNotes(const std::string &notes);
  void addProtonChargeRawInMicroAmpHours(float protonCharge);
  void addProtonChargeInMicroAmpHours(float protonCharge);
  void addPeriods(int32_t output, float totalCountsInMegaElectronVolts,
                  float protonChargeInMicroAmpHours, int32_t goodFramesDaq,
                  int32_t sequences, int32_t framesRequested,
                  int32_t goodFrames, int32_t number, int32_t highestUsed,
                  const std::string &labels,
                  float protonChargeRawInMicroAmpHours, int32_t type,
                  int32_t rawFrames);
  void addExperimentIdentifier(const std::string &experimentIdentifier);
  void addScriptName(const std::string &scriptName);

  template <typename T>
  void addVmsRecord(const std::string &name, const std::string &typeStr,
                    T record) {
    m_isisVmsCompatJson["children"].push_back(
        createDataset<T>(name, typeStr, record));
  }

  template <typename T>
  void addRunlogRecord(const std::string &name, const std::string &typeStr,
                       const T &values, const std::vector<float> &times,
                       const std::string &startTime,
                       const std::string &units = "") {
    auto logGroup =
        createLogGroup<T>(name, typeStr, values, times, startTime, units);
    m_runlogJson["children"].push_back(logGroup);
  }

  template <typename T>
  void addFramelogRecord(const std::string &name, const std::string &typeStr,
                         const T &values, const std::vector<float> &times,
                         const std::string &startTime,
                         const std::string &units = "") {
    auto logGroup =
        createLogGroup<T>(name, typeStr, values, times, startTime, units);
    m_framelogJson["children"].push_back(logGroup);
  }

  // Can be called multiple times to add more users
  void addUser(const std::string &name, const std::string &affiliation);

private:
  void initEntryGroupJson();
  void addInstrument(const std::string &instrumentNameStr);
  void addRunCycle(const std::string &runCycleStr);
  void addRunNumber(int32_t runNumber);
  void addStartTime();
  void initIsisVmsCompat();
  void initFramelog();
  void initRunlog();

  nlohmann::json createStream(const std::string &module,
                              const std::string &nexusPath,
                              const std::string &source,
                              const std::string &topic) const;

  nlohmann::json createInstrumentNameJson(const std::string &instrumentNameStr);
  nlohmann::json createBeamlineJson(const std::string &beamlineName);

  const std::string m_jobID;
  const std::string m_instrumentName;
  const std::string m_broker;
  const std::string m_filename;
  const std::string m_startTimeIso8601;
  nlohmann::json m_entryGroupJson;
  nlohmann::json m_isisVmsCompatJson;
  nlohmann::json m_framelogJson;
  nlohmann::json m_runlogJson;
  uint32_t m_numberOfUsers = 0;
};
