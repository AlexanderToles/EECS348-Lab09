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
        void print_matrix() const{
            cout << "Print matrix called \n";
            for(int i = 0; i < size; ++i){
                for(int j = 0; j < size; ++j){
                    cout << data[i][j] << " ";
                }
                cout << "\n";
            }
        }
};

vector<vector<string>> readData(vector<string> fileData, int start, int end, int type ){

    vector<vector<string>> returnData;

    for(int i = start; i < end; i++){

        vector<string> row;

        cout << "line: " << i << "\n" ;
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
            cout << match.str() << "\n";
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

        matrixA.print_matrix();
        matrixB.print_matrix();
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