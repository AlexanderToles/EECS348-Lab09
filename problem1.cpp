#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

void scanFile(vector<string> fileData){
    for(int i = 0; i < fileData.size(); i++){
        cout << fileData[i] << "\n";
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