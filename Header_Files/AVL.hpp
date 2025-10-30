#ifndef AVL_HPP
#define AVL_HPP

#include <iostream>
#include <vector>
using namespace std;

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

template <typename A>
class AVL {
private:
    Node<A>* root;

public:
    AVL() {
        root = nullptr;
    }

    int BalanceFactor(Node<A>* temp) {
        if (!temp) return 0;
        int lh = (temp->left) ? temp->left->height : 0;
        int rh = (temp->right) ? temp->right->height : 0;
        return lh - rh;
    }

    int UpdateHeight(Node<A>* temp) {
        if (temp == nullptr) return 0;
        int lh = (temp->left) ? temp->left->height : 0;
        int rh = (temp->right) ? temp->right->height : 0;
        temp->height = 1 + max(lh, rh);
        return temp->height;
    }

    Node<A>* llrotate(Node<A>* var) {
        Node<A>* child = var->left;
        Node<A>* childRight = child->right;
        child->right = var;
        var->left = childRight;

        UpdateHeight(var);
        UpdateHeight(child);
        return child;
    }

    Node<A>* lrrotate(Node<A>* var) {
        var->left = rrrotate(var->left);
        return llrotate(var);
    }

    Node<A>* rrrotate(Node<A>* var) {
        Node<A>* child = var->right;
        Node<A>* childLeft = child->left;
        child->left = var;
        var->right = childLeft;

        UpdateHeight(var);
        UpdateHeight(child);
        return child;
    }

    Node<A>* rlrotate(Node<A>* var) {
        var->right = llrotate(var->right);
        return rrrotate(var);
    }

    Node<A>* addnode(Node<A>* temp, A var) {
        if (temp == nullptr)
            return new Node<A>(var);

        if (var < temp->data)
            temp->left = addnode(temp->left, var);
        else if (var > temp->data)
            temp->right = addnode(temp->right, var);

        UpdateHeight(temp);
        int balance = BalanceFactor(temp);

        if (balance > 1 && var < temp->left->data)
            return llrotate(temp);
        if (balance > 1 && var > temp->left->data)
            return lrrotate(temp);
        if (balance < -1 && var > temp->right->data)
            return rrrotate(temp);
        if (balance < -1 && var < temp->right->data)
            return rlrotate(temp);

        return temp;
    }

    void createtree(const vector<A>& v, int size) {
        if (size == 0) return;
        for (int i = 0; i < size; i++)
            root = addnode(root, v[i]);
    }

    // ASCENDING
    void inorder(Node<A>* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }
    void displayinorder() {
        inorder(root);
    }

    void inorderdescend(Node<A>* node) {
        if (!node) return;
        inorderdescend(node->right);
        cout << node->data << " ";
        inorderdescend(node->left);
    }
    void displayinorderdescend() {
        inorderdescend(root);
    }
};

#endif
