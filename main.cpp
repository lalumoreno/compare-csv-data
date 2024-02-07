#include <iostream>
#include "MyApp.hpp"

using namespace std;

int main()
{
  MyApp app; 
    
  app.showAppDescription();
  app.showAppUse();

  app.Main();
  
  app.enterToContinue("\nPresione enter para cerrar esta ventana");    
  
  return 0;
}
