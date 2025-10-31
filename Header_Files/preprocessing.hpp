#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>
#include "json.hpp"

// ...existing code...
using namespace std;
using json = nlohmann::json;

#ifndef PREPROCESSING_HPP
#define PREPROCESSING_HPP

//put all functions prototypes, structs, classes related to preprocessing here
unordered_map<string, json> create_hashtable_title();
unordered_map<int, vector<string>> create_hashtable_duration();

struct node {
    
};

class hashtable{
private:
    
};
#endif // PREPROCESSING_HPP

//put all function definitions related to preprocessing here
unordered_map<string,json> create_hashtable_title() {
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
        // read file into json (works for a top-level array or object)
        info >> data;
    } catch (json::parse_error& e) {
        cerr << "Error parsing info.json: " << e.what() << endl;
        return songhash;
    }

    // Accept either: top-level array OR object with "songs": [...]
    const json* songs_ptr = nullptr;
    if (data.is_array()) {
        songs_ptr = &data;
    }
    else {
        cerr << "JSON does not contain a valid 'songs' array." << endl;
        return songhash;
    }

    // Insert each song into the hash table
    for (const auto& song : *songs_ptr) {
        if (!song.is_object() || !song.contains("title")) {
            cerr << "Skipping entry without a title." << endl;
            continue;
        }
        string key = song.at("title").get<string>();
        songhash[key] = song;
        cout << "The song '" << key << "' has been added to the hash table." << endl;
    }
    return songhash;
}

unordered_map<int,vector<string>> create_hashtable_duration() {
    unordered_map<int,vector<string>> durationhash;
    cout << "An empty hash table has been created." << endl;

    // Open the JSON file
    ifstream info("Info_files/info.json");
    if (!info.is_open()) {
        cerr << "The file cannot be opened." << endl;
        return durationhash;
    }

    json data;
    try {
        // read file into json (works for a top-level array or object)
        info >> data;
    } catch (json::parse_error& e) {
        cerr << "Error parsing info.json: " << e.what() << endl;
        return durationhash;
    }

    // Accept either: top-level array OR object with "songs": [...]
    const json* songs_ptr = nullptr;
    if (data.is_array()) {
        songs_ptr = &data;
    }
    else {
        cerr << "JSON does not contain a valid 'songs' array." << endl;
        return durationhash;
    }

    for (const auto& song : *songs_ptr) {
        if (!song.is_object() || !song.contains("duration")) {
            cerr << "Skipping entry without any duration." << endl;
            continue;
        }
        int key = stoi(song.at("duration").get<string>());
        durationhash[key].push_back(song.at("title").get<string>());
        cerr << "The song with duration '" << key << "' has been added to the hash table." << endl;
    }
    return durationhash;
}
