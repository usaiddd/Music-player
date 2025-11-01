#include <unordered_map>
#include <string>
#include <vector>
#include "Header_Files/downloader.hpp"
#include "Header_Files/preprocessing.hpp"
#include "Header_Files/json.hpp"

int main(){
    downloadSong();
    vector <string> titles; 
    unordered_map<string, json> song_table = create_hashtable_title();
    for (const auto& pair : song_table) {
        titles.push_back(pair.first);
    }
    cout << "\n\n";
    vector<int> durations; 
    vector<string> durationtitles; 
    unordered_map<int, vector<string>> duration_table = create_hashtable_duration();
    for (const auto& pair : duration_table) {
        durations.push_back(pair.first);
    }
    AVL<string> a;
    AVL<int> b; 
    a.createtree(titles,titles.size());
    cout << "ASCENDING ORDER OF TITLES: \n"; 
    a.displayinorder();
    cout << "\nDESCENDING ORDER OF TITLES: \n"; 
    a.displayinorderdescend();
    b.createtree(durations,durations.size());
    cout << "\nASCENDING ORDER OF DURATION: \n"; 
    inorderdur(b.root, duration_table, durationtitles);
    for(string x: durationtitles){ 
        cout << x << " ";
    }
    durationtitles.clear();
    cout << "\nDESCENDING ORDER OF DURATION: \n"; 
    inorderdurdes(b.root, duration_table, durationtitles);
    for(string x: durationtitles){ 
        cout << x << " ";
    } 
    return 0;
}