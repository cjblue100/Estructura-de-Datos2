#ifndef _AVL_H_
#define _AVL_H_

#include <algorithm>

namespace Avl
{
    template <typename T>
    struct Node
    {
        Node() = default;
        
        Node(T k): key(k), height(0), left(nullptr), right(nullptr)
        {}

        T key;
        long height;
        Node *left;
        Node *right;
    };

    template <typename T>
    void rotateLeft(Node<T> *&root)
    {
        
        Node<T> *remplaso = root->left;
        root->left = remplaso->right;
        remplaso->right = root;

        if(root->right!=nullptr && root->left!=nullptr)
            root->height=std::max(root->right->height,root->left->height)+1;
        else if(root->right!=nullptr && root->left==nullptr)
            root->height=root->right->height +1;
        else if(root->left!=nullptr && root->right==nullptr)
            root->height=root->left->height +1;

        
        if(remplaso->right!=nullptr && remplaso->left!=nullptr)
            remplaso->height=std::max(remplaso->right->height,remplaso->left->height) +1;
        else if(remplaso->right!=nullptr && remplaso->left==nullptr)
            remplaso->height=remplaso->right->height +1;
        else if(remplaso->left!=nullptr && remplaso->right==nullptr)
            remplaso->height=remplaso->left->height +1;

        root=remplaso;


        

        
    }

    template <typename T>
    void rotateRight(Node<T> *&root)
    {
        Node<T> *remplaso = root->right;
        root->right = remplaso->left;
        remplaso->left = root;

        if(root->right!=nullptr && root->left!=nullptr)
            root->height=std::max(root->right->height,root->left->height)+1;

        if(root->right!=nullptr && root->left==nullptr)
            root->height=root->right->height +1;

        if(root->left!=nullptr && root->right==nullptr)
            root->height=root->left->height +1;


        if(remplaso->right!=nullptr && remplaso->left!=nullptr)
            remplaso->height=std::max(remplaso->right->height,remplaso->left->height) +1;

        if(remplaso->right!=nullptr && remplaso->left==nullptr)
            remplaso->height=remplaso->right->height +1;

        if(remplaso->left!=nullptr && remplaso->right==nullptr)
            remplaso->height=remplaso->left->height + 1;

        root=remplaso;
        
    }
    
} // namespace Avl

#endif
