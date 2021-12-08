#include <string>
#include <algorithm>
#include <sstream>
#include <cmath>

#define IsNotNumber throw "Operand is not number"

typedef long long ll;

class bigint
{
private:

    std::string num;
    bool isminus = false;

public:
    bigint();
    bigint(int num);
    bigint(ll num);
    bigint(std::string num);
    bigint(const char* num);
    bigint(const bigint& other);

    friend bigint operator+(const bigint& num1, const bigint& num2);
    friend bigint operator-(const bigint& num1, const bigint& num2);
    friend bigint operator*(const bigint& num1, const bigint& num2);
    friend bigint operator/(const bigint& num1, const bigint& num2);
    friend bigint operator%(const bigint& num1, const bigint& num2);

    bigint operator++(int);
    bigint& operator++();
    bigint operator--(int);
    bigint& operator--();

    friend bigint operator+=(bigint& num1, const bigint& num2) { return num1 = num1 + num2; }
    friend bigint operator-=(bigint& num1, const bigint& num2) { return num1 = num1 - num2; }
    friend bigint operator*=(bigint& num1, const bigint& num2) { return num1 = num1 * num2; }
    friend bigint operator/=(bigint& num1, const bigint& num2) { return num1 = num1 / num2; }
    friend bigint operator%=(bigint& num1, const bigint& num2) { return num1 = num1 % num2; }



    bigint& operator=(const bigint& num);

    friend std::ostream& operator<<(std::ostream& os, const bigint& num);
    friend std::istream& operator>>(std::istream& is, bigint& num);

    bool operator==(const bigint& num) const;
    bool operator!=(const bigint& num) const;
    bool operator<(const bigint& num)  const;
    bool operator>(const bigint& num)  const;
    bool operator<=(const bigint& num)  const;
    bool operator>=(const bigint& num)  const;
    
    const bool isodd()  const { return num.back()&1; }
    const bool iseven() const { return !(num.back()&1); }

    const bigint operator-();
    const bigint operator-() const;

    friend bigint abs(const bigint& num);


private:

    size_t length() const { return num.size(); };
    const char operator[](int index) const { return num[index]; };
    const char at(int index) const;
};
