#include <string>
#include <algorithm>

using namespace std;

string operator+ (string a, string b)
{
    reverse(a.begin(), a.end());
    reverse(b.begin(), b.end());

    string result;
    int upper = 0;

    for(int i = 0; i < (int)a.size() || i < (int)b.size(); i++)
    {
        int first  = ((i < (int)a.size())?a[i]-'0':0);
        int second = ((i < (int)b.size())?b[i]-'0':0);

        result.push_back((first + second + upper)%10 + '0');
        
        upper = (first + second + upper)/10;
    }

    if(upper) result.push_back('1');

    reverse(result.begin(), result.end());

    return result;
}
