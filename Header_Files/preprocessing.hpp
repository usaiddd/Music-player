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

template <typename T>
struct Node {
    T data;
    Node<T>* left;
    Node<T>* right;
    int height;
    Node(T data) {
        this->data = data;
        left = right = nullptr;
        height = 1;
    }
};

void inorderdurdes(Node<int>* temp, unordered_map<int, vector<string>> &arr, vector<string> &arr2);
void inorderdur(Node<int>* temp, unordered_map<int, vector<string>> &arr, vector<string> &arr2);

template <typename A>
class AVL {
public:
    Node<A> * root;
    AVL();
    int BalanceFactor(Node<A>* temp);
    int UpdateHeight(Node<A>* temp);
    Node<A>* llrotate(Node<A>* var);
    Node<A>* lrrotate(Node<A>* var);
    Node<A>* rrrotate(Node<A>* var);
    Node<A>* rlrotate(Node<A>* var);
    Node<A>* addnode(Node<A>* temp, A var);
    void createtree(const vector<A>& v, int size) ;
    void inorder(Node<A>* node);
    void displayinorder();
    void inorderdescend(Node<A>* node);
    void displayinorderdescend() ;
};

class hashtable{
private:
    
};
#endif // PREPROCESSING_HPP

//put all function definitions related to preprocessing here
unordered_map<string,json> create_hashtable_title() {
    unordered_map<string, json> songhash;

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
    }
    return songhash;
}

unordered_map<int,vector<string>> create_hashtable_duration() {
    unordered_map<int,vector<string>> durationhash;

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
    }
    return durationhash;
}

template <typename A>
AVL<A>::AVL() {
    root = nullptr;
}

template <typename A>
int AVL<A>::BalanceFactor(Node<A>* temp) {
    if (!temp) return 0;
    int lh = (temp->left) ? temp->left->height : 0;
    int rh = (temp->right) ? temp->right->height : 0;
    return lh - rh;
}

template <typename A>
int AVL<A>::UpdateHeight(Node<A>* temp) {
    if (temp == nullptr) return 0;
    int lh = (temp->left) ? temp->left->height : 0;
    int rh = (temp->right) ? temp->right->height : 0;
    temp->height = 1 + max(lh, rh);
    return temp->height;
}

template <typename A>
Node<A>* AVL<A>::llrotate(Node<A>* var) {
    Node<A>* child = var->left;
    Node<A>* childRight = child->right;
    child->right = var;
    var->left = childRight;

    UpdateHeight(var);
    UpdateHeight(child);
    return child;
}

template <typename A>
Node<A>* AVL<A>::lrrotate(Node<A>* var) {
    var->left = rrrotate(var->left);
    return llrotate(var);
}

template <typename A>
Node<A>* AVL<A>::rrrotate(Node<A>* var) {
    Node<A>* child = var->right;
    Node<A>* childLeft = child->left;
    child->left = var;
    var->right = childLeft;

    UpdateHeight(var);
    UpdateHeight(child);
    return child;
}

template <typename A>
Node<A>* AVL<A>::rlrotate(Node<A>* var) {
    var->right = llrotate(var->right);
    return rrrotate(var);
}

template <typename A>
Node<A>* AVL<A>::addnode(Node<A>* temp, A var) {
    if (temp == nullptr)
        return new Node<A>(var);

    if (var < temp->data)
        temp->left = addnode(temp->left, var);
    else if (var >= temp->data)
        temp->right = addnode(temp->right, var);

    UpdateHeight(temp);
    int balance = BalanceFactor(temp);

    if (balance > 1 && var < temp->left->data)
        return llrotate(temp);
    if (balance > 1 && var >= temp->left->data)
        return lrrotate(temp);
    if (balance < -1 && var >= temp->right->data)
        return rrrotate(temp);
    if (balance < -1 && var < temp->right->data)
        return rlrotate(temp);

    return temp;
}

template <typename A>
void AVL<A>::createtree(const vector<A>& v, int size) {
    if (size == 0) return;
    for (int i = 0; i < size; i++)
        root = addnode(root, v[i]);
}

// ASCENDING TITLE
template <typename A>
void AVL<A>::inorder(Node<A>* node) {
    if (!node) return;
    inorder(node->left);
    cout << node->data << " ";
    inorder(node->right);
}

template <typename A>
void AVL<A>::displayinorder() {
    inorder(root);
}

//DESCENDING TITLE
template <typename A>
void AVL<A>::inorderdescend(Node<A>* node) {
    if (!node) return;
    inorderdescend(node->right);
    cout << node->data << " ";
    inorderdescend(node->left);
}

template <typename A>
void AVL<A>::displayinorderdescend() {
    inorderdescend(root);
}

void inorderdur(Node<int>* temp, unordered_map<int, vector<string>> &arr, vector<string> &arr2){ 
    if (!temp) return;
    inorderdur(temp->left, arr, arr2);
    for (string i: arr[temp->data])
        arr2.push_back(i);
    inorderdur(temp->right, arr, arr2);
}

void inorderdurdes(Node<int>* temp, unordered_map<int, vector<string>> &arr, vector<string> &arr2){ 
    if (!temp) return;
    inorderdurdes(temp->right, arr, arr2);
    for (string i: arr[temp->data])
        arr2.push_back(i);
    inorderdurdes(temp->left, arr, arr2);
}
