#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>

#include "MyApp.hpp"
#include "MyFile.hpp"

using namespace std;

#define VERSION "1.0.0"

#define FILE_CONFIG       "files/config.csv"
#define FILE_NUM_CIRCUITO "files/numeroCircuito.csv"
#define FILE_PROP_NT1     "files/propActivoNT1.csv"

#define FILTER_COL_TITLE  "OPERADOR_RED"

#define TITLE_ROW         0
#define FIRST_VALUE_ROW   1

#define CONFIG_REF_COL    0
#define CONFIG_TC1_COL    1

#define REF_NUM_CIRCUITO_COL    28-1 
#define REF_NIVEL_TENSION_COL   26-1
#define REF_DUENO_RED_COL       32-1

#define TC1_NUM_CIRCUITO_COL1  2-1    //TODO change name
#define TC1_NUM_CIRCUITO_COL2  12-1   //TODO change name

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
    cout << "   siguientes archivos: config.csv, numeroCircuito.csv, propActivoNT1.csv" << endl;
    cout << "2. Verifique que el archivo de Mithra y el TC1 se encuentran en formato csv separado" << endl;
    cout << "   por ';'" << endl;    
    cout << "************************************************************************************" << endl << endl;
}

int MyApp::enterToContinue(string text) {

    string option;        
    cout << text << endl;    
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return EXIT;

}

int MyApp::Main() {

  // ------------------  1. Open all files 
  //Open reference document by name  
  MyFile refFile;
  refFile.requestOpenFile("doc de Mithra", true); //TODO check that is Mithra valid doc    
  //Open TC1 by name
  MyFile tc1File;
  tc1File.requestOpenFile("TC1", true);           //TODO check that is tc1 valid doc  
  //Open config file for column association    
  MyFile configFile;                        
  if (!configFile.openFile(FILE_CONFIG, false)) return APP_FAILURE; //TODO check that is a config valid doc
  //Open numeroCircuito file for comparison
  MyFile numCircFile;
  if(!numCircFile.openFile(FILE_NUM_CIRCUITO, false)) return APP_FAILURE;  
  //Open propiedad activo file for comparison
  MyFile propNT1File;
  if(!propNT1File.openFile(FILE_PROP_NT1, false)) return APP_FAILURE;  



  //------------------  2. Print columns to compare
  cout << "Las siguientes columnas van a ser comparadas " << endl;
  cout << configFile.content.getStringByRowCol(TITLE_ROW, CONFIG_REF_COL) <<"\t\t\t" 
       << configFile.content.getStringByRowCol(TITLE_ROW, CONFIG_TC1_COL) << endl;
  for(int r=1; r < configFile.content.getTotalRow(); r++) {
    cout << refFile.content.getStringByRowCol(TITLE_ROW, configFile.content.getIntByRowCol(r, CONFIG_REF_COL)-1) <<"\t\t" 
         << tc1File.content.getStringByRowCol(TITLE_ROW, configFile.content.getIntByRowCol(r,CONFIG_TC1_COL)-1) << endl;
  }
  cout << endl;
  


  // ------------------  3. Request confirmation to continue
  enterToContinue("Presione enter para continuar");



  // ------------------  4. Set list filter
  int refColFilterTitle = refFile.content.getColNumByTitle(FILTER_COL_TITLE);  
  vector<string> v = refFile.content.getListbyCol(refColFilterTitle);
  refFile.setFilterFromList(v);



  // ------------------  5. Apply Filter
  //filter Mithra doc by OPERADOR_RED  
  MyMatrix refFiltered;
  refFiltered.addRow(refFile.content.getRowDatabyRow(TITLE_ROW));

  for(int row=1; row < refFile.content.getTotalRow(); row++) {
    
      if(refFile.getFilter().compare(refFile.content.getStringByRowCol(row,refColFilterTitle)) != 0 )
        continue;

      refFiltered.addRow(refFile.content.getRowDatabyRow(row));
  }
  
  

  // ------------------  6. Compare all columns
  int refFronteraCol = configFile.content.getIntByRowCol(1,CONFIG_REF_COL)-1;
  int tc1FronteraCol = configFile.content.getIntByRowCol(1,CONFIG_TC1_COL)-1;
    
  string fronteraName;
  int fronteraTc1Row;  
   int fronteraRefRow;     
  string refString;
  string tc1String;
  vector<string> fronteras;
  vector<string> tmpRow;
  MyMatrix result;
  
  //for each row in Mithra doc, find frontera in TC1  
  for(int row=1; row < refFiltered.getTotalRow(); row++) {
            
      fronteraName = refFiltered.getStringByRowCol(row,refFronteraCol);                    //Get frontera name in Mithra doc
      fronteraTc1Row = tc1File.content.getRowByStringInCol(tc1FronteraCol,fronteraName);   //Find frontera name in TC1

      //If found in TC1
      if (fronteraTc1Row >= 0) {                      
        fronteras.push_back(fronteraName);

        //Compare all other columns with TC1
        for(int configRow = 2; configRow < configFile.content.getTotalRow(); configRow++ ) {
          
          int refCol = configFile.content.getIntByRowCol(configRow,CONFIG_REF_COL)-1;
          int tc1Col = configFile.content.getIntByRowCol(configRow,CONFIG_TC1_COL)-1;

          string refTitle = refFiltered.getStringByRowCol(TITLE_ROW,refCol);
          string tc1Title = tc1File.content.getStringByRowCol(TITLE_ROW,tc1Col);     

          //NUMERO DE CIRCUITO
          if(refCol == REF_NUM_CIRCUITO_COL) {            
            int num = refFiltered.getIntByRowCol(row,refCol);
            string codString;            

            if(tc1Col == TC1_NUM_CIRCUITO_COL1) {
              codString = numCircFile.content.getStringByRowCol(num,CONFIG_TC1_COL);
            } else { //TC1_NUM_CIRCUITO_COL2
              codString = numCircFile.content.getStringByRowCol(num,CONFIG_TC1_COL+1);
            }        
            //TODO: This string may be empty as long as numCircFile is incomplete
            refString = codString;
            
          } //NIVEL DE TENSION
          else if (refCol == REF_DUENO_RED_COL) {        
            int level = refFiltered.getIntByRowCol(row,REF_NIVEL_TENSION_COL);
            string levelString;
            int rowx;            

            if(level == 1) {
              rowx = propNT1File.content.getRowByStringInCol(CONFIG_REF_COL, refFiltered.getStringByRowCol(row,refCol));           
              levelString = propNT1File.content.getStringByRowCol(rowx,CONFIG_TC1_COL);

            } else {              
              levelString = "101"; //TODO get from config file
            }

            refString = levelString;

          } else {
              refString = refFiltered.getStringByRowCol(row,refCol);
          }

          tc1String = tc1File.content.getStringByRowCol(fronteraTc1Row,tc1Col);
          
          //TODO remove empty filter
          if(!refString.empty() &&
            refString.compare(tc1String) != 0) {
            tmpRow.clear();
            tmpRow.push_back(fronteraName); tmpRow.push_back(refTitle + ": " + refString + ", " + tc1Title + ": " + tc1String);            
            result.addRow(tmpRow);            
          }        
        }
      } else {
         tmpRow.clear();
         tmpRow.push_back(fronteraName); tmpRow.push_back("no se encuentra en TC1");         
         result.addRow(tmpRow);
      }      
    }

  // ------------------  6. Check if missed fronteras  
  int tc1Fronteras = tc1File.content.getTotalRow()-1;
  int refFronteras =  fronteras.size();

  cout << endl << tc1Fronteras << " fronteras en tc1" << endl;
  cout << refFronteras << " fronteras de Mithra encontradas en tc1" << endl << endl;

  if(tc1Fronteras > refFronteras) {

    //find missed fronteras in Mithra
    for(int row = 1; row < tc1File.content.getTotalRow(); row++) {
      fronteraName = tc1File.content.getStringByRowCol(row,tc1FronteraCol);            //Get frontera name in TC1 doc
      fronteraRefRow = refFiltered.getRowByStringInCol(refFronteraCol,fronteraName);   //Find frontera name in Mithra doc

      //If not found in Mithra
      if (fronteraRefRow <= 0) {
         tmpRow.clear();
         tmpRow.push_back(fronteraName); tmpRow.push_back("no se encuentra en MITHRA doc pero si en TC1!!");         
         result.addRow(tmpRow);         
      }
    }    
  }

  // ------------------  6. Save result in file
  auto t = std::time(nullptr);
  auto tm = *std::localtime(&t);
  std::ostringstream oss;
  oss << std::put_time(&tm, "%d-%m-%Y_%H-%M-%S");
  string resultFile = refFile.getFilter() + "_" + oss.str() + ".csv";
  
  //Add files names
  tmpRow.clear();
  tmpRow.push_back("Mithra doc"); tmpRow.push_back(refFile.getPath());
  result.addRow(tmpRow);         

  tmpRow.clear();
  tmpRow.push_back("TC1 doc"); tmpRow.push_back(tc1File.getPath());
  result.addRow(tmpRow);         

  MyFile res("files/"+resultFile);
  res.content = result;  
  if(res.writeCsv()) cout << "Diferencias guardadas en " << res.getPath() << endl << endl;


  // ------------------  7. Print result
  enterToContinue("\nPresione enter para ver diferencias");
  res.content.printMatrix();

  return APP_SUCCESS;

}