#include <iostream>
#include <vector>

using namespace std;

vector<int> heap;

void insert(int x)
{
    heap.push_back(x);
    int i = heap.size() - 1;
    int p = (i - 1) / 2;
    while ((i > 0) && (heap[p] < heap[i]))
    {
        swap(heap[i], heap[p]);
        i = (i - 1) / 2;
        p = (i - 1) / 2;
    }
}

int extract()
{
    int max = heap[0];

    heap[0] = heap[heap.size() - 1];
    heap.erase(heap.begin() + heap.size() - 1);

    int i = 0;
    while (2 * i + 1 < heap.size())
    {
        int j = 2 * i + 1;
        if (j + 1 < heap.size() && heap[j] < heap[j + 1])
            j++;
        if (heap[i] >= heap[j])
            break;
        swap(heap[i], heap[j]);
        i = j;
    }

    return max;
}

int main()
{
    int n;
    cin >> n;

    for (int i = 0; i < n; i++)
    {
        int k;
        cin >> k;
        if (k == 0)
        {
            int x;
            cin >> x;
            insert(x);
            continue;
        }
        cout << extract() << '\n';
    }

    return 0;
}