#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main() {
  json json_structure = {
    {"pi", 3.141},
    {"happy", true},
    {"name", "Niels"},
    {"nothing", nullptr},
    {"answer", {
              {"everything", 42}
           }},
    {"list", {1, 0, 2}},
    {"object", {
              {"currency", "USD"},
                 {"value", 42.99}
           }}
  };

  std::cout << json_structure.dump() << std::endl;
  return 0;
}
