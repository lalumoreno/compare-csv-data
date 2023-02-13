#ifndef _FILE_HPP_
#define _FILE_HPP_

#include <string>
#include <vector>

class MyFile{

private:
  std::string _path;
  std::vector<std::vector<std::string>> _content;
  
  bool isCsvFormat(std::string path);
  int getColTotal(){ return getRowTotal() > 0? _content[0].size() : 0;}

public: 

  std::string _filter;

  bool requestCsvPath(void);
  bool setCsvPath(std::string path);
  bool readCsv();
  void printFileContent();
  void printFileInfo();
  std::string getStringByRowCol(int row, int col);
  int getIntByRowCol(int row, int col);
  int getColNumByTitle(std::string word);
  int getRowByStringInCol(int col, std::string word);
  void printDataInCol(int col);
  int getRowTotal(){ return _content.size();}
  std::vector<std::string> getListbyCol(int col);
  void setFilterFromList(std::vector <std::string> v);
  std::vector<std::string> getRowDatabyRow(int row);
  void requestOpenFile(std::string FileName) ;
  bool openFile(std::string filePath);
};

#endif