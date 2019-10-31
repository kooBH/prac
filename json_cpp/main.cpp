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

  json json_names= j["name"];
  for (auto it = json_names.begin(); it != json_names.end(); ++it) {
    // 연습을 해야겠다 
    v.push_back(*it);
  }
  ifs.close();

  for(auto it : v )
    std::cout<< it <<std::endl;
  return 0;
}
