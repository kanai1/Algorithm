#include <vector>

using namespace std;

vector<int> arr(131073);
vector<int> segtree(262150);

int init(int start, int end, int index)
{
    if(start == end) return segtree[index] = arr[start];
    int mid = (start + end) / 2;
    int front = init(start, mid, index * 2);
    int back  = init(mid+1, end, index * 2 + 1);
    return segtree[index] = front + back;
}

int query(int start, int end, int s, int e, int index)
{
    if(start > e || end < s) return 0;
    if(start <= s && end >= e) return segtree[index];

    int mid = (s + e) / 2;

    int front = query(start, end, s, mid, index * 2);
    int back  = query(start, end, mid + 1, e, index * 2 + 1);

    return front + back;
}
