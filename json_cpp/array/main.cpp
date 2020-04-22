#include "json.hpp"
#include <fstream>
#include <iostream>
#include <vector>

using json = nlohmann::json;
using std::string;
using std::map;
using std::vector;

int main(){
  std::ifstream ifs("data.json");
  json j = json::parse(ifs);

  std::vector<std::string> v;

  json json_names= j;
  for (auto it = json_names.begin(); it != json_names.end(); ++it) {
    std::cout<<it.value()["A"]<<std::endl;
  }
  ifs.close();

  return 0;
}
