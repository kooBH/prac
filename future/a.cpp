#include <iostream>
#include <thread>
#include <chrono> 
#include <future>

using namespace std;
//그냥 클래스
class obj_2{
  public:
    obj_2(int _id){
      id = _id;
    }
    void tell() const{
      cout<<id<<endl;
      this_thread::sleep_for(chrono::seconds(id));
      cout<<id<<endl;
    }
  private:
    int id;

};

void async_tell(){
  int iter = 20;
  while(iter--){
    cout<<"hello dum dum.\n";
    this_thread::sleep_for(chrono::seconds(1));
  }
}

int main(){

  future<void> result(async(async_tell));

  string a;

  obj_2 o3(3),o4(4);

  thread t3{&obj_2::tell,&o3}; 
  thread t4{&obj_2::tell,&o4}; 

  cout<<"IO block s\n";
  cin>>a;
  cout<<"IO block e\n";

  result.get();

  t3.join();
  t4.join();

    return 0;
}
