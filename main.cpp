#include "Header_Files/json.hpp"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using json = nlohmann::json;
using namespace std;

int main()
{
    cout << "enter keywords : ";
    string mid, first = "yt-dlp \"ytsearch1:", last = " \" --get-id 1 >> new.txt", fin = "", errorHandler;
    #ifdef _WIN32
        errorHandler = " 2>nul";
    #else
        errorHandler = " 2>/dev/null";
    #endif
    getline(cin, mid);
    fin = first + mid + last + errorHandler;
    system(fin.c_str());

    string firstLine;
    try {
        ifstream inFile("new.txt");
        getline(inFile, firstLine);
        inFile.close();
        ofstream outFile("new.txt", ios::trunc);
        outFile.close();
    }
    catch(...){

    }
    string videoUrl="https://www.youtube.com/watch?v=" + firstLine;
    string commandtojson = "yt-dlp \"" + videoUrl +
                           "\" --print \"{\\\"title\\\": \\\"%(title)s\\\", "
                           "\\\"uploader\\\": \\\"%(uploader)s\\\", "
                           "\\\"duration\\\": \\\"%(duration)s\\\"}\" > Info_files/temp.json" + errorHandler;
    string commandtodownload = "yt-dlp -x --audio-quality 0 --audio-format mp3 -o \"audioloc/%(title)s.%(ext)s\" \"" + videoUrl + "\"" + errorHandler;

    cout << "Running command..." << endl;
    int result1 = system(commandtojson.c_str());
    int result2 = system(commandtodownload.c_str());

    if (result1 != 0 || result2 != 0)
    {
        if (result1 != 0) cerr << "JSON command failed!" << endl;
        if (result2 != 0) cerr << "DOWNLOAD command failed!" << endl;
        return 1;
    }

    ifstream tempFile("Info_files/temp.json");
    if (!tempFile)
    {
        cerr << "Failed to open temp.json" << endl;
        return 1;
    }
    json newEntry;
    tempFile >> newEntry;
    cout<< "Adding new download "<< newEntry;
    tempFile.close();

    json allData;
    ifstream infoFile("Info_files/info.json");
    if (infoFile && infoFile.peek() != ifstream::traits_type::eof())
    {
        try
        {
            infoFile >> allData;
        }
        catch (...)
        {
            cerr << "Corrupted info.json, resetting..." << endl;
            allData = json::array();
        }
    }
    else
    {
        allData = json::array();
        if (infoFile) infoFile.close();
    }

    allData.push_back(newEntry);

    ofstream jsonOutFile("Info_files/info.json");
    jsonOutFile << setw(4) << allData << endl;
    jsonOutFile.close();

    cout << endl << "Commands run successfully and JSON appended!" << endl;
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
