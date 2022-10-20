#pragma once
struct Node
{
    int id;
    vector<Node*>child;
    Node* parents;
    Node* spouse;
    Node(int i) {
        id = i;
        parents = nullptr;
        spouse = nullptr;
    }
    Node() {
        id = -1;
        parents = nullptr;
        spouse = nullptr;
    }
};
