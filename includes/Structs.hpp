#pragma once

#include <string>
#include <cmath>
#include <vector>
#include <cstddef>

struct ForwardList {
    struct Node {
        Node* Next;
        std::string Data;
    };
    Node* Head;
};

struct ForwardList2 {
    struct Node {
        Node* Next;
        double Data;
    };
    Node* Head;
};
