#pragma once

#include <nlohmann/json.hpp>

namespace {

struct Attribute {
  const std::string name;
  const std::string value;
};

enum class NodeType { DATASET, GROUP };
}

class NexusWriteCommandBuilder {
public:
  NexusWriteCommandBuilder(const std::string &instrumentName, int32_t runNumber,
                           const std::string &broker,
                           const std::string &runCycle);

  // Get the output command messages as strings
  std::string startMessageAsString();
  std::string stopMessageAsString();

  // Add stuff to the file
  void addMonitor(uint32_t monitorNumber, uint32_t spectrumNumber);
  void addSample(float height, float thickness, float width,
                 double distance = 0.0, const std::string &shape = "",
                 const std::string &name = "", const std::string &type = "",
                 const std::string &id = "");
  void addStartTime(const std::string &startTimeIso8601);
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
  void addEventData(uint32_t detectorNumber, const std::string &sourceName);
  void addSELogData(const std::vector<std::string> &pVs);
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

  // Can be called multiple times to add more users
  void addUser(const std::string &name, const std::string &affiliation);

private:
  void initStartMessageJson(const std::string &broker,
                            const std::string &filename,
                            const std::string &instrumentName);
  void addInstrument(const std::string &instrumentNameStr);
  void addRunCycle(const std::string &runCycleStr);
  void addRunNumber(int32_t runNumber);

  template <typename T>
  nlohmann::json createDataset(const std::string &name,
                               const std::string &typeStr, T value,
                               const std::vector<Attribute> &attributes = {});

  nlohmann::json createGroup(const std::string &name,
                             const std::vector<Attribute> &attributes = {});

  nlohmann::json createNode(const std::string &name, NodeType nodeType,
                            const std::vector<Attribute> &attributes) const;

  nlohmann::json createStream(const std::string &module,
                              const std::string &nexusPath,
                              const std::string &source,
                              const std::string &topic) const;

  nlohmann::json createInstrumentNameJson(const std::string &instrumentNameStr);
  nlohmann::json createBeamlineJson(const std::string &beamlineName);

  const std::string m_jobID;
  const std::string m_instrumentName;
  nlohmann::json m_startMessageJson;
  uint32_t m_numberOfUsers = 0;
};
