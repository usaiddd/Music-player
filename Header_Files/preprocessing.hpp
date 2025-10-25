#include <iostream>
#include <string>
#include<fstream>
#include<unordered_map>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

#ifndef PREPROCESSING_HPP
#define PREPROCESSING_HPP

//put all functions prototypes, structs, classes related to preprocessing here
unordered_map<string, json> create_hashtable();

struct node {
    
};

class hashtable{
private:
    
};
#endif // PREPROCESSING_HPP

//put all function definitions related to preprocessing here
unordered_map<string,json> create_hashtable() {
    unordered_map<string, json> songhash;

    cout << "An empty hash table has been created." << endl;

    // Open the JSON file
    ifstream info("Info_files/info.json");
    if (!info.is_open()) {
        cerr << "The file cannot be opened." << endl;
        return songhash;
    }

    json data;
    try {
        data = json::parse(info);
    } catch (json::parse_error& e) {
        cerr << "Error parsing info.json: " << e.what() << endl;
        return songhash;
    }

    // Check if the JSON contains the "songs" array
    if (!data.contains("songs") || !data["songs"].is_array()) {
        cerr << "JSON does not contain a valid 'songs' array." << endl;
        return songhash;
    }

    // Insert each song into the hash table
    for (const auto& song : data["songs"]) {
        string key = song.at("title").get<string>();
        songhash[key] = song;
        cout << "The song '" << key << "' has been added to the hash table." << endl;
    }

    cout << "\n--- Hash Table Contents ---\n" << endl;

    // Print all songs once
    for (const auto& pair : songhash) {
        cout << "Key: " << pair.first << "\nValue: " << pair.second.dump(2) << endl;
        cout << "--------------------" << endl;
    }
    return songhash;
}
