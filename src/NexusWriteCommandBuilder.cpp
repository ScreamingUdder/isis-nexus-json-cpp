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
                  "values": "NXuser"
                }
              ],
              "children": [
                {
                  "dataset": {
                    "type": "string"
                  },
                  "type": "dataset",
                  "name": "affiliation",
                  "values": " "
                },
                {
                  "dataset": {
                    "type": "string"
                  },
                  "type": "dataset",
                  "name": "name",
                  "values": " "
                }
              ],
              "type": "group",
              "name": "user_1"
            },
            {
              "attributes": [
                {
                  "name": "units",
                  "values": "ISO8601"
                }
              ],
              "dataset": {
                "type": "string"
              },
              "type": "dataset",
              "name": "end_time",
              "values": "2018-07-06T10:18:21"
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
    "broker": "PLACEHOLDER",
    "cmd": "FileWriter_new",
    "job_id": "PLACEHOLDER",
    "file_attributes": {
      "file_name": "PLACEHOLDER"
    }
  })"_json;
  // clang-format on
  m_startMessageJson["broker"] = broker;
  m_startMessageJson["job_id"] = m_jobID;
  m_startMessageJson["file_attributes"]["file_name"] = filename;

  m_startMessageJson["nexus_structure"]["children"][0]["children"].push_back(
      createInstrumentNameJson(instrumentName));
  m_startMessageJson["nexus_structure"]["children"][0]["children"].push_back(
      createBeamlineJson(instrumentName));
}

json NexusWriteCommandBuilder::createBeamlineJson(
    const std::string &beamlineName) const {
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
  // clang-format off
  auto sample = R"(
    {
      "attributes": [
        {
          "name": "NX_class",
          "values": "NXsample"
        }
      ],
      "children": [
      ],
      "type": "group",
      "name": "sample"
    }
  )"_json;
  // clang-format on

  sample["children"].push_back(createDataset<float>("height", "float", height));
  sample["children"].push_back(
      createDataset<float>("thickness", "float", thickness));
  sample["children"].push_back(createDataset<float>("width", "float", width));
  sample["children"].push_back(
      createDataset<std::string>("shape", "string", shape));
  sample["children"].push_back(
      createDataset<std::string>("name", "string", name));
  sample["children"].push_back(
      createDataset<double>("distance", "string", distance));
  sample["children"].push_back(
      createDataset<std::string>("type", "string", type));
  sample["children"].push_back(createDataset<std::string>("id", "string", id));

  m_startMessageJson["nexus_structure"]["children"][0]["children"].push_back(
      sample);
}

template <typename T>
json NexusWriteCommandBuilder::createDataset(const std::string &name,
                                             const std::string &typeStr,
                                             T value) const {
  // clang-format off
  auto dataset = R"(
    {
      "dataset": {
        "type": "PLACEHOLDER"
      },
      "type": "dataset",
      "name": "PLACEHOLDER",
      "values": "PLACEHOLDER"
    }
  )"_json;
  // clang-format on

  std::stringstream strStream;
  strStream << value;
  dataset["values"] = strStream.str();

  dataset["name"] = name;
  dataset["dataset"]["type"] = typeStr;

  return dataset;
}

template <typename T>
json NexusWriteCommandBuilder::createDataset(
    const std::string &name, const std::string &typeStr, T value,
    const std::vector<Attribute> &attributes) const {
  auto dataset = createDataset<T>(name, typeStr, value);
  dataset["attributes"] = {};
  for (const auto &attribute : attributes) {
    dataset["attributes"].push_back(
        {{"name", attribute.name}, {"values", attribute.value}});
  }
  return dataset;
}

void NexusWriteCommandBuilder::addInstrument(
    const std::string &instrumentNameStr) {
  // clang-format off
  auto instrument = R"(
    {
      "attributes": [
        {
          "name": "NX_class",
          "values": "NXinstrument"
        }
      ],
      "children": [
        {
          "attributes": [
            {
              "name": "NX_class",
              "values": "NXmoderator"
            }
          ],
          "children": [
            {
              "attributes": [
                {
                  "name": "units",
                  "values": "metre"
                }
              ],
              "dataset": {
                "type": "float"
              },
              "type": "dataset",
              "name": "distance",
              "values": -0.0
            }
          ],
          "type": "group",
          "name": "moderator"
        },
        {
          "attributes": [
            {
              "name": "NX_class",
              "values": "NXdetector"
            }
          ],
          "children": [
            {
              "dataset": {
                "type": "float"
              },
              "type": "dataset",
              "name": "source_detector_distance",
              "values": 0.0
            },
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
              "values": "NXsource"
            }
          ],
          "children": [
            {
              "dataset": {
                "type": "string"
              },
              "type": "dataset",
              "name": "probe",
              "values": "neutrons"
            },
            {
              "dataset": {
                "type": "string"
              },
              "type": "dataset",
              "name": "type",
              "values": "Pulsed Neutron Source"
            },
            {
              "dataset": {
                "type": "string"
              },
              "type": "dataset",
              "name": "name",
              "values": "ISIS"
            }
          ],
          "type": "group",
          "name": "source"
        }
      ],
      "type": "group",
      "name": "instrument"
    }
  )"_json;
  // clang-format on

  instrument["children"].push_back(createInstrumentNameJson(instrumentNameStr));

  m_startMessageJson["nexus_structure"]["children"][0]["children"].push_back(
      instrument);
}

json NexusWriteCommandBuilder::createInstrumentNameJson(
    const std::string &instrumentNameStr) const {
  // clang-format off
  auto instrumentName = R"(
  {
    "attributes": [
      {
        "name": "short_name",
        "values": "PLACEHOLDER"
      }
    ],
    "dataset": {
      "type": "string"
    },
    "type": "dataset",
    "name": "name",
    "values": "PLACEHOLDER"
  }
  )"_json;
  // clang-format on

  instrumentName["values"] = instrumentNameStr;
  instrumentName["attributes"][0]["values"] = instrumentNameStr.substr(0, 3);

  return instrumentName;
}

void NexusWriteCommandBuilder::addMonitor(uint32_t monitorNumber,
                                          uint32_t spectrumIndex) {
  const std::string monitorName = "monitor_" + std::to_string(monitorNumber);
  // clang-format off
  json monitor = R"(
    {
      "attributes": [
        {
          "name": "NX_class",
          "values": "NXmonitor"
        }
      ],
      "children": [
        {
          "dataset": {
            "type": "int32"
          },
          "type": "dataset",
          "name": "monitor_number",
          "values": 8
        },
        {
          "children": [],
          "type": "group",
          "name": "period_index"
        },
        {
          "dataset": {
            "type": "int32"
          },
          "type": "dataset",
          "name": "spectrum_index",
          "values": 8
        }
      ],
      "type": "group",
      "name": "PLACEHOLDER"
    })"_json;
  // clang-format on

  monitor["name"] = monitorName;
  for (auto &child : monitor["children"]) {
    if (child["name"] == "spectrum_index") {
      child["values"] = spectrumIndex;
    } else if (child["name"] == "monitor_number") {
      child["values"] = monitorNumber;
    }
  }

  m_startMessageJson["nexus_structure"]["children"][0]["children"].push_back(
      monitor);
}

void NexusWriteCommandBuilder::addSampleEnvLog(const std::string &name) {}

std::string NexusWriteCommandBuilder::startMessageAsString() {
  return m_startMessageJson.dump(4);
}

std::string NexusWriteCommandBuilder::stopMessageAsString() {
  json stopMessageJson = {{"job_id", m_jobID}, {"cmd", "FileWriter_stop"}};
  return stopMessageJson.dump(4);
}
