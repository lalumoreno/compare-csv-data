#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

#include "MyFile.hpp"

using namespace std;

void removeDuplicated(std::vector<int> &v);

void MyFile::setPath(string path) {  
  _path = path;    
}

void MyFile::setPath() {
  string path;
  cout << "What is doc path? ";
  getline(cin, path);    
  _path = path;
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
  cout << "path: " << _path << endl;
  cout << "rows: " << getRowsNumber() << endl;
  cout << "columns: " << getColNumber() << endl;
  cout << "----------------------- " << endl << endl;

}

bool MyFile::readCsv() {

  //TODO check that is a csv file
  cout << "Opening, " << _path << endl;

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
    cout<<"Could not open the file" << endl;
    return false;
  }

  return true;
}

string MyFile::getStringInRowCol(int row, int col) {
  
  return _content[row][col];  

 }

int MyFile::findColumnName(string word) {
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

vector<string> MyFile::getDataInColList(int col) {

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

int MyFile::findStringinCol(int col, string word) {

  //row
  for(int i=0;i<_content.size();i++) {
    //column
    if( word.compare(_content[i][col]) == 0 ) {
      return i;
    }    
  }

  return -1; 
}

void MyFile::setFilter(vector <string> v) {

  cout << "Filter by " << endl;
  int ite = 0;

  for (auto it = v.cbegin(); it != v.cend(); ++it) {
        cout << "option " << ++ite << ". " << *it << endl;
    }

  cout << endl;

  int option;
  cin >> option;
  //TODO evaluate option
  _filter = v[option-1]; 

  cout << _filter << " filter selected " << endl;

}