#ifndef _FILE_HPP_
#define _FILE_HPP_

#include "MyMatrix.hpp"

class MyFile{

private:
  std::string _path;
  std::string _filter;
  
  bool isCsvFormat(std::string path);
  bool isExpectedDelimitator(std::string line);  
  bool requestCsvPath(void);
  bool readCsv();
  bool setCsvPath(std::string path);

public:
  MyFile(){};
  MyFile(std::string path):_path(path){};
  
  MyMatrix content;

  std::string getPath() { return _path;}
  std::string getFilter() { return _filter;}  
  void printFileInfo();
  void setFilterFromList(std::vector <std::string> v);
  void requestOpenFile(std::string FileName, bool printInfo) ;
  bool openFile(std::string filePath, bool printInfo);  
  bool writeCsv();
};

#endif