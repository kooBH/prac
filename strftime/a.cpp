#include <iostream>
#include <ctime>

int main ()
{
  time_t rawtime;
  struct tm * timeinfo;
  char buffer[80];

  time (&rawtime);
  timeinfo = localtime(&rawtime);

  strftime(buffer,sizeof(buffer),"%Y-%m-%d_%H:%M:%S",timeinfo);
  std::string str(buffer);

  std::cout << str<<std::endl;

  return 0;
}
