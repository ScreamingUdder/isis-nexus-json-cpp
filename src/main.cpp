#include "NexusWriteCommandBuilder.h"
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main() {
  const std::string instrumentName = "ZOOM";
  const std::string filename = "ZOOM_782582.nxs";
  // jobID must match in start and stop message
  // It must be unique (could be generated UUID)
  const std::string jobID = "ZOOM_782582";
  NexusWriteCommandBuilder commandBuilder(instrumentName, filename, jobID);

  // Add 8 monitors
  for (uint32_t monitorNumber = 1; monitorNumber <= 8; monitorNumber++) {
    auto spectrumNumber = monitorNumber;
    commandBuilder.addMonitor(monitorNumber, spectrumNumber);
  }

  std::cout << commandBuilder.startMessageAsString() << std::endl;

  std::cout << commandBuilder.stopMessageAsString() << std::endl;
  return 0;
}
