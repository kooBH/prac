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
      cout<<id<<" created.\n";
      run = true;
    }
    void tell() {
      while(run){
      cout<<id<<endl;
      this_thread::sleep_for(chrono::seconds(id));
      if(!run){
        cout<<"Bye\n";
        run=false;
        }
      }
    }

    void call(){
      cout<<"call : "<<id<<endl;
      run = false;
    }
  private:
    bool run;
    int id;

};

int main(){


  string a;

  obj_2 o1(1),o2(2);
  thread t1{&obj_2::tell,&o1}; 
  thread t2{&obj_2::tell,&o2}; 

  while(true){
    cin>>a;
    if(a.compare("w")==0){
      o1.call();
    }
    if(a.compare("e")==0)
      o2.call();
  
    if(a.compare("q")==0)
      break;
  }


  t1.join();
  t2.join();

    return 0;
}
