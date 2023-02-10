#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

#include "MyFile.hpp"

using namespace std;

bool MyFile::setPath() {
    string path;
    cout << "What is reference doc path? ";
    getline (cin, path);
    cout << "Opening, " << path << "\n";

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