#include <unordered_map>
#include <string>
#include <vector>
#include "Header_Files/downloader.hpp"
#include "Header_Files/preprocessing.hpp"
#include "Header_Files/json.hpp"
#include "Header_Files/AVL.hpp"

int main(){
    for (int i=0; i<3; i++){ //FOR TESTING TREE BUILD OF 3 SONGS 
        downloadSong();
    }
    vector <string> titles; 
    unordered_map<string, json> song_table = create_hashtable();
    for (const auto& pair : song_table) {
        titles.push_back(pair.first);
    }
    AVL<string> a; 
    a.createtree(titles,titles.size());
    cout << "ASCENDING ORDER OF TITLES: \n"; 
    a.displayinorder();
    cout << "\nDESCENDING ORDER OF TITLES: \n"; 
    a.displayinorderdescend();
    return 0;
}

