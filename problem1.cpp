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
        Matrix(size_t N);
        Matrix(vector<vector<T>> nums);
    
        Matrix operator+(const Matrix &rhs) const;
        Matrix operator*(const Matrix &rhs) const;
        void set_value(size_t i, size_t j, T n);
        T get_value(size_t i, size_t j) const;
        int get_size() const;
        T sum_diagonal_major() const;
        T sum_diagonal_minor() const;
        void swap_rows(size_t r1, size_t r2);
        void swap_cols(size_t c1, size_t c2);
        void print_matrix() const;
    };

void readData(vector<string> fileData, int start, int end){
    for(int i = start; i < end; i++){
        smatch match;
        cout << "line: " << i << "\n" ;
        regex searchTerm("(\\d+)");
        auto lineStart = sregex_iterator(fileData[i].begin(),fileData[i].end(),searchTerm);
        auto lineEnd = sregex_iterator();
        for(sregex_iterator i = lineStart; i != lineEnd; ++i){
            smatch match = *i;
            cout << match.str() << "\n";
        }
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
            readData(fileData, i, i+size);
            break;
        }
        //cout << fileData[i] << "\n";
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