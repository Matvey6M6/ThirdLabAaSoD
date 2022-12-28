#include "Mnogochlen.hpp"
#include <complex>

template <typename T>
inline bool operator>(const complex<T> a, const complex<T> b)
{
    return ((a.real() > b.real()) && (a.imag() > b.imag()));
}

template <typename T>
inline bool operator<(const complex<T> a, const complex<T> b)
{
    return ((a.real() < b.real()) && (a.imag() < b.imag()));
}

template <typename T>
inline bool operator<=(const complex<T> a, const complex<T> b)
{
    return ((a.real() <= b.real()) && (a.imag() <= b.imag()));
}

template <typename T>
inline bool operator>=(const complex<T> a, const complex<T> b)
{
    return ((a.real() >= b.real()) && (a.imag() >= b.imag()));
}

Mnogochlen<int> Mnogochlen<int>::Normalize() const
{
    Mnogochlen Newbie = *this;

    double Delitel = double((*this)[GetOrderOfMnogochlen()]);

    int i = GetOrderOfMnogochlen();

    cout << Newbie << endl;

    for (auto it = Newbie.begin(); it != Newbie.end(); it++)
    {
        //Newbie.Set(i, ((*this)[i] / Delitel));
        //cout << (double((*this)[i]) / Delitel) << endl;
        if (i == it->MyOrder) it->Value = (double((*this)[i]) / Delitel);
        i--;
    }

    //cout << Newbie << endl;

    return Newbie;
}

template <typename T>
Mnogochlen<T> Mnogochlen<T>::Normalize() const
{
    Mnogochlen Newbie = *this;

    T Delitel = T((*this)[GetOrderOfMnogochlen()]);

    int i = GetOrderOfMnogochlen();

    for (auto it = Newbie.cbegin(); it != Newbie.cend(); it++)
    {
        Newbie.Set(i, ((*this)[i] / Delitel));
        i--;
    }

    //cout << Newbie<<endl;

    return Newbie;
}

/*template <typename T>
Node<T>* Mnogochlen<T>::GetHead() const
{
    return Head;
}*/

template <typename T>
long long Mnogochlen<T>::GetOrderOfMnogochlen() const
{
    return OrderOfMnogochlen;
}

template <typename T>
Mnogochlen<T>::Mnogochlen(long long Order)
{
    if (Order >= 0 || Epsilon > T(0))
    {
        this->OrderOfMnogochlen = Order;
        this->Epsilon = Epsilon;
    }
    else
    {
        delete this;
        throw RangeError("Incorrect \"Order\" for polynomianl");
    }
}

/*template <typename T>
Mnogochlen<T>::Mnogochlen(const Mnogochlen &Other)
{
    OrderOfMnogochlen = Other.GetOrderOfMnogochlen();

    auto P = Other.cbegin();

    while (P != Other.cend())
    {
        Set(P->MyOrder, P->Value);
        P++;
    }
}*/

/*template <typename T>
Mnogochlen<T>::~Mnogochlen()
{
    while (Head->Next != nullptr)
    {
        Node<T> *tmp = Head;
        Head = Head->Next;
        delete tmp;
    }
}*/

template <typename T>
void Mnogochlen<T>::Set(long long Order, T Coef)
{
    if (Order > OrderOfMnogochlen || Order < 0)
    {
        throw RangeError("Out of mnogochlen's size.");
    }
       
    if (Coef == T(0))
    {
        if (Data.empty())
        {
            OrderOfMnogochlen -= 1;
        }
        else
        {
            for (auto elem = Data.begin(); elem != Data.end(); elem++)
            {
                if (elem->MyOrder == Order)
                {
                    Data.erase(elem);
                    return;
                }
            }
        }
        return;
    }

    for (auto elem = Data.begin(); elem != Data.end(); elem++)
    {
        if (elem->MyOrder == Order)
        {
            elem->Value = Coef;
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

template <typename T>
T Mnogochlen<T>::operator[](long long Order) const
{
    for (auto it = Data.cbegin(); it != Data.cend(); it++)
    {
        if ((*it).MyOrder == Order) return ((*it).Value);
    }
    return 0;
}

template <typename T>
Mnogochlen<T> Mnogochlen<T>::operator+(const Mnogochlen &Other) const
{
    long long Maximum = 0;

    this->GetOrderOfMnogochlen() < Other.GetOrderOfMnogochlen() ? Maximum = Other.GetOrderOfMnogochlen() : Maximum = this->GetOrderOfMnogochlen();

    Mnogochlen Result(Maximum);

    long long CurrentOrder = Maximum;

    while (CurrentOrder > -1)
    {
        Result.Set(CurrentOrder, ((*this)[CurrentOrder]) + (Other[CurrentOrder]));
        CurrentOrder--;
    }

    return Result;
}

template <typename T>
Mnogochlen<T> Mnogochlen<T>::operator-(const Mnogochlen &Other) const
{
    long long Maximum = 0;

    this->GetOrderOfMnogochlen() < Other.GetOrderOfMnogochlen() ? Maximum = Other.GetOrderOfMnogochlen() : Maximum = this->GetOrderOfMnogochlen();

    Mnogochlen Result(Maximum);

    long long CurrentOrder = Maximum;

    while (CurrentOrder > -1)
    {
        Result.Set(CurrentOrder, ((*this)[CurrentOrder]) - (Other[CurrentOrder]));
        CurrentOrder--;
    }

    return Result;
}

template <typename T>
Mnogochlen<T> Mnogochlen<T>::operator*(T Val) const
{
    auto it = Data.begin();

    Mnogochlen Result((*it).MyOrder);

    for(it; it!=Data.end();it++)
    {
        Result.Set((*it).MyOrder, (*it).Value * Val);
    }
    return Result;
}

template <typename T>
Mnogochlen<T> operator*(const T val, const Mnogochlen<T> &M) // обеспечивает коммутативность
{
    return M * val;
}

template <typename T>
bool Mnogochlen<T>::operator==(const Mnogochlen &Other) const
{
    cout << "Epsilon = " << Epsilon << endl;
    auto P1 = Data.cbegin();
    auto P2 = Data.cbegin();

    if (P1 != Data.cend() && P2 != Data.cend())
    {
        if (P1->MyOrder == P2->MyOrder)
        {
            while (P1 != Data.cend() && P2 != Data.cend())
            {
                if (T(abs(P1->Value - P2->Value)) < Epsilon)
                {
                    if (P1->MyOrder == P2->MyOrder && (++P1) == Data.cend() && (++P2) == Data.cend())
                        return true;
                }
                else
                    return false;
                P1++;
                P2++;
            }
        }
        else
            return false;
    }
    if (Data.empty() || Other.GetData().empty()) { return false; }
    return true;
}

template <typename T>
bool Mnogochlen<T>::operator!=(const Mnogochlen& Other) const
{
    cout << "Epsilon = " << Epsilon << endl;
    auto P1 = Data.cbegin();
    auto P2 = Data.cbegin();

    if (P1 != Data.cend() && P2 != Data.cend())
    {
        if (P1->MyOrder == P2->MyOrder)
        {
            while (P1 != Data.cend() && P2 != Data.cend())
            {
                if (T(abs(P1->Value - P2->Value)) > Epsilon)
                {
                    if (P1->MyOrder == P2->MyOrder && (++P1) == Data.cend() && (++P2) == Data.cend())
                        return true;
                }
                else
                    return false;
                P1++;
                P2++;
            }
        }
        else
            return true;
    }
    if (Data.empty() || Other.GetData().empty()) { return true; }
    return false;
}

void Mnogochlen<int>::GetRoots() const
{
    if (GetOrderOfMnogochlen() != 3)
    {
        throw RangeError("Order is not 3");
    }
    //Node* Pointer = GetHead();
    Mnogochlen Normalized = Normalize();
    cout << Normalized << endl;
    // cout << Normalized << endl;
    double a = Normalized[2];
    double b = Normalized[1];
    double c = Normalized[0];
    double x1;
    double x2;
    double x3;
    double q, r, r2, q3;
    q = (a * a - 3. * b) / 9.;
    r = (a * (2. * a * a - 9. * b) + 27. * c) / 54.;
    r2 = r * r;
    q3 = q * q * q;
    if (r2 < q3)
    {
        double t = acos(r / sqrt(q3));
        a /= 3.;
        q = -2. * sqrt(q);
        x1 = q * cos(t / 3.) - a;
        x2 = q * cos((t + M_2PI) / 3.) - a;
        x3 = q * cos((t - M_2PI) / 3.) - a;
        cout << "Root 1 = " << x1 << endl;
        cout << "Root 2 = " << x2 << endl;
        cout << "Root 3 = " << x3 << endl;
    }
    else
    {
        double aa, bb;
        if (r <= 0.)
            r = -r;
        aa = -pow(r + sqrt(r2 - q3), 1. / 3.);
        if (aa != 0.)
            bb = q / aa;
        else
            bb = 0.;
        a /= 3.;
        q = aa + bb;
        r = aa - bb;
        x1 = q - a;
        x2 = (-0.5) * q - a;
        x3 = (sqrt(3.) * 0.5) * fabs(r);
        if (x3 == 0.)
        {
            cout << "Root 1 = " << x1 << endl;
            cout << "Root 2 = " << x2 << endl;
        }
        cout << "Root 1 = " << x1 << endl;
    }
}

template <typename T>
void Mnogochlen<T>::GetRoots() const
{
    if (GetOrderOfMnogochlen() != 3)
    {
        throw RangeError("Order is not 3");
    }
    auto Pointer = Data.begin();

    Mnogochlen Normalized = Normalize();

    T a = Normalized[2];
    T b = Normalized[1];
    T c = Normalized[0];
    T x1;
    T x2;
    T x3;
    T q, r, r2, q3;
    q = (a * a - T(3) * b) / T(9);
    r = (a * (T(2) * a * a - T(9) * b) + T(27) * c) / T(54);
    r2 = r * r;
    q3 = q * q * q;
    if (r2 < q3)
    {
        T t = acos(r / sqrt(q3));
        a /= T(3.);
        q = T(-2.) * sqrt(q);
        x1 = q * cos(t / T(3.)) - a;
        x2 = q * cos((t + T(M_2PI)) / T(3.)) - a;
        x3 = q * cos((t - T(M_2PI)) / T(3.)) - a;
        cout << "Root 1 = " << x1 << endl;
        cout << "Root 2 = " << x2 << endl;
        cout << "Root 3 = " << x3 << endl;
    }
    else
    {
        T aa, bb;
        if (r <= T(0))
            r = -r;
        aa = -pow(r + sqrt(r2 - q3), T(1) / T(3));
        if (aa != T(0))
            bb = q / aa;
        else
            bb = T(0);
        a /= T(3);
        q = aa + bb;
        r = aa - bb;
        x1 = q - a;
        x2 = T(-0.5) * q - a;
        x3 = (sqrt(T(3)) * T(0.5)) * abs(r);
        if (x3 == T(0.))
        {
            cout << "Root 1 = " << x1 << endl;
            cout << "Root 2 = " << x2 << endl;
        }
        else
        {
            cout << "Root 1 = " << x1 << endl;
        }
    }
}

template <typename T>
T Mnogochlen<T>::CountValue(T x) const
{
    auto Pointer = Data.begin();
    T Ans = T(0);
    for (long long i = 0; i < GetOrderOfMnogochlen() + 1 && Pointer != Data.end(); i++)
    {
        Ans += Pointer->Value * pow(x, T(Pointer->MyOrder));
        Pointer++;
    }
    return Ans;
}

/*template struct Node<int>;
template struct Node<float>;
template struct Node<double>;
template struct Node<complex<float>>;
template struct Node<complex<double>>;*/

template class Mnogochlen<int>;
template class Mnogochlen<float>;
template class Mnogochlen<double>;
template class Mnogochlen<complex<float>>;
template class Mnogochlen<complex<double>>;