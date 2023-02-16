#include <iostream>
#include <sstream>
#include <fstream>

#include "MyMatrix.hpp"

using namespace std;

void removeDuplicated(vector<string> &v)
{
    auto end = v.end();
    for (auto it = v.begin(); it != end; ++it) {
        end = std::remove(it + 1, end, *it);
    }
 
    v.erase(end, v.end());
}

void MyMatrix::printMatrix() {
  
  for(int i=0;i<_matrix.size();i++) {
    //column
    for(int j=0;j<_matrix[i].size();j++) {
      cout<<_matrix[i][j]<<" ";
    }
    cout<< endl;
  }
}

string MyMatrix::getStringByRowCol(int row, int col) {
  
  if (row < getTotalRow()) {
    return _matrix[row][col];  
  } else {
    return "";
  }
}

int MyMatrix::getIntByRowCol(int row, int col) {

   if (row < getTotalRow()) {
    return stoi(_matrix[row][col]); 
  } else {
    return -1;
  }  

}

int MyMatrix::getColNumByTitle(string word) {
  //row
  for(int i=0;i<_matrix.size();i++) {
    //column
    for(int j=0;j<_matrix[i].size();j++) {
      if( word.compare(_matrix[i][j]) == 0 ) {
        return j;
      }
    }  
  }

  return -1;
}

void MyMatrix::printDataInCol(int col) {

  if(col > 0) {
  //row
  for(int i=0;i<_matrix.size();i++) {    
      cout << _matrix[i][col] << endl;
    }      
  }      
}

vector<string> MyMatrix::getRowDatabyRow(int row) {

  return _matrix[row];

}

int MyMatrix::getRowByStringInCol(int col, string word) {

  //row
  for(int i=0;i<_matrix.size();i++) {
    //row
    if( word.compare(_matrix[i][col]) == 0 ) {
      return i;
    }    
  }

  return -1; 
}

//Returns data in column without title and no repeated values
vector<string> MyMatrix::getListbyCol(int col) {

  vector<string> colData;

  if(col > 0) {
    for(int row=1; row<_matrix.size(); row++) {
      colData.push_back(_matrix[row][col]);
    }
    removeDuplicated(colData);
  }

  return colData;
}