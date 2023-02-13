#include <iostream>
#include "MyApp.hpp"

using namespace std;

int main()
{
  MyApp app; 
  //int initMenuOption = MyApp::NOT_VALID;
  app.showAppDescription();
  /*
  while(initMenuOption != MyApp::ENTER) {
    initMenuOption = app.initMenu();

    if(initMenuOption == MyApp::EXIT) {
      return 0;
    }
  }
  */

  app.Main();
  app.exitMenu();    
   
  return 0;
}
