#ifndef _MY_MATRIX_HPP_
#define _MY_MATRIX_HPP_

#include <string>
#include <vector>

class MyMatrix {

private:
    std::vector<std::vector<std::string>> _matrix;

public:    
    int getTotalRow(){ return _matrix.size();}
    int getTotalCol(){ return _matrix.size() > 0 ? _matrix[0].size() : 0;}
    void printMatrix();
    void addRow(std::vector<std::string> row) { _matrix.push_back(row);};
    std::string getStringByRowCol(int row, int col);
    int getIntByRowCol(int row, int col);
    int getColNumByTitle(std::string word);
    int getRowByStringInCol(int col, std::string word);
    void printDataInCol(int col);
    std::vector<std::string> getRowDatabyRow(int row);
    std::vector<std::string> getListbyCol(int col);

};

#endif