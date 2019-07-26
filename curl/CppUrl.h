#ifndef _H_CURLAPI_
#define _H_CURLAPI_

#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <iostream>

using std::string;


/*
 * CURLcode curl_easy_setopt(CURL *handle, CURLoption option, parameter);
 * https://curl.haxx.se/libcurl/c/curl_easy_setopt.html
 * */
class CppUrl{

  private:
    const int MAX_CHAR_BUF = 1024;

    string url;
    int port;


    static size_t write_callback(void *ptr, size_t size, size_t nmemb, std::string* data) {
      data->append((char*) ptr, size * nmemb);
      return size * nmemb;
    }

    static size_t write_file(void *ptr, size_t size, size_t nmemb, void *stream)
    {
      size_t written = fwrite(ptr, size, nmemb, (FILE *)stream);
      return written;
    }

  public:
    CppUrl(string _url,int _port):
     url(_url),
     port(_port){
       std::cout<<_url<<"\n";
       std::cout<<_port<<"\n";
      
    }
    ~CppUrl(){}

    /* https://curl.haxx.se/libcurl/c/simple.html */
    string GET_kor(string input,string kor);

    /* https://curl.haxx.se/libcurl/c/url2file.html */
    int Url2File(string url);
    
};

string CppUrl::GET_kor(string input,string kor){
  
      char temp_buffer[MAX_CHAR_BUF];
      char post_field [MAX_CHAR_BUF];
      string output;

      CURL *curl;
      CURLcode res;

      curl = curl_easy_init();

      /* http://jeremyko.blogspot.com/2018/01/libcurl-post-encoding.html
       * encoding할 한글데이터만 분리해서 처리 후 
       */
      
      int len=snprintf(temp_buffer, sizeof(temp_buffer),"%s",kor.c_str());
      char* encoded = curl_easy_escape(curl, temp_buffer, len);

      //하나의 문자열로 조합해야한다.
      snprintf(post_field, sizeof(post_field),"%s:%d%s%s",url.c_str(),port , input.c_str(),encoded);
      std::cout<<post_field<<"\n";

      if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, post_field);

        /* example.com is redirected, so we tell libcurl to follow redirection */ 
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA,     &output);

        /* Perform the request, res will get the return code */ 
        res = curl_easy_perform(curl);

        /* Check for errors */ 
        if(res != CURLE_OK)
          fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));

        /* always cleanup */ 
        curl_easy_cleanup(curl);
      }
    return output;
}


int CppUrl::Url2File(string path){

  CURL *curl_handle;
  static const char *pagefilename = "output.wav";
  FILE *pagefile;
  string temp_url;
 
  curl_global_init(CURL_GLOBAL_ALL);
 
  /* init the curl session */ 
  curl_handle = curl_easy_init();
 
  temp_url = url +':' +std::to_string(port) + path;
  std::cout<<"temp_url : "<<temp_url;
  
  /* set URL to get here */ 
  curl_easy_setopt(curl_handle, CURLOPT_URL, temp_url.c_str());
 
  /* Switch on full protocol/debug output while testing */ 
  curl_easy_setopt(curl_handle, CURLOPT_VERBOSE, 1L);
 
  /* disable progress meter, set to 0L to enable and disable debug output */ 
  curl_easy_setopt(curl_handle, CURLOPT_NOPROGRESS, 1L);
 
  /* send all data to this function  */ 
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_file);
 
  /* open the file */ 
  pagefile = fopen(pagefilename, "wb");
  if(pagefile) {
 
    /* write the page body to this file handle */ 
    curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, pagefile);
 
    /* get it! */ 
    curl_easy_perform(curl_handle);
 
    /* close the header file */ 
    fclose(pagefile);
  }
 
  /* cleanup curl stuff */ 
  curl_easy_cleanup(curl_handle);
 
  curl_global_cleanup();
 
  return 0;

}

#endif
