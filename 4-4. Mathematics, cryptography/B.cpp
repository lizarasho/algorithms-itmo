#include <iostream>
#include <vector>

using namespace std;

const size_t N = 1000000;

vector<int> prime(N + 1, -1);

void fill_table()
{
    for (auto i = 2; i < prime.size(); i++) {
        if (prime[i] != -1) {
            continue;
        }
        for (auto j = i; j < prime.size(); j += i) {
            if (prime[j] == -1) {
                prime[j] = i;
            }
        }
    }
}

void print_dividers(int i)
{
    cout << prime[i] << ' ';
    if (i == prime[i]) return;
    print_dividers(i / prime[i]);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    fill_table();

    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int a;
        cin >> a;
        print_dividers(a);
        cout << '\n';
    }
    
    return 0;
}