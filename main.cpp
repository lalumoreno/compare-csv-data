// Example program
#include <iostream>
#include "MyFile.hpp"

using namespace std;

int main()
{
  //TODO: Add flags for execution
  cout << "compare-cs-data Version 1.0.0" << endl;

  cout << "Reference doc:" << endl;

  //Open reference document by name
  MyFile refDoc;
  //refDoc.setPath();  
  refDoc.setPath("files/ref.csv");
  if (refDoc.readCsv()) {
    refDoc.printFileInfo();
  }

  //Open main document by name
  cout << endl << "Other doc:" << endl;
  MyFile otherDoc;
  otherDoc.setPath("files/doc.csv");
  if (otherDoc.readCsv()) {
    otherDoc.printFileInfo();
  }

  //Read config file for column association
  //TODO verify values or fill it using app
  cout << endl << "Config file:" << endl;
  MyFile configFile;
  configFile.setPath("files/config.csv");
  if(configFile.readCsv()) {
    configFile.printFileContent();
    configFile.printFileInfo();
  }
  
  //filter ref doc by OPERADOR_RED
  //TODO Read filter name from config file
  int refColOpRed = refDoc.getColNumByTitle("OPERADOR_RED");
  vector<string> v = refDoc.getListbyCol(refColOpRed);

  refDoc.setFilterFromList(v);

  //Look for title in ref and other file
  int refColTitle1 = refDoc.getColNumByTitle(configFile.getStringByRowCol(0,0));
  cout << "first title " << configFile.getStringByRowCol(0,0) << " found in column " << refColTitle1 << " of reference doc" << endl;
  
  int otherColTitle1 = otherDoc.getColNumByTitle(configFile.getStringByRowCol(0,1));
  cout << "second title " << configFile.getStringByRowCol(0,1) << " found in column " << otherColTitle1 << " of other doc" << endl << endl;
  
  vector<string> rowFound;  
int i;

  //FILTER
  //for each row in column a of ref , find frontera in otherdoc
  if(refColTitle1 >= 0) {    
    string tmp;
    int c;       
    
    for(i=1;i<refDoc.getRowTotal();i++) {
      
      //If ref filter not match
      if(refDoc._filter.compare(refDoc.getStringByRowCol(i,refColOpRed)) != 0 )
        continue;

      tmp = refDoc.getStringByRowCol(i,refColTitle1);      
      c = otherDoc.getRowByStringInCol(otherColTitle1,tmp);
      if (c >= 0){
        cout << "word " << tmp << " found in row " << c << " of other doc" << endl;              
        //rowFound.push_back(tmp);

        //Compare all columns
        for(int y = 1; y<configFile.getRowTotal(); y++ ) {
          
          string refTitle = configFile.getStringByRowCol(y,0);
          string otherTitle = configFile.getStringByRowCol(y,1);
          cout << "comparing " << refTitle << " with " << otherTitle  <<endl;

          int refCol = refDoc.getColNumByTitle(refTitle);
          int otherCol = otherDoc.getColNumByTitle(otherTitle);

          string otherString = otherDoc.getStringByRowCol(c,otherCol);
          string refString = refDoc.getStringByRowCol(i,refCol);

          if(refString.compare(otherString) != 0){
            cout << tmp <<" - "<< refTitle << ": " << refString << " " << otherTitle << ": " << otherString << endl;
          } else {
            //cout << tmp << "all fields equal" << endl;
          }
        
        }

      } else {
        cout << tmp << " NOT found in other doc" << endl;
      }
      
    }
  
  }  

  #if 0
  if(rowFound.size() > 0) {

     for(i=0;i<rowFound.size();i++) { //row
      int p = otherDoc.getRowByStringInCol(otherColTitle1,rowFound[i]);
      cout << "word " << rowFound[i] << " found in row " << p << " of other doc" << endl;               

      }
    }  
  
#endif
   //For each row in reference document
    //Look for id in second document
      //If matched compare first A column with B 
        //If any difference in rows, print the difference with ID 
      //else print an error

  return 0;

}