#ifndef _FILE_HPP_
#define _FILE_HPP_

#include <string>
#include <vector>

class MyFile{

private:
  std::string _path;
  std::vector<std::vector<std::string>> _content;  

  std::string getPath(){ return _path; };  
  
  int getColNumber(){ return getRowsNumber() > 0? _content[0].size() : 0;}

public: 

  std::string _filter;

  void setPath(void);
  void setPath(std::string path);
  bool readCsv();
  void printFileContent();
  void printFileInfo();
  std::string getStringInRowCol(int row, int col);
  int findColumnName(std::string word);
  int findStringinCol(int col, std::string word);
  void printDataInCol(int col);
  int getRowsNumber(){ return _content.size();}
  std::vector<std::string> getDataInColList(int col);
  void setFilter(std::vector <std::string> v);
};

#endif