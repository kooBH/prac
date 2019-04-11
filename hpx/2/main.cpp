#include <hpx/hpx_start.hpp>
#include <hpx/hpx_suspend.hpp>
#include <hpx/include/iostreams.hpp>

#include <iostream>

int main(int argc, char* argv[])
{
  std::cout<<hpx::start(nullptr,argc,argv);
/*
  hpx::apply([](){
      hpx::cout<<"hpx hello\n";
      });
  hpx::suspend();
  std::cout << "std hello"<<std::endl;

  hpx::resume();*/
  hpx::apply([](){hpx::finalize();});


return hpx::stop();
}


