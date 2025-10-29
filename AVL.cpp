#include <iostream>
using namespace std; 

template <typename T>

struct Node{ 
  T data;
  Node<T> *left; 
  Node<T> *right; 
  int height; 
  Node(T data){ 
    this->data=data; 
    left = right = nullptr;
    height = 1; 
  }
}; 

template <typename A>
class AVL{ 
private: 
  Node <A>* root; 
public:
  AVL(){
    root=nullptr;
  }
  int BalanceFactor(Node<A>*temp){
    if(!temp)return 0;
    else if(!temp->left && !temp->right){return 0;}
    else if(temp->left==nullptr){return temp->right->height;}
    else if(temp->right==nullptr){return temp->left->height;}
    else return abs((temp->left->height)-(temp->right->height));
  }
  int UpdateHeight(Node<A>* temp){
    if (temp == nullptr) {
      return 0;
    }
    int lh = UpdateHeight(temp->left);
    int rh = UpdateHeight(temp->right);
    temp->height = 1 + max(lh, rh);
    return temp->height;
  }
  Node<A>* llrotate(Node<A>* var){
    Node<A>* child = var->left;
    Node<A>* childRight = child->right;
    child->right = var;
    var->left = childRight;
    return child;
  }       
  Node<A>* lrrotate(Node<A>* var){
    var->left = rrrotate(var->left);
    return llrotate(var);
  }
  Node<A>* rrrotate(Node<A>* var){
    Node<A>* child = var->right;
    Node<A>* childLeft = child->left;
    child->left = var;
    var->right = childLeft;
    return child; 
  }
  Node<A>* rlrotate(Node<A>* var){
    var->right = llrotate(var->right);
    return rrrotate(var);
  }
  Node<A>* addnode(Node <A>* temp, A var){  
    if (temp == nullptr){ 
        return new Node<A>(var);
    }
    if(var < temp->data){
        temp->left = addnode(temp->left, var);
    }
    else if(var > temp->data){
        temp->right = addnode(temp->right, var);
    }
    UpdateHeight(temp);
    int balance = BalanceFactor(temp);
    
    if(balance > 1 && var < temp->left->data)
        return llrotate(temp);
    if(balance > 1 && var > temp->left->data)
        return lrrotate(temp);
    if(balance < -1 && var > temp->right->data)
        return rrrotate(temp);
    if(balance < -1 && var < temp->right->data)
        return rlrotate(temp);
        
    return temp;
}
  void createtree(int arr[],int size){
    if(size == 0) return;
    root = addnode(root, arr[0]);
    for(int i = 1; i < size; i++){
        root = addnode(root, arr[i]);
    }
  }
};

int main(){ 
  int arr[9]={1,2,3,4,5,6,7,8,9};
  AVL<int> a;
  a.createtree(arr,9);
}