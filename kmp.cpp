#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<int> getPi(string& p)
{
    int n = (int)p.size(), j = 0;
    vector<int> pi(n, 0);

    for(int i = 1; i < n; i++)
    {
        while(j > 0 && p[i] != p[j])
            j = pi[j-1];
        if(p[i] == p[j])
            pi[i] = ++j;
    }
    return pi;
}

vector<int> kmp(string& s, string& p)
{
    vector<int> ans;
    auto pi = getPi(p);
    int n = (int)s.size(), m = (int)p.size(), j = 0;
    for(int i = 0; i < n; i++)
    {
        while(j > 0 && s[i] != p[j])
            j = pi[j-1];
        if(s[i] == p[j])
        {
            if(j == m-1)
            {
                ans.push_back(i - m + 1);
                j = pi[j];
            }
            else
            {
                j++;
            }
        }
    }
    return ans;
}

int main()
{
    string s, p;
    getline(cin, s); // 주어진 문자열
    getline(cin, p); // 부분문자열
    auto cnt = kmp(s, p);
    cout << (int)cnt.size() << "\n"; //부분문자열의 개수
    for(auto i : cnt) cout << i + 1 << " "; //부분문자열의 시작위치
    return 0;
}
