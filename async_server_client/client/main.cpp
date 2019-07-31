#include <string.h>
#include <string>
#include <stdlib.h>
#include <curl/curl.h>
#include <iostream>

#include <unistd.h>

#include <atomic>
#include <queue>
#include <mutex>
#include <thread>

using std::atomic;
using std::queue;
using std::mutex;

static size_t write_callback(void *ptr, size_t size, size_t nmemb, std::string* data) {
  data->assign((char*) ptr, size * nmemb);
  return size * nmemb;
}

static size_t write_file(void *ptr, size_t size, size_t nmemb, void *stream){
  size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
  return written;
}


/* std::lock_guard 
 * lock in local scope */

template<typename T>
class MutexQueue{

  public:
    void push( const T& value ){
      std::lock_guard<mutex> lock(m_mutex);
      m_queque.push(value);
    }

    T pop(){
      std::lock_guard<mutex> lock(m_mutex);
      T temp = m_queque.front();
      m_queque.pop();
      return temp;
    }

    int size(){
      return m_queque.size();
    }

  private:
    std::queue<T> m_queque;
    mutable std::mutex m_mutex;
};



class Processor{
  private:
   int max_idx; 
   int cur_idx;
   MutexQueue<int> q;
   int cur_v;

  public:

   Processor(int _max_idx){
    max_idx = _max_idx;
    cur_idx=0;
   }

   void Push(std::string input){
    q.push(stoi(input));
    cur_idx+=1;
   }
   int Pop(){
     return  q.pop();
   }

   void process(){
     std::cout<<"process call\n";
     for(int i=0;i<max_idx;i++){
       while(q.size()<1);
        std::cout<<"processing.. ("<< i<<")\n";
        sleep(5);
        cur_v = q.pop();
        std::cout<<"pop : "<<cur_v<<"\n";
     }
   }
};

int main(){
  std::string output;
  int max_idx;

  CURL *curl;
  CURLcode res;

  curl = curl_easy_init();
  curl_easy_setopt(curl, CURLOPT_URL, "localhost:8080");
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA,     &output);
  res = curl_easy_perform(curl);
  curl_easy_cleanup(curl);
  std::cout<<output<<"\n";

  //Request Process
 
  curl = curl_easy_init();
  curl_easy_setopt(curl, CURLOPT_URL,"localhost:8080/async");
  curl_easy_setopt(curl, CURLOPT_POSTFIELDS, "request=process");
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA,     &output);
  res = curl_easy_perform(curl);
  printf("res : %d\n",res);
  curl_easy_cleanup(curl);
  /* server : Do some process and return num of result*/
  // Get Num of result

  max_idx = stoi(output);
  std::cout<<"max_idx :" <<max_idx<<"\n";

  Processor proc(max_idx);
  std::thread t = std::thread(&Processor::process,&proc);
  
  for(int i=0;i<max_idx;i++)
  {
//    std::cout<<"i : "<<i<<"\n";
    //Get first result and do some stuff
    curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL,"localhost:8080/async");
    std::string postfiled = "request=get&idx=";
    postfiled = postfiled + std::to_string(i);
    curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postfiled.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA,     &output);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    /* server : send first result */
 //   std::cout<<"push"<<output<<"\n";
    proc.Push(output);

  } 
  t.join();
  return 0;
}
