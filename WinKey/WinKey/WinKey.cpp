// WinKey.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream>
#include <thread>
#include <windows.h>

bool run_main = true;
bool fF2 = false;

void key();

int main()
{
  
  std::thread* t;
  t = new std::thread(&key);
  while (run_main) {
    ;
  }
}

void key(){
  bool run = true;

  while (run) {
    
    if (GetKeyState(VK_F2) < 0 && !fF2)
    {
      fF2 = true;
      std::cout << "F2 pressed" << std::endl;
    }
    if (GetKeyState(VK_F2) >=0 && fF2)
    {
      std::cout << "F2 Released" << std::endl;
      fF2 = false;
    }
    if ((GetKeyState(VK_F3) & 0x8000))
    {
      std::cout << "F3 pressed" << std::endl;
    }
    if ((GetKeyState(VK_F4) & 0x8000))
    {
      std::cout << "F4 pressed" << std::endl;
      run_main = false;
      run = false;
    }
  }
}

