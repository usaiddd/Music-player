#include <iostream>
#include <fstream>
#include <cstdlib>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

int main() {
  string videoUrl;
  cout << "Enter a video to download: ";
  cin >> videoUrl;
  string commandtojson = "yt-dlp \"" + videoUrl +
    "\" --print \"{\\\"title\\\": \\\"%(title)s\\\", "
    "\\\"uploader\\\": \\\"%(uploader)s\\\", "
    "\\\"duration\\\": \\\"%(duration)s\\\"}\" > temp.json";
  string commandtodownload = "yt-dlp -x --audio-quality 0 --audio-format mp3 -o \"audioloc/%(title)s.%(ext)s\" \"" + videoUrl + "\"";

  cout << "Running command..." << endl;
  int result1 = system(commandtojson.c_str());
  int result2 = system(commandtodownload.c_str());

  if (result1 != 0 || result2 != 0) {
    if (result1 != 0)
        cerr << "JSON command failed!" << endl;
    if (result2 != 0)
        cerr << "DOWNLOAD command failed!" << endl;
    return 1;
  }

  ifstream tempFile("temp.json");
  if (!tempFile) {
    cerr << "Failed to open temp.json" << endl;
    return 1;
  }
  json newEntry;
  tempFile >> newEntry;
  tempFile.close();

  json allData;
  ifstream infoFile("info.json");
  if (infoFile.peek() != ifstream::traits_type::eof()) {
    try {
        infoFile >> allData;
    } catch (...) {
        cerr << "Corrupted info.json, resetting..." << endl;
        allData = json::array();
    }
  } else {
      allData = json::array();
  }
  infoFile.close();

  allData.push_back(newEntry);

  ofstream outFile("info.json");
  outFile << setw(4) << allData << endl;
  outFile.close();

  cout << "Commands run successfully and JSON appended!" << endl;
  return 0;
}
