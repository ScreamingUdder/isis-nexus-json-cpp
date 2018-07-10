#include "NexusWriteCommandBuilder.h"
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main() {
  const std::string instrumentName = "ZOOM";
  const std::string filename = "ZOOM_782582.nxs";
  // jobID must match in start and stop message, must be unique (could be generated UUID)
  const std::string jobID = "ZOOM_782582";
  NexusWriteCommandBuilder commandBuilder(instrumentName, filename, "ZOOM_782582");

  std::cout << commandBuilder.startMessageAsString() << std::endl;

  commandBuilder.addMonitor(11,11);

  std::cout << commandBuilder.stopMessageAsString() << std::endl;
  return 0;
}
