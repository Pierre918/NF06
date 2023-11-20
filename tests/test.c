#include <C:\Users\kaspa\AppData\Local\Programs\Python\Python312\include\Python.h>

//#include <C:\Python312\include\Python.h>
 //   #include <stdio.h>
  //  #include <conio.h>
int main(){
    Py_Initialize();
    PyRun_SimpleString("print('coucou')");
    Py_Finalize();
    printf("%s","coucou");
    return 0;
}