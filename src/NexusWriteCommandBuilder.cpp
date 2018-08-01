#include "NexusWriteCommandBuilder.h"

using json = nlohmann::json;

namespace {

std::vector<std::string> split(const std::string &s, char delimiter) {
  std::vector<std::string> tokens;
  std::string token;
  std::istringstream tokenStream(s);
  while (std::getline(tokenStream, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}
}

NexusWriteCommandBuilder::NexusWriteCommandBuilder(
    const std::string &instrumentName, const int32_t runNumber,
    const std::string &broker, const std::string &runCycle)
    : m_jobID(instrumentName + "_" + std::to_string(runNumber)),
      m_instrumentName(instrumentName), m_broker(broker),
      m_filename(instrumentName + "_" + std::to_string(runNumber) + ".nxs") {
  initEntryGroupJson();
  initIsisVmsCompat();
  addRunCycle(runCycle);
  addRunNumber(runNumber);
  addInstrument(instrumentName);
}

void NexusWriteCommandBuilder::addStartTime(
    const std::string &startTimeIso8601) {
  auto dataset =
      createDataset<std::string>("start_time", "string", startTimeIso8601,
                                 {Attribute{"units", "ISO8601"}});
  m_entryGroupJson["children"].push_back(dataset);
}

void NexusWriteCommandBuilder::addEndTime(const std::string &endTimeIso8601) {
  auto dataset = createDataset<std::string>(
      "end_time", "string", endTimeIso8601, {Attribute{"units", "ISO8601"}});
  m_entryGroupJson["children"].push_back(dataset);
}

void NexusWriteCommandBuilder::addTitle(const std::string &title) {
  auto dataset = createDataset<std::string>("title", "string", title);
  m_entryGroupJson["children"].push_back(dataset);
}

void NexusWriteCommandBuilder::addTotalCounts(const uint64_t totalCounts) {
  auto dataset = createDataset<uint64_t>("total_counts", "uint64", totalCounts);
  m_entryGroupJson["children"].push_back(dataset);
}

void NexusWriteCommandBuilder::addMonitorEventsNotSaved(
    const int64_t monitorEventsNotSaved) {
  auto dataset = createDataset<int64_t>("monitor_events_not_saved", "int64",
                                        monitorEventsNotSaved);
  m_entryGroupJson["children"].push_back(dataset);
}

void NexusWriteCommandBuilder::addTotalUncountedCounts(
    const int32_t uncountedCounts) {
  auto dataset = createDataset<int32_t>("total_uncounted_counts", "int32",
                                        uncountedCounts);
  m_entryGroupJson["children"].push_back(dataset);
}

void NexusWriteCommandBuilder::addRunNumber(const int32_t runNumber) {
  auto dataset = createDataset<int32_t>("run_number", "int32", runNumber);
  m_entryGroupJson["children"].push_back(dataset);
}

void NexusWriteCommandBuilder::addSeciConfig(const std::string &SeciConfig) {
  auto dataset =
      createDataset<std::string>("seci_config", "string", SeciConfig);
  m_entryGroupJson["children"].push_back(dataset);
}

void NexusWriteCommandBuilder::addProgramName(const std::string &programName,
                                              const std::string &version) {
  auto dataset = createDataset<std::string>(
      "program_name", "string", programName, {{"version", version}});
  m_entryGroupJson["children"].push_back(dataset);
}

void NexusWriteCommandBuilder::addNexusDefinition(const std::string &name,
                                                  const std::string &version,
                                                  const std::string &url) {
  auto dataset = createDataset<std::string>(
      "definition", "string", name, {{"version", version}, {"url", url}});
  m_entryGroupJson["children"].push_back(dataset);
}

void NexusWriteCommandBuilder::addLocalNexusDefinition(
    const std::string &name, const std::string &version,
    const std::string &url) {
  auto dataset = createDataset<std::string>(
      "definition_local", "string", name, {{"version", version}, {"url", url}});
  m_entryGroupJson["children"].push_back(dataset);
}

void NexusWriteCommandBuilder::addNotes(const std::string &notes) {
  auto dataset = createDataset<std::string>("notes", "string", notes);
  m_entryGroupJson["children"].push_back(dataset);
}

void NexusWriteCommandBuilder::addProtonChargeRawInMicroAmpHours(
    float protonCharge) {
  auto dataset = createDataset<float>("proton_charge_raw", "float",
                                      protonCharge, {{"units", "uAh"}});
  m_entryGroupJson["children"].push_back(dataset);
}

void NexusWriteCommandBuilder::addProtonChargeInMicroAmpHours(
    float protonCharge) {
  auto dataset = createDataset<float>("proton_charge", "float", protonCharge,
                                      {{"units", "uAh"}});
  m_entryGroupJson["children"].push_back(dataset);
}

void NexusWriteCommandBuilder::addCollectionTime(
    float collectionTimeInSeconds) {
  auto dataset =
      createDataset<float>("collection_time", "float", collectionTimeInSeconds,
                           {{"units", "second"}});
  m_entryGroupJson["children"].push_back(dataset);
}

void NexusWriteCommandBuilder::addDuration(float durationInSeconds) {
  auto dataset = createDataset<float>("duration", "float", durationInSeconds,
                                      {{"units", "second"}});
  m_entryGroupJson["children"].push_back(dataset);
}

void NexusWriteCommandBuilder::addUser(const std::string &name,
                                       const std::string &affiliation) {
  m_numberOfUsers++;
  auto userGroup = createGroup("user_" + std::to_string(m_numberOfUsers),
                               {{"NX_class", "NXuser"}});
  userGroup["children"].push_back(createDataset("name", "string", name));
  userGroup["children"].push_back(
      createDataset("affiliation", "string", affiliation));

  m_entryGroupJson["children"].push_back(userGroup);
}

void NexusWriteCommandBuilder::addDetector(uint32_t detectorNumber,
                                           float sourceDetectorDistance) {
  auto detectorGroup = createGroup("detector_" + std::to_string(detectorNumber),
                                   {{"NX_class", "NXdetector"}});
  detectorGroup["children"].push_back(createDataset<float>(
      "source_detector_distance", "float", sourceDetectorDistance));
  detectorGroup["children"].push_back(createGroup("period_index"));

  for (auto &node : m_entryGroupJson["children"]) {
    if (node["name"] == "instrument") {
      node["children"].push_back(detectorGroup);
    }
  }
}

void NexusWriteCommandBuilder::addMeasurement(const std::string &label,
                                              const std::string &id,
                                              const std::string &subId,
                                              const std::string &type,
                                              int32_t firstRun) {
  auto measurementGroup =
      createGroup("measurement", {{"NX_class", "NXcollection"}});
  measurementGroup["children"].push_back(
      createDataset<std::string>("id", "string", id));
  measurementGroup["children"].push_back(
      createDataset<std::string>("subid", "string", subId));
  measurementGroup["children"].push_back(
      createDataset<std::string>("type", "string", type));
  measurementGroup["children"].push_back(
      createDataset<std::string>("label", "string", label));
  measurementGroup["children"].push_back(
      createDataset<int32_t>("label", "int32", firstRun));

  m_entryGroupJson["children"].push_back(measurementGroup);
  m_entryGroupJson["children"].push_back(
      createDataset<std::string>("measurement_label", "string", label));
  m_entryGroupJson["children"].push_back(
      createDataset<std::string>("measurement_id", "string", id));
  m_entryGroupJson["children"].push_back(
      createDataset<std::string>("measurement_subid", "string", subId));
  m_entryGroupJson["children"].push_back(
      createDataset<std::string>("measurement_type", "string", type));
  m_entryGroupJson["children"].push_back(
      createDataset<int32_t>("measurement_first_run", "int32", firstRun));
}

json NexusWriteCommandBuilder::createStream(const std::string &module,
                                            const std::string &nexusPath,
                                            const std::string &source,
                                            const std::string &topic) const {
  json stream = {{"type", "stream"}};
  stream["stream"] = {{"writer_module", module},
                      {"nexus_path", nexusPath},
                      {"source", source},
                      {"topic", topic}};

  return stream;
}

void NexusWriteCommandBuilder::addEventData(uint32_t detectorNumber,
                                            const std::string &sourceName) {
  auto eventDataStream =
      createStream("ev42", "/raw_data_1/detector_" +
                               std::to_string(detectorNumber) + "_events",
                   sourceName, m_instrumentName + "_events");

  m_entryGroupJson["children"].push_back(eventDataStream);
}

void NexusWriteCommandBuilder::addSELogData(
    const std::vector<std::string> &pVs) {
  const std::string topicName = m_instrumentName + "_sampleEnv";
  auto selogGroup = createGroup("selog", {{"NX_class", "IXselog"}});

  for (const auto &pv : pVs) {
    auto splitPV = split(pv, ':');
    selogGroup["children"].push_back(createStream(
        "f142", "/raw_data_1/selog/" + splitPV.back(), pv, topicName));
  }
  m_entryGroupJson["children"].push_back(selogGroup);
}

void NexusWriteCommandBuilder::addPeriods(
    int32_t output, float totalCountsInMegaElectronVolts,
    float protonChargeInMicroAmpHours, int32_t goodFramesDaq, int32_t sequences,
    int32_t framesRequested, int32_t goodFrames, int32_t number,
    int32_t highestUsed, const std::string &labels,
    float protonChargeRawInMicroAmpHours, int32_t type, int32_t rawFrames) {
  auto periodsGroup = createGroup("periods", {{"NX_class", "IXperiods"}});
  periodsGroup["children"].push_back(
      createDataset<int32_t>("output", "int32", output));
  periodsGroup["children"].push_back(
      createDataset<float>("total_counts", "int32",
                           totalCountsInMegaElectronVolts, {{"units", "Mev"}}));
  periodsGroup["children"].push_back(
      createDataset<float>("proton_charge", "float",
                           protonChargeInMicroAmpHours, {{"units", "uAh"}}));
  periodsGroup["children"].push_back(
      createDataset<int32_t>("good_frames_daq", "int32", goodFramesDaq));
  periodsGroup["children"].push_back(
      createDataset<int32_t>("sequences", "int32", sequences));
  periodsGroup["children"].push_back(
      createDataset<int32_t>("frames_requested", "int32", framesRequested));
  periodsGroup["children"].push_back(
      createDataset<int32_t>("good_frames", "int32", goodFrames));
  periodsGroup["children"].push_back(
      createDataset<int32_t>("number", "int32", number));
  periodsGroup["children"].push_back(
      createDataset<int32_t>("highest_used", "int32", highestUsed));
  periodsGroup["children"].push_back(
      createDataset<std::string>("output", "string", labels));
  periodsGroup["children"].push_back(
      createDataset<float>("proton_charge_raw", "float",
                           protonChargeRawInMicroAmpHours, {{"units", "uAh"}}));
  periodsGroup["children"].push_back(
      createDataset<int32_t>("type", "int32", type));
  periodsGroup["children"].push_back(
      createDataset<int32_t>("raw_frames", "int32", rawFrames));

  m_entryGroupJson["children"].push_back(periodsGroup);
  m_entryGroupJson["children"].push_back(
      createDataset<int32_t>("good_frames", "int32", goodFrames));
  m_entryGroupJson["children"].push_back(
      createDataset<int32_t>("raw_frames", "int32", rawFrames));
}

void NexusWriteCommandBuilder::addExperimentIdentifier(
    const std::string &experimentIdentifier) {
  m_entryGroupJson["children"].push_back(
      createDataset("experiment_identifier", "string", experimentIdentifier));
}

void NexusWriteCommandBuilder::addScriptName(const std::string &scriptName) {
  m_entryGroupJson["children"].push_back(
      createDataset("script_name", "string", scriptName));
}

void NexusWriteCommandBuilder::initIsisVmsCompat() {
  m_isisVmsCompatJson = createGroup("isis_vms_compat", {{"NX_class", "IXvms"}});
}

void NexusWriteCommandBuilder::initEntryGroupJson() {
  // clang-format off
  m_entryGroupJson = R"({
    "attributes": [
      {
        "name": "NX_class",
        "values": "NXentry"
      }
    ],
    "children": [
      {
        "attributes": [
          {
            "name": "NX_class",
            "values": "IXrunlog"
          }
        ],
        "children": [
          {
            "stream": {
              "writer_module": "f142",
              "nexus_path": "/raw_data_1/runlog",
              "source": "MUST MATCH SOURCE NAME SET IN ICP",
              "topic": "INSTR_runlog"
            },
            "type": "stream"
          }
        ],
        "type": "group",
        "name": "runlog"
      },
      {
        "attributes": [
          {
            "name": "NX_class",
            "values": "NXcollection"
          }
        ],
        "children": [
          {
            "stream": {
              "writer_module": "f142",
              "nexus_path": "/raw_data_1/framelog",
              "source": "MUST MATCH SOURCE NAME SET IN ICP",
              "topic": "INSTR_framelog"
            },
            "type": "stream"
          }
        ],
        "type": "group",
        "name": "framelog"
      }
    ],
    "type": "group",
    "name": "raw_data_1"
  })"_json;
  // clang-format on
}

json NexusWriteCommandBuilder::createBeamlineJson(
    const std::string &beamlineName) {
  return createDataset<std::string>("beamline", "string", beamlineName);
}

void NexusWriteCommandBuilder::addRunCycle(const std::string &runCycleStr) {
  auto runCycle =
      createDataset<std::string>("run_cycle", "string", runCycleStr);
  m_entryGroupJson["children"].push_back(runCycle);
}

void NexusWriteCommandBuilder::addSample(float height, float thickness,
                                         float width, double distance,
                                         const std::string &shape,
                                         const std::string &name,
                                         const std::string &type,
                                         const std::string &id) {
  auto sampleGroup = createGroup("sample", {{"NX_class", "NXsample"}});

  sampleGroup["children"].push_back(
      createDataset<float>("height", "float", height));
  sampleGroup["children"].push_back(
      createDataset<float>("thickness", "float", thickness));
  sampleGroup["children"].push_back(
      createDataset<float>("width", "float", width));
  sampleGroup["children"].push_back(
      createDataset<std::string>("shape", "string", shape));
  sampleGroup["children"].push_back(
      createDataset<std::string>("name", "string", name));
  sampleGroup["children"].push_back(
      createDataset<double>("distance", "string", distance));
  sampleGroup["children"].push_back(
      createDataset<std::string>("type", "string", type));
  sampleGroup["children"].push_back(
      createDataset<std::string>("id", "string", id));

  m_entryGroupJson["children"].push_back(sampleGroup);
}

json NexusWriteCommandBuilder::createGroup(
    const std::string &name, const std::vector<Attribute> &attributes) {
  return createNode(name, NodeType::GROUP, attributes);
}

void NexusWriteCommandBuilder::addInstrument(
    const std::string &instrumentNameStr) {

  auto moderatorGroup = createGroup("moderator", {{"NX_class", "NXmoderator"}});
  moderatorGroup["children"].push_back(
      createDataset<float>("distance", "float", 0.0, {{"units", "metre"}}));

  auto sourceGroup = createGroup("source", {{"NX_class", "NXsource"}});
  sourceGroup["children"].push_back(
      createDataset<std::string>("probe", "string", "neutrons"));
  sourceGroup["children"].push_back(
      createDataset<std::string>("type", "string", "Pulsed Neutron Source"));
  sourceGroup["children"].push_back(
      createDataset<std::string>("name", "string", "ISIS"));

  auto instrumentGroup =
      createGroup("instrument", {{"NX_class", "NXinstrument"}});
  instrumentGroup["children"].push_back(moderatorGroup);
  instrumentGroup["children"].push_back(sourceGroup);

  instrumentGroup["children"].push_back(
      createInstrumentNameJson(instrumentNameStr));

  m_entryGroupJson["children"].push_back(instrumentGroup);
}

json NexusWriteCommandBuilder::createInstrumentNameJson(
    const std::string &instrumentNameStr) {
  return createDataset<std::string>(
      "name", "string", instrumentNameStr,
      {{"short_name", instrumentNameStr.substr(0, 3)}});
}

void NexusWriteCommandBuilder::addMonitor(uint32_t monitorNumber,
                                          uint32_t spectrumIndex) {
  const std::string monitorName = "monitor_" + std::to_string(monitorNumber);

  auto monitorGroup = createGroup(monitorName, {{"NX_class", "NXmonitor"}});
  monitorGroup["children"].push_back(
      createDataset<int32_t>("monitor_number", "int32", monitorNumber));
  monitorGroup["children"].push_back(
      createDataset<int32_t>("spectrum_index", "int32", spectrumIndex));
  monitorGroup["children"].push_back(createGroup("period_index"));

  m_entryGroupJson["children"].push_back(monitorGroup);
}

std::string NexusWriteCommandBuilder::startMessageAsString() {
  json nexusStructureJson = {{"children", json::array()}};
  nexusStructureJson["children"].push_back(m_entryGroupJson);
  json startMessageJson = {{"cmd", "FileWriter_new"},
                           {"broker", m_broker},
                           {"job_id", m_jobID},
                           {"nexus_structure", nexusStructureJson},
                           {"file_attributes", {"file_name", m_filename}}};

  startMessageJson["nexus_structure"]["children"][0]["children"].push_back(
      createInstrumentNameJson(m_instrumentName));
  startMessageJson["nexus_structure"]["children"][0]["children"].push_back(
      createBeamlineJson(m_instrumentName));
  startMessageJson["nexus_structure"]["children"][0]["children"].push_back(
      m_isisVmsCompatJson);
  return startMessageJson.dump(4);
}

std::string NexusWriteCommandBuilder::stopMessageAsString() {
  json stopMessageJson = {{"job_id", m_jobID}, {"cmd", "FileWriter_stop"}};
  return stopMessageJson.dump(4);
}
