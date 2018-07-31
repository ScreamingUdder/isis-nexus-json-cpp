#include "NexusWriteCommandBuilder.h"

using json = nlohmann::json;

NexusWriteCommandBuilder::NexusWriteCommandBuilder(
    const std::string &instrumentName, const int32_t runNumber,
    const std::string &broker, const std::string &runCycle)
    : m_jobID(instrumentName + "_" + std::to_string(runNumber)) {
  const std::string filename =
      instrumentName + "_" + std::to_string(runNumber) + ".nxs";
  initStartMessageJson(broker, filename, instrumentName);
  addRunCycle(runCycle);
  addRunNumber(runNumber);
  addInstrument(instrumentName);
}

void NexusWriteCommandBuilder::addStartTime(
    const std::string &startTimeIso8601) {
  auto dataset =
      createDataset<std::string>("start_time", "string", startTimeIso8601,
                                 {Attribute{"units", "ISO8601"}});
  m_startMessageJson["nexus_structure"]["children"][0]["children"].push_back(
      dataset);
}

void NexusWriteCommandBuilder::addEndTime(
    const std::string &endTimeIso8601) {
  auto dataset =
      createDataset<std::string>("end_time", "string", endTimeIso8601,
                                 {Attribute{"units", "ISO8601"}});
  m_startMessageJson["nexus_structure"]["children"][0]["children"].push_back(
      dataset);
}

void NexusWriteCommandBuilder::addTitle(const std::string &title) {
  auto dataset = createDataset<std::string>("title", "string", title);
  m_startMessageJson["nexus_structure"]["children"][0]["children"].push_back(
      dataset);
}

void NexusWriteCommandBuilder::addTotalCounts(const uint64_t totalCounts) {
  auto dataset = createDataset<uint64_t>("total_counts", "uint64", totalCounts);
  m_startMessageJson["nexus_structure"]["children"][0]["children"].push_back(
      dataset);
}

void NexusWriteCommandBuilder::addMonitorEventsNotSaved(
    const int64_t monitorEventsNotSaved) {
  auto dataset = createDataset<int64_t>("monitor_events_not_saved", "int64",
                                        monitorEventsNotSaved);
  m_startMessageJson["nexus_structure"]["children"][0]["children"].push_back(
      dataset);
}

void NexusWriteCommandBuilder::addTotalUncountedCounts(
    const int32_t uncountedCounts) {
  auto dataset = createDataset<int32_t>("total_uncounted_counts", "int32",
                                        uncountedCounts);
  m_startMessageJson["nexus_structure"]["children"][0]["children"].push_back(
      dataset);
}

void NexusWriteCommandBuilder::addRunNumber(const int32_t runNumber) {
  auto dataset = createDataset<int32_t>("run_number", "int32", runNumber);
  m_startMessageJson["nexus_structure"]["children"][0]["children"].push_back(
      dataset);
}

void NexusWriteCommandBuilder::addMeasurementLabel(
    const std::string &measurementLabel) {
  auto dataset =
      createDataset<std::string>("title", "string", measurementLabel);
  m_startMessageJson["nexus_structure"]["children"][0]["children"].push_back(
      dataset);
}

void NexusWriteCommandBuilder::addMeasurementID(
    const std::string &measurementID) {
  auto dataset = createDataset<std::string>("title", "string", measurementID);
  m_startMessageJson["nexus_structure"]["children"][0]["children"].push_back(
      dataset);
}

void NexusWriteCommandBuilder::addSeciConfig(const std::string &SeciConfig) {
  auto dataset = createDataset<std::string>("title", "string", SeciConfig);
  m_startMessageJson["nexus_structure"]["children"][0]["children"].push_back(
      dataset);
}

void NexusWriteCommandBuilder::addUser(const std::string &name,
                                       const std::string &affiliation) {
  m_numberOfUsers++;
  auto userGroup = createGroup("user_" + std::to_string(m_numberOfUsers),
                               {{"NX_class", "NXuser"}});
  userGroup["children"].push_back(createDataset("name", "string", name));
  userGroup["children"].push_back(
      createDataset("affiliation", "string", affiliation));

  m_startMessageJson["nexus_structure"]["children"][0]["children"].push_back(
      userGroup);
}

void NexusWriteCommandBuilder::addDetector(uint32_t detectorNumber,
                                           float sourceDetectorDistance) {
  auto detectorGroup = createGroup("detector_" + std::to_string(detectorNumber),
                                   {{"NX_class", "NXdetector"}});
  detectorGroup["children"].push_back(createDataset<float>(
      "source_detector_distance", "float", sourceDetectorDistance));
  detectorGroup["children"].push_back(createGroup("period_index"));

  for (auto &node :
       m_startMessageJson["nexus_structure"]["children"][0]["children"]) {
    if (node["name"] == "instrument") {
      node["children"].push_back(detectorGroup);
    }
  }
}

void NexusWriteCommandBuilder::initStartMessageJson(
    const std::string &broker, const std::string &filename,
    const std::string &instrumentName) {
  // clang-format off
  m_startMessageJson = R"({
    "nexus_structure": {
      "children": [
        {
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
                  "values": "IXselog"
                }
              ],
              "children": [
                {
                  "stream": {
                    "writer_module": "f142",
                    "nexus_path": "/raw_data_1/selog",
                    "source": "FakePV",
                    "topic": "TEST_sampleEnv"
                  },
                  "type": "stream"
                }
              ],
              "type": "group",
              "name": "selog"
            },
            {
              "attributes": [
                {
                  "name": "NX_class",
                  "values": "NXevent_data"
                }
              ],
              "children": [
                {
                  "stream": {
                    "writer_module": "ev42",
                    "nexus_path": "/raw_data_1/detector_1_events",
                    "source": "MUST MATCH SOURCE NAME SET IN ICP",
                    "topic": "INSTR_events"
                  },
                  "type": "stream"
                }
              ],
              "type": "group",
              "name": "detector_1_events"
            },
            {
              "attributes": [
                {
                  "name": "NX_class",
                  "values": "NXdata"
                }
              ],
              "children": [
                {
                  "children": [],
                  "type": "group",
                  "name": "period_index"
                }
              ],
              "type": "group",
              "name": "detector_1"
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
                  "dataset": {
                    "type": "string"
                  },
                  "type": "dataset",
                  "name": "id",
                  "values": " "
                },
                {
                  "dataset": {
                    "type": "string"
                  },
                  "type": "dataset",
                  "name": "type",
                  "values": " "
                },
                {
                  "dataset": {
                    "type": "string"
                  },
                  "type": "dataset",
                  "name": "label",
                  "values": " "
                },
                {
                  "dataset": {
                    "type": "string"
                  },
                  "type": "dataset",
                  "name": "subid",
                  "values": " "
                },
                {
                  "dataset": {
                    "type": "int32"
                  },
                  "type": "dataset",
                  "name": "first_run",
                  "values": 0
                }
              ],
              "type": "group",
              "name": "measurement"
            },
            {
              "dataset": {
                "type": "string"
              },
              "type": "dataset",
              "name": "measurement_subid",
              "values": " "
            },
            {
              "attributes": [
                {
                  "name": "units",
                  "values": "second"
                }
              ],
              "dataset": {
                "type": "float"
              },
              "type": "dataset",
              "name": "collection_time",
              "values": 1837.0
            },
            {
              "attributes": [
                {
                  "name": "version",
                  "values": "SVN R1959 (2018/06/13 13:15:08, Mixed revision WC 1958:1959, Modified) "
                }
              ],
              "dataset": {
                "type": "string"
              },
              "type": "dataset",
              "name": "program_name",
              "values": "ISISICP.EXE"
            },
            {
              "attributes": [
                {
                  "name": "version",
                  "values": "1.0"
                },
                {
                  "name": "url",
                  "values": "http://definition.nexusformat.org/instruments/TOFRAW?version=1.0"
                }
              ],
              "dataset": {
                "type": "string"
              },
              "type": "dataset",
              "name": "definition",
              "values": "TOFRAW"
            },
            {
              "dataset": {
                "type": "string"
              },
              "type": "dataset",
              "name": "experiment_identifier",
              "values": "0"
            },
            {
              "dataset": {
                "type": "int32"
              },
              "type": "dataset",
              "name": "good_frames",
              "values": 18234
            },
            {
              "dataset": {
                "type": "string"
              },
              "type": "dataset",
              "name": "measurement_type",
              "values": " "
            },
            {
              "dataset": {
                "type": "int32"
              },
              "type": "dataset",
              "name": "measurement_first_run",
              "values": 0
            },
            {
              "dataset": {
                "type": "string"
              },
              "type": "dataset",
              "name": "script_name",
              "values": " "
            },
            {
              "attributes": [
                {
                  "name": "units",
                  "values": "second"
                }
              ],
              "dataset": {
                "type": "float"
              },
              "type": "dataset",
              "name": "duration",
              "values": 1837.0
            },
            {
              "attributes": [
                {
                  "name": "units",
                  "values": "uAh"
                }
              ],
              "dataset": {
                "type": "float"
              },
              "type": "dataset",
              "name": "proton_charge",
              "values": 20.061872482299805
            },
            {
              "attributes": [
                {
                  "name": "version",
                  "values": "1.0"
                },
                {
                  "name": "url",
                  "values": "http://svn.isis.rl.ac.uk/instruments/ISISTOFRAW?version=1.0"
                }
              ],
              "dataset": {
                "type": "string"
              },
              "type": "dataset",
              "name": "definition_local",
              "values": "ISISTOFRAW"
            },
            {
              "dataset": {
                "type": "int32"
              },
              "type": "dataset",
              "name": "raw_frames",
              "values": 18234
            },
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
                  "values": "IXvms"
                }
              ],
              "children": [
                {
                  "stream": {
                    "writer_module": "AAAAA",
                    "nexus_path": "/raw_data_1/isis_vms_compat",
                    "type": "AAAAA",
                    "source": "AAAAA",
                    "topic": "AAAAA"
                  },
                  "type": "stream"
                }
              ],
              "type": "group",
              "name": "isis_vms_compat"
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
                    "nexus_path": "/raw_data_1/runlog",
                    "source": "MUST MATCH SOURCE NAME SET IN ICP",
                    "topic": "INSTR_framelog"
                  },
                  "type": "stream"
                }
              ],
              "type": "group",
              "name": "framelog"
            },
            {
              "dataset": {
                "type": "string"
              },
              "type": "dataset",
              "name": "notes",
              "values": " "
            },
            {
              "attributes": [
                {
                  "name": "NX_class",
                  "values": "IXperiods"
                }
              ],
              "children": [
                {
                  "dataset": {
                    "type": "int32"
                  },
                  "type": "dataset",
                  "name": "output",
                  "values": 0
                },
                {
                  "attributes": [
                    {
                      "name": "units",
                      "values": "Mev"
                    }
                  ],
                  "dataset": {
                    "type": "float"
                  },
                  "type": "dataset",
                  "name": "total_counts",
                  "values": 21.20301055908203
                },
                {
                  "attributes": [
                    {
                      "name": "units",
                      "values": "uAh"
                    }
                  ],
                  "dataset": {
                    "type": "float"
                  },
                  "type": "dataset",
                  "name": "proton_charge",
                  "values": 20.061872482299805
                },
                {
                  "dataset": {
                    "type": "int32"
                  },
                  "type": "dataset",
                  "name": "good_frames_daq",
                  "values": 18234
                },
                {
                  "dataset": {
                    "type": "int32"
                  },
                  "type": "dataset",
                  "name": "sequences",
                  "values": 1
                },
                {
                  "dataset": {
                    "type": "int32"
                  },
                  "type": "dataset",
                  "name": "frames_requested",
                  "values": 0
                },
                {
                  "dataset": {
                    "type": "int32"
                  },
                  "type": "dataset",
                  "name": "good_frames",
                  "values": 18234
                },
                {
                  "dataset": {
                    "type": "int32"
                  },
                  "type": "dataset",
                  "name": "number",
                  "values": 1
                },
                {
                  "dataset": {
                    "type": "int32"
                  },
                  "type": "dataset",
                  "name": "highest_used",
                  "values": 1
                },
                {
                  "dataset": {
                    "type": "string"
                  },
                  "type": "dataset",
                  "name": "labels",
                  "values": "Period 1"
                },
                {
                  "attributes": [
                    {
                      "name": "units",
                      "values": "uAh"
                    }
                  ],
                  "dataset": {
                    "type": "float"
                  },
                  "type": "dataset",
                  "name": "proton_charge_raw",
                  "values": 20.061872482299805
                },
                {
                  "dataset": {
                    "type": "int32"
                  },
                  "type": "dataset",
                  "name": "type",
                  "values": 1
                },
                {
                  "dataset": {
                    "type": "int32"
                  },
                  "type": "dataset",
                  "name": "raw_frames",
                  "values": 18234
                }
              ],
              "type": "group",
              "name": "periods"
            },
            {
              "attributes": [
                {
                  "name": "units",
                  "values": "uAh"
                }
              ],
              "dataset": {
                "type": "float"
              },
              "type": "dataset",
              "name": "proton_charge_raw",
              "values": 20.061872482299805
            }
          ],
          "type": "group",
          "name": "raw_data_1"
        }
      ]
    },
    "cmd": "FileWriter_new"
  })"_json;
  // clang-format on
  m_startMessageJson["broker"] = broker;
  m_startMessageJson["job_id"] = m_jobID;
  m_startMessageJson["file_attributes"] = {"file_name", filename};

  m_startMessageJson["nexus_structure"]["children"][0]["children"].push_back(
      createInstrumentNameJson(instrumentName));
  m_startMessageJson["nexus_structure"]["children"][0]["children"].push_back(
      createBeamlineJson(instrumentName));
}

json NexusWriteCommandBuilder::createBeamlineJson(
    const std::string &beamlineName) {
  return createDataset<std::string>("beamline", "string", beamlineName);
}

void NexusWriteCommandBuilder::addRunCycle(const std::string &runCycleStr) {
  auto runCycle =
      createDataset<std::string>("run_cycle", "string", runCycleStr);
  m_startMessageJson["nexus_structure"]["children"][0]["children"].push_back(
      runCycle);
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

  m_startMessageJson["nexus_structure"]["children"][0]["children"].push_back(
      sampleGroup);
}

json NexusWriteCommandBuilder::createNode(
    const std::string &name, const NodeType nodeType,
    const std::vector<Attribute> &attributes) const {
  auto node = json::object();

  node["name"] = name;

  if (nodeType == NodeType::DATASET) {
    node["type"] = "dataset";
  } else if (nodeType == NodeType::GROUP) {
    node["type"] = "group";
    node["children"] = json::array();
  } else {
    throw std::runtime_error(
        "Unhandled NodeType in NexusWriteCommandBuilder::createNode()");
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
json NexusWriteCommandBuilder::createDataset(
    const std::string &name, const std::string &typeStr, T value,
    const std::vector<Attribute> &attributes) {
  auto dataset = createNode(name, NodeType::DATASET, attributes);
  std::stringstream strStream;
  strStream << value;
  dataset["values"] = strStream.str();
  dataset["dataset"] = {"type", typeStr};

  return dataset;
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

  m_startMessageJson["nexus_structure"]["children"][0]["children"].push_back(
      instrumentGroup);
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

  m_startMessageJson["nexus_structure"]["children"][0]["children"].push_back(
      monitorGroup);
}

void NexusWriteCommandBuilder::addSampleEnvLog(const std::string &name) {}

std::string NexusWriteCommandBuilder::startMessageAsString() {
  return m_startMessageJson.dump(4);
}

std::string NexusWriteCommandBuilder::stopMessageAsString() {
  json stopMessageJson = {{"job_id", m_jobID}, {"cmd", "FileWriter_stop"}};
  return stopMessageJson.dump(4);
}
