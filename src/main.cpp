#include "NexusWriteCommandBuilder.h"
#include <fstream>
#include <iostream>

int main() {
  const std::string instrumentName = "ZOOM";
  const std::string filename = "ZOOM_782582.nxs";
  // jobID must match in start and stop message
  // It must be unique (could be generated UUID or instrument name and run
  // number)
  const std::string jobID = "ZOOM_782582";
  const std::string broker = "livedata.isis.cclrc.ac.uk";
  const std::string runCycle = "18_2";

  NexusWriteCommandBuilder commandBuilder(instrumentName, filename, jobID,
                                          broker, runCycle);

  // TODO Add detector

  // TODO Add event data

  // Add 8 monitors
  for (uint32_t monitorNumber = 1; monitorNumber <= 8; monitorNumber++) {
    auto spectrumNumber = monitorNumber;
    commandBuilder.addMonitor(monitorNumber, spectrumNumber);
  }

  // The returned string can be used directly as a Kafka message payload
  std::cout << commandBuilder.startMessageAsString() << std::endl;
  std::cout << commandBuilder.stopMessageAsString() << std::endl;

  std::ofstream out("startMessage.json");
  out << commandBuilder.startMessageAsString();
  out.close();

  return 0;
}
