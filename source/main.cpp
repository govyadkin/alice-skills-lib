#include <Request.hpp>
#include <Response.hpp>
#include "Structs.hpp"
#include <Skill.hpp>

ForwardList polsk(const std::vector<std::string>& v, Alice::Response& response) // writes an example in Polish notation
{
    ForwardList list, station;
    Construct(list);
    Construct(station);
    PushFront(station, "|");
    int action = 2;
    bool flag = 0, flag2 = 0;
    for (size_t i = 1; i < v.size(); ++i)
    {
        action = 2;
        /*
        Значения action:
        1. Вагон на стрелке отправляется в station
            PushFront(station, v[i]);
        2. Последний вагон, направившийся в station, разворачивается и направляется в list
            PushFront(list,PopFront(station));
        3. Вагон, находящийся на стрелке, и последний вагон, отправившийся в station, угоняются и исчезают

        4. Остановка. Символы, находящиеся на list, представляют собой формулу в обратной польской записи
        5. Остановка. Произошла ошибка. Изначальная формула была некорректно сбалансирована
        6. Это mod, sin, cos, tg, ctg, sh, ch, th, arcsin, arccos, arctg, arcctg
        */
        while (action == 2)
        {
            if (v[i] == "(")
            {
                action = 1;
                PushFront(station, v[i]);
            }
            else if ((v[i] == "+") || (v[i] == "-"))
            {
                if ((v[i - 1] == "+") || (v[i - 1] == "-") ||
                    (v[i - 1] == "*") || (v[i - 1] == "/") ||
                    (v[i - 1] == "(") || (v[i - 1] == "|"))
                {
                    PushFront(list, v[i] + v[i + 1]);
                    action = 0;
                    ++i;
                }
                else if (((station.Head)->Data == "|") || ((station.Head)->Data == "("))
                {
                    action = 1;
                    PushFront(station, v[i]);
                }
                else {
                    action = 2;
                    PushFront(list, PopFront(station));
                }
            }
            else if (v[i] == "*")
            {
                if (((station.Head)->Data == "*") || ((station.Head)->Data == "/"))
                {
                    action = 2;
                    PushFront(list, PopFront(station));
                }
                else {
                    action = 1;
                    PushFront(station, v[i]);
                }
            }
            else if (v[i] == "/")
            {
                flag = 1;
                if (((station.Head)->Data == "*") || ((station.Head)->Data == "/"))
                {
                    action = 2;
                    PushFront(list, PopFront(station));
                }
                else {
                    action = 1;
                    PushFront(station, v[i]);
                }
            }
            else if (v[i] == "|")
            {
                if ((station.Head)->Data == "|")
                {
                    action = 4;
                }
                else if ((station.Head)->Data == "(") {
                    action = 5;
                    response.SetText("ERROR");
                    response.SetTts("ERROR");
                }
                else {
                    action = 2;
                    PushFront(list, PopFront(station));
                }
            }
            else if (v[i] == ")")
            {
                if ((station.Head)->Data == "|")
                {
                    action = 5;
                    response.SetText("ERROR");
                    response.SetTts("ERROR");
                }
                else if ((station.Head)->Data == "(") {
                    action = 3;
                    std::string s = PopFront(station);
                }
                else {
                    action = 2;
                    PushFront(list, PopFront(station));
                }
            }
            else if (v[i] == "sin")
            {
                double value = trigon(i, v);
                PushFront(list, std::to_string(sin(value)));
                action = 6;
                flag = 1;
            }
            else if (v[i] == "cos")
            {
                double value = trigon(i, v);
                PushFront(list, std::to_string(cos(value)));
                action = 6;
                flag = 1;
            }
            else if (v[i] == "tg")
            {
                double value = trigon(i, v);
                PushFront(list, std::to_string(tan(value)));
                action = 6;
                flag = 1;
            }
            else if (v[i] == "ctg")
            {
                double value = trigon(i, v);
                PushFront(list, std::to_string(1 / tan(value)));
                action = 6;
                flag = 1;
            }
            else if (v[i] == "asin")
            {
                double value = trigon(i, v);
                PushFront(list, std::to_string(asin(value)));
                action = 6;
                flag = 1;
            }
            else if (v[i] == "acos")
            {
                double value = trigon(i, v);
                PushFront(list, std::to_string(acos(value)));
                action = 6;
                flag = 1;
            }
            else if (v[i] == "atg")
            {
                double value = trigon(i, v);
                PushFront(list, std::to_string(atan(value)));
                action = 6;
                flag = 1;
            }
            else if (v[i] == "actg")
            {
                double value = trigon(i, v);
                value = (3.14 / 2) - atan(value);
                PushFront(list, std::to_string(value));
                action = 6;
                flag = 1;
            }
            else if (v[i] == "sh")
            {
                double value = trigon(i, v);
                PushFront(list, std::to_string(sinh(value)));
                action = 6;
                flag = 1;
            }
            else if (v[i] == "ch")
            {
                double value = trigon(i, v);
                PushFront(list, std::to_string(cosh(value)));
                action = 6;
                flag = 1;
            }
            else if (v[i] == "th")
            {
                double value = trigon(i, v);
                PushFront(list, std::to_string(tanh(value)));
                action = 6;
                flag = 1;
            }
            else if (v[i] == "mod")
            {
                for (size_t j = 1; j < Size(station);)
                {
                    PushFront(list, PopFront(station));
                }
                double value = trigon(i, v);
                PushFront(list, "mod");
                PushFront(list, std::to_string(value));
                action = 7;
                flag2 = 1;
            }
            else {
                PushFront(list, v[i]);
                action = 0;
            }
        }
    }
    if (action != 7)
    {
        PushFront(list, PopFront(station));
    }
    if (flag && flag2)
    {
        action = 5;
        response.SetText("ERROR");
        response.SetTts("ERROR");
    }
    Destruct(station);
    return list;
}

double trigon(size_t& i, const std::vector<std::string>& v) // calculate result trigonometric function
{
    int count = 1;
    i = i + 2;
    std::vector<std::string> v1;
    v1.push_back("|");
    v1.push_back("(");
    while (count > 0)
    {
        v1.push_back(v[i]);
        if (v[i] == ")")
        {
            --count;
        }
        else if (v[i] == "(")
        {
            ++count;
        }
        ++i;
    }
    --i;
    v1.push_back("|");
    ForwardList subg;
    Construct(subg);
    subg = polsk(v1);
    PopFront(subg);
    Reverse(subg);
    double value = calc(subg);
    return value;
}

double calc(ForwardList& list) // calculate result
{
    ForwardList2 station;
    Construct(station);
    size_t sizelist = Size(list);
    for (size_t i = 0; i < sizelist; ++i)
    {
        std::string str = PopFront(list);
        if (str == "+")
        {
            double b = PopFront(station), a = PopFront(station);
            a = a + b;
            PushFront(station, a);
        }
        else if (str == "-") {
            double b = PopFront(station), a = PopFront(station);
            a = a - b;
            PushFront(station, a);
        }
        else if (str == "*") {
            double b = PopFront(station), a = PopFront(station);
            a = a * b;
            PushFront(station, a);
        }
        else if (str == "/") {
            double b = PopFront(station), a = PopFront(station);
            a = a / b;
            PushFront(station, a);
        }
        else if (str == "mod") {
            int a = (int)PopFront(station);
            str = PopFront(list);
            ++i;
            int b = (int)std::stoi(str);
            a = a % b;
            PushFront(station, a);
        }
        else {
            double a = Strtodouble(str);
            PushFront(station, a);
        }
    }
    double calc = PopFront(station);
    Destruct(station);
    return calc;
}

std::vector<std::string> split(const std::string& str) // splits string into individual elements
{
    std::string str1 = ' ' + str + ' ';
    std::vector<int> num;
    for (size_t i = 0; i < str1.size(); ++i)
    {
        if (str1[i] == ' ')
        {
            num.push_back(i);
        }
    }
    std::vector<std::string> value_;
    for (size_t i = 0; i < num.size() - 1; ++i)
    {
        if ((num[i + 1] - num[i] - 1) != 0)
        {
            value_.push_back(str1.substr(num[i] + 1,
                num[i + 1] - num[i] - 1));
        }
    }
    std::vector<std::string> value;
    value.push_back("|");
    for (size_t i = 0; i < value_.size(); ++i)
    {
        value_[i] = '+' + value_[i] + '+';
        std::vector<int> num1;
        for (size_t j = 0; j < value_[i].size(); ++j)
        {
            if ((value_[i][j] == '+') || (value_[i][j] == '-') ||
                (value_[i][j] == '*') || (value_[i][j] == '/') ||
                (value_[i][j] == '(') || (value_[i][j] == ')') ||
                (value_[i][j] == '|'))
            {
                num1.push_back(j);
            }
        }
        for (size_t j = 0; j < num1.size() - 1; ++j)
        {
            if ((num1[j + 1] - num1[j] - 1) != 0)
            {
                value.push_back(value_[i].substr(num1[j] + 1,
                    num1[j + 1] - num1[j] - 1));
            }
            if ((j + 1) != (num1.size() - 1))
            {
                value.push_back(value_[i].substr(num1[j + 1], 1));
            }
        }
    }
    return value;
}

double Strtodouble(const std::string str) // transformation string to double
{
    size_t i = 0;
    for (; (i < str.size()) && (str[i] != '.'); ++i) {}
    double a = 0;
    if (str[0] == '-')
    {
        a = std::stoi(str.substr(1, i));
        if (i != str.size())
        {
            a = a + std::stoi(str.substr(i + 1, str.size() - i - 1)) *
                pow(0.1, str.size() - i - 1);
        }
        a = -a;
    }
    else if (str[0] == '+')
    {
        a = std::stoi(str.substr(1, i));
        if (i != str.size())
        {
            a = a + std::stoi(str.substr(i + 1, str.size() - i - 1)) *
                pow(0.1, str.size() - i - 1);
        }
    }
    else {
        a = std::stoi(str);
        if (i != str.size())
        {
            a = a + std::stoi(str.substr(i + 1, str.size() - i - 1)) *
                pow(0.1, str.size() - i - 1);
        }
    }
    return a;
}

void Construct(ForwardList& list)
{
    list.Head = nullptr;
}

void Destruct(ForwardList& list)
{
    for (auto* i = list.Head; i != nullptr; i = list.Head)
    {
        list.Head = list.Head->Next;
        delete i;
    }
}

void PushFront(ForwardList& list, std::string value)
{
    ForwardList::Node* NNode = new ForwardList::Node();
    NNode->Data = value;
    NNode->Next = list.Head;
    list.Head = NNode;
}

std::string PopFront(ForwardList& list)
{
    if (list.Head != nullptr)
    {
        auto* i = list.Head;
        std::string a = i->Data;
        list.Head = list.Head->Next;
        delete i;
        return a;
    }
}

size_t Size(const ForwardList& list)
{
    size_t count = 0u;
    for (auto* i = list.Head; i != nullptr; i = i->Next)
    {
        ++count;
    }
    return count;
}

void Reverse(ForwardList& list)
{
    ForwardList::Node* copy = nullptr;
    while ((list.Head != nullptr) && (list.Head->Next != nullptr))
    {
        auto* g1 = list.Head->Next;
        list.Head->Next = copy;
        copy = list.Head;
        list.Head = g1;
    }
    list.Head->Next = copy;
}

void Construct(ForwardList2& list)
{
    list.Head = nullptr;
}

void Destruct(ForwardList2& list)
{
    for (auto* i = list.Head; i != nullptr; i = list.Head)
    {
        list.Head = list.Head->Next;
        delete i;
    }
}

void PushFront(ForwardList2& list, double value)
{
    ForwardList2::Node* NNode = new ForwardList2::Node();
    NNode->Data = value;
    NNode->Next = list.Head;
    list.Head = NNode;
}

double PopFront(ForwardList2& list)
{
    if (list.Head != nullptr)
    {
        auto* i = list.Head;
        double a = i->Data;
        list.Head = list.Head->Next;
        delete i;
        return a;
    }
}

size_t Size(const ForwardList2& list)
{
    size_t count = 0u;
    for (auto* i = list.Head; i != nullptr; i = i->Next)
    {
        ++count;
    }
    return count;
}

void MyCallback(const Alice::Request& request, Alice::Response& response)
{
    std::string answer;
    do
    {
        response.SetText("Enter your expression. For example: 3 * (5 + sin(5)) mod(4)\n");
        response.SetTts("Enter your expression.For example : 3 * (5 + sin(5)) mod(4)\n");
        std::vector<std::string> v = split(request.Command() + " |");
        ForwardList list;
        Construct(list);
        list = polsk(v);
        PopFront(list);
        Reverse(list);
        answer = " = " + std::to_string(calc(list)) + "\n";
        response.SetText(answer);
        response.SetTts(answer);
        Destruct(list);
        response.SetText("Calculate you still what any expression?\n");
        response.SetTts("Calculate you still what any expression?\n");
        answer = request.Command();
    } while (answer == "Yes");
    response.SetEndSession(true);
}

int main()
{
    Skill battleships;
    battleships.SetCallback(MyCallback);
    battleships.Run();
    return 0;
}