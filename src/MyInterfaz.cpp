#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <algorithm>

#include "MyInterfaz.hpp"
#include "MyFile.hpp"

using namespace std;

#define VERSION "1.0.4"

#define FILE_CONFIG       "files/config.csv"
#define FILE_PROP_NT1     "files/propActivoNT1.csv"
#define FILE_NUM_CIRCUITO "files/Circuitos_Todos.csv"
#define FILE_MITHRA       "10/Fron_y_Asoc.csv"//"files/Fron_y_Asoc.csv"

#define TITLE_ROW         0
#define FIRST_VALUE_ROW   1

#define FIRST_COL    0
#define SECOND_COL    1

#define CONFIG_REF_COL    1
#define CONFIG_TC1_COL    2

#define CONFIG_NIVEL_TENSION_ROW    4
#define CONFIG_NUM_CIRCUITO_ROW1    5
#define CONFIG_NUM_CIRCUITO_ROW2    6
#define CONFIG_DUENO_RED_ROW        7

#define TC1_NUM_CIRCUITO_COL1  2-1    //TODO change name
#define TC1_NUM_CIRCUITO_COL2  12-1   //TODO change name

#define CIR_ID_COL      5-1  //ID Circuito
#define CIRC_NAME_COL   6-1  //Nombre
#define CIRC_COD_COL    8-1  //Codigo alimentador


int MyInterfaz::Main() {

  printf("Main of interfaz\n");
  // ------------------  1. Open all files 
  //TODO check if empty files
  //Open reference document by name  
  MyFile refFile;
  if(!refFile.openFile(FILE_MITHRA, true)) return APP_FAILURE;  
  
  // ------------------  2. Ask period to evaluate
  std::string option;
  cout << "Ingrese ciclo [YYYMM]: ";

  while(true) {
    cin >> option;
    cin.clear();
    //TODO evaluate format
    break;
  }
  cout << "Ciclo: " << option << endl;  

  //  ------------------  3. Create csv file 
  MyFile testFile;  
  if(!testFile.createCsv("files/laura.csv")) return APP_FAILURE;
  
  vector<string> tmpRow;  
  tmpRow.clear();
  tmpRow.push_back("PERIODO"); tmpRow.push_back("CODIGO_SIC"); tmpRow.push_back("ID_OR");
  tmpRow.push_back("GRUPO_CALIDAD"); tmpRow.push_back("CODIGO_TX"); tmpRow.push_back("NIU");
  tmpRow.push_back("DIUG"); tmpRow.push_back("FIUG"); tmpRow.push_back("DIU");
  tmpRow.push_back("DIUM"); tmpRow.push_back("FIU"); tmpRow.push_back("FIUM");
  
  testFile.content.addRow(tmpRow);
  //testFile.writeCsv();

  //  ------------------  4. Open first file AIRE
  MyFile aireFile;
  if(!aireFile.openFile("10/AIRE.csv", true)) return APP_FAILURE;

  vector<string> row;
  row = aireFile.content.getRowDatabyRow(1);
  string niu = row.at(0);
  
  //Look niu in front and asc
  cout << "niu :" << niu.c_str()<<endl;
  int rowofniu = refFile.content.getRowByStringInCol(34, niu);
  if(rowofniu < 0){
    cout << "NIU no encontrado: " << niu << endl;
    return APP_FAILURE;
  } 

  //Get sic
  cout << "niu encontrado en fila: " << rowofniu << endl;
  string sic = refFile.content.getStringByRowCol(rowofniu, 5);
  cout << "sic: " << sic << endl;

  //Step 4 : sacar ID_OR
  tmpRow.clear();
  tmpRow.push_back(option); 
  tmpRow.push_back(sic); 
  //tmpRow.push_back("ID_OR");
  // tmpRow.push_back("GRUPO_CALIDAD"); tmpRow.push_back("CODIGO_TX"); tmpRow.push_back("NIU");
  // tmpRow.push_back("DIUG"); tmpRow.push_back("FIUG"); tmpRow.push_back("DIU");
  // tmpRow.push_back("DIUM"); tmpRow.push_back("FIU"); tmpRow.push_back("FIUM");
  
  // testFile.content.addRow(tmpRow);

  return APP_SUCCESS;
}