#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

#include "MyFile.hpp"

#define DELIMITATOR1     ';'
#define DELIMITATOR2     ','

using namespace std;

string FILE_FORMAT = ".csv";

//with user input
void MyFile::requestOpenFile(string FileName, bool printInfo) {

  while(true) {
    cout << "Inserte ruta de " << FileName << ":";
    if ( requestCsvPath() ) {    
      if ( readCsv() ) {
        printFileInfo();
        break;
      } 
    }
  }   
}

bool MyFile::createCsv(string filePath) {
     
    if ( !setCsvPath(filePath) ) {
      return false;
    }   
 
    return true;
}

bool MyFile::openFile(string filePath, bool printInfo) {
     
    if ( !setCsvPath(filePath) ) {
      return false;
    }
    
    if ( !readCsv() ) {
        return false;
    }
    
    if (printInfo) printFileInfo();      

    return true;
}

bool MyFile::isCsvFormat(string path) {  

  if(path.size() < FILE_FORMAT.size()) {
    cout << "ERROR: Ruta invalida [" << path  << "]"<< endl; 
    return false; 
  }
  
  string format = path.substr(path.size()-FILE_FORMAT.size());
  
  if(format.compare(FILE_FORMAT) != 0 ) {
    cout << "ERROR: El formato debe ser .csv [" << path  << "]"<< endl; 
    return false;
  }

  return true;
}

bool MyFile::setCsvPath(string path) {

  if (!isCsvFormat(path)) {
    return false;
  }

  _path = path;
  return true;
}

bool MyFile::requestCsvPath() {

  string path;  
  getline(cin, path);    
  
  //Validate format
  if (!isCsvFormat(path)) {
    cin.clear();
    return false;
  }
  
  _path = path;  
  return true;
  
}

void MyFile::printFileInfo() {  
  
  cout << "----------------------- " << endl;
  cout << "Ruta: " << _path << endl;
  cout << "Filas: " << content.getTotalRow() << endl;
  cout << "Columnas: " << content.getTotalCol() << endl;
  cout << "----------------------- " << endl << endl;

}

MyFile::DELIMITATOR MyFile::getDelimitator(string line) {

  if (line.find(DELIMITATOR1) != string::npos) {
    return DELIMITATOR_1;
  } else if (line.find(DELIMITATOR2) != string::npos) {    
    return DELIMITATOR_2;
  } else {
    cout<<"ERROR: Verifique que el delimitador es ';' o ',' en el archivo: [" << _path << "]" << endl;
    return DELIMITATOR_UNKWON;
  }
}

bool MyFile::readCsv() {
  
  vector<string> row;
  string line, word;
  fstream file(_path, ios::in);
  bool firstRow = true;
  DELIMITATOR delimit;
  char del;

  if(file.is_open()){
    while(getline(file, line))//get each line in file
    {
      //Check if ';' or ',' delimitator
      if(firstRow) {
        delimit = getDelimitator(line);
        if(delimit == DELIMITATOR_UNKWON) {
          return false;          
        } else {
          firstRow = false;                    
        }
      }

      del = (delimit == DELIMITATOR_1) ? DELIMITATOR1 : DELIMITATOR2;
      
      row.clear();
      stringstream str(line); //get whole line string
 
      //get each word in str sepparated by ; 
      while(getline(str, word, del)) {
        row.push_back(word); //save each word in row
      }    

      content.addRow(row); //save each row in content
      
    }
  } else {
    cout<<"ERROR: No se puede abrir el archivo: [" << _path << "]" << endl;
    return false;
  }
  
  file.close();
  return true;
}

void MyFile::setFilterFromList(vector <string> v) {
  
  int i = 1;
  int option;
  int optionRow;

  cout << "Seleccione filtro:" << endl;  
  for (auto it = v.cbegin(); it != v.cend(); ++it) {
        cout << i++ << ". " << *it << endl;
    }

  cout << endl;

  while(true) {
    cin >> option;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    optionRow = option-1;
    if(optionRow >= v.size()) {
      cout << "Opcion invalida" << endl;
    } else break;
  }
    
  _filter = v[optionRow]; 

  cout << "Filtro seleccionado: " << _filter << endl << endl;

}

bool MyFile::writeCsv() {

 fstream file(_path, ios::out);

 if(file.is_open()){
  for(int row = 0; row < content.getTotalRow(); row++ ) {    
    for(int col = 0; col < content.getTotalCol(); col++) {
      file << content.getStringByRowCol(row,col);
      file << DELIMITATOR1;
    }
    file << endl;     
  }
 } else {
    cout<<"ERROR: No se puede abrir el archivo: [" << _path << "]" << endl;
    return false;
 }

  file.close();
  return true; 
 
}