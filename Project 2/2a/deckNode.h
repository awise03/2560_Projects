//
// Created by Jackymora Isa on 2/20/24.
//

#ifndef INC_2560_PROJECTS_DECKNODE_H
#define INC_2560_PROJECTS_DECKNODE_H

#include "card.h"

// Linked list node
template <typename T>
class DeckNode {
public:
    // Default constructor with no initial value
    DeckNode() : next(nullptr) {}

    // Constructor, initialized node value and next value
    DeckNode(const T& item, DeckNode<T>* nextNode = nullptr) : dataValue(item), next(nextNode) {}

    DeckNode<T>* next; // Data held by node
    T dataValue;// Next node in the list

};

#endif //INC_2560_PROJECTS_DECKNODE_H

