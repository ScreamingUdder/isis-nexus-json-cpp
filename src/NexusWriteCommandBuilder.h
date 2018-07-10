#pragma once

#include <nlohmann/json.hpp>

class NexusWriteCommandBuilder {
public:
  NexusWriteCommandBuilder(const std::string &instrumentName,
                           const std::string &filename,
                           const std::string &jobID, const std::string &broker);
  std::string startMessageAsString();
  std::string stopMessageAsString();
  void addSampleEnvLog(const std::string &name);

private:
  void initStartMessageJson();

  const std::string m_jobID;
  nlohmann::json m_startMessageJson;
};
