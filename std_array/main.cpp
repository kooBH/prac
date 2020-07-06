#include <vector>
#include <array>
#include <iostream>


void Set(std::array<float,128>& a){

  a[0]=654.321;

}

int main(){

  std::vector<std::array<float,128>> vec;
  std::array<float,128> temp;
  temp[0]=123.456;

  std::cout<<temp[0]<<std::endl;
  vec.push_back(temp);

  std::cout<<vec.at(0).at(0)<<std::endl;
  Set(vec.at(0));
  std::cout<<vec.at(0).at(0)<<std::endl;

  return 0;
}

