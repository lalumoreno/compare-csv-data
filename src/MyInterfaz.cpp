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
#define FILE_MITHRA       "files/Fron_y_Asoc.csv"

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

  printf("Main of interfaz");
  // ------------------  1. Open all files 
  //TODO check if empty files
  //Open reference document by name  
  MyFile refFile;
  if(!refFile.openFile(FILE_MITHRA, true)) return APP_FAILURE; //TODO check that is Mithra valid doc    
  //Open config file for column association    
  
  // ------------------  2. Ask period to evaluate
  std::string option;
  cout << "Ingrese el periodo a evaluar [YYYMM]: ";

  while(true) {
    cin >> option;
    cin.clear();
    //TODO evaluate format
    break;
  }
  cout << "Periodo: " << option << endl;
  return APP_SUCCESS;

  //  ------------------  3. Create csv file 
  MyFile testFile;
  //testfile.createFile()
}