#ifndef _MY_APP_HPP_
#define _MY_APP_HPP_

#include <string>

#define APP_FAILURE -1
#define APP_SUCCESS 0

class MyApp {

private:
    std::string name;
    std::string version;    
    std::string description;
    std::string use;
    
    std::string menuOption;
        
public: 
    
    enum{
        ENTER,
        INFO,
        EXIT,
        NOT_VALID
    };

    MyApp();
    void setName(std::string n) {this->name = n;};
    void setVersion(std::string ver) {this->version = ver;};
    void setDescription(std::string desc) {this->description = desc;};        
    void setUse(std::string u) {this->use = u;};        
    std::string getName() {return this->name;};
    std::string getVersion() {return this->version;};
    std::string getDescription() {return this->description;};
    std::string getUse() {return this->use;};

    void showDescription();    
    void showUse();
    int enterToContinue(std::string text);
    virtual int Main();

};

#endif
