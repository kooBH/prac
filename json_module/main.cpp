#ifndef _H_JSON_CONFIG_
#define _H_JSON_CONFIG_

#include <iostream>
//https://stackoverflow.com/questions/41236982/how-to-iterate-over-variadic-function-with-stdstring-arguments
#include <initializer_list>
#include <map>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;
using std::string;
using std::map;

template <typename T>
class ConfigJson{
  private:
    string file_path;
    map <string,T> data;

  public:
    inline ConfigJson(string file_path);
    inline ~ConfigJson();
    inline void Load(std::initializer_list<string> );
    inline void Print();

    inline T& operator[](string key){
     return data[key];
    }


};


template<typename T>
inline ConfigJson<T>::ConfigJson(string _file_path){
  file_path = _file_path;

}

template<typename T>
inline ConfigJson<T>::~ConfigJson(){

}


template<typename T>
inline void ConfigJson<T>::Load(std::initializer_list<string> args ){
  std::ifstream ifs(file_path);
  json j = json::parse(ifs);
  auto it = args.begin();

  string name = *it;
  it++;
  while(it!=args.end()){
  std::cout<<"param : "<< *it<<"\n";
  data[*it] = j[name][*it].get<T>();
  it++;
  
  }
  ifs.close();
}


template<typename T>
inline void ConfigJson<T>::Print(){
  for( auto const& it : data)
    std::cout<<it.first<<" : " << it.second<<"\n";
}


#endif

int main(){
  // 하나의 묶음으로 해줘야함 {}
  ConfigJson<double> config("../config.json");
  config.Load({"A","A1","A2"});
  config.Print();

  std::cout<<config["A1"] << " | " << config["A2"]<<"\n";

  return 0;
}
