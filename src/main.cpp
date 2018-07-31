#include "NexusWriteCommandBuilder.h"
#include <fstream>
#include <iostream>

int main() {
  const std::string instrumentName = "ZOOM";
  const uint32_t runNumber = 4112;
  const std::string broker = "livedata.isis.cclrc.ac.uk";
  const std::string runCycle = "18_2";

  NexusWriteCommandBuilder commandBuilder(instrumentName, runNumber, broker,
                                          runCycle);

  commandBuilder.addSample(6.0, 1.0, 6.0);
  commandBuilder.addStartTime("2018-07-06T09:47:44");
  commandBuilder.addTitle("MT Beam A2=6mm SANS");
  commandBuilder.addTotalCounts(170700);
  commandBuilder.addMonitorEventsNotSaved(0);
  commandBuilder.addTotalUncountedCounts(7629);
  commandBuilder.addMeasurementLabel(" ");
  commandBuilder.addMeasurementID(" ");
  commandBuilder.addSeciConfig(" ");

  // Add some users
  commandBuilder.addUser("Alice", "The Unseen University");
  commandBuilder.addUser("Bob", "The Unseen University");

  commandBuilder.addDetector(1, 0.0);

  // TODO Add event data

  // TODO Add logs (take vector of PV names)

  // Add 8 monitors
  for (uint32_t monitorNumber = 1; monitorNumber <= 8; monitorNumber++) {
    auto spectrumNumber = monitorNumber;
    commandBuilder.addMonitor(monitorNumber, spectrumNumber);
  }

  // The returned string can be used directly as a Kafka message payload
  std::cout << commandBuilder.startMessageAsString() << std::endl;
  std::cout << commandBuilder.stopMessageAsString() << std::endl;

  std::ofstream startOut("startMessage.json");
  startOut << commandBuilder.startMessageAsString();
  startOut.close();

  std::ofstream stopOut("stopMessage.json");
  stopOut << commandBuilder.startMessageAsString();
  stopOut.close();

  return 0;
}
