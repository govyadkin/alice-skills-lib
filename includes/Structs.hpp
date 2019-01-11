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

ForwardList polsk(const std::vector<std::string>& v, Alice::Response& response);
double trigon(size_t& i, const std::vector<std::string>& v, Alice::Response& response);
double calc(ForwardList& list);
std::vector<std::string> split(const std::string& str);

double Strtodouble(const std::string str);

void Construct(ForwardList& list);
void Destruct(ForwardList& list);
void PushFront(ForwardList& list, std::string value);
std::string PopFront(ForwardList& list);
size_t Size(const ForwardList& list);
void Reverse(ForwardList& list);

void Construct(ForwardList2& list);
void Destruct(ForwardList2& list);
void PushFront(ForwardList2& list, double value);
double PopFront(ForwardList2& list);
size_t Size(const ForwardList2& list);
void MyCallback(const Alice::Request& request, Alice::Response& response);
