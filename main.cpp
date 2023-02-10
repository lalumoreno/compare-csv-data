// Example program
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

#include "inc/MyFile.hpp"

using namespace std;

//Move this to correct fike
bool MyFile::setPath() {
    string path;
    cout << "What is doc path? ";
    getline (cin, path);
    
    _path = path;

    return true;
    //false if empty
}


bool MyFile::openCsv() {

  cout << "Opening, " << _path << "\n";
  
  vector<vector<string>> content;
  vector<string> row;
  string line, word;
  fstream file(_path, ios::in);
  
  if(file.is_open()){
    while(getline(file, line))
    {
      row.clear();
      stringstream str(line);
 
      while(getline(str, word, ','))
        row.push_back(word);
        content.push_back(row);
    }
  } else {
    cout<<"Could not open the file\n";
  }
 
  for(int i=0;i<content.size();i++) {
    for(int j=0;j<content[i].size();j++) {
      cout<<content[i][j]<<" ";
    }
    cout<<"\n";
  }

  return true;
}

int main()
{
  cout << "Reference doc:";

  MyFile refDoc;
  refDoc.setPath();
  //refDoc.openCsv();
  refDoc.openCsv();

  cout << "Main doc:";
  MyFile mainDoc;
  mainDoc.setPath();
  mainDoc.openCsv();

  //Open reference document by name - request name?
  //Request column name of fronteraID or fixed column
  //Open main document by name - request name?
  //Request column name of fronteraID or fixed column

  //On another file save names of the columns to compare in ref and main doc
  //Read that association - can be edited manually
  //In the future can be edited using the app

  //For each row in reference document
    //Look for id in second document
      //If matched compare first A column with B 
        //If any difference in rows, print the difference with ID 
      //else print an error

  return 0;

}