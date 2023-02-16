#ifndef _FILE_HPP_
#define _FILE_HPP_

#include "MyMatrix.hpp"

class MyFile{

private:
  std::string _path;
  std::string _filter;
  
  bool isCsvFormat(std::string path);
  bool isExpectedDelimitator(std::string line);  

public:
  MyMatrix content;

  std::string getPath() { return _path;}
  std::string getFilter() { return _filter;}  
  bool requestCsvPath(void);
  bool setCsvPath(std::string path);
  bool readCsv();
  void printFileInfo();
  void setFilterFromList(std::vector <std::string> v);
  void requestOpenFile(std::string FileName, bool printInfo) ;
  bool openFile(std::string filePath, bool printInfo);
};

#endif