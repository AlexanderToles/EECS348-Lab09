//  EECS 348 LAB 09
//  MATRIX OPERATIONS
//  INPUT: Test file, menu selection
//  OUTPUT: Menu, matricies
//  ALEXANDER TOLES      
//  APRIL 08 2025



#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <regex>


using namespace std;

template <typename T> class Matrix { //Matrix class definition, using template, need to pass in Matrix type during declaration
    private: //variables used in matrix functions
        int size; 
        vector<vector<T>> data; //2d vector of passed in values
    
    public:
        Matrix(vector<vector<T>> nums){ //constructor, takes in a 2d vector of numbers
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
            vector<T> tempRow = data[r1]; //set tempory val
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
            for(int i = 0; i < size; ++i){ //go through each row, printing each column to the screen
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

//read the data from the line, takes a starting line postion and end position, indexing over
//each line and adding it to a 2d vector

vector<vector<string>> readData(vector<string> fileData, int start, int end, int type ){ 

    vector<vector<string>> returnData; //2d vector of strings, gets translated in compileMatricies() function

    for(int i = start; i < end; i++){ //go through each line from the start of the matrix to the end

        vector<string> row;
        regex searchTerm;
        
        if(type == 1){ //regex search changes depending on double or int
            searchTerm = ("(\\d+[.]\\d+)"); //need the number before and after, and the decimal
        } else {
            searchTerm = ("(\\d+)"); //just need the numbers
        }
        
        //setup sregex_iterator, this bit parses through each regex match in the line, apending them to the
        //returnData

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


//compileMatricies Takes in the data as strings, and then translates the data based on the matrix type, then creates
//two matrix objects for the matricies. Finally, it calls the printMenu function.

void compileMatricies(vector<vector<string>> matrixAData, vector<vector<string>> matrixBData, int size, int type){
    
    if(type==0){ //if matrix type is integer

        //create two 2d vectors to store the translated data

        vector<vector<int>> convertAData(size,vector<int>(size));
        vector<vector<int>> convertBData(size,vector<int>(size));
        //goes through each entry in the input data, translates it, and adds it to the converted data
        for(int i = 0; i < size; ++i){
            for(int j = 0; j < size; ++j){
                convertAData[i][j] = stoi(matrixAData[i][j]);
                convertBData[i][j] = stoi(matrixBData[i][j]);
            }
        }

        //create matricies using the converted data
        Matrix<int> matrixA(convertAData);
        Matrix<int> matrixB(convertBData);

        matrixA.printMatrix();
        matrixB.printMatrix();

        //call printMenu with the matricies
        printMenu(matrixA,matrixB);
    }
    else{ //same thing but with double, now that i think of it, probably coulda used a template here but im tired
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

//scan through each line
void scanFile(vector<string> fileData){
    for(int i = 0; i < fileData.size(); i++){ //iterate through each line
        smatch match; //variable to store matches
        int size; 
        int type;
        if(regex_search(fileData[i],match,regex ("^(\\d+)\\s(\\d)")) && i==0){ //search for the first two numbers
            size = stoi(match[1].str());
            type = stoi(match[2].str());
        }
        if(fileData[i]!= "" && i>0){ //find start of matrixA, read the data, pass the data to compileMatrices
            vector<vector<string>> matrixAData = readData(fileData, i, i+size, type);
            vector<vector<string>> matrixBData = readData(fileData, i+size, i+size+size, type); //call from matrixB start position
            compileMatricies(matrixAData,matrixBData,size,type);
            break;
        }
    }
}


bool verify(string fileName){ //check if the input file is able to be opened
    fstream inputFile;
    inputFile.open(fileName, fstream::in);
    if(inputFile.is_open()){
        string line;
        vector<string> fileData;
        while(getline(inputFile,line)){ //create a vector containing each of the lines
            fileData.push_back(line);
        }
        scanFile(fileData);    //pass vector to the scanFile function
        return 1;
    }
    else{
        cout << "File not found.\n";
        return 0;
    }
}


//Matrix program flow:
//1) get file from user
//2) read the data from file
//3) create two 2d vectors containing the data as strings
//4) compileMatricies translates the data and calls print menu
//5) printMenu handles user interaction






int main() {
    while(true){ //prompt user for input file name until valid name is chosen
        string fileName;
        cout << "Enter file name: ";
        cin >> fileName;
        if(verify(fileName)){ //check if file was able to be opened
            break;
        }
    }
    

    return 0;
}