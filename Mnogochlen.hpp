#pragma once
#include <iostream>
#include <math.h>
#include "MnogochlenExceptions.hpp"
using namespace std;
#define M_PI (3.141592653589793)
#define M_2PI (2. * M_PI)

#include <list>

template <typename T>
struct Node
{
    long long MyOrder;
    T Value;
    Node *Next;
    Node(long long MyOrder = 0, T Value = 0, Node *Next = nullptr)
    {
        this->MyOrder = MyOrder;
        this->Value = Value;
        this->Next = Next;
    }
};

template <typename T>
class Mnogochlen
{
    list<Node<T>> Data;

    long long OrderOfMnogochlen;

    Mnogochlen Normalize() const;

    auto begin() { return Data.begin(); }

    auto end() { return Data.end(); }

public:

    static T Epsilon;

    auto cbegin() const { return Data.cbegin(); }

    auto cend() const { return Data.cend(); }

    auto crbegin() const { return Data.crbegin(); }

    auto crend() const { return Data.crend(); }

    long long GetOrderOfMnogochlen() const;

    //Node<T> *GetHead() const;

    Mnogochlen(long long Order);

    Mnogochlen(const Mnogochlen& Other) = default;

    ~Mnogochlen() = default;

    void Set(long long Order, T Coef)
    {
        if (Coef == T(0))
        {
            if (Data.empty())
            {
                OrderOfMnogochlen -= 1;
            }
            return;
        }

        for (auto elem : Data)
        {
            if (elem.MyOrder == Order)
            {
                elem.Value = Coef;
                return;
            }
        }

        for (auto elem = Data.begin(); elem!= Data.end(); elem++)
        {
            if ((*elem).MyOrder < Order)
            {
                Data.insert(elem, Node<T>(Order, Coef));
                return;
            }
        }

        Data.push_back(Node<T>(Order, Coef));
    }

    T operator[](long long Order) const;

    Mnogochlen operator+(const Mnogochlen &Other) const;

    Mnogochlen operator-(const Mnogochlen &Other) const;

    Mnogochlen operator*(T Val) const;

    bool operator==(const Mnogochlen &Other) const;

    bool operator!=(const Mnogochlen &Other) const;

    Mnogochlen& operator=(const Mnogochlen& Other) = default;

    void GetRoots() const;

    T CountValue(T x) const;

    list<Node<T>> GetData() const 
    { 
        const list<Node<T>>& link = Data;
        return link;
    }

    friend ostream& operator<<(ostream& os, const Mnogochlen<T>& Obj)
    {
        if (Obj.GetOrderOfMnogochlen() == -1)
        {
            cout << "Mnogochlen has no coefs" << endl;
        }
        for (auto node_el: Obj.Data)
        {
            os << node_el.Value << "*x^" << node_el.MyOrder;
            os << " + ";
        }
        os << '0';
        /*for (auto it = Obj.cbegin(); it != Obj.cend(); it++)
        {
            os << (*it).Value << "*x^" << (*it).MyOrder;
            if ((it++)!= Obj.cend())
                os << " + ";
        }*/
        return os;
    }
};

template <typename T>
T Mnogochlen<T>::Epsilon = T(0);

