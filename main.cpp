//#include<nlohmann/json.hpp>
#include<cstdlib>
#include<iostream>
#include<fstream>
#include<string>

//using json = nlohmann::json;
using namespace std;

int main(){
    cout<<"enter keywords : ";
    string mid,first="yt-dlp \"ytsearch1:",last=" \" --get-id 1 >> new.txt",fin="";
    getline(cin,mid);
    fin=first+mid+last;
    system("cd ytdl");
    system(fin.c_str());
    system("cd ..");
    string firstLine;
    ifstream inFile("new.txt");
    if (!inFile.is_open()) {
        cerr << "Error: Could not open file 'new.txt' for reading.\n";
        return 1;
    }
    getline(inFile, firstLine);
    inFile.close();
    ofstream outFile("new.txt", ios::trunc);
    outFile.close();
    cout<<firstLine;
    return 0;
    // ifstream file("prac.json");  // open file
    // if (!file.is_open()) {
    //     cerr << "Could not open file!" << endl;
    //     return 1;
    // }
    // json j;
    // file >> j;
    // cout<< j[1][1];
}
