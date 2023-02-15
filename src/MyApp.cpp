#include <iostream>
#include "MyApp.hpp"
#include "MyFile.hpp"

using namespace std;

#define VERSION "1.0.0"

#define FILE_CONFIG     "files/config.csv"
#define FILE_NUM_CIRCUITO "files/numeroCircuito.csv"
#define FILE_PROP_NT1   "files/propActivoNT1.csv"
#define FILE_PROP       "files/propActivo.csv"

#define FILTER_COL_TITLE "OPERADOR_RED"

#define TITLE_ROW         0
#define FIRST_VALUE_ROW   1

#define CONFIG_REF_COL    0
#define CONFIG_TC1_COL    1

#define REF_NUM_CIRCUITO_COL    28
#define REF_NIVEL_TENSION_COL   26
#define REF_DUENO_RED_COL       32

#define TC1_NUM_CIRCUITO_COL1  2 //TOCO change name
#define TC1_NUM_CIRCUITO_COL2  12  //TOCO change name

//TODO read from file
void MyApp::showAppDescription() {  
  
    cout << "************************************************************************************" << endl;
    cout << "                                     compare-tc1 V. "<< VERSION << endl;    
    cout << "Este programa compara los datos del documento de Mithra con los datos del TC1 para" << endl;
    cout << "cada frontera segun el filtro seleccionado y devuelve las diferencias " << endl;    
    cout << "************************************************************************************" << endl << endl;
}

//TODO read from file
void MyApp::showAppUse() {  
  
    cout << "************************************************************************************" << endl;    
    cout << "Antes de empezar:" << endl;
    cout << "1. Verifique que junto a este programa se encuentra la carpeta 'files' con los  " << endl; 
    cout << "   siguientes archivos: numeroCircuito.csv, porcentaje.csv y config.csv" << endl;
    cout << "2. Verifique que el archivo de Mithra y el TC1 se encuentran en formato csv separado" << endl;
    cout << "   por ';'" << endl;    
    cout << "************************************************************************************" << endl << endl;
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

  // ------------------  1. Open all files 
  //Open reference document by name    
  MyFile refFile;
  refFile.requestOpenFile("doc de Mithra");    
  //Open TC1 by name
  MyFile tc1File;
  tc1File.requestOpenFile("TC1");
  //Open config file for column association    
  MyFile config;                      //TODO create class for config files and not show all info  
  if (!config.openFile(FILE_CONFIG)) return APP_FAILURE;
  //TODO print name of columns to compare
  //Open numeroCircuito file for comparison
  MyFile numCircFile;
  if(!numCircFile.openFile(FILE_NUM_CIRCUITO)) return APP_FAILURE;  
  //Open propiedad activo file for comparison
  MyFile propFile;
  if(!propFile.openFile(FILE_PROP)) return APP_FAILURE;
  MyFile propNT1File;
  if(!propNT1File.openFile(FILE_PROP_NT1)) return APP_FAILURE;  
    
  /*
  cout << "compare " << refDoc.getStringByRowCol(0,configFile.getIntByRowCol(0,0)-1) <<
  " with " << otherDoc.getStringByRowCol(0,configFile.getIntByRowCol(0,1)-1) << endl;
  */

  // ------------------  2. Compare files
  //filter ref doc by OPERADOR_RED
  //TODO Read filter name from config file
  int refColFilterTitle = refFile.getColNumByTitle(FILTER_COL_TITLE);
  vector<string> v = refFile.getListbyCol(refColFilterTitle);

  refFile.setFilterFromList(v);

  //Look for title in ref and TC1 file
  int refColTitle1 = config.getIntByRowCol(0,0)-1;
  int otherColTitle1 = config.getIntByRowCol(0,1)-1;
  
  vector<string> rowFound;
  int row;  

  //FILTER
  if(refColTitle1 >= 0) {    
    string tmp;
    int c;       
    string refString;
    string tc1String;
    
    //for each row in column of ref, find frontera in TC1
    for(row=1;row<refFile.getRowTotal();row++) {
      
      //If ref filter does not match
      if(refFile._filter.compare(refFile.getStringByRowCol(row,refColFilterTitle)) != 0 )
        continue;

      tmp = refFile.getStringByRowCol(row,refColTitle1);      
      c = tc1File.getRowByStringInCol(otherColTitle1,tmp);
      if (c >= 0) {               
        //cout << "word " << tmp << " found in row " << c << " of other doc" << endl;              
        rowFound.push_back(tmp);

        //Compare all other columns with tc1
        for(int y = 1; y<config.getRowTotal(); y++ ) {
          
          int refCol = config.getIntByRowCol(y,CONFIG_REF_COL)-1;
          int tc1Col = config.getIntByRowCol(y,CONFIG_TC1_COL)-1;

          string refTitle = refFile.getStringByRowCol(TITLE_ROW,refCol);
          string tc1Title = tc1File.getStringByRowCol(TITLE_ROW,tc1Col);     

          //NUMERO DE CIRCUITO
          if(refCol == REF_NUM_CIRCUITO_COL) {
            int cod = refFile.getIntByRowCol(row,refCol);
            string codString;

            if(tc1Col == TC1_NUM_CIRCUITO_COL1) {
              codString = numCircFile.getStringByRowCol(cod,CONFIG_TC1_COL);
            } else {
              codString = numCircFile.getStringByRowCol(cod,CONFIG_TC1_COL+1);
            }        
            
            refString = codString;
            
          } //NIVEL DE TENSION
          else if (refCol == REF_DUENO_RED_COL) {
            int level = refFile.getIntByRowCol(row,REF_NIVEL_TENSION_COL-1);
            string levelString;
            int rowx;

            if(level == 1) {
              rowx = propNT1File.getRowByStringInCol(CONFIG_REF_COL, refFile.getStringByRowCol(row,refCol));           
              levelString = propNT1File.getStringByRowCol(rowx,CONFIG_TC1_COL);

            } else {              
              levelString = "101";
            }

            refString = levelString;

          } else {
              refString = refFile.getStringByRowCol(row,refCol);
          }

          tc1String = tc1File.getStringByRowCol(c,tc1Col);
          
          if(refString.compare(tc1String) != 0){
            cout << tmp <<"; "<< refTitle << ": " << refString << ", " << tc1Title << ": " << tc1String << endl;
          }        
        }
      } else {
        cout << tmp << "; no se encuentra en TC1" << endl;
      }      
    }

    //TODO add option to show fronteras list
    cout << endl << rowFound.size() << " fronteras encontradas en tc1, revise las diferencias arriba" << endl;
  
  } 

  return APP_SUCCESS;

}