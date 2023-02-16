#ifndef _MY_APP_HPP_
#define _MY_APP_HPP_

#include <string>

#define APP_FAILURE -1
#define APP_SUCCESS 0

class MyApp {

private:
    std::string menuOption;
    
public: 
    
    enum{
        ENTER,
        INFO,
        EXIT,
        NOT_VALID
    };

    void showAppDescription();
    void showAppUse();
    int entryMenu();
    int enterToContinue(std::string text);    
    int Main();

};

#endif
