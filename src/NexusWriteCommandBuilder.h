#pragma once

#include <nlohmann/json.hpp>

class NexusWriteCommandBuilder {
public:
  NexusWriteCommandBuilder(const std::string &instrumentName,
                           const std::string &filename,
                           const std::string &jobID, const std::string &broker,
                           const std::string &runCycle);
  std::string startMessageAsString();
  std::string stopMessageAsString();
  void addSampleEnvLog(const std::string &name);
  void addMonitor(uint32_t monitorNumber, uint32_t spectrumNumber);
  void addSample(float height, float thickness, float width,
                 double distance = 0.0, const std::string &shape = "",
                 const std::string &name = "", const std::string &type = "",
                 const std::string &id = "");

private:
  void initStartMessageJson(const std::string &broker,
                            const std::string &filename,
                            const std::string &instrumentName);
  void addInstrument(const std::string &instrumentNameStr);
  void addRunCycle(const std::string &runCycleStr);

  template <typename T>
  nlohmann::json createSimpleDataset(const std::string &name,
                                     const std::string &typeStr, T value) const;
  nlohmann::json
  createInstrumentNameJson(const std::string &instrumentNameStr) const;
  nlohmann::json createBeamlineJson(const std::string &beamlineName) const;

  const std::string m_jobID;
  nlohmann::json m_startMessageJson;
};
