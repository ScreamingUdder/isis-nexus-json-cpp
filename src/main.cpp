#include "NexusWriteCommandBuilder.h"
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main() {
  NexusWriteCommandBuilder startCommand;

  std::cout << startCommand.startMessageAsString() << std::endl;
  return 0;
}
