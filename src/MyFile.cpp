#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

#include "MyFile.hpp"

#define DELIMITATOR ';'

using namespace std;

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
  
  if(path.size() < 5) {
    cout << "ERROR: Ruta invalida [" << path  << "]"<< endl; 
    return false; 
  } 
  
  string format = path.substr(path.size()-4); 
  if(format.compare(".csv") != 0 ) {
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

bool MyFile::isExpectedDelimitator(string line) {
  if (line.find(DELIMITATOR) != string::npos) {
    return true;
  } else {
    cout<<"ERROR: Verifique que el delimitador es ';' en el archivo: [" << _path << "]" << endl;
    return false;
  }
}

bool MyFile::readCsv() {
  
  vector<string> row;
  string line, word;
  fstream file(_path, ios::in);
  bool firstRow = true;

  if(file.is_open()){
    while(getline(file, line))//get each line in file
    {
      //Check if ';' delimitator
      if(firstRow) {         
        if (isExpectedDelimitator(line)) {
          firstRow = false;          
        } else {          
          return false;
        }
      }

      row.clear();
      stringstream str(line); //get whole line string
 
      //get each word in str sepparated by ; 
      while(getline(str, word, DELIMITATOR)) {
        row.push_back(word); //save each word in row
      }    

      content.addRow(row); //save each row in content
      
    }
  } else {
    cout<<"ERROR: No se puede abrir el archivo: [" << _path << "]" << endl;
    return false;
  }

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
    optionRow = option-1;
    if(optionRow >= v.size()) {
      cout << "Opcion invalida" << endl;
    } else break;
  }
    
  _filter = v[optionRow]; 

  cout << "Filtro seleccionado: " << _filter << endl << endl;

}

void MyFile::save() {

 fstream file(_path, ios::out); 

 if(file.is_open()){

  file << content.getStringByRowCol(0,0);

 }
}