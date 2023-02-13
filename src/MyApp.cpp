#include <iostream>
#include "MyApp.hpp"
#include "MyFile.hpp"

using namespace std;

#define VERSION "1.0.0"
void MyApp::showAppDescription() {  
  
    cout << "**************************************************************" << endl;
    cout << "                 compare-tc1 V. "<< VERSION << endl;
    cout << "**************************************************************" << endl;
    cout << "Este programa compara los datos del documento de referencia " << endl;
    cout << "con los datos del TC1 para cada frontera segun el filtro " << endl;
    cout << "seleccionado y devuelve las diferencias encontradas" << endl;
    cout << "**************************************************************" << endl << endl;
}

int MyApp::entryMenu() {

    int option;    

    cout << "1. Empezar" << endl;
    cout << "2. Mas informacion" << endl;
    cout << "3. Salir" << endl;    
    cin >> option;

    switch(option) {
        case 1:
            return ENTER;                  
        case 2:
            cout << "Mas informacion disponible proximamente" << endl << endl;            
            return INFO;            
        case 3:            
            return EXIT;            
        default:
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Opcion invalida" << endl << endl;
            return NOT_VALID;            
    }    
}

int MyApp::exitMenu() {

    int option;    
    //TODO improve not to use enter
    cout << endl << "Ahora puede cerrar esta ventana" << endl;
    cin >> option;
    return EXIT;                
}

int MyApp::Main() {

  //Open reference document by name    
  MyFile refDoc;
  refDoc.requestOpenFile("doc referencia");    
  //Open TC1 by name
  MyFile tc1;
  tc1.requestOpenFile("TC1");

  //Read config file for column association
  //TODO verify values or fill it using app
  //TODO create class for config files  
  MyFile columns;  
  if (!columns.openFile("files/config.csv")) {
    //TODO wait before exit    
    return APP_FAILURE;
  }
  //TODO print name of columns to compare
    
  MyFile numCircuit;
  if(!numCircuit.openFile("files/cod.csv")) {
    //TODO wait before exit
    return APP_FAILURE;
  }
    
  /*
  cout << "compare " << refDoc.getStringByRowCol(0,configFile.getIntByRowCol(0,0)-1) <<
  " with " << otherDoc.getStringByRowCol(0,configFile.getIntByRowCol(0,1)-1) << endl;
*/
  //filter ref doc by OPERADOR_RED
  //TODO Read filter name from config file
  int refColOpRed = refDoc.getColNumByTitle("OPERADOR_RED");
  vector<string> v = refDoc.getListbyCol(refColOpRed);

  refDoc.setFilterFromList(v);

  //Look for title in ref and TC1 file
  int refColTitle1 = columns.getIntByRowCol(0,0)-1;
  int otherColTitle1 = columns.getIntByRowCol(0,1)-1;
  
  vector<string> rowFound;
  int i;

  //FILTER

  if(refColTitle1 >= 0) {    
    string tmp;
    int c;       
    string refString;
    string otherString;
    
    //for each row in column a of ref, find frontera in TC1
    for(i=1;i<refDoc.getRowTotal();i++) {
      
      //If ref filter does not match
      if(refDoc._filter.compare(refDoc.getStringByRowCol(i,refColOpRed)) != 0 )
        continue;

      tmp = refDoc.getStringByRowCol(i,refColTitle1);      
      c = tc1.getRowByStringInCol(otherColTitle1,tmp);
      if (c >= 0){
        //cout << "word " << tmp << " found in row " << c << " of other doc" << endl;              
        //rowFound.push_back(tmp);

        //Compare all other columns
        for(int y = 1; y<columns.getRowTotal(); y++ ) {
          
          int refCol = columns.getIntByRowCol(y,0)-1;
          int otherCol = columns.getIntByRowCol(y,1)-1;

          string refTitle = refDoc.getStringByRowCol(0,refCol);
          string otherTitle = tc1.getStringByRowCol(0,otherCol);     

          //NUMERO DE CIRCUITO
          if(refCol==28){
            int cod = refDoc.getIntByRowCol(i,refCol);
            string codString = numCircuit.getStringByRowCol(cod,1);
            refString = codString;
            //convert data
          } else {
              refString = refDoc.getStringByRowCol(i,refCol);
          }

          otherString = tc1.getStringByRowCol(c,otherCol);
          
          if(refString.compare(otherString) != 0){
            cout << tmp <<"; "<< refTitle << ": " << refString << ", " << otherTitle << ": " << otherString << endl;
          }        
        }
      } else {
        cout << tmp << "; no se encuentra en TC1" << endl;
      }
      
    }
  
  } 

  return APP_SUCCESS;

}