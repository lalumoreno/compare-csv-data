#ifndef _FILE_HPP_
#define _FILE_HPP_

#include "MyMatrix.hpp"

class MyFile{

private:

  enum DELIMITATOR
  {
    DELIMITATOR_1,
    DELIMITATOR_2,
    DELIMITATOR_UNKWON
  }; 

  std::string _path;
  std::string _filter;
  
  bool isCsvFormat(std::string path);  
  bool requestCsvPath(void);
  bool readCsv();
  bool setCsvPath(std::string path);
  DELIMITATOR getDelimitator(std::string line);

public:

  MyFile(){};
  MyFile(std::string path):_path(path){};
  
  MyMatrix content;

  std::string getPath() { return _path;}
  std::string getFilter() { return _filter;}  
  void printFileInfo();
  void setFilterFromList(std::vector <std::string> v);
  void requestOpenFile(std::string FileName, bool printInfo) ;
  bool readFile(std::string filePath, bool printInfo);  
  bool writeCsv();
  bool createCsv(std::string filePath);  
};

#endif