#include <iostream>
#include "MyInterfaz.hpp"

using namespace std;

int main()
{
  MyInterfaz app; 
  app.setName("Interface54");
  app.setVersion("1.0.0");
  app.setDescription("Este programa crea el archivo INTERFACE54CALIDAD.csv en base a los datos del\n"
                     "documento de Mithra y los archivos encontrados en 'files/CS2'");
  app.setUse("1. Verifique que junto a este programa se encuentra la carpeta 'files' con los\n"
             "   siguientes archivos: Fron_y_Asoc.csv, OperadoresRed.csv y la subcarpeta 'CS2'\n"
             "2. Verifique que todos los archivos dentro de 'files' y 'files/CS2' se \n"
             "   encuentran en formato csv separado por ';' o ','");
  app.showDescription();
  app.showUse();

  app.Main();
  
  app.enterToContinue("\nPresione enter para cerrar esta ventana");    
  
  return 0;
}
