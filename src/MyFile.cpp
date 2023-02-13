#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

#include "MyFile.hpp"

using namespace std;

void removeDuplicated(std::vector<int> &v);

//with user input
void MyFile::requestOpenFile(string FileName) {

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

bool MyFile::openFile(string filePath) {
     
    if ( !setCsvPath(filePath) ) {
      return false;
    }
    
    if ( !readCsv() ) {
        return false;
    }
    
    printFileInfo();      
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

void MyFile::printFileContent() {
  
  //row
  for(int i=0;i<_content.size();i++) {
    //column
    for(int j=0;j<_content[i].size();j++) {
      cout<<_content[i][j]<<" ";
    }
    cout<< endl;
  }
}

void MyFile::printFileInfo() {  
  
  cout << "----------------------- " << endl;
  cout << "Ruta: " << _path << endl;
  cout << "Filas: " << getRowTotal() << endl;
  cout << "Columnas: " << getColTotal() << endl;
  cout << "----------------------- " << endl << endl;

}


bool MyFile::readCsv() {
  
  vector<string> row;
  string line, word;
  fstream file(_path, ios::in);
  
  if(file.is_open()){
    while(getline(file, line))//get each line in file
    {
      row.clear();
      stringstream str(line); //get whole line string
 
      //get each word in str sepparated by ; 
      while(getline(str, word, ';')) { 
        row.push_back(word); //save each word in row
      }    

      _content.push_back(row); //save each row in content
    }
  } else {
    cout<<"No se pudo abrir el archivo: " << endl;
    return false;
  }

  return true;
}

string MyFile::getStringByRowCol(int row, int col) {
  
  return _content[row][col];  

 }

int MyFile::getIntByRowCol(int row, int col) {
  
  return stoi(_content[row][col]);  

 }

int MyFile::getColNumByTitle(string word) {
  //row
  for(int i=0;i<_content.size();i++) {
    //column
    for(int j=0;j<_content[i].size();j++) {
      if( word.compare(_content[i][j]) == 0 ) {
        return j;
      }
    }  
  }

  return -1;
}

void MyFile::printDataInCol(int col) {

  if(col > 0) {
  //row
  for(int i=0;i<_content.size();i++) {    
      cout << _content[i][col] << endl;
    }      
  }      
}

void removeDuplicated(vector<string> &v)
{
    auto end = v.end();
    for (auto it = v.begin(); it != end; ++it) {
        end = std::remove(it + 1, end, *it);
    }
 
    v.erase(end, v.end());
}

//Returns data in column without repeat values
vector<string> MyFile::getListbyCol(int col) {

  vector<string> colData;

  if(col > 0) {
  //row
  for(int i=0;i<_content.size();i++) {    
      colData.push_back(_content[i][col]);
    }      

    removeDuplicated(colData);
  }

  return colData;
}

int MyFile::getRowByStringInCol(int col, string word) {

  //row
  for(int i=0;i<_content.size();i++) {
    //row
    if( word.compare(_content[i][col]) == 0 ) {
      return i;
    }    
  }

  return -1; 
}

//TODO improve
void MyFile::setFilterFromList(vector <string> v) {

  cout << "Seleccione filtro:" << endl<< endl;
  int ite = 0;

  for (auto it = v.cbegin(); it != v.cend(); ++it) {
        if(ite == 0){
          ite++;
          continue;
        }
        cout << ite++ << ". " << *it << endl;
    }

  cout << endl;

  int option;
  cin >> option;
  //TODO evaluate valid option
  _filter = v[option]; 

  cout << "Filtro seleccionado: " << _filter << endl;

}

vector<string> MyFile::getRowDatabyRow(int row) {

  return _content[row];

}
