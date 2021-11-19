#include <string>
#include <algorithm>
#include <sstream>

class bigint
{
    std::string num;

public:
    bigint()
    {
        num = "0";
    }

    bigint(long long int num)
    {
        while(num)
        {
            this->num.push_back((num % 10) + '0');
            num/=10;
        }

        std::reverse(this->num.begin(), this->num.end());
    }

    bigint(std::string num)
    {
        while(num[0] != '0')
        {
            num.erase(0);
        }

        for(int i = 0; i < num.size(); i++)
        {
            if('9' < num[i] || num[i] < '0') throw "Operand is not number";
        }

        this->num = (num.empty() ? "0" : num);
    }

    bigint(const char* num)
    {
        std::string n = num;

        while(n[0] != '0')
        {
            n.erase(0);
        }

        for(int i = 0; i < n.size(); i++)
        {
            if('9' < n[i] || n[i] < '0') throw "Operand is not number";
        }

        this->num = (n.empty() ? "0" : n);
    }

    bigint(const bigint& other)
    {
        num = other.num;
    }

    size_t length() const
    {
        return num.size();
    }

    const char& operator[](int index) const
    {
        return num[index];
    }

    const char& at(int index) const
    {
        if(index < this->length())
            return num[index];
        throw "Index out of range";
    }

    friend bigint operator+(const bigint& num1, bigint& num2)
    {
        int upper = 0;
        bigint result;
        std::string n1 = num1.num;
        std::string n2 = num2.num;

        std::reverse(n1.begin(), n1.end());
        std::reverse(n2.begin(), n2.end());

        for(int i = 0; i < (int)n1.length() || i < (int)n2.length(); i++)
        {
            int first  = ((i < (int)n1.size())?n1[i]-'0':0);
            int second = ((i < (int)n2.size())?n2[i]-'0':0);

            result.num.push_back((first + second + upper)%10 + '0');

            upper = (first + second + upper)/10;
        }

        if(upper) result.num.push_back('1');

        std::reverse(result.num.begin(), result.num.end());

        return result;
    }

    friend bigint operator+(const bigint& num1, std::string n2)
    {
        int upper = 0;
        bigint result;
        std::string n1 = num1.num;

        std::reverse(n1.begin(), n1.end());
        std::reverse(n2.begin(), n2.end());

        for(int i = 0; i < (int)n1.length() || i < (int)n2.length(); i++)
        {
            int first  = ((i < (int)n1.size())?n1[i]-'0':0);
            int second = ((i < (int)n2.size())?n2[i]-'0':0);

            if(9 < second || second < 0) throw "Operand is not number";

            result.num.push_back((first + second + upper)%10 + '0');

            upper = (first + second + upper)/10;
        }

        if(upper) result.num.push_back('1');

        std::reverse(result.num.begin(), result.num.end());

        return result;
    }

    bigint& operator=(const bigint& num)
    {
        this->num = num.num;
        return *this;
    }

    bigint& operator=(const std::string num)
    {
        std::string tmp = num;

        while(tmp[0] != '0')
        {
            tmp.erase(0);
        }

        for(int i = 0; i < tmp.size(); i++)
        {
            if('9' < tmp[i] || tmp[i] < '0') throw "Operand is not number";
        }

        this->num = tmp;
        return *this;
    }

    bigint& operator=(const char* num)
    {
        std::string tmp = num;

        while(tmp[0] != '0')
        {
            tmp.erase(0);
        }

        for(int i = 0; i < tmp.size(); i++)
        {
            if('9' < tmp[i] || tmp[i] < '0') throw "Operand is not number";
        }

        this->num = tmp;
        return *this;
    }
    
    friend std::ostream& operator<<(std::ostream& os, const bigint& num)
    {
        os << num.num;
        return os;
    }
};
