#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>


using namespace std;

template <typename T> class Matrix {
    private:
        int size;
        vector<vector<T>> data;
    
    public:
        Matrix(vector<vector<T>> nums){
            data = nums;
            size = nums.size();
        }
        Matrix operator+(const Matrix &other) const{
            Matrix<T> result(vector<vector<T>>(size, vector<T>(size, 0)));
            for(int i = 0; i < size; i++){ //iterate through every element
                for(int j = 0; j < size; j++){
                    T sum = data[i][j] + other.data[i][j]; //add the elements of both matrixies together, append it to the result matrix
                    result.data[i][j] = sum;
                }
            }
            return result;
        }
        
        Matrix operator*(const Matrix &other){ //overload multiplication
            Matrix<T> result(vector<vector<T>>(size, vector<T>(size, 0)));
            for(int i = 0; i < size; i++){
                for(int j = 0; j < size; j++){ //multply rows against columns, sum the results, and append result matrix
                    T sum = 0; 
                    for(int k = 0; k < size; k++){ 
                        sum+=data[i][k]*other.data[k][j];
                    }
                    result.data[i][j] = sum;
                }
            }
            return result;
        }
        void setValue(std::size_t i, std::size_t j, T n){
            data[i][j] = n;
            printMatrix();
        }
        int getValue(std::size_t i, std::size_t j) const{
            return data[i][j];
        }
        int getSize() const{
            return size;
        }
        int sumMajorDiagonal() const{
            T sum;
            for(int i = 0; i < size; i++){ //go through every diagonal entry, summing them together
                sum+=data[i][i];
            }
            cout << sum << "\n";
            return(sum);
        }
        int sumMinorDiagonal() const{
            T sum = 0;
            for(int i = size-1; i >= 0; i--){ //start at last column and move backward
                sum+=data[size-1-i][i]; //iterate over each row, picking the i column
            }
            cout << sum << "\n";
            return(sum);
        }
        void swapRows(std::size_t r1, std::size_t r2){
            vector<T> tempRow = data[r1];
            data[r1] = data[r2];
            data[r2] = tempRow;
            printMatrix();
            
        }
        void swapCols(std::size_t c1, std::size_t c2){
            for(int i = 0; i < size; i++){ //similar to swapRow, but need to iterate over each row
                T tempval = data[i][c1];
                data[i][c1] = data[i][c2];
                data[i][c2] = tempval;
            }
            printMatrix();
        }
        void printMatrix() const{
            for(int i = 0; i < size; ++i){
                for(int j = 0; j < size; ++j){
                    cout << data[i][j] << " ";
                }
                cout << "\n";
            }
            cout << "\n";
        }
};

template <typename T>
void printMenu(Matrix<T> &matrixA,Matrix<T> &matrixB){
    while(true){ //loop to handle exit
        int choice;
    
        cout << "1) Add matricies" << "\n";
        cout << "2) Multiply matricies" << "\n";
        cout << "3) Sum diagonals" << "\n";
        cout << "4) Swap rows" << "\n";
        cout << "5) Swap columns" << "\n";
        cout << "6) Set element" << "\n";
        cout << "7) Exit" << "\n";

        cin >> choice; //get choice from user

        switch(choice){ //call respective functions
            case 1:
                (matrixA + matrixB).printMatrix();
                break;
            case 2:
                (matrixA * matrixB).printMatrix();
                break;
            case 3:
                cout << "Major: ";
                matrixA.sumMajorDiagonal();
                cout << "Minor: ";
                matrixA.sumMinorDiagonal();
                break;
            case 4:
                
                while(true){ //loop to prompt user until in-bounds selection is chosen
                    int r1,r2;
                    cout << "Enter first row: ";
                    cin >> r1;
                    cout << "Enter second row: ";
                    cin >> r2;
                    if((r1 < matrixA.getSize() && r1 >= 0)&&(r2 < matrixA.getSize() && r2 >= 0)){
                        matrixA.swapRows(r1,r2);
                        break;
                    }
                    else{
                        cout << "Selection out of bounds.\n";
                    }
                }
                break;
            case 5:
                
                while(true){ //loop to prompt user until in-bounds selection is chosen
                    int c1,c2;
                    cout << "Enter first column: ";
                    cin >> c1;
                    cout << "Enter second column: ";
                    cin >> c2;
                    if((c1 < matrixA.getSize() && c1 >= 0)&&(c2 < matrixA.getSize() && c2 >= 0)){
                    matrixA.swapCols(c1,c2);
                    break;
                    }
                    else{
                        cout << "Selection out of bounds.";
                    }
                }
                break;
            case 6:
                
                while(true){ //loop to prompt user until in-bounds selection is chosen
                    int row,col,val;
                    cout << "Enter row: ";
                    cin >> row;
                    cout << "Enter column: ";
                    cin >> col;
                    cout << "Enter value: ";
                    cin >> val;
                    if((row < matrixA.getSize() && row >= 0)&&(col < matrixA.getSize() && col >= 0)){
                    matrixA.setValue(row,col,val);
                    break;
                    }
                    else{
                        cout << "Selection out of bounds.";
                    }
                }
                break;
            case 7:
                return; //return from function, exiting program
            default: 
                cout << "Invalid selection";
                printMenu(matrixA,matrixB);
                break;
        }
    }
}
vector<vector<string>> readData(vector<string> fileData, int start, int end, int type ){

    vector<vector<string>> returnData;

    for(int i = start; i < end; i++){

        vector<string> row;
        regex searchTerm;
        
        if(type == 1){
            searchTerm = ("(\\d+[.]\\d+)");
        } else {
            searchTerm = ("(\\d+)");
        }
        
        auto lineStart = sregex_iterator(fileData[i].begin(),fileData[i].end(),searchTerm);
        auto lineEnd = sregex_iterator();
        for(sregex_iterator i = lineStart; i != lineEnd; ++i){
            smatch match = *i;
            row.push_back(match.str());
        }
        returnData.push_back(row);
    }
    
    return returnData;

}
void compileMatricies(vector<vector<string>> matrixAData, vector<vector<string>> matrixBData, int size, int type){
    
    if(type==0){

        vector<vector<int>> convertAData(size,vector<int>(size));
        vector<vector<int>> convertBData(size,vector<int>(size));

        for(int i = 0; i < size; ++i){
            for(int j = 0; j < size; ++j){
                convertAData[i][j] = stoi(matrixAData[i][j]);
                convertBData[i][j] = stoi(matrixBData[i][j]);
            }
        }
        Matrix<int> matrixA(convertAData);
        Matrix<int> matrixB(convertBData);

        matrixA.printMatrix();
        matrixB.printMatrix();
        printMenu(matrixA,matrixB);
    }
    else{
        vector<vector<double>> convertAData(size,vector<double>(size));
        vector<vector<double>> convertBData(size,vector<double>(size));

        for(int i = 0; i < size; ++i){
            for(int j = 0; j < size; ++j){
                convertAData[i][j] = stod(matrixAData[i][j]);
                convertBData[i][j] = stod(matrixBData[i][j]);
            }
        }
        Matrix<double> matrixA(convertAData);
        Matrix<double> matrixB(convertBData);

        matrixA.printMatrix();
        matrixB.printMatrix();
        printMenu(matrixA,matrixB);
    }
    
}
void scanFile(vector<string> fileData){
    for(int i = 0; i < fileData.size(); i++){
        smatch match;
        int size; 
        int type;
        if(regex_search(fileData[i],match,regex ("^(\\d+)\\s(\\d)")) && i==0){
            size = stoi(match[1].str());
            type = stoi(match[2].str());
        }
        if(fileData[i]!= "" && i>0){
            vector<vector<string>> matrixAData = readData(fileData, i, i+size, type);
            vector<vector<string>> matrixBData = readData(fileData, i+size, i+size+size, type);
            compileMatricies(matrixAData,matrixBData,size,type);
            break;
        }
        if(fileData[i]!= "" && i>0){
            vector<vector<string>> matrixAData = readData(fileData, i, i+size, type);
            vector<vector<string>> matrixBData = readData(fileData, i+size, i+size+size, type);
            compileMatricies(matrixAData,matrixBData,size,type);
            break;
        }
    }
}


bool verify(string fileName){
    fstream inputFile;
    inputFile.open(fileName, fstream::in);
    if(inputFile.is_open()){
        string line;
        vector<string> fileData;
        while(getline(inputFile,line)){
            fileData.push_back(line);
        }
        scanFile(fileData);    
        return 1;
    }
    else{
        cout << "File not found.\n";
        return 0;
    }
}

int main() {
    while(true){
        string fileName;
        cout << "Enter file name: ";
        cin >> fileName;
        if(verify(fileName)){
            break;
        }
    }
    

    return 0;
}