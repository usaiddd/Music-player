#include <iostream> 
using namespace std; 

struct AVL{ 
  string songname; 
  AVL *left; 
  AVL *right; 
  int balance; 
  AVL(string s){ 
    songname = s; 
    left = right = nullptr;
    balance = 1; 
  }
}; 

int main(){ 

  return 0;
}