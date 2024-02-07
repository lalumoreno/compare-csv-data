#include <iostream>
#include "MyInterfaz.hpp"

using namespace std;

int main()
{
  MyInterfaz app; 

  app.setDescription("Este programa crea el archivo interfaz54.csv en base a los datos de ...");
  app.setUse("Verifique que...");
  app.showDescription();
  app.showUse();

  app.Main();
  
  app.enterToContinue("\nPresione enter para cerrar esta ventana");    
  
  return 0;
}
