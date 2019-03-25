#include <stdlib.h>
#include <stdio.h>
#include <Python.h>

int main(int argc,char*argv[]){
  Py_SetProgramName(argv[0]);  /* optional but recommended */
  Py_Initialize();
  PyRun_SimpleString("import os\n"
      "import sys\n"
      "sys.path.append(os.getcwd()+'/..')\n"
      "print(os.getcwd())\n"
      );
  PyRun_SimpleString("from module import *\n"
       "hello()\n"
                      );

  PyRun_SimpleString("value = 17\n"
      "print('value is 17')\n"
      );
  printf("Gonna print value\n");
  PyRun_SimpleString("print(value)\n");
  Py_Finalize();

  printf("Restart\n");

  Py_Initialize();
  PyRun_SimpleString("value = 17\n");
  PyRun_SimpleString("print(value)\n");
  Py_Finalize();
  printf("END\n");
  return 0;
}
