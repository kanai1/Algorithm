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

    size_t length() const { return num.size(); };

    friend bigint operator+(const bigint& num1, const bigint& num2);
    friend bigint operator-(const bigint& num1, const bigint& num2);
    // friend bigint operator*(const bigint& num1, const bigint& num2);
    // friend bigint operator/(const bigint& num1, const bigint& num2);

    bigint& operator=(const bigint& num);

    friend std::ostream& operator<<(std::ostream& os, const bigint& num);

    bool operator==(const bigint& num) const;
    bool operator<(const bigint& num) const;
    bool operator>(const bigint& num) const;

    const bigint operator-();
    const bigint operator-() const;

    friend bigint abs(const bigint& num);

private:

    const char operator[](int index) const { return num[index]; };
    const char at(int index) const;
};
