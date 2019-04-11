#include <hpx/hpx_start.hpp>
#include <hpx/include/iostreams.hpp>

#include <iostream>

int hpx_main(int argc, char* argv[])
{
    // Any HPX application logic goes here...
    //
    for(int j=0;j<10;j++){
      for(int i=0;i<1000000;i++);
        hpx::cout << "Hello World!\n" << hpx::flush;
    }
    return hpx::finalize();
}

int main(int argc, char* argv[])
{
  hpx::start(argc,argv);
    for(int j=0;j<10;j++){
      for(int i=0;i<1000000;i++);
        std::cout << "std hello"<<std::endl;
    }

  return hpx::stop();
//    return hpx::init(argc, argv);
}
