#include "CppUrl.h"

using std::string;

int main(){

  string path;
  //CppUrl url("http://127.0.0.1",5000);
  CppUrl url("http://163.239.192.87",5000);
  path = url.GET_kor("/login?text=","서버에서 받은 파일입니다.");
  std::cout<<"path : " <<path<<"\n";
  url.Url2File("/file/");
  std::cout<<path<<"\n";

  return 0;
}
