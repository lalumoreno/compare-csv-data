// Example program
#include <iostream>
#include "MyFile.hpp"

using namespace std;

int main()
{
  //Add flags for execution

  cout << endl << "Reference doc:" << endl;

  //Open reference document by name - request name?
  MyFile refDoc;
  //refDoc.setPath();  
  refDoc.setPath("files/ref.csv");
  if (refDoc.readCsv()) {
    refDoc.printFileInfo();
  }

  //Open main document by name - request name?
  cout << endl << "Other doc:" << endl;
  MyFile otherDoc;
  otherDoc.setPath("files/doc.csv");
  if (otherDoc.readCsv()) {
    otherDoc.printFileInfo();
  }

  //Read that association - can be edited manually
  //In the future can be edited using the app
  cout << endl << "Config file:" << endl;
  MyFile configFile;
  configFile.setPath("files/config.csv");
  if(configFile.readCsv()) {
    configFile.printFileContent();
  }
  
  //filter ref doc by OPERADOR_RED
  int refColOpRed = refDoc.findColumnName("OPERADOR_RED");
  vector<string> v = refDoc.getDataInColList(refColOpRed);

  refDoc.setFilter(v);

  //Look for title in content? 
  //first column with all columns 
  int refColTitle1 = refDoc.findColumnName(configFile.getStringInRowCol(0,0));
  cout << "first title " << configFile.getStringInRowCol(0,0) << " found in column " << refColTitle1 << " of reference doc" << endl;
  
  int otherColTitle1 = otherDoc.findColumnName(configFile.getStringInRowCol(0,1));
  cout << "second title " << configFile.getStringInRowCol(0,1) << " found in column " << otherColTitle1 << " of other doc" << endl << endl;
  
  //for each row in column a of ref , find row in otherdoc and compare all columns
  //refDoc.getDataInCol(a);    

  if(refColTitle1 >= 0) {    
    string tmp;
    int c; 

    for(int i=1;i<refDoc.getRowsNumber();i++) {
      //TODO evluate filter
      if(refDoc._filter.compare(refDoc.getStringInRowCol(refColOpRed,i)) != 0 )
        continue;

      tmp = refDoc.getStringInRowCol(i,refColTitle1);      
      c = otherDoc.findStringinCol(otherColTitle1,tmp);
      if (c >= 0){
        cout << "word " << tmp << " found in row " << c << " of other doc" << endl;
      } else {
        cout << "word " << tmp << " NOT found in other doc" << endl;
      }
      
    }
  }

  

   //For each row in reference document
    //Look for id in second document
      //If matched compare first A column with B 
        //If any difference in rows, print the difference with ID 
      //else print an error

  return 0;

}