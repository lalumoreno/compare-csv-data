#ifndef _FILE_HPP_
#define _FILE_HPP_

#include <string>

class MyFile{

private:
  std::string _path;

public: 
    bool setPath();
    bool openCsv();    
    
    std::string getPath(){return _path;};


};

#endif