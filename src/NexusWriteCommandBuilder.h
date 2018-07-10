#pragma once

#include <nlohmann/json.hpp>

class NexusWriteCommandBuilder {
public:
  NexusWriteCommandBuilder(
      const std::string &instrumentName, const std::string &filename,
      const std::string &jobID,
      const std::string &broker = "livedata.isis.cclrc.ac.uk");
  std::string startMessageAsString();
  std::string stopMessageAsString();
  void addSampleEnvLog(const std::string &name);
  void addMonitor(uint32_t monitorNumber, uint32_t spectrumNumber);

private:
  void initStartMessageJson(const std::string &broker,
                            const std::string &filename);

  const std::string m_jobID;
  nlohmann::json m_startMessageJson;
};
