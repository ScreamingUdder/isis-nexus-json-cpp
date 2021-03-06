#include "NexusWriteCommandBuilder.h"
#include <fstream>
#include <iostream>

int main() {
  const std::string instrumentName = "ZOOM";
  const uint32_t runNumber = 4112;
  const std::string broker = "livedata.isis.cclrc.ac.uk";
  const std::string runCycle = "18_2";

  NexusWriteCommandBuilder commandBuilder(instrumentName, runNumber, broker,
                                          runCycle, "2018-07-06T09:47:44");

  commandBuilder.addSample(6.0, 1.0, 6.0);
  commandBuilder.addEndTime("2018-07-06T10:18:21");
  commandBuilder.addTitle("MT Beam A2=6mm SANS");
  commandBuilder.addTotalCounts(170700);
  commandBuilder.addMonitorEventsNotSaved(0);
  commandBuilder.addTotalUncountedCounts(7629);
  commandBuilder.addMeasurement();
  commandBuilder.addCollectionTime(1837.0);
  commandBuilder.addDuration(1837.0);
  commandBuilder.addProgramName(
      "ISISICP.EXE",
      "SVN R1959 (2018/06/13 13:15:08, Mixed revision WC 1958:1959, Modified)");
  commandBuilder.addNexusDefinition(
      "TOFRAW", "1.0",
      "http://definition.nexusformat.org/instruments/TOFRAW?version=1.0");
  commandBuilder.addLocalNexusDefinition(
      "ISISTOFRAW", "1.0",
      "http://svn.isis.rl.ac.uk/instruments/ISISTOFRAW?version=1.0");
  commandBuilder.addProtonChargeRawInMicroAmpHours(20.061872482299805f);
  commandBuilder.addProtonChargeInMicroAmpHours(20.061872482299805f);
  commandBuilder.addSeciConfig(" ");
  commandBuilder.addNotes(" ");
  commandBuilder.addExperimentIdentifier("0");
  commandBuilder.addScriptName(" ");

  // Add some users
  commandBuilder.addUser("Alice", "The Unseen University");
  commandBuilder.addUser("Bob", "The Unseen University");

  commandBuilder.addDetector(1, 0.0);

  // NB, source name for addEventDataSource must match whatever the ICP sets as
  // the
  // source name in event data messages it produces
  commandBuilder.addEventDataSource(1, "ICP");

  commandBuilder.addSELogSources({"full:pv:name", "bar:foo", "foo:bar"});

  // TODO What if there are multiple periods? Should some/all of these
  // parameters be vectors? Or allow calling "addPeriod" multiple times?
  commandBuilder.addPeriods(0, 21.20301055908203f, 20.061872482299805f, 18234,
                            1, 0, 18234, 1, 1, "Period 1", 20.061872482299805f,
                            1, 18234);

  // Add 8 monitors (with 1:1 mapping of monitor and spectrum numbers)
  for (uint32_t monitorNumber = 1; monitorNumber <= 8; monitorNumber++) {
    auto spectrumNumber = monitorNumber;
    commandBuilder.addMonitor(monitorNumber, spectrumNumber);
  }

  // Add some VMS compat records
  commandBuilder.addVmsRecord<std::string>(
      "HDR", "string", "ZOO04112                    MT Beam A2=6mm SANS "
                       "    06-JUL-2018 09:47:44   20.06");
  commandBuilder.addVmsRecord<std::vector<int32_t>>("CRAT", "int32",
                                                    {0, 1, 1, 0, 0, 1, 0});

  // Add some runlog records
  // TODO - is this interface convenient? Should we publish to Kafka as f142
  // instead?
  const std::string startTime = "2018-07-06T09:47:44";
  const std::vector<float> times{-30.0, 12.0, 54.0, 97.0};
  commandBuilder.addRunlogRecord<std::vector<float>>(
      "count_rate", "float", {0.0, 40.8772, 42.2018, 41.6405}, times, startTime,
      "counts");
  commandBuilder.addRunlogRecord<std::vector<float>>(
      "dae_beam_current", "float", {0.0, 38.6239, 39.7357, 39.4712}, times,
      startTime, "uAh");
  commandBuilder.addRunlogRecord<std::string>(
      "icp_event", "string", "CHANGE_PERIOD 1", times, startTime);

  // Add some framelog records
  commandBuilder.addFramelogRecord<std::vector<int32_t>>(
      "events_log", "int32", {11, 8, 6, 12}, times, startTime, "counts");
  commandBuilder.addFramelogRecord<std::vector<float>>(
      "proton_charge", "float", {0.001091, 0.001045, 0.001085, 0.001015}, times,
      startTime, "uAh");

  // The returned string can be used directly as a Kafka message payload
  std::cout << commandBuilder.startMessageAsString() << std::endl;
  std::cout << commandBuilder.stopMessageAsString() << std::endl;

  std::ofstream startOut("startMessage.json");
  startOut << commandBuilder.startMessageAsString();
  startOut.close();

  std::ofstream stopOut("stopMessage.json");
  stopOut << commandBuilder.stopMessageAsString();
  stopOut.close();

  return 0;
}
