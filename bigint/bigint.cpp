#include "bigint.h"

bigint::bigint()
{
    num = "0";
}

bigint::bigint(int num)
{
    isminus = (num < 0);

    num = abs(num);

    while(num)
    {
        this->num.push_back((num % 10) + '0');
        num/=10;
    }

    if(this->num.empty()) this->num = "0";

    std::reverse(this->num.begin(), this->num.end());
}

bigint::bigint(ll num)
{
    isminus = (num < 0);

    num = abs(num);

    while(num)
    {
        this->num.push_back((num % 10) + '0');
        num/=10;
    }

    if(this->num.empty()) this->num = "0";

    std::reverse(this->num.begin(), this->num.end());
}

bigint::bigint(std::string num)
{
    if(num[0] == '-')
    {
        num.erase(0, 1);
        isminus = true;
    }

    while(num[0] == '0')
    {
        num.erase(0, 1);
    }

    for(size_t i = 0; i < num.size(); i++)
    {
        if('9' < num[i] || num[i] < '0') IsNotNumber;
    }

    this->num = (num.empty() ? "0" : num);
}

bigint::bigint(const char* num)
{
    std::string n = num;

    if(n[0] == '-')
    {
        n.erase(0, 1);
        isminus = true;
    }

    while(n[0] == '0')
    {
        n.erase(0, 1);
    }

    for(size_t i = 0; i < n.size(); i++)
    {
        if('9' < n[i] || n[i] < '0') IsNotNumber;
    }

    this->num = (n.empty() ? "0" : n);
}

bigint::bigint(const bigint& other)
{
    isminus = other.isminus;
    num = other.num;
}

bigint operator+(const bigint& num1, const bigint& num2)
{
    if(num1.isminus && num2.isminus)
    {
        return -((-num1) + (-num2));
    }
    if(num1.isminus && !num2.isminus)
    {
        return num2 - (-num1);
    }
    if(!num1.isminus && num2.isminus)
    {
        return num1 - (-num2);
    }

    int upper = 0;
    bigint result;
    std::string n1 = num1.num;
    std::string n2 = num2.num;

    result.num = "";

    std::reverse(n1.begin(), n1.end());
    std::reverse(n2.begin(), n2.end());

    for(size_t i = 0; i < (int)n1.length() || i < (int)n2.length(); i++)
    {
        int first  = ((i < n1.size())?n1[i]-'0':0);
        int second = ((i < n2.size())?n2[i]-'0':0);

        result.num.push_back((first + second + upper)%10 + '0');

        upper = (first + second + upper)/10;
    }

    if(upper) result.num.push_back('1');

    std::reverse(result.num.begin(), result.num.end());

    return result;
}

bigint operator-(const bigint& num1, const bigint& num2)
{
    if(!num1.isminus && num2.isminus)
    {
        return (num1 + (-num2));
    }
    if(num1.isminus && !num2.isminus)
    {
        return -((-num1) + num2);
    }
    if(num1.isminus && num2.isminus)
    {
        return ((-num2) - (-num1));
    }

    if(num1 < num2)
    {
        return -(num2 - num1);
    }

    bigint result;
    std::string n1 = num1.num;
    std::string n2 = num2.num;

    result.num = "";

    std::reverse(n1.begin(), n1.end());
    std::reverse(n2.begin(), n2.end());

    for(size_t i = 0; i < n1.size() || i < n2.size(); i++)
    {
        int first  = ((i < n1.size())?n1[i]-'0':0);
        int second = ((i < n2.size())?n2[i]-'0':0);

        if(first < second)
        {
            first+=10;
            n1[i + 1]--;
        }
        result.num.push_back(first - second + '0');
    }

    while(result.num.back() == '0') result.num.pop_back();

    std::reverse(result.num.begin(), result.num.end());

    if(result.num.empty()) result.num = "0";

    return result;
}

bigint operator*(const bigint& num1, const bigint& num2)
{
    bigint result;

    bool isminus_tmp = num1.isminus ^ num2.isminus;

    int m = std::max(num1.length(), num2.length())/2;

    bigint n1 = abs(num1);
    bigint n2 = abs(num2);

    if(m == 0)
    {
        int x = n1[0] - '0';
        int y = n2[0] - '0';

        result = (x * y);

        if(isminus_tmp) return -bigint(result);
        else return bigint(result);
    }

    std::string x1, x2, y1, y2;

    while(n1.length() > n2.length()) n2.num = "0" + n2.num;
    while(n1.length() < n2.length()) n1.num = "0" + n1.num;

    bigint high1(n1.num.substr(0, n1.length() - m));
    bigint high2(n2.num.substr(0, n2.length() - m));
    bigint low1(n1.num.substr(n1.length() - m));
    bigint low2(n2.num.substr(n2.length() - m));

    bigint z2 = high1 * high2;
    bigint z0 = low1 * low2;
    bigint z1 = ((high1 + low1) * (high2 + low2)) - z2 - z0;

    for(int i = 0; i < m; i++)
    {
        z2.num += "00";
        z1.num += "0";
    }

    result = z2 + z1 + z0;

    while(result.num[0] == '0') result.num.erase(0, 1);

    if(isminus_tmp) return -bigint(result);
    else return bigint(result);
}

bigint operator/(const bigint& num1, const bigint& num2)
{
    if(num2 == 0) throw "division by zero";
    if(abs(num1) < abs(num2)) return bigint(0);

    bigint result(0);

    bigint n1(num1);

    while(abs(n1) > abs(num2))
    {
        bool isminus_tmp = n1.isminus ^ num2.isminus;

        int first  = n1[0] - '0';
        int second = num2[0] - '0';
        size_t first_length  = n1.length();
        size_t second_length = num2.length();

        if(first < second)
        {
            first *= 10;
            first += (n1[1] - '0');
            first_length--;
        }

        bigint tmp(first / second);

        for(int i = second_length; i < first_length; i++) tmp.num += "0";

        if(isminus_tmp)
        {
            result -= tmp;
            n1 += tmp * num2;
        }
        else
        {
            result += tmp;
            n1 -= tmp * num2;
        }
    }

    if(n1 == 0) return result;

    while(n1.isminus && (n1.isminus ^ num1.isminus))
    {
        n1 += num2;
        result--;
    }

    while(!n1.isminus && (n1.isminus ^ num1.isminus))
    {
        n1 -= num2;
        result++;
    }

    return result;
}

bigint bigint::operator++(int)
{
    bigint tmp(*this);
    *this += 1;
    return tmp;
}

bigint& bigint::operator++()
{
    *this += 1;
    return *this;
}

bigint bigint::operator--(int)
{
    bigint tmp(*this);
    *this -= 1;
    return tmp;
}

bigint& bigint::operator--()
{
    *this -= 1;
    return *this;
}

bigint& bigint::operator=(const bigint& num)
{
    this->isminus = num.isminus;
    this->num = num.num;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const bigint& num)
{
    if(num.num == "0")
    {
        os << "0";
        return os;
    }

    if(num.isminus) os << '-';
    os << num.num;
    return os;
}

std::istream& operator>>(std::istream& is, bigint& num)
{
    std::string tmp;
    is >> tmp;
    num = tmp;
    return is;
}

bool bigint::operator==(const bigint& num) const
{
    if(this->num == "0" && num.num == "0") return true;
    return ((this->isminus == num.isminus) && (this->num == num.num));
}

bool bigint::operator!=(const bigint& num) const
{
    return !(*this == num);
}

bool bigint::operator<(const bigint& num) const
{
    if(*this == num) return false;
    if(this->isminus && !num.isminus) return true;  // 음수 < 양수
    if(!this->isminus && num.isminus) return false; // 양수 < 음수

    if(this->isminus) // 둘다 음수
    {
        if(this->length() < num.length()) return false;
        if(this->length() > num.length()) return true;

        for(int i = 0; i < num.length(); i++)
        {
            if(this->num[i] == num[i]) continue;
            if(this->num[i] < num[i])  return false;
            if(this->num[i] > num[i])  return true;
        }
        return false;
    }
    else
    {
        if(this->length() < num.length()) return true;
        if(this->length() > num.length()) return false;

        for(int i = 0; i < num.length(); i++)
        {
            if(this->num[i] == num[i]) continue;
            if(this->num[i] < num[i])  return true;
            if(this->num[i] > num[i])  return false;
        }
        return false;
    }
}

bool bigint::operator>(const bigint& num) const
{
    if(*this == num) return false;
    if(*this < num)  return false;
    return true;
}

bool bigint::operator<=(const bigint& num) const
{
    return (*this < num) || (*this == num);
}

bool bigint::operator>=(const bigint& num) const
{
    return (*this > num) || (*this == num);
}

const bigint bigint::operator-()
{
    bigint tmp = *this;
    tmp.isminus ^= 1;
    return tmp;
}

const bigint bigint::operator-() const
{
    bigint tmp = *this;
    tmp.isminus ^= 1;
    return tmp;
}

bigint abs(const bigint& num)
{
    bigint tmp = num;
    tmp.isminus = false;
    return tmp;
}

const char bigint::at(int index) const
{
    if(index < this->length() && 0 <= index)
        return num[index];
    throw "Index out of range";
}
