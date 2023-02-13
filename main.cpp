// Example program
#include <iostream>
#include "MyFile.hpp"

#define FAILURE -1

using namespace std;

int main()
{
  //TODO: Add flags for execution
  //do not close app until press any key
  cout << "compare-csv-data V. 1.0.0" << endl;
  cout << "-------------------------------" << endl << endl;

  cout << "Doc referencia:" << endl;
  //Open reference document by name
  MyFile refDoc;
  //refDoc.setPath();  
  refDoc.setPath("files/ref.csv");
  if (refDoc.readCsv()) {
    refDoc.printFileInfo();
  } else {
    return FAILURE;
  }

  //Open main document by name
  cout << "Doc TC1:" << endl;
  MyFile tc1;
  tc1.setPath("files/doc.csv");
  if (tc1.readCsv()) {
    tc1.printFileInfo();
  } else {
    return FAILURE;
  }

  //Read config file for column association
  //TODO verify values or fill it using app
  cout << "Config:" << endl;
  MyFile configFile;
  configFile.setPath("files/config.csv");
  if(configFile.readCsv()) {
    configFile.printFileInfo();
    //TODO print name of columns to compare
  } else {
    return FAILURE;
  }

  cout << "Num circuito: " << endl;
  MyFile numCirc;
  numCirc.setPath("files/cod.csv");
  if(numCirc.readCsv()){
    numCirc.printFileInfo();
  } else {
    return FAILURE;
  }
  
  /*
  cout << "compare " << refDoc.getStringByRowCol(0,configFile.getIntByRowCol(0,0)-1) <<
  " with " << otherDoc.getStringByRowCol(0,configFile.getIntByRowCol(0,1)-1) << endl;
*/
  //filter ref doc by OPERADOR_RED
  //TODO Read filter name from config file
  int refColOpRed = refDoc.getColNumByTitle("OPERADOR_RED");
  vector<string> v = refDoc.getListbyCol(refColOpRed);

  refDoc.setFilterFromList(v);

  //Look for title in ref and TC1 file
  int refColTitle1 = configFile.getIntByRowCol(0,0)-1;
  int otherColTitle1 = configFile.getIntByRowCol(0,1)-1;
  
  vector<string> rowFound;
  int i;

  //FILTER

  if(refColTitle1 >= 0) {    
    string tmp;
    int c;       
    string refString;
    string otherString;
    
    //for each row in column a of ref, find frontera in TC1
    for(i=1;i<refDoc.getRowTotal();i++) {
      
      //If ref filter does not match
      if(refDoc._filter.compare(refDoc.getStringByRowCol(i,refColOpRed)) != 0 )
        continue;

      tmp = refDoc.getStringByRowCol(i,refColTitle1);      
      c = tc1.getRowByStringInCol(otherColTitle1,tmp);
      if (c >= 0){
        //cout << "word " << tmp << " found in row " << c << " of other doc" << endl;              
        //rowFound.push_back(tmp);

        //Compare all other columns
        for(int y = 1; y<configFile.getRowTotal(); y++ ) {
          
          int refCol = configFile.getIntByRowCol(y,0)-1;
          int otherCol = configFile.getIntByRowCol(y,1)-1;

          string refTitle = refDoc.getStringByRowCol(0,refCol);
          string otherTitle = tc1.getStringByRowCol(0,otherCol);     

          //NUMERO DE CIRCUITO
          if(refCol==28){
            int cod = refDoc.getIntByRowCol(i,refCol);
            string codString = numCirc.getStringByRowCol(cod,1);
            refString = codString;
            //convert data
          } else {
              refString = refDoc.getStringByRowCol(i,refCol);
          }

          otherString = tc1.getStringByRowCol(c,otherCol);
          
          if(refString.compare(otherString) != 0){
            cout << tmp <<"; "<< refTitle << ": " << refString << ", " << otherTitle << ": " << otherString << endl;
          }        
        }
      } else {
        cout << tmp << "; no se encuentra en TC1" << endl;
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