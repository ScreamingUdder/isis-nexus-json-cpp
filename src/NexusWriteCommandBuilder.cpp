#include "NexusWriteCommandBuilder.h"

using json = nlohmann::json;

NexusWriteCommandBuilder::NexusWriteCommandBuilder(
    const std::string &instrumentName, const std::string &filename,
    const std::string &jobID, const std::string &broker)
    : m_jobID(jobID) {
  initStartMessageJson(broker, filename);
}

void NexusWriteCommandBuilder::initStartMessageJson(
    const std::string &broker, const std::string &filename) {
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
                  "name": "units",
                  "values": "ISO8601"
                }
              ],
              "dataset": {
                "type": "string"
              },
              "type": "dataset",
              "name": "start_time",
              "values": "2018-07-06T09:47:44"
            },
            {
              "dataset": {
                "type": "string"
              },
              "type": "dataset",
              "name": "title",
              "values": "MT Beam A2=6mm SANS"
            },
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
                      "attributes": [
                        {
                          "name": "target",
                          "values": "/raw_data_1/instrument/detector_1/total_counts"
                        }
                      ],
                      "dataset": {
                        "type": "uint64"
                      },
                      "type": "dataset",
                      "name": "total_counts",
                      "values": 170700
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
                      "name": "short_name",
                      "values": "ZOO"
                    }
                  ],
                  "dataset": {
                    "type": "string"
                  },
                  "type": "dataset",
                  "name": "name",
                  "values": "ZOOM"
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
            },
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
              "dataset": {
                "type": "uint64"
              },
              "type": "dataset",
              "name": "total_counts",
              "values": 170700
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
              "dataset": {
                "type": "int64"
              },
              "type": "dataset",
              "name": "monitor_events_not_saved",
              "values": 0
            },
            {
              "dataset": {
                "type": "int32"
              },
              "type": "dataset",
              "name": "total_uncounted_counts",
              "values": 7629
            },
            {
              "dataset": {
                "type": "string"
              },
              "type": "dataset",
              "name": "measurement_label",
              "values": " "
            },
            {
              "dataset": {
                "type": "int32"
              },
              "type": "dataset",
              "name": "run_number",
              "values": 4112
            },
            {
              "dataset": {
                "type": "string"
              },
              "type": "dataset",
              "name": "seci_config",
              "values": " "
            },
            {
              "dataset": {
                "type": "string"
              },
              "type": "dataset",
              "name": "measurement_id",
              "values": " "
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
              "attributes": [
                {
                  "name": "NX_class",
                  "values": "NXsample"
                }
              ],
              "children": [
                {
                  "dataset": {
                    "type": "float"
                  },
                  "type": "dataset",
                  "name": "height",
                  "values": 6.0
                },
                {
                  "dataset": {
                    "type": "string"
                  },
                  "type": "dataset",
                  "name": "shape",
                  "values": " "
                },
                {
                  "dataset": {
                    "type": "string"
                  },
                  "type": "dataset",
                  "name": "name",
                  "values": " "
                },
                {
                  "dataset": {
                    "type": "double"
                  },
                  "type": "dataset",
                  "name": "distance",
                  "values": 0.0
                },
                {
                  "dataset": {
                    "type": "float"
                  },
                  "type": "dataset",
                  "name": "thickness",
                  "values": 1.0
                },
                {
                  "dataset": {
                    "type": "float"
                  },
                  "type": "dataset",
                  "name": "width",
                  "values": 6.0
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
                  "name": "id",
                  "values": " "
                }
              ],
              "type": "group",
              "name": "sample"
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
                  "name": "short_name",
                  "values": "ZOO"
                }
              ],
              "dataset": {
                "type": "string"
              },
              "type": "dataset",
              "name": "name",
              "values": "ZOOM"
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
                "type": "string"
              },
              "type": "dataset",
              "name": "beamline",
              "values": "ZOOM"
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
                "type": "string"
              },
              "type": "dataset",
              "name": "run_cycle",
              "values": "18_1"
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
    "broker": "BROKER",
    "cmd": "FileWriter_new",
    "job_id": "JOBID",
    "file_attributes": {
      "file_name": "FILENAME"
    }
  })"_json;
  // clang-format on
  m_startMessageJson["broker"] = broker;
  m_startMessageJson["job_id"] = m_jobID;
  m_startMessageJson["file_attributes"]["file_name"] = filename;
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
      "name": "MONITOR_NAME"
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

  m_startMessageJson["nexus_structure"]["children"].push_back(monitor);
}

void NexusWriteCommandBuilder::addSampleEnvLog(const std::string &name) {}

std::string NexusWriteCommandBuilder::startMessageAsString() {
  return m_startMessageJson.dump();
}

std::string NexusWriteCommandBuilder::stopMessageAsString() {
  json stopMessageJson = {{"job_id", m_jobID}, {"cmd", "FileWriter_stop"}};
  return stopMessageJson.dump();
}
