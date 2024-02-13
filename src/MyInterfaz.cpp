#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
#include <algorithm>
#include <string>
#include <filesystem>

#include "MyInterfaz.hpp"
#include "MyFile.hpp"

using namespace std;
using std::filesystem::directory_iterator;


#define FILE_OPERADOR     "files/OperadoresRed.csv"
#define FILE_MITHRA       "files/Fron_y_Asoc.csv"

#define COL_DIU           2-1
#define COL_DIUM          3-1
#define COL_FIU           4-1
#define COL_FIUM          5-1
#define COL_FIUG          8-1
#define COL_DIUG          9-1


int MyInterfaz::Main() {
  
  // ------------------  1. Open all reference files   
  //Open references document by name
  MyFile fronterasFile;
  if(!fronterasFile.readFile(FILE_MITHRA, true)) return APP_FAILURE;  
  
  MyFile operadoresFile;
  if(!operadoresFile.readFile(FILE_OPERADOR, true)) return APP_FAILURE;    

  // ------------------  2. Ask period to evaluate
  std::string cycle;
  cout << "Ingrese ciclo [YYYYMM]: ";

  while(true) {
    cin >> cycle;
    cin.clear();
    cout << endl;
    break;
  }  
  
  //  ------------------  3. Create csv file 
  auto t = std::time(nullptr);
  auto tm = *std::localtime(&t);
  std::ostringstream oss;
  oss << std::put_time(&tm, "%d-%m-%Y_%H-%M-%S");
  string outputName = "files/INTERFACE54CALIDAD_" + oss.str() + ".csv";
  
  MyFile outputFile;  
  if(!outputFile.createCsv(outputName)) return APP_FAILURE;  
  
  vector<string> tmpRow;  
  tmpRow.clear();
  tmpRow.push_back("PERIODO"); tmpRow.push_back("CODIGO_SIC"); tmpRow.push_back("ID_OR");
  tmpRow.push_back("GRUPO_CALIDAD"); tmpRow.push_back("CODIGO_TX"); tmpRow.push_back("NIU");
  tmpRow.push_back("DIUG"); tmpRow.push_back("FIUG"); tmpRow.push_back("DIU");
  tmpRow.push_back("DIUM"); tmpRow.push_back("FIU"); tmpRow.push_back("FIUM");
  
  outputFile.content.addRow(tmpRow);  

  
  //  ------------------  4. Get list of CS2 files
  string path = "files/CS2/";
  vector<string> cs2List;  
  for (const auto & entry : directory_iterator(path)){
    cs2List.push_back(entry.path().string());        
  }

  if(cs2List.size() < 1) {
    cout << "No se encontraron archivos en " << path << endl;
    return APP_FAILURE;
  } 


  //  ------------------  5. Open each CS2 file
  cout << "Abriendo archivos CS2: " << endl;
  for(const auto& cs2 : cs2List) {

    MyFile cs2File;
    if(!cs2File.readFile(cs2, true)) {
      continue;
      return APP_FAILURE;
    }    

    for(int row = 1; row < cs2File.content.getTotalRow(); row++) {
      vector<string> rowSelected;
      rowSelected = cs2File.content.getRowDatabyRow(row);
      string niu = rowSelected.at(0);
      
      //  Find NIU in front and asc
      //cout << "niu :" << niu.c_str()<<endl;
      int rowNiu = fronterasFile.content.getRowByStringInCol(34, niu);
      if(rowNiu < 0){
        //cout << "NIU no encontrado: " << niu << endl;
        continue;        
      } 

      //  Get SIC      
      string sic = fronterasFile.content.getStringByRowCol(rowNiu, 5);
      //cout << "sic: " << sic << endl;

      //  Find OPERADOR_RED
      string op_red = fronterasFile.content.getStringByRowCol(rowNiu, 26);
      //cout << "op_red: " << op_red << endl;
      int rowOp = operadoresFile.content.getRowByStringInCol(4,op_red);
      if(rowOp < 0){
        cout << "OPERADOR_RED no encontrado en OperadoresRed.csv : " << op_red << endl;
        return APP_FAILURE;
      }

      //  Get Sigla
      //cout << "Sigla fila: " << rowop << endl;
      string id_op = operadoresFile.content.getStringByRowCol(rowOp, 0);
      //cout << "id_op: " << id_op << endl;

      //  Set diu/fiu
      string diu = rowSelected.at(COL_DIU);
      string dium = rowSelected.at(COL_DIUM);
      string fiu = rowSelected.at(COL_FIU);
      string fium = rowSelected.at(COL_FIUM);
      string fiug = rowSelected.at(COL_FIUG);
      string diug = rowSelected.at(COL_DIUG);

      tmpRow.clear();
      tmpRow.push_back(cycle); 
      tmpRow.push_back(sic);
      tmpRow.push_back(id_op);  //ID_OR  
      tmpRow.push_back("11");   //GRUPO_CALIDAD
      tmpRow.push_back(id_op);  //CODIGO_TX
      tmpRow.push_back(niu);    //NIU
      tmpRow.push_back(diug);   //DIUG
      tmpRow.push_back(fiug);   //FIUG
      tmpRow.push_back(diu);    //DIU
      tmpRow.push_back(dium);   //DIUM
      tmpRow.push_back(fiu);    //FIU
      tmpRow.push_back(fium);   //FIUM
      
      outputFile.content.addRow(tmpRow);
    }
  }

  // ------------------  6. Save result in file
  if(outputFile.writeCsv()) cout << "Resultado guardado en " << outputFile.getPath() << endl << endl;

  enterToContinue("");

  return APP_SUCCESS;
}