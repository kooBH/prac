#include <iostream>
#include <cstdlib>
#include <stdio.h> 

#include <unistd.h>
#define GetCurrentDir getcwd

#define ENV "TEST"

int main()
{
  const char* env_p = std::getenv(ENV);
  if(env_p)
    std::cout << "Your PATH is: " << env_p << '\n';
  else{
    printf("Can't find 'PATH'\n");
    setenv("TEST","TEST",0);
  }

  char cwd[FILENAME_MAX];
  printf("FILENAME_MAX  : %d\n",FILENAME_MAX);

  GetCurrentDir( cwd, FILENAME_MAX );

  printf("CWD : %s\n",cwd);

  std::string env_s(std::getenv(ENV));

  if(env_s.find(cwd)==std::string::npos)
    printf("%s is not in %s\n",cwd,env_s.c_str());
  else
    printf("Found %s in %s",cwd,env_s.c_str());


}
