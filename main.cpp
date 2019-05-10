#include <iostream>
#include "BinaryTree.h"

void vistor(void *data) {
    std::cout<<"  ";
    std::cout << (*(int *) data) << std::endl;
}

int cmp(void *dest, void *souce) {
    return *(int *) dest - *(int *) souce;
}

int main() {
    BinaryTree<int> bt(cmp);
    bt.appendNode(2);
    bt.appendNode(1);
    bt.appendNode(34);
    bt.addTravelCallback(vistor);

    bt.midTravel();
    return 0;
}