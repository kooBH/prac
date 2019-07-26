#include "CppUrl.h"

using std::string;

int main(){

  string path;
  CppUrl url("http://127.0.0.1",5000);
  path = url.GET_kor("/login?text=","안녕들하십니까");
  std::cout<<"path : " <<path<<"\n";
  url.Url2File("/file/");
  std::cout<<path<<"\n";

  return 0;
}
