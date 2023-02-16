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

#define REF_NUM_CIRCUITO_COL    28-1 
#define REF_NIVEL_TENSION_COL   26-1
#define REF_DUENO_RED_COL       32-1

#define TC1_NUM_CIRCUITO_COL1  2-1 //TOCO change name
#define TC1_NUM_CIRCUITO_COL2  12-1  //TOCO change name

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

int MyApp::enterToContinue(string text) {

    string option;        
    cout << text << endl;
    cin.clear(); //TODO fix if other key si pressed
    cin.ignore();    
    return EXIT;                
}

int MyApp::Main() {

  // ------------------  1. Open all files 
  //Open reference document by name  
  MyFile refFile;
  //refFile.requestOpenFile("doc de Mithra", true); //TODO check that is Mithra valid doc  
  refFile.openFile("files/ref.csv", true);
  //Open TC1 by name
  MyFile tc1File;
  //tc1File.requestOpenFile("TC1", true);           //TODO check that is tc1 valid doc
  tc1File.openFile("files/tc1.csv", true);
  //Open config file for column association    
  MyFile configFile;                        
  if (!configFile.openFile(FILE_CONFIG, false)) return APP_FAILURE; //TODO check that is a config valid doc
  //TODO print name of columns to compare
  //Open numeroCircuito file for comparison
  MyFile numCircFile;
  if(!numCircFile.openFile(FILE_NUM_CIRCUITO, false)) return APP_FAILURE;  
  //Open propiedad activo file for comparison
  MyFile propFile;
  if(!propFile.openFile(FILE_PROP, false)) return APP_FAILURE;
  MyFile propNT1File;
  if(!propNT1File.openFile(FILE_PROP_NT1, false)) return APP_FAILURE;  



  //------------------  2. Print columns to compare
  cout << "Las siguientes columnas van a ser comparadas " << endl;
  cout << "[Mithra] \t\t[TC1]" << endl; 
  for(int r=0; r < configFile.content.getTotalRow(); r++) {
    cout << refFile.content.getStringByRowCol(TITLE_ROW, configFile.content.getIntByRowCol(r, CONFIG_REF_COL)-1) <<"\t\t" 
         << tc1File.content.getStringByRowCol(TITLE_ROW, configFile.content.getIntByRowCol(r,CONFIG_TC1_COL)-1) << endl;
  }
  cout << endl;
  


  // ------------------  3. Request confirmation to continue
  enterToContinue("Presione enter para continuar");



  // ------------------  4. Request list filter
  //filter Mithra doc by OPERADOR_RED  
  int refColFilterTitle = refFile.content.getColNumByTitle(FILTER_COL_TITLE);  
  vector<string> v = refFile.content.getListbyCol(refColFilterTitle);
  refFile.setFilterFromList(v);



  // ------------------  5. Compare all columns
  int refColTitle = configFile.content.getIntByRowCol(0,CONFIG_REF_COL)-1;
  int tc1ColTitle = configFile.content.getIntByRowCol(0,CONFIG_TC1_COL)-1;

  vector<string> frontFound;
  int row;  
  string frontera;
  int c;       
  string refString;
  string tc1String;
    
  //for each row in Mithra doc, find frontera in TC1  
  for(row=1; row < refFile.content.getTotalRow(); row++) {
        
      //Only compare rows that match with filter
      if(refFile.getFilter().compare(refFile.content.getStringByRowCol(row,refColFilterTitle)) != 0 )
        continue;

      frontera = refFile.content.getStringByRowCol(row,refColTitle);   //Get frontera name in Mithra doc
      c = tc1File.content.getRowByStringInCol(tc1ColTitle,frontera);   //Find frontera name in TC1

      //If found in TC1
      if (c >= 0) {          
        //cout << "word " << tmp << " found in row " << c << " of other doc" << endl;              
        frontFound.push_back(frontera);

        //Compare all other columns with TC1
        for(int configRow = 1; configRow<configFile.content.getTotalRow(); configRow++ ) {
          
          int refCol = configFile.content.getIntByRowCol(configRow,CONFIG_REF_COL)-1;
          int tc1Col = configFile.content.getIntByRowCol(configRow,CONFIG_TC1_COL)-1;

          string refTitle = refFile.content.getStringByRowCol(TITLE_ROW,refCol);
          string tc1Title = tc1File.content.getStringByRowCol(TITLE_ROW,tc1Col);     

          //NUMERO DE CIRCUITO
          if(refCol == REF_NUM_CIRCUITO_COL) {            
            int cod = refFile.content.getIntByRowCol(row,refCol);
            string codString;            

            if(tc1Col == TC1_NUM_CIRCUITO_COL1) {
              codString = numCircFile.content.getStringByRowCol(cod,CONFIG_TC1_COL);
            } else {
              codString = numCircFile.content.getStringByRowCol(cod,CONFIG_TC1_COL+1);
            }        
            
            refString = codString;
            
          } //NIVEL DE TENSION
          else if (refCol == REF_DUENO_RED_COL) {            
            int level = refFile.content.getIntByRowCol(row,REF_NIVEL_TENSION_COL);
            string levelString;
            int rowx;            

            if(level == 1) {
              rowx = propNT1File.content.getRowByStringInCol(CONFIG_REF_COL, refFile.content.getStringByRowCol(row,refCol));           
              levelString = propNT1File.content.getStringByRowCol(rowx,CONFIG_TC1_COL);

            } else {              
              levelString = "101"; //TODO get from config file
            }

            refString = levelString;

          } else {
              refString = refFile.content.getStringByRowCol(row,refCol);
          }

          tc1String = tc1File.content.getStringByRowCol(c,tc1Col);
          
          if(!refString.empty() &&
            refString.compare(tc1String) != 0){
            cout << frontera <<"; "<< refTitle << ": " << refString << ", " << tc1Title << ": " << tc1String << endl;
          }        
        }
      } else {
        cout << frontera << "; no se encuentra en TC1" << endl;
      }      
    }

    //TODO add option to show fronteras list
    cout << endl << tc1File.content.getTotalRow()-1 << " fronteras en tc1" << endl;
    cout << endl << frontFound.size() << " fronteras encontradas en tc1, revise las diferencias arriba" << endl;

  return APP_SUCCESS;

}