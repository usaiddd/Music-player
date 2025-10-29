#include <unordered_map>
#include <string>
#include "Header_Files/downloader.hpp"
#include "Header_Files/preprocessing.hpp"
#include "Header_Files/json.hpp"

int main(){
    downloadSong();
    unordered_map<string, json> song_table = create_hashtable();
    return 0;
}

