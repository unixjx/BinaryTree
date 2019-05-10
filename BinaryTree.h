//
// Created by root on 19-5-8.
//

#ifndef BINARYTREE_BINARYTREE_H
#define BINARYTREE_BINARYTREE_H

#include <iostream>

template<typename T>
struct TreeNode {
    struct TreeNode *left;
    T data;
    struct TreeNode *right;
};

// 返回比较的大小
typedef int (*cmp_ptr)(void *, void *);

typedef void (*travel_ptr)(void *);

template<class T>
class BinaryTree {
    /*
 *  传入参数： 用于数据比较的回调函数
 * */
public:
    explicit BinaryTree(cmp_ptr);

    bool appendNode(T);

    void preTravel();

    void midTravel();

    void lastTravel();

    void addTravelCallback(travel_ptr);

protected:
    TreeNode<T> *_initNode(T);

    void _preTravel(TreeNode<T> *, int);

    void _midTravel(TreeNode<T> *, int);

    void _lastTravel(TreeNode<T> *, int);

private:
    int m_number;
    TreeNode<T> *m_root;

    cmp_ptr m_cmpFunction;   // 比较回调函数的指针
    travel_ptr m_travelFunction;
};

template<class T>
BinaryTree<T>::BinaryTree(cmp_ptr func) : m_cmpFunction(func) {
    m_number = 0;
    m_root = nullptr;
    m_travelFunction = nullptr;
}

template<class T>
bool BinaryTree<T>::appendNode(T data) {
    TreeNode<T> *temp_ptr;
    if (!(temp_ptr = this->_initNode(data)))
        return false;

    if (!m_root) {
        m_root = temp_ptr;
        return true;
    }

    TreeNode<T> *t_ptr = m_root;
    while (t_ptr) {
        if (m_cmpFunction(&data, &(t_ptr->data)) <= 0) {
            if (t_ptr->left) {
                t_ptr = t_ptr->left;
            } else {
                t_ptr->left = temp_ptr;
                break;
            }
        } else {
            if (t_ptr->right) {
                t_ptr = t_ptr->right;
            } else {
                t_ptr->right = temp_ptr;
                break;
            }
        }
    }
    return true;
}

template<class T>
void BinaryTree<T>::_preTravel(TreeNode<T> *node, int level) {
    if (!node) {
        return;
    }

    for (int i = 0; i < level; i++) {
        std::cout << "-";
    }

    if (m_travelFunction)
        m_travelFunction((void *) &(node->data));

    _preTravel(node->left, level + 1);
    _preTravel(node->right, level + 1);
}

template<class T>
TreeNode<T> *BinaryTree<T>::_initNode(T data) {
    auto *temp_ptr = new TreeNode<T>;
    if (!temp_ptr)
        return nullptr;

    temp_ptr->left = temp_ptr->right = nullptr;
    temp_ptr->data = data;
    return temp_ptr;
}

template<class T>
void BinaryTree<T>::preTravel() {
    _preTravel(m_root, 1);
}

template<class T>
void BinaryTree<T>::addTravelCallback(travel_ptr fun) {
    m_travelFunction = fun;
}

template<class T>
void BinaryTree<T>::midTravel() {
    _midTravel(m_root, 1);
}

template<class T>
void BinaryTree<T>::_midTravel(TreeNode<T> *node, int level) {
    if (!node) {
        return;
    }


    _midTravel(node->left, level + 1);

    for (int i = 0; i < level; i++) {
        std::cout << "-";
    }
    if (m_travelFunction) {
        m_travelFunction((void *) &(node->data));
    }

    _midTravel(node->right, level + 1);
}

template<class T>
void BinaryTree<T>::_lastTravel(TreeNode<T> *node, int level) {
    if (!node) {
        return;
    }

    _lastTravel(node->left, level + 1);
    _lastTravel(node->right, level + 1);

    for (int i = 0; i < level; i++) {
        std::cout << "-";
    }
    if (m_travelFunction) {
        m_travelFunction((void *) &(node->data));
    }
}

template<class T>
void BinaryTree<T>::lastTravel() {
    _lastTravel(m_root, 1);
}


#endif //BINARYTREE_BINARYTREE_H
