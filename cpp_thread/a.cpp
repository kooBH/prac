#include <iostream>
#include <thread>
#include <chrono> 

using namespace std;

//함수 클래스
class obj_1{
 public:
   obj_1(int _id){
     id = _id;
   }


 void operator()() const{
 cout<<id<<endl;
 this_thread::sleep_for(chrono::seconds(1));
 cout<<id<<endl;
   
 }

 private:
   int id;

};

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

int main(){


  string a;

  thread t1{obj_1(1)}; 
  thread t2{obj_1(2)}; 
  obj_2 o3(3),o4(4);
  thread t3{&obj_2::tell,&o3}; 
  thread t4{&obj_2::tell,&o4}; 


  t1.join();
  t2.join();
  t3.join();
  t4.join();

    return 0;
}
