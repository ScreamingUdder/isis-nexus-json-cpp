#include "NexusWriteCommandBuilder.h"
#include <fstream>
#include <iostream>

int main() {
  const std::string instrumentName = "ZOOM";
  const uint32_t runNumber = 782582;

  // jobID must match in start and stop message
  // It must be unique (could be generated UUID or instrument name and run
  // number)
  const std::string jobID = instrumentName + "_" + std::to_string(runNumber);

  const std::string filename = instrumentName + "_" + std::to_string(runNumber) + ".nxs";
  const std::string broker = "livedata.isis.cclrc.ac.uk";
  const std::string runCycle = "18_2";

  NexusWriteCommandBuilder commandBuilder(instrumentName, filename, jobID,
                                          broker, runCycle);

  commandBuilder.addSample(6.0, 1.0, 6.0);
  commandBuilder.addStartTime("2018-07-06T09:47:44");
  commandBuilder.addTitle("MT Beam A2=6mm SANS");
  commandBuilder.addTotalCounts(170700);

  // TODO Add detector

  // TODO Add event data

  // TODO Add PV (take vector of PV names)

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
